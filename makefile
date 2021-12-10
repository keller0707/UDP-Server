udp_server.out: Server/udp_server.c udp_client.out
	gcc Server/udp_server.c -o udp_server.out
udp_client.out: Client/udp_client.c
	gcc Client/udp_client.c -o udp_client.out
clean:
	rm udp_server.out udp_client.out
run:
	./udp_server.out
