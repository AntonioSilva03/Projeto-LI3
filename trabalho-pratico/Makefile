CC = gcc

CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0`

LDFLAGS=`pkg-config --libs glib-2.0` -lm

programa-principal: src/main.o src/calculos.o src/data.o src/querys.o src/queryscheck.o 
	$(CC) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c

src/calculos.o: src/calculos.c

src/data.o: src/data.c

src/querys.o: src/querys.c

src/queryscheck.o: src/queryscheck.c

PASTA = Resultados
build_folder := $(shell mkdir -p $(PASTA))

clean:
	rm -f programa-principal  Resultados/*.txt src/*.o
	rmdir Resultados