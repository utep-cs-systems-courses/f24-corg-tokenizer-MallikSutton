CC =gcc
CFLAGS=-g -O3
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: tokenizer
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

tokenizer:$(OBJS)
	$(CC) -o tokenizer $(OBJS) $(CFLAGS)
clean:
	rm -f *.o  tokenizer
run:tokenizer
	./tokenizer
