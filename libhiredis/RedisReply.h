#ifndef __LIBHIREDIS_REDISREPLY_H__
#define __LIBHIREDIS_REDISREPLY_H__
#include "common_type.h"

class RedisReply
{
public:
    // 包含non-trivial数据的类，小心构造函数与operator=
	RedisReply(redisReply* pReply);
	~RedisReply();

    RedisReply(const RedisReply&) = delete;
    RedisReply& operator=(const RedisReply&) = delete;

    RedisReply(RedisReply&&);
    RedisReply& operator=(RedisReply&&);

public:
	int			AsInt() const;
	String      AsString() const;
	StringVec   AsArray() const;


private:
	redisReply* m_pReply;
};

#endif // !__LIBHIREDIS_REDISREPLY_H__
