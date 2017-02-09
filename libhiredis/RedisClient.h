#ifndef __LIBREDIS_REDISCLIENT_H__
#define __LIBREDIS_REDISCLIENT_H__
#include "common_type.h"

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
	int Connect(const String& host, int port, struct timeval timeout);

	void Close();

    bool Ping();
public:
	
    // connection
    RedisReply Auth(const String& passwd);
    RedisReply PingImpl();
    RedisReply Quit();
    RedisReply SelectDB(const String& index);

    // string operation

    RedisReply Set(const String& key, const String& val);
	RedisReply Get(const String& key);
    RedisReply GetSet(const String& key, const String& val);
    RedisReply Append(const String& key, const String& val);

    RedisReply SetNX(const String& key, const String& val);
    RedisReply PSetEx(const String& key, long timeout, const String& val);

    RedisReply Incr(const String& key);
    RedisReply IncrBy(const String& key, int val);
    
    // hash operation
    RedisReply HDel(const String& key, const String& field);
    RedisReply HExists(const String& key, const String& field);
    RedisReply HGet(const String& key, const String& field);
    RedisReply HGetAll(const String& key);
    RedisReply HIncrBy(const String& key, const String& field, const String& val);
    RedisReply HIncrByFloat(const String& key, const String& field, const String& val);
    RedisReply HKeys(const String& key);
    RedisReply HLen(const String& key);
    RedisReply HMGet(const String& key, const StringVec& vecField);
    RedisReply HMSet(const String& key, const StringVec& vecFieldValue);
    RedisReply HSet(const String& key, const String& field, const String& val);
    RedisReply HSetNx(const String& key, const String& field, const String& val);
    RedisReply HStrlen(const String& key, const String& field);
    RedisReply HVals(const String& key);
    RedisReply HScan();

    // keys operation
    
    // op
    RedisReply Sort(const String& identif);
    RedisReply Del(const String& key);
    RedisReply Contain(const String& key);

    // keys ttl
    RedisReply PExpire(const String& key, long timeout /* milliseconds */);
    RedisReply PExpireAt(const String& key, long timestamp /* milliseconds */);
    RedisReply Persist(const String& key);
    RedisReply PTTL(const String& key);

    // list operation
    RedisReply BLPop(const StringVec& param);
    RedisReply BRPop(const StringVec& param);
    RedisReply BRPopLPush(const String& src, const String& dest, const String& timeout);
    RedisReply LIndex(const String& key, const String& index);
    RedisReply LInsert(const StringVec& param);
    RedisReply LLen(const String& key);
    RedisReply LPop(const String& key);
    RedisReply LPush(const String& key, const String& val);
    RedisReply LPushX(const String& key, const String& val);
    RedisReply LRange(const String& key, const String& start, const String& stop);
    RedisReply LRem(const String& key, const String& count, const String& value);
    RedisReply LSet(const String& key, const String& index, const String& val);
    RedisReply LTRem(const String& key, const String& count, const String& value);
    RedisReply RPop(const String& key);
    RedisReply RPopLPush(const String& src, const String dest);
    RedisReply RPush(const String& key, const String& val);
    RedisReply RPushX(const String& key, const String& val);
    
    // script operation
    RedisReply Eval(const String& script, int numkeys, const StringVec& keys, const StringVec& args);
    RedisReply EvalSha(const String& sha1, int numkeys, const StringVec& keys, const StringVec& args);
    RedisReply ScriptDebug(const String& mode);
    RedisReply ScriptExists(const StringVec& sha1Vec);
    RedisReply ScriptFlush();
    RedisReply ScriptKill();
    RedisReply ScriptLoad(const String& script);

    // set operation
    RedisReply SAdd(const String& key, const String& member);
    RedisReply SCard(const String& key);
    RedisReply SDiff(const String& lhs, const String& rhs);
    RedisReply SDiffStore(const String& dest, const String& lhs, const String& rhs);
    RedisReply SInter(const String& lhs, const String& rhs);
    RedisReply SInterStore(const String& dest, const String& lhs, const String& rhs);
    RedisReply SIsMember(const String& key, const String& member);
    RedisReply SMembers(const String& key);
    RedisReply SMove(const String& src, const String& dest, const String& member);
    RedisReply SPop(const String& key);
    RedisReply SRandMember(const String& key, const String& count);
    RedisReply SRem(const String& key, const String& count);
    RedisReply SUnion(const String& lhs, const String& rhs);
    RedisReply SUnionStore(const String& dest, const String& lhs, const String& rhs);
    RedisReply SScan();

    // sorted set
    RedisReply ZAdd(const String& key, const String& member);
    RedisReply ZCard(const String& key);

    // transaction
    RedisReply Discard();
    RedisReply Exec();
    RedisReply Multi();
    RedisReply Unwatch();
    RedisReply Watch(const StringVec& keyVec);

private:
    String BuildCommand(String&& cmd, const StringVec& vecParam);
	RedisReply Send(String&& cmd, const StringVec& vecParam);

private:
	std::shared_ptr<redisContext>	m_spConn;
};

#endif // !__LIBREDIS_REDISCLIENT_H__
