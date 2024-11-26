text = input("Text: ")

sentence_count = 0
# counts the number of sentences, looking for how many times a dot, exclamation mark or a question mark has appeared
sentence_count = text.count(".") + text.count("!") + text.count("?")
if sentence_count == 0:  # if no ".", "!" or "?" at the end of sentence, then set the counter to 1
    sentence_count = 1

# creates a list called words and inserts each word of the text as different elements
words = text.split()
word_count = len(words)

# count letters, iterating through each symbol, looking if it is one of the letters of the alphabet
letter_count = 0
for symbol in text:
    if symbol.upper() in "QWERTYUIOPASDFGHJKLZXCVBNM":
        letter_count += 1

# the Coleman-Liau index
l = (letter_count / word_count) * 100
s = (sentence_count / word_count) * 100

grade = round(0.0588 * l - 0.296 * s - 15.8)

# print resultssubmit50 cs50/problems/2024/x/sentimental/readability
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
