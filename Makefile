all: hello
hello: hello.c
	gcc -Wall -Werror -o hello hello.c
clean:
	rm hello
run:
	./hello
