names = ["Carter", "David", "John"]

name = input("Name: ")

# in Python, for loops can have an else clause -> if you go through the entire loop without breaking out of it, then the else clause will be executed

# for n in names:
#     if n == name:
#         print("Found")
#         break
# else:
#     print("Not found")

if name in names:
    print("Found")
else:
    print("Not found")
