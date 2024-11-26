# people is a list of dictionaries
# people = [
#     {"name": "Carter", "number": "+1-617-495-100"},
#     {"name": "David", "number": "+1-617-495-100"},
#     {"name": "John", "number": "+1-949-468-2750"},
# ]

# name = input("Name: ")

# iterates through each dictionary from above
# for person in people:
#     if person["name"] == name:
#         print(f"Found {person['number']}")
#         break
# else:
#     print("Not found")


people = {
    "Carter": "+1-617-495-100",
    "David": "+1-617-495-100",
    "John": "+1-949-468-2750",
}

name = input("Name: ")

# looks for the name among the KEYS in the dictonary, if found, then print the associated number
if name in people:
    number = people[name]
    print(f"Found {number}")
else:
    print("Not found")
