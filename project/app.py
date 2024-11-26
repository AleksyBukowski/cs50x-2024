from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import timedelta

from helpers import apology, login_required

app = Flask(__name__)

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///ideasea.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


posts_per_page = 9

@app.route("/")
def index():
    return render_template("index.html", posts_per_page=posts_per_page)


@app.route('/get_posts', methods=['GET'])
def get_posts():
    page = int(request.args.get('page', 1))  # Default to page 1
    limit = int(request.args.get('limit', posts_per_page))  # Default posts per page
    offset = (page - 1) * limit

    # Fetch posts from the database
    posts = db.execute("SELECT * FROM posts ORDER BY created_at DESC LIMIT ? OFFSET ?", limit, offset)

    # Get the total number of posts
    total_posts = db.execute("SELECT COUNT(*) AS count FROM posts")[0]["count"]

    return jsonify({"posts": posts, "total": total_posts})


@app.route('/post/<int:post_id>')
def post_detail(post_id):
    post = db.execute("SELECT * FROM posts WHERE id = ?", post_id)
    if not post:
        return "Post not found", 404

    if post[0]["anonymous"] == 1:
        author = "Anonymous"
    else:
        u = db.execute("SELECT username FROM users WHERE id = ?", post[0]["user_id"])
        author = u[0]["username"]


    return render_template("post_detailed.html", post=post[0], author=author)


@app.route("/about")
def about():
    return render_template("about.html")


@app.route("/contact")
def contact():
    return render_template("contact.html")


@app.route("/login", methods=["GET", "POST"])
def login():

    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        remember = request.form.get("remember")
        if not username:
            return apology("must provide username", 403)
        elif not password:
            return apology("must provide password", 403)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 1 or not check_password_hash(rows[0]['hash'], password):
            return apology("invalid username and/or password", 403)

        session['user_id'] = rows[0]['id']
        session['username'] = rows[0]['username']

        if remember:
            session.permanent = True
            app.permanent_session_lifetime = timedelta(days=7)
        else:
            session.permanent = False

        return redirect("/")
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif password != request.form.get("confirmPassword"):
            return apology("passwords don't match", 400)

        usernames = db.execute("SELECT * FROM users WHERE username = ?", username)
        if usernames:
            return apology("username taken", 400)

        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        session['user_id'] = id
        session['username'] = username

        flash("Registered successfully")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/account")
@login_required
def account():
    return render_template("account.html")


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
            session['username'] = new_username
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


@app.route("/create", methods=["GET", "POST"])
@login_required
def create():
    if request.method == "POST":
        title = request.form.get("postTitle")
        text = request.form.get("postContent")
        anonymous = 1 if request.form.get("anonymous") == "on" else 0

        if not title:
            return apology("must provide title")
        elif not text:
            return apology("post cannot be empty")

        add = db.execute("INSERT INTO posts (title, text, user_id, anonymous, created_at) VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)", title, text, session["user_id"], anonymous)
        if not add:
            return apology("error adding post")


        flash(f"You have successfully posted!")
        return redirect("/")
    else:
        return render_template("create.html")



