CC         = gcc
CFLAGS     = -Werror -std=c11 -g
LIBS       = -lSDL2
OBJS       = main.o util/common.o
EXECUTABLE = hex-game

SRCS       = $(OBJS:.o=.c)


all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXECUTABLE)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

clean:
	find . -name '*.o' -type f -delete
	rm hex-game
