SRCS=./src/main.c ./src/list.c ./src/binary_tree.c

./bin/main: $(SRCS) ./bin
	gcc -Wall -Wextra $(SRCS) -o bin/main

./bin:
	mkdir ./bin

run: ./bin/main
	./bin/main ./files/input.txt

clean:
	rm ./bin/*