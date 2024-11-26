import csv

''' FIRST VERSION '''

# PRINTS EACH ROW, MAKING IT A LIST
# with open("favourites.csv") as file:
#     reader = csv.reader(file)
#     next(reader)
#     for row in reader:
#         favourite = row[1]  # <-- this is dangerous, considering that someone can move the column in the spreadsheet and make the row[1] column something different than the fav language
#         print(favourite)



''' SECOND VERSION '''

# PRINTS EACH ROW, MAKING IT A DICT
# def main():
#     with open("favourites.csv") as file:
#         reader = csv.DictReader(file)
#         python, c, scratch = 0, 0, 0
#         for row in reader:
#             if row["language"] == "Python":
#                 python += 1
#             elif row["language"] == "C":
#                 c += 1
#             elif row["language"] == "Scratch":
#                 scratch += 1
#     stats(python, scratch, c)


# def stats(python, scratch, c):
#     sum = python + scratch + c
#     # print(f"{python} people ({round((python / sum) * 100, 2)}%) have chosen Python as their favourite, {c} have chosen C ({round((c / sum) * 100, 2)}%), and {scratch} have chosen Scratch ({round((scratch / sum) * 100, 2)}%).")
#     print("----  Favourites:  ----")
#     print(f"Python: {python} people ({round((python / sum) * 100, 2)} %)")
#     print(f"C: {c} people ({round((c / sum) * 100, 2)} %)")
#     print(f"Scratch: {scratch} people ({round((scratch / sum) * 100, 2)} %)")
#     print("-----------------------")

# main()



''' THIRD VERSION '''

# CREATES A DICT CONTAINING THE LANGUAGES AND THEIR COUNT
# def main():
#     with open("favourites.csv") as file:
#         reader = csv.DictReader(file)
#         counts = {"sum": 0}

#         for row in reader:
#             favourite = row["language"]
#             counts["sum"] += 1
#             if favourite in counts:
#                 counts[favourite] += 1
#             else:
#                 counts[favourite] = 1

#     stats(counts)

# def stats(counts):
#     print("----  Favourites:  ----")

#     # for fav in sorted(counts):  # sorts alphabetically by key
#     for fav in sorted(counts, key=counts.get, reverse=True):  # sorts in descending order by values --> sorted(iterable, key=the_key, reverse=True/False)  <-- the_key should be a function (or other callable) that takes a single argument and returns a key to use for sorting purposes.
#         if fav == "sum":
#             continue
#         print(f"{fav}: {counts[fav]} people ({round((counts[fav] / counts["sum"]) * 100, 2)} %)")

#     print("-----------------------")

# main()



''' FOURTH VERSION '''

from collections import Counter

# CREATES A DICT CONTAINING THE LANGUAGES AND THEIR COUNT
def main():
    with open("favourites.csv") as file:
        reader = csv.DictReader(file)
        counts = Counter()  # initializes every single key and sets their value to 0 (because they're holding the count number of that key in there)
        counts["sum"] = 0

        # prompts for which column to analyse
        while True:
            analysed = input("Which column do you want to analyse? (language / problem): ")
            if analysed in ("language", "problem"):
                break

        # increments each languages counter (and the sum, too)
        for row in reader:
            favourite = row[analysed]  # <-- change "language" to "problem" to see the stats of favourite problems, instead of languages
            counts[favourite] += 1
            counts["sum"] += 1

    stats(counts)


def stats(counts):
    print("----  Favourites:  ----")

    # for fav in sorted(counts):  # sorts alphabetically by key
    # for fav in sorted(counts, key=counts.get, reverse=True):  # sorts in descending order by values --> sorted(iterable, key=the_key, reverse=True/False)  <-- the_key should be a function (or other callable) that takes a single argument and returns a key to use for sorting purposes.

    # most_common() is a function built into Counter, which returns a list of tuples with key-value pairs (e.g.: ('C', 7)), sorted by values, descending
    # so each iteration of this for loop returns a single key-value tuple
    for fav, count in counts.most_common():
        if fav == "sum":
            continue
        print(f"{fav}: {count} people ({round((count / counts["sum"]) * 100, 2)} %)")

    print("-----------------------")


    val = input("which values count do you want to see? ")
    if counts[val] != 1:
        print(f"{val}: {counts[val]} people have chosen this option")
    else:
        print(f"{val}: {counts[val]} person has chosen this option")

main()
