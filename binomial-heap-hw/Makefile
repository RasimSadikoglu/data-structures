SRCS=main.c node.c ../src/list.c ../src/binomial_heap.c

../bin/main: $(SRCS) ../bin
	gcc -Wall -Wextra $(SRCS) -o ../bin/main

../bin:
	mkdir ../bin

run: ../bin/main
	../bin/main

clean:
	rm ../bin/* ../*stackdump