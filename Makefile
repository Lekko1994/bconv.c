bconv: bconv.c
	gcc -Wall -Werror -std=c11 bconv.c -o bconv
clean:
	rm -f *.o
	rm bconv
