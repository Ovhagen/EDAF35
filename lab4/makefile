CC	= gcc
OUT	= lab4
OBJS	= main.o error.o instr_table.o
CFLAGS	= -g -m32
LDFLAGS	= -g -static -m32

all: $(OUT)
	./$(OUT) p0 > output
	diff output correct
	@echo PASS p0 test
	#(cd gzip;time ./gzip input.compressed 2 > output; diff output correct)
	#(cd gzip;time ../$(OUT) gzip input.compressed 2 > output; diff output correct)
	#@echo PASS gzip test
	#(cd twolf;time ./twolf test > output; diff output correct)
	#(cd twolf;time ../$(OUT) twolf test > output; diff output correct)
	#@echo PASS twolf test

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

clean:
	rm -rf $(OUT) $(OBJS)
