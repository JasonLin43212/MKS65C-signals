all: signal.o
	gcc signal.o

signal.o: signal.c
	gcc -c signal.c

run:
	./a.out

clear:
	echo "It is OK if it fails to remove the log.txt. Proceed to run"
	rm *.o
	rm *.out
	rm log.txt
