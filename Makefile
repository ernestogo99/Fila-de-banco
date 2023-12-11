all: main

main: fila_fifo.o logtree.o escalonador.o caixa.o main.o
	gcc -o main fila_fifo.o logtree.o escalonador.o caixa.o main.o

fila_fifo.o: fila_fifo.c fila_fifo.h
	gcc -c fila_fifo.c

logtree.o: logtree.c logtree.h
	gcc -c logtree.c

escalonador.o: escalonador.c escalonador.h fila_fifo.h
	gcc -c escalonador.c

caixa.o: caixa.c caixa.h
	gcc -c caixa.c

main.o: main.c fila_fifo.h logtree.h escalonador.h
	gcc -c main.c

clean:
	rm -f main *.o