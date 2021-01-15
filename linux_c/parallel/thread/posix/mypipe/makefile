CFLAGS+=-pthread
LDFLAGS+=-pthread

all:test

test:main.o mypipe.o pipeopen.o
	gcc $^ -o $@ $(CFLAGS) $(LDFLAGS)
clean:
	rm -rf *.o test
