client:
	gcc client.c -o client -Wall

server:
	gcc server.c -o server -Wall

rm:
	rm server
	rm client