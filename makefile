all: fclean
	@gcc -Wall -Wextra -Werror microshell/*.c -o microshell/microshell.a
	@ulimit -n 30 ; python3 tester/main.py

clean:
	@rm -rf microshell/*.o

fclean: clean
	@rm -rf microshell/*.a

env:
	pip3 install termcolor

log:
	@cat logs/correct.txt
	@cat logs/error.txt
	@cat logs/verify.txt
