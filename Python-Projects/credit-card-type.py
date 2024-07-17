# write a program that prompts the user for a credit card number and then 
# reports (via print) whether it is a valid American Express, MasterCard,
# or Visa card number,

from cs50 import get_int

# Getting the card number from the user
number = str(get_int("Number: "))

# Determining the length of the number
length = len(number)

# Calculating the checksum using Luhn's algorithm
checksum = 0
for i in range(length):
    # Initializing the string from end
    digit = int(number[length - 1 - i])

    # Simply adding the last digit onwards
    if i % 2 == 0:
        checksum += digit

    # Doubling the last second digits onwards
    else:
        doubled = digit * 2
        checksum += doubled // 10 + doubled % 10

# Checking if checksum is valid
if checksum % 10 != 0:
    card = "INVALID"

else:
    # Determining if card is AMEX
    if length==15 and (number[0:2] in ['34','37']):
        card = "AMEX"

    # Determining if card is MASTERCARD
    elif length==16 and (number[0:2] in ['51','52','53','54','55']):
        card = "MASTERCARD"

    # Determining if card is VISA
    elif (length==13 or length==16) and number[0]=='4':
        card = "VISA"

    # INVALID if none
    else:
        card = "INVALID"

print(card)

