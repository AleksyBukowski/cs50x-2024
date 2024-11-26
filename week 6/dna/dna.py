import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py <database csv file> <DNA sequence txt file>")
        return 1

    # Read database file into a variable
    database = []
    with open(sys.argv[1]) as dbfile:
        reader = csv.DictReader(dbfile)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as txtfile:
        dna = txtfile.read()

    # Find longest match of each STR in DNA sequence
    sequence_counts = dict()
    for key in database[0].keys():
        if key == "name":
            continue
        sequence_counts[key] = longest_match(dna, key)

    # Check database for matching profiles
    # iterate through each person who has his "counts" of specific STRs (database is a list of dicts!)
    for person in database:
        matches = True  # set the "matches" bool to True by default, check if anything doesn't match and then set it to false
        for str in sequence_counts.keys():  # iterate through each STR by using each key from sequence_count (sequence_counts is a dict!)
            # if the persons count of the CURRENTLY CONSIDERED STR is not equal to the count of that STR (counted from the txt file)
            if int(person[str]) != sequence_counts[str]:
                matches = False  # then it doesn't match
                break  # and break
        if matches == True:  # if it didn't break after looping through EACH STR, then they all match, therefore that person matches
            print(person["name"])  # print out that person and return 0
            return 0
    print("No match")  # say "No match" and return when no matches found
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
