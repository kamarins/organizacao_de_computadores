all: main.o instrucao.o memoria.o
	g++ main.o instrucao.o memoria.o -o exec -Wall

instrucao.o: instrucao.cpp
	g++ -o instrucao.o -c instrucao.cpp 

memoria.o: memoria.cpp
	g++ -o memoria.o -c memoria.cpp

main.o: main.cpp
	g++ -o main.o -c main.cpp
	
clean:
	rm -f *.o exec

run:
	./exec 