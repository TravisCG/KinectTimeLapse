CC=gcc
CFLAGS=-Wall -W -pedantic
CLIBS=-lfreenect -lfreenect_sync -L/usr/lib/i386-linux-gnu

ktl: main.o params.o timelapse.o
	$(CC) *.o $(CLIBS) -o ktl
main.o: main.c params.h timelapse.h
	$(CC) $(CFLAGS) main.c -c
params.o: params.c params.h
	$(CC) $(CFLAGS) params.c -c
timelapse.o: timelapse.c timelapse.h params.h
	$(CC) $(CFLAGS) timelapse.c -c
clean:
	rm *.o ktl core*
