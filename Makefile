CC=gcc
CFLAGS=-c -Wall -Wextra

LDFLAGS=

SRCS=Comporators.c Erase.c FGetLine.c FunctionsExecution.c InputFunctions.c Insert.c InsertInSortedArray.c KGetLine.c main.c MainCircle.c MenuClass.c OutputFunctions.c MenuCreation.c Sorts.c StartSession.c Timing.c

OBJS=$(SRCS:.c=.o)

EXE=app

all: $(SRCS) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	rm -rf $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(EXE)
