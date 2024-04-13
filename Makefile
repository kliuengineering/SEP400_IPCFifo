CC=g++
CFLAGS=-I.
CFLAGS=-Wall
FILES1=FifoA.cpp
FILES2=FifoB.cpp

fifoa: $(FILES1)
	$(CC) $(CFLAGS) $^ -o $@

fifob: $(FILES2)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o fifoa fifob

all: fifoa fifob