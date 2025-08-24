TARGETS=main

.PHONY: all clear

all: $(TARGETS)

clean:
	$(RM) $(TARGETS) *.o

main: main.c list.c list.h
	$(CC) -std=c23 main.c list.c -O3 -o main

