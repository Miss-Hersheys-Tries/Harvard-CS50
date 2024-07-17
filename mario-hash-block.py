# Writig a Mario program to create blocks of hashes of height input from users

# Asking user for the height
height = int(input("Height: "))

# Looping while heigth falls under the range
while (height<1 or height >8):
    height = int(input("Height: "))

# Printing the table
for i in range(height):
    spaces = " "*(height - i -1)
    hashes = "#"*(i + 1)
    print(spaces+hashes+"  "+hashes)

