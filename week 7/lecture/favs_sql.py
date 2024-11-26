from cs50 import SQL

db = SQL("sqlite:///favourites.db")

favourite = input("Favourite problem: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favourites WHERE problem = ?", favourite)

row = rows[0]
print(row["n"])
