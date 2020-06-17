CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: function

function: function.c
	$(CC) $(CFLAGS) -o function function.c

clean veryclean:
	$(RM) function