#ifndef __LIBHIREDIS_REDISREPLY_H__
#define __LIBHIREDIS_REDISREPLY_H__
#include "../libhiredis/src/hiredis.h"
#include <vector>

class RedisReply
{
public:
	RedisReply(redisReply* pReply);
	~RedisReply();

public:
	int			GetInt() const;
	std::string GetString() const;
	std::vector<std::string> GetArray() const;


private:
	redisReply* m_pReply;
};

#endif // !__LIBHIREDIS_REDISREPLY_H__
