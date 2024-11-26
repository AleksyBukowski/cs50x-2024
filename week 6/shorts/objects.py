#!/usr/bin/env python3
# shebang allowing us to run the program with ./objects.py (only after we changed the permissions with chmod a+x objects.py)
# it has to be on the top of the file, otherwise it won't work!

# creates a class called Student
class Student():

    # that is the constructor - the initalization function; we define 2 properties: name and id
    # we use self to let the class know that the name is the name of that specific object we are considering
    def __init__(self, name, id):
        self.name = name
        self.id = id

    # takes 2 arguments (self, which is always here, and id that we want to assign)
    def changeID(self, id):
        self.id = id

    # doesn't take any arguments, just prints (we still have to mention self)
    def print(self):
        print(f"{self.name} - {self.id}")


# we define a new variable (object) called jane and assign the name and the id
jane = Student("Jane", 10)
jane.print()  # we use the print function created inside of class Student
jane.changeID(12)  # and the changeID function etc
jane.print()

mark = Student("Mark", 15)
mark.print()
