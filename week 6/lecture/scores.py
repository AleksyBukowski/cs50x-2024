from cs50 import get_int

# scores = [72, 73, 33]
scores = []

n = get_int("Count: ")

for _ in range(n):
    # scores.append(get_int("Score: "))
    score = get_int("Score: ")
    scores = scores + [score]

average = sum(scores) / len(scores)

print(f"Average: {average}")
