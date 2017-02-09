#include "RedisClient.h"
#include "RedisReply.h"
#include <cassert>

RedisClient::RedisClient()
{
}

RedisClient::~RedisClient()
{
}

int RedisClient::Connect(const String & host, int port, timeval timeout)
{
	redisContext* p = redisConnectWithTimeout(host.data(), port, timeout);
	assert(nullptr != p);
    m_spConn.reset(p, destruct_redis_context);
	return 0;
}

void RedisClient::Close()
{
    m_spConn.reset();
}

bool RedisClient::Ping()
{
    RedisReply reply = Send("PING", StringVec());
    return "PONG" == reply.AsString();
}

RedisReply RedisClient::Set(const String & key, const String & val)
{
	std::vector<String> vec{ key, val };
	return Send("SET", vec);
}

RedisReply RedisClient::Get(const String & key)
{
	std::vector<String> vec{ key };
	return Send("GET", vec);
}

String RedisClient::BuildCommand(String && cmd, const StringVec& vecParam)
{
    return String();
}

RedisReply RedisClient::Send(String && cmd, const StringVec& vecParam)
{
	for (auto& item : vecParam)
		cmd += " " + item;
	return RedisReply(static_cast<redisReply*>(redisCommand(m_spConn.get(), cmd.data())));
}
