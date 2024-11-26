from cs50 import get_int
from math import floor

while True:
    number = input("Number: ")
    if int(number) >= 0:
        break

every_2nd_reversed = number[-2::-2]
print(every_2nd_reversed)
sum_every_2nd = 0

for digit in every_2nd_reversed:
    times_two = int(digit[0]) * 2
    sum_every_2nd += times_two % 10
    if times_two >= 10:
        sum_every_2nd += floor(times_two/10)


every_1st_ones = number[-1::-2]
sum_1st_ones = 0

for digit in every_1st_ones:
    sum_1st_ones += int(digit)

sum_total = sum_every_2nd + sum_1st_ones

if sum_total % 10 != 0:
    print("INVALID")
elif int(number[:2]) in (34, 37) and len(number) == 15:
    print("AMEX")
elif int(number[:2]) in range(51, 55+1) and len(number) == 16:
    print("MASTERCARD")
elif int(number[:1]) == 4 and len(number) in (16, 13):
    print("VISA")
else:
    print("INVALID")
