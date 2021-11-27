./bin/main: ./src/main.c ./src/tree.c ./src/binary_tree.c ./bin
	gcc -Wall -Wextra src/binary_tree.c ./src/tree.c src/main.c -o bin/main

./bin:
	mkdir ./bin

run: ./bin/main
	./bin/main ./files/input.txt

clean:
	rm ./bin/*