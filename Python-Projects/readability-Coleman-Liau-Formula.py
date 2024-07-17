# A program that first asks the user to type in some text, and then outputs
#  the grade level for the text, according to the Coleman-Liau formula

from cs50 import get_string

text = get_string("Text: ")

# Initializing letters, words, sentences
letters = 0
words = 1
sentences = 0

# Looping to find the number of letters, words & texts
for i in text:
    if i.isalpha():
        letters += 1
    if i == " ":
        words += 1
    if i in [".", "!", "?"]:
        sentences += 1

# Determining the Coleman-Liau index
L = letters/(words)*100
S = sentences/(words)*100
index = round((0.0588*L)-(0.296*S)-15.8)

#Printing the required output
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade", index)


