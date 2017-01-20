gcc: server.c network.c client.c
	gcc -o server server.c network.c
	gcc -o client client.c network.c
clear:
	rm *~
