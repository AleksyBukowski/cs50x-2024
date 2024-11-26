import csv

books = []

# add books to shelf by reading books.csv
with open("books.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        books.append(row)

# print books
for book in books:
    print(f'{book["author"]} wrote "{book["title"]}"')
