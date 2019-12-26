control: control.c control.h
	gcc -o control.c

write: write.c control.h
	gcc -o write.c

clean:
	rm *.o
	rm control
	rm write
