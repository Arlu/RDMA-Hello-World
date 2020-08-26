LDFLAGS = -libverbs

all: client server

client: client.c setup_ib.c helper.c
	$(CC) $^ ${LDFLAGS} -o $@

server: server.c setup_ib.c helper.c
	$(CC) $^ ${LDFLAGS} -o $@

clean:
	rm client
	rm server
