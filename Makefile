CC = clang
CFLAGS = -pedantic -pedantic-errors -Wall -Werror -Wextra
LDFLAGS = -lm
SOURCES = main.c
STYLE = Google

all: main reformat run

run:
	./main

reformat:
	clang-format -i --style=$(STYLE) $(SOURCES)

main: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(SOURCES) -o main

.PHONY = run all reformat
