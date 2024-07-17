#  implement a program that identifies to whom a sequence of DNA belongs.

import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Command-Line Argument Error")
        sys.exit(1)

    # Read database file into a variable
    db = []
    with open(sys.argv[1]) as db_file:
        db_reader = csv.DictReader(db_file)
        for row in db_reader:
            db.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sq_file:
        sq = sq_file.read()

    # Find longest match of each STR in DNA sequence
        # Getting the first row's keys from csv file
    str_keys = list(db[0].keys())[1:]
 
        # Looping to find number of each key
    str_counts = {}
    for key in str_keys:
        str_counts[key] = longest_match(sq, key)

    # Check database for matching profiles
    for person in db:
        match = True
        for key in str_keys:
            if int(person[key]) != str_counts[key]:
                match = False
                break
        if match:
            print(person["name"])
            return

    print("No match")
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
