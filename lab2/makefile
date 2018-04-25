CC		= gcc

CFLAGS		= -g -Wall -pedantic

LDFLAGS		= -g

OUT		= machine

OBJS		= machine.o

main: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OUT)
	./machine

clean:
	rm -f *.o sh core out
