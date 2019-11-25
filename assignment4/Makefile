all:
	gcc -o client client.c -lseccomp
	gcc -o server server.c -lseccomp
	gcc -o server2 server2.c -lseccomp

client: client.c
	gcc -o client client.c -lseccomp
server: server.c
	gcc -o server server.c -lseccomp
server2: server2.c
	gcc -o server2 server2.c -leccomp

clean:
	rm client server server2
