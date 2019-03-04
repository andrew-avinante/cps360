all: my-cat my-grep my-zip my-unzip

my-cat: my-cat.o
	gcc -o my-cat my-cat.o

my-cat.o: my-cat.c
	gcc -c my-cat.c

my-grep: my-grep.o
	gcc -o my-grep my-grep.o

my-grep.o: my-grep.c
	gcc -c my-grep.c

my-zip: my-zip.o
	gcc -o my-zip my-zip.o

my-zip.o: my-zip.c
	gcc -c my-zip.c

my-unzip: my-unzip.o
	gcc -o my-unzip my-unzip.o

my-unzip.o: my-unzip.c
	gcc -c my-unzip.c

clean:
	rm *.o