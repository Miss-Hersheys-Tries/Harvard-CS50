# write a program that asks the user how much change is owed 
# and then spits out the minimum number of coins with which said
#  change can be made.

from cs50 import get_float

# Get a float input from user
change = get_float("Change: ")

# Make sure change is positive
while change < 0:
    change = get_float("Change: ")

# Counting the coins from 0
coins = 0

# Creating a list of types of change
coin_type = [0.25, 0.10, 0.05, 0.01]

# Looping through each type of change
for coin in coin_type:
    # Adding the number of coins
    coins += int(change//coin)
    # Updating the value of change left
    change = round(change%coin, 2)

print(coins)
