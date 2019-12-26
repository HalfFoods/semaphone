control: control.c
	gcc -o control.c

write: write.c
	gcc -o write.c

clean:
	rm *.o
	rm control
	rm write
