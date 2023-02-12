BUILD_FLAGS:=-Iinclude -I../include -std=gnu2x
OPT_FLAGS:=-Ofast
ERROR_FLAGS:=-Wall -Werror -Wextra \
	-Wconversion -Wcast-align -Wunused -Wpointer-arith -Wcast-qual \
	-Wno-missing-braces -Wshadow #-Wold-style-cast -Wpedantic
MACROS:=

DEPS:=node
OBJS:=main node list binomial_heap
DIRS:=bin obj
BIN:=bin/main

_DEPS:=$(patsubst %, include/%.h, $(DEPS))
_OBJS:=$(patsubst %, obj/%.o, $(OBJS))

$(BIN): $(DIRS) $(_OBJS)
	$(CC) $(_OBJS) -o $@

obj/%.o: src/%.c $(_DEPS)
	$(CC) $(CFLAGS) $(BUILD_FLAGS) $(OPT_FLAGS) $(ERROR_FLAGS) $(MACROS) -c $< -o $@

obj/%.o: ../src/%.c $(_DEPS)
	$(CC) $(CFLAGS) $(BUILD_FLAGS) $(OPT_FLAGS) $(ERROR_FLAGS) $(MACROS) -c $< -o $@

run: bin/main
	bin/main

debug: bin/main
	gdb bin/main

valgrind: bin/main
	valgrind --leak-check=full --show-leak-kinds=all bin/main

$(DIRS):
	mkdir $@

.PHONY: clean
clean:
	rm -rf ${DIRS} .vscode