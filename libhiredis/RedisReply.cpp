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

int RedisReply::GetInt() const
{
	return m_pReply->integer;
}

std::string RedisReply::GetString() const
{
	return m_pReply->str;
}

std::vector<std::string> RedisReply::GetArray() const
{
	std::vector<std::string> vecReply;
	for (size_t i = 0; i < m_pReply->elements; i++)
	{
		vecReply.push_back(m_pReply->element[i]->str);
	}

	return vecReply;
}
