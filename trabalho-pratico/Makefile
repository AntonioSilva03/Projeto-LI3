CC = gcc

CFLAGS=-Wall -O3 -Iinclude `pkg-config --cflags glib-2.0`

LDFLAGS=`pkg-config --libs glib-2.0` -lm

programa-principal: src/main.o src/calculos.o src/querys.o src/queryscheck.o src/getdriverdata.o src/getridedata.o src/getuserdata.o src/parsedrivers.o src/parserides.o src/parseusers.o src/estatisticas.o src/hashing.o
	$(CC) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c

src/calculos.o: src/calculos.c

src/querys.o: src/querys.c

src/queryscheck.o: src/queryscheck.c

src/getdriverdata.o : src/getdriverdata.c

src/getridedata.o : src/getridedata.c

src/getuserdata.o : src/getuserdata.c

src/parsedrivers.o : src/parsedrivers.c

src/parserides.o : src/parserides.c

src/parseusers.o : src/parseusers.c

src/estatisticas.o : src/estatisticas.c

src/hashing.o : src/hashing.c

PASTA = Resultados
build_folder := $(shell mkdir -p $(PASTA))

clean:
	rm -f programa-principal  Resultados/*.txt src/*.o
	rmdir Resultados