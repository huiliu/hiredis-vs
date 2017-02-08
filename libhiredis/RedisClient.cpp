#include "RedisClient.h"
#include "RedisReply.h"
#include <cassert>

RedisClient::RedisClient()
	: m_pConn(nullptr)
{
}

RedisClient::~RedisClient()
{
	if (nullptr != m_pConn)
	{
		redisFree(m_pConn);
	}
}

int RedisClient::Connect(const std::string & host, int port, timeval timeout)
{
	m_pConn = redisConnectWithTimeout(host.data(), port, timeout);
	assert(nullptr != m_pConn);
	return 0;
}

void RedisClient::Close()
{
	if (nullptr != m_pConn)
	{
		redisFree(m_pConn);
	}
}

RedisReply RedisClient::Set(const std::string & key, const std::string & val)
{
	std::vector<std::string> vec{ key, val };
	return Send("SET", vec);
}

RedisReply RedisClient::Get(const std::string & key)
{
	std::vector<std::string> vec{ key };
	return Send("GET", vec);
}

RedisReply RedisClient::Send(std::string && cmd, const std::vector<std::string>& vecParam)
{
	for (auto& item : vecParam)
		cmd += " " + item;
	return RedisReply(static_cast<redisReply*>(redisCommand(m_pConn, cmd.data())));
}
