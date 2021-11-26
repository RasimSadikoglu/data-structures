./bin/main: ./src/main.c ./src/binary_tree.c
	gcc src/binary_tree.c src/main.c -o bin/main

run: ./bin/main
	./bin/main ./files/input.txt

clean:
	rm ./bin/*