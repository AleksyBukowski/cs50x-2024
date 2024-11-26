from cs50 import SQL
from flask import Flask, render_template, request, redirect
import functools

app = Flask(__name__)

# REGISTRANTS = {}

db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/deregister", methods=["POST"])
def deregister():

    # Forget registrant
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/register", methods=["POST"])
def register():

    # validate name
    name = request.form.get("name")
    if not name:
        return render_template("failure.html", message="Missing name")

    # validate sport
    sports = request.form.getlist("sport")
    if not sports:
        return render_template("failure.html", message="Missing sport")

    for s in sports:
        if s not in SPORTS:
            return render_template("failure.html", message="Invalid sport")

    # remember registrant

    # REGISTRANTS[name] = tuple(sport)

    # using reduce function, a list of sports is turned into a single string
    sport = functools.reduce(lambda x, y : x + ", " + y, sports)
    
    # using the questionmark placeholders to avoid SQL injection
    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

    # confirm registration
    return redirect("/registrants")


@app.route("/registrants")
def registrants():
    # db.execute returns a list of dictionaries, with keys being the SQL column names
    # (in this example: id, name, sport)
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("success.html", registrants=registrants)
