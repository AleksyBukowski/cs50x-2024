# creates a list called books
books = []

# asks for the ammount of books to add and calls the functions later


def main():
    while True:
        try:
            n = int(input("How many books do you wish to add? "))
            break
        except ValueError:
            pass

    # calls add_books and print_books
    add_books(n)
    print_books()
    do_nothing()


# adds books to the list
def add_books(n):
    for i in range(n):
        books.append({"title": input(f"Book {i+1} title: "),
                      "author": input(f"Book {i+1} author: ")})


# prints books
def print_books():
    for element in books:
        print(f'{element["author"]} - "{element["title"]}"')


# does nothing lol (using the ... symbol essentialy does nothing - it's called a ellipsis)
# https://realpython.com/python-ellipsis/
def do_nothing():
    ...


# calls main in order to run the program
main()

# dictionary.keys()  <-- prints out all of the keys of a dict
