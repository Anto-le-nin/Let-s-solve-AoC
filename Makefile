CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all:
	$(CC) $(CFLAGS) day_1/day_1.c -o day_1/Day1
	$(CC) $(CFLAGS) day_2/day_2.c -o day_2/Day2
	$(CC) $(CFLAGS) day_3/day_3.c -o day_3/Day3
	$(CC) $(CFLAGS) day_4/day_4.c -o day_4/Day4


day1:
	@cd day_1 && ./Day1

day2:
	@cd day_2 && ./Day2

day3:
	@cd day_3 && ./Day3

day4:
	@cd day_4 && ./Day4

clean:
	@rm -f day_*/Day*

