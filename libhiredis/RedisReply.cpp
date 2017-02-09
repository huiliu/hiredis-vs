#include "RedisReply.h"

RedisReply::RedisReply(redisReply * pReply)
	: m_pReply(pReply)
{
}

RedisReply::~RedisReply()
{
	if (nullptr != m_pReply)
	{
		freeReplyObject(m_pReply);
	}
}

RedisReply::RedisReply(RedisReply && rhs)
{
    freeReplyObject(m_pReply);
    m_pReply = rhs.m_pReply;
    rhs.m_pReply = nullptr;
}

RedisReply& RedisReply::operator=(RedisReply && rhs)
{
    freeReplyObject(m_pReply);
    m_pReply = rhs.m_pReply;
    rhs.m_pReply = nullptr;

    return *this;
}

int RedisReply::AsInt() const
{
	return m_pReply->integer;
}

std::string RedisReply::AsString() const
{
	return m_pReply->str;
}

std::vector<std::string> RedisReply::AsArray() const
{
	std::vector<std::string> vecReply;
	for (size_t i = 0; i < m_pReply->elements; i++)
	{
		vecReply.push_back(m_pReply->element[i]->str);
	}

	return vecReply;
}
