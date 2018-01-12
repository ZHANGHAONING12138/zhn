all:edge.c server_and.c server_or.c client.c
	gcc edge.c -o edge.o
	gcc server_and.c -o server_and.o
	gcc server_or.c -o server_or.o
	gcc client.c -o client
server_and:server_and.o
	./server_and.o
server_or:server_or.o
	./server_or.o
edge:edge.o
	./edge.o