from flask import Flask, redirect, render_template, request


app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():
    q = request.args.get("q")
    #
    #
    shows = q
    #
    #
    #
    return render_template("search.html", shows=shows)
