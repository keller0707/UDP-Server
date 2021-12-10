udp_server.out: udp_server.c udp_client.out
	gcc udp_server.c -o udp_server.out
udp_client.out: udp_client.c
	gcc udp_client.c -o udp_client.out
clean:
	rm udp_server.out udp_client.out
run:
	./udp_server.out
