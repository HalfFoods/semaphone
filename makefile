all: control.o write.o
	gcc -o program control.o write.o

control.o: control.c
	gcc -c control.c

write.o: write.c
	gcc -c write.c

run:
	./program

clean:
	rm *.o
	rm program
