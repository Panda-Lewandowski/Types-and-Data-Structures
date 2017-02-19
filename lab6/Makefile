CC := gcc

CFLAGS := -std=c99 -Wall -ggdb 

main.exe : main.o tree.o functions.h
	$(CC) -o $@ $^
	
%.o : %.c *.h
	$(CC) $(CFLAGS) -c $< -gdwarf-3
	
clean :
	rm *o *.exe