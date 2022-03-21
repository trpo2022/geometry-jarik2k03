all: geom
hello: geom.c
	gcc -Wall -Werror -o geom geom.c
clean:
	rm geom
run:
	./geom
