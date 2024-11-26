from flask import Flask, render_template, request

# __name__ = special variable that defines the current's file name
app = Flask(__name__)

# defines the route for that application - it implies that whenever someone visits / then function index() should be called
@app.route("/", methods=["GET", "POST"])
def index():
    # if the requested method is POST, meaning a form has been submitted, then get name and return greet.html, sending name through to the placeholder
    if request.method == "POST":
        name = request.form.get("name")
        return render_template("greet.html", name=name)
    # else, display default index page
    return render_template("index.html")



# methods=["POST"] makes the POST method supported - you can also include both. (default: "GET")
# @app.route("/greet", methods=["POST"])
# def greet():
#     # tries to get the value of a key "name" and returns it. If such key doesn't exist, it returns "world". Works with GET form method.
#     # request.args.get("name") would return "None" as default (if "name" doesn't exist) - if there's no 2nd argument (such as "world" in this example).
#     # request.form.get("name") works the same way, but with POST method
#     name = request.form.get("name", "world")
#     # 1st name is the placeholder in index.html, 2nd name means the variable specified in this file - so the value of placeholder name.
#     return render_template("greet.html", name=name)

