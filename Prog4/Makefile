proj: ut_threads.o test.c
	gcc -fsanitize=address -g -oprog -fno-omit-frame-pointer -std=c99 -fno-stack-protector ut_threads.o test.c

ut_threads.o: ut_threads.c ut_threads.h
	gcc -fsanitize=address -g -c -fno-omit-frame-pointer -std=c99 -fno-stack-protector ut_threads.c
	
test: prog
	./prog

clean:
	rm *.o