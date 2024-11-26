import os, re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Check if a string represents a number (integer or float)
def is_number(s):
    return bool(re.match(r'^[-+]?(\d*\.?\d+)$', s))

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_holdings = db.execute("SELECT * FROM user_holdings WHERE user_id = ?", session["user_id"])
    cash_q = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    if cash_q is None:
        return apology("error: could not load balance", 500)

    cash = cash_q[0]["cash"]
    total = cash

    for holding in user_holdings:
        if lookup(holding["stock_symbol"]):
            holding["current_price"] = lookup(holding["stock_symbol"])["price"]
        else:
            return apology("error: could not load stocks", 500)
        holding["total"] = round(holding["current_price"] * holding["quantity"], 2)
        total += holding["total"]

    username = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["username"]

    return render_template("index.html", user_holdings=user_holdings, cash=cash, total=total, username=username)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # get the variables through GET method for dynamic price calculation
    symbol = request.args.get("symbol")
    shares_string = request.args.get("shares")

    # POST method and validation, if user submits the buy
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_string = request.form.get("shares")
        if not symbol:
            return apology("must provide stock symbol", 400)
        elif not shares_string:
            return apology("must provide amount to buy", 400)
        elif not is_number(shares_string):
            return apology("invalid shares quantity", 400)
        ############################ CS50 SPECIFIC ###################################
        # elif not shares_string.isnumeric():
        #     return apology("invalid shares quantity", 400)
        ##############################################################################

        shares = float(shares_string)
        if shares <= 0:
            return apology("invalid shares quantity", 400)

        quote = lookup(symbol)
        if not quote:
            return apology("invalid stock symbol", 404)

        price_total = round(shares * quote["price"], 2)
        user_balance = float((db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"]))[0]["cash"])

        if price_total > user_balance:
            return apology("insufficient balance")
        else:
            # if balance is sufficient, execute the queries (return apology if anything goes wrong)
            exe1 = db.execute("INSERT INTO transactions (user_id, type, stock_symbol, quantity, price_per_share) VALUES (?, ?, ?, ?, ?)", session["user_id"], 'buy', quote["symbol"], shares, quote["price"])
            if exe1 is None or exe1 <= 0:
                return apology("transaction unsuccessful", 500)

            exe2 = db.execute("INSERT INTO user_holdings (user_id, stock_symbol, quantity) VALUES(?, ?, ?) ON CONFLICT(user_id, stock_symbol) DO UPDATE SET quantity=quantity + excluded.quantity", session["user_id"], quote["symbol"], shares)
            if exe2 is None or exe2 <= 0:
                return apology("transaction unsuccessful", 500)

            exe3 = db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", price_total, session["user_id"])
            if exe3 is None or exe3 <= 0:
                return apology("transaction unsuccessful", 500)

            # if no errors encountered, flash a success
            current_balance = (db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"]))[0]["cash"]
            if shares < 1:
                flash(f"You have successfully bought {shares_string} of a share of {quote['symbol']} for ${price_total} total. Current balance: ${round(current_balance, 2)}")
            elif shares == 1:
                flash(f"You have successfully bought 1 share of {quote['symbol']} for ${price_total} total. Current balance: ${round(current_balance, 2)}")
            else:
                flash(f"You have successfully bought {shares_string} shares of {quote['symbol']} for ${price_total} total. Current balance: ${round(current_balance, 2)}")

            # redirect to main page
            return redirect("/")
    # else if the method is GET (user is viewing the page)
    else:
        # if there are no values typed in ever (the paged just loaded) - render the page itself
        if symbol is None and shares_string is None:
            return render_template("buy.html")
        # else if the value in symbol or shares is empty (but was typed in before) return empty string so that nothing shows up on the dynamic price
        elif "" in {symbol, shares_string}:
            return ""
        # else if both the symbol and shares inputs are filled, dynamically render the price of the stock the user is planning to buy
        else:
            # if quote doesn't exist or the shares input is invalid, return empty string
            quote = lookup(symbol)
            if not quote or not is_number(shares_string):
                return ""

            shares = float(shares_string)
            if shares <= 0:
                return ""

            # if no errors encountered, render price dynamically
            cash_q = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            if cash_q is None:
                return apology("error querying balance", 500)

            balance = cash_q[0]["cash"]
            price_total = round(shares * quote["price"], 2)

            if price_total > balance:
                exceeds = True
            else:
                exceeds = False

            return render_template("buy_price.html", quote=quote, shares=shares_string, price_total=price_total, exceeds=exceeds)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY date DESC", session["user_id"])
    for event in history:
        event["total"] = round(event["quantity"] * event["price_per_share"], 2)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    ######################################### MY VERSION #######################################################
    # get the stock symbol provided by user
    symbol = request.args.get("symbol")

    # if the symbol is of type None (the user has not yet inputted anything) then render default page
    if symbol is None:
        return render_template("quote.html")
    # else = the user provided anything already
    else:
        # check for price (if symbol exists)
        quote = lookup(symbol)

        # return quote (symbol and price)
        return render_template("quoted.html", quote=quote)
    ############################################################################################################


    ############################ CS50 SPECIFIC ###################################
    # if request.method == "POST":
    #     symbol = request.form.get("symbol")

    #     if symbol is None or lookup(symbol) is None:
    #         return apology("invalid stock symbol", 400)
    #     else:
    #         return render_template("quote.html", quote=lookup(symbol))

    # else:
    #     return render_template("quote.html")
    ##############################################################################



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Ensure passwords match
        if not password == request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        # Ensure that no such username already exists
        usernames = db.execute("SELECT * FROM users WHERE username = ?", username)
        if usernames:
            return apology("username taken", 400)

        # Register the user
        id = db.execute("INSERT INTO USERS (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        session["user_id"] = id

        flash("Registered successfully")
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # get the variables through GET method for dynamic price calculation
    symbol = request.args.get("symbol")
    shares_string = request.args.get("shares")

    # POST method and validation, if user submits the buy
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_string = request.form.get("shares")
        if not symbol:
            return apology("must provide stock symbol", 400)
        elif not shares_string:
            return apology("must provide amount to sell", 400)
        elif not is_number(shares_string):
            return apology("invalid shares quantity", 400)

        shares = float(shares_string)
        if shares <= 0:
            return apology("invalid shares quantity", 400)

        quote = lookup(symbol)
        if not quote:
            return apology("invalid stock symbol", 400)

        shares_owned = db.execute("SELECT * FROM user_holdings WHERE user_id = ? AND stock_symbol = ?", session["user_id"], quote["symbol"])[0]["quantity"]

        if shares > shares_owned:
            return apology("you don't own the amount of shares provided", 400)

        # if no errors encountered, execute the queries (return apology if anything goes wrong)
        exe1 = db.execute("INSERT INTO transactions (user_id, type, stock_symbol, quantity, price_per_share) VALUES (?, ?, ?, ?, ?)", session["user_id"], 'sell', quote["symbol"], shares, quote["price"])
        if exe1 is None or exe1 <= 0:
            return apology("transaction unsuccessful", 500)

        # different queries to execute = if user sells all shares of stock, remove the entire row in db, if user sells just a fraction - update row
        if shares == shares_owned:
            exe2 = db.execute("DELETE FROM user_holdings WHERE user_id = ? AND stock_symbol = ?", session["user_id"], quote["symbol"])
            if exe2 is None or exe1 <= 0:
                return apology("transaction unsuccessful", 500)
        elif shares < shares_owned:
            exe2 = db.execute("UPDATE user_holdings SET quantity = quantity - ? WHERE user_id = ? AND stock_symbol = ?", shares, session["user_id"], quote["symbol"])
            if exe2 is None or exe1 <= 0:
                return apology("transaction unsuccessful", 500)

        price_total = round(shares * quote["price"], 2)
        exe3 = db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", price_total, session["user_id"])
        if exe3 is None or exe3 <= 0:
            return apology("transaction unsuccessful", 500)

        # if no errors encountered, flash a success
        current_balance = (db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"]))[0]["cash"]
        if shares < 1:
            flash(f"You have successfully sold {shares_string} of a share of {quote['symbol']} for ${price_total} total. Current balance: ${round(current_balance, 2)}")
        elif shares == 1:
            flash(f"You have successfully sold 1 share of {quote['symbol']} for ${price_total} total. Current balance: ${round(current_balance, 2)}")
        else:
            flash(f"You have successfully sold {shares_string} shares of {quote['symbol']} for ${price_total} total. Current balance: ${round(current_balance, 2)}")

        # redirect to main page
        return redirect("/")
    # else if the method is GET (user is viewing the page)
    else:
        # if there are no values typed in ever (the paged just loaded) - render the page itself
        if symbol is None and shares_string is None:
            stocks = db.execute("SELECT * FROM user_holdings WHERE user_id = ?", session["user_id"])
            return render_template("sell.html", stocks=stocks)
        # else if the value in symbol or shares is empty (but was typed in before) return empty string so that nothing shows up on the dynamic price
        elif "" in {symbol, shares_string}:
            return ""
        # else if both the symbol and shares inputs are filled, dynamically render the price of the stock the user is planning to sell
        else:
            # if quote doesn't exist or the shares input is invalid, return empty string
            quote = lookup(symbol)
            if not quote or not is_number(shares_string):
                return ""

            shares = float(shares_string)
            if shares <= 0:
                return ""

            # if no errors encountered, render price dynamically
            price_total = round(shares * quote["price"], 2)
            shares_owned = round(db.execute("SELECT * FROM user_holdings WHERE user_id = ? AND stock_symbol = ?", session["user_id"], quote["symbol"])[0]["quantity"], 2)
            if shares > shares_owned:
                exceeds = True
            else:
                exceeds = False
            return render_template("sell_price.html", quote=quote, shares=shares_string, price_total=price_total, shares_owned=shares_owned, exceeds=exceeds)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Allow the user to deposit cash"""
    if request.method == "POST":
        # check for validity
        cash = request.form.get("cash")
        if not cash or not is_number(cash) or float(cash) <= 0:
            return apology("invalid deposit amount", 400)

        # execute query, return apology if query doesn't execute right
        exe = db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash, session["user_id"])
        if exe is None or exe <= 0:
            return apology("error adding cash", 500)

        # no errors encountered
        sqli
        return redirect("/")
    else:
        return render_template("deposit.html")


@app.route("/settings")
@login_required
def settings():
    """Settings page"""
    return render_template("settings.html")


@app.route("/change_password", methods=["POST"])
@login_required
def change_password():
    """Change password"""
    old_password = request.form.get("old_password")
    new_password = request.form.get("new_password")
    new_password_retype = request.form.get("new_password_retype")

    if "" in {old_password, new_password, new_password_retype}:
        return apology("must fill all blank areas", 400)

    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    if not check_password_hash(rows[0]["hash"], old_password):
        return apology("wrong old password provided", 403)
    elif new_password != new_password_retype:
        return apology("passwords do not match", 400)
    else:
        db.execute("UPDATE users SET hash = ?", generate_password_hash(new_password))
        flash("Password updated")
        return redirect("/")


@app.route("/change_username", methods=["GET", "POST"])
@login_required
def change_username():
    """Change username"""
    u = request.args.get("u")
    if request.method == "POST":
        new_username = request.form.get("new_username")
        password = request.form.get("password")

        if "" in {new_username, password}:
            return apology("must fill all blank areas", 400)

        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        username_q = db.execute("SELECT * FROM users WHERE username = ?", new_username)

        if not check_password_hash(rows[0]["hash"], password):
            return apology("wrong password", 403)
        elif username_q:
            return apology("username taken", 400)
        else:
            db.execute("UPDATE users SET username = ? WHERE id = ?", new_username, session["user_id"])
            flash("Username updated")
            return redirect("/")
    else:
        if u == "":
            return ""
        else:
            username_q = db.execute("SELECT * FROM users WHERE username = ?", u)
            if username_q:
                return '<p class="fw-semibold text-danger">Username taken</p>'
            else:
                return ""


@app.route("/quicksell", methods=["POST"])
@login_required
def quicksell():
    """Allow user to quicksell his shares directly from /index"""
    stock_symbol = request.form.get("symbol")
    symbol = lookup(stock_symbol)
    if not stock_symbol or not symbol:
        return apology("invalid stock symbol", 400)

    q = db.execute("SELECT * FROM user_holdings WHERE user_id = ? AND stock_symbol = ?", session["user_id"], symbol["symbol"])
    if q is None:
        return apology("shares of stock not owned", 400)

    q = q[0]

    cash_added = round(q["quantity"] * symbol["price"], 2)

    current_balance = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    exe1 = db.execute("DELETE FROM user_holdings WHERE user_id = ? AND stock_symbol = ?", session["user_id"], symbol["symbol"])
    if exe1 is None or exe1 <= 0:
        return apology("transaction unsuccessful", 500)

    exe2 = db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash_added, session["user_id"])
    if exe2 is None or exe2 <= 0:
        return apology("transaction unsuccessful", 500)


    if q["quantity"] < 1:
        flash(f"Quick sold {round(q["quantity"], 2)} of a share of {symbol["symbol"]} for ${cash_added}. Current balance: ${round(current_balance, 2)}")
    elif q["quantity"] == 1:
        flash(f"Quick sold 1 share of {symbol["symbol"]} for ${cash_added}. Current balance: ${round(current_balance, 2)}")
    else:
        flash(f"Quick sold {round(q["quantity"], 2)} shares of {symbol["symbol"]} for ${cash_added}. Current balance: ${round(current_balance, 2)}")

    return redirect("/")
