//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include "../libhiredis/src/hiredis.h"
#include "../libhiredis/RedisClient.h"
#include "../libhiredis/RedisReply.h"
#include "../libhiredis/RedisCommand.h"
#include "../libhiredis/RedisClientManager.h"
#include <iostream>
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

void winsock_init()
{
	//----------------------
	// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("WSAStartup failed: %d\n", iResult);
	}
}

void winsock_fini()
{
	WSACleanup();
}

void case01(const char* host, int port)
{
    unsigned int j;
    redisContext *c;
    redisReply *reply;

	c = redisConnect(host, port);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* PING server */
    reply = (redisReply*)redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key */
    reply = (redisReply*)redisCommand(c,"SET %s %s", "foo", "hello world");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key using binary safe API */
    reply = (redisReply*)redisCommand(c,"SET %b %b", "bar", (size_t) 3, "hello", (size_t) 5);
    printf("SET (binary API): %s\n", reply->str);
    freeReplyObject(reply);

    /* Try a GET and two INCR */
    reply = (redisReply*)redisCommand(c,"GET foo");
    printf("GET foo: %s\n", reply->str);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);
    /* again ... */
    reply = (redisReply*)redisCommand(c,"INCR counter");
    printf("INCR counter: %lld\n", reply->integer);
    freeReplyObject(reply);

    /* Create a list of numbers, from 0 to 9 */
    reply = (redisReply*)redisCommand(c,"DEL mylist");
    freeReplyObject(reply);
    for (j = 0; j < 10; j++) {
        char buf[64];

        snprintf(buf,64,"%u",j);
        reply = (redisReply*)redisCommand(c,"LPUSH mylist element-%s", buf);
        freeReplyObject(reply);
    }

    /* Let's check what we have inside the list */
    reply = (redisReply*)redisCommand(c,"LRANGE mylist 0 -1");
    if (reply->type == REDIS_REPLY_ARRAY) {
        for (j = 0; j < reply->elements; j++) {
            printf("%u) %s\n", j, reply->element[j]->str);
        }
    }
    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);

}

void case02(const char* host, int port, struct timeval tv)
{
    RedisClientManager ClientMgr;
	RedisReply  reply(nullptr);

    ConnectNo client = ClientMgr.CreateClient(host, port, 1000);
    std::cout << "ping : " << ClientMgr.FindClient(client)->Ping() << std::endl;
	reply = ClientMgr.FindClient(client)->Get("name");
	std::cout << reply.AsString() << std::endl;
}

int main(int argc, char **argv) {
	const char *hostname = (argc > 1) ? argv[1] : "192.168.0.105";
    // const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds

	winsock_init();
	case01(hostname, port);
	case02(hostname, port, timeout);
	winsock_fini();
    return 0;
}
