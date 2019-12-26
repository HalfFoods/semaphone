all: control.c write.c control.h
	gcc -o write control.c
	gcc -o write write.c
	
clean:
	rm *.o
	rm control
	rm write
