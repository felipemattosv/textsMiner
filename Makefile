all: full

%.o: %.c %.h
	gcc -c $< -o $@

libtads.a: tads/documento.o tads/indices.o tads/palavra.o tads/info.o
	ar -crs libtads.a tads/documento.o tads/indices.o tads/palavra.o tads/info.o

full: indexador.c main.c libtads.a
	@gcc -L. indexador.c -o indexador  -I tads -ltads  -lm
	@gcc -L. main.c -o main  -I tads -ltads  -lm

clean:
	@rm -f main libtads tads.a tads/*.o *.o
prog1:
	@./indexador datasets/tiny/train.txt indice.bin
prog2:
	@./main indice.bin 10