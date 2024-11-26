import sys

# if more or less than 2 command line arguments, then exit
if len(sys.argv) != 2:
    print("Missing comand line arguments")
    sys.exit(1) # you don't have to exit with 1, but if we exit with 0 if successful, then we can exit with 1 indicating an error herexcd

print(f"hello, {sys.argv[1]}")
sys.exit(0)
