#ifndef __LIBREDIS_REDISCLIENT_H__
#define __LIBREDIS_REDISCLIENT_H__
#include "../libhiredis/src/hiredis.h"
#include <string>
#include <vector>

class RedisReply;

class RedisClient
{
public:
	RedisClient();
	~RedisClient();

	RedisClient(const RedisClient&) = delete;
	RedisClient(RedisClient&&) = delete;
	RedisClient operator=(const RedisClient&) = delete;
	RedisClient operator=(RedisClient&&) = delete;

public:
	int Connect(const std::string& host, int port, struct timeval timeout);

	void Close();

public:
	RedisReply Set(const std::string& key, const std::string& val);
	RedisReply Get(const std::string& key);

private:
	RedisReply Send(std::string&& cmd, const std::vector<std::string>& vecParam);

private:
	redisContext*	m_pConn;
};

#endif // !__LIBREDIS_REDISCLIENT_H__
