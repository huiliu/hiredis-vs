#ifndef __LIBREDIS_REDISCLIENT_H__
#define __LIBREDIS_REDISCLIENT_H__
#include "../libhiredis/src/hiredis.h"
#include <string>
#include <vector>

class RedisReply;

typedef std::vector<std::string>    StringVec;

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

    bool Ping();
public:
	
    // connection
    RedisReply Auth(const std::string& passwd);
    RedisReply PingImpl();
    RedisReply Quit();
    RedisReply SelectDB(const std::string& index);

    // string operation

    RedisReply Set(const std::string& key, const std::string& val);
	RedisReply Get(const std::string& key);
    RedisReply GetSet(const std::string& key, const std::string& val);
    RedisReply Append(const std::string& key, const std::string& val);

    RedisReply SetNX(const std::string& key, const std::string& val);
    RedisReply PSetEx(const std::string& key, long timeout, const std::string& val);

    RedisReply Incr(const std::string& key);
    RedisReply IncrBy(const std::string& key, int val);
    
    // hash operation
    RedisReply HDel(const std::string& key, const std::string& field);
    RedisReply HExists(const std::string& key, const std::string& field);
    RedisReply HGet(const std::string& key, const std::string& field);
    RedisReply HGetAll(const std::string& key);
    RedisReply HIncrBy(const std::string& key, const std::string& field, const std::string& val);
    RedisReply HIncrByFloat(const std::string& key, const std::string& field, const std::string& val);
    RedisReply HKeys(const std::string& key);
    RedisReply HLen(const std::string& key);
    RedisReply HMGet(const std::string& key, const StringVec& vecField);
    RedisReply HMSet(const std::string& key, const StringVec& vecFieldValue);
    RedisReply HSet(const std::string& key, const std::string& field, const std::string& val);
    RedisReply HSetNx(const std::string& key, const std::string& field, const std::string& val);
    RedisReply HStrlen(const std::string& key, const std::string& field);
    RedisReply HVals(const std::string& key);
    RedisReply HScan();

    // keys operation
    
    // op
    RedisReply Sort(const std::string& identif);
    RedisReply Del(const std::string& key);
    RedisReply Contain(const std::string& key);

    // keys ttl
    RedisReply PExpire(const std::string& key, long timeout /* milliseconds */);
    RedisReply PExpireAt(const std::string& key, long timestamp /* milliseconds */);
    RedisReply Persist(const std::string& key);
    RedisReply PTTL(const std::string& key);

    // list operation
    RedisReply BLPop(const StringVec& param);
    RedisReply BRPop(const StringVec& param);
    RedisReply BRPopLPush(const std::string& src, const std::string& dest, const std::string& timeout);
    RedisReply LIndex(const std::string& key, const std::string& index);
    RedisReply LInsert(const StringVec& param);
    RedisReply LLen(const std::string& key);
    RedisReply LPop(const std::string& key);
    RedisReply LPush(const std::string& key, const std::string& val);
    RedisReply LPushX(const std::string& key, const std::string& val);
    RedisReply LRange(const std::string& key, const std::string& start, const std::string& stop);
    RedisReply LRem(const std::string& key, const std::string& count, const std::string& value);
    RedisReply LSet(const std::string& key, const std::string& index, const std::string& val);
    RedisReply LTRem(const std::string& key, const std::string& count, const std::string& value);
    RedisReply RPop(const std::string& key);
    RedisReply RPopLPush(const std::string& src, const std::string dest);
    RedisReply RPush(const std::string& key, const std::string& val);
    RedisReply RPushX(const std::string& key, const std::string& val);
    
    // script operation
    RedisReply Eval(const std::string& script, int numkeys, const StringVec& keys, const StringVec& args);
    RedisReply EvalSha(const std::string& sha1, int numkeys, const StringVec& keys, const StringVec& args);
    RedisReply ScriptDebug(const std::string& mode);
    RedisReply ScriptExists(const StringVec& sha1Vec);
    RedisReply ScriptFlush();
    RedisReply ScriptKill();
    RedisReply ScriptLoad(const std::string& script);

    // set operation
    RedisReply SAdd(const std::string& key, const std::string& member);
    RedisReply SCard(const std::string& key);
    RedisReply SDiff(const std::string& lhs, const std::string& rhs);
    RedisReply SDiffStore(const std::string& dest, const std::string& lhs, const std::string& rhs);
    RedisReply SInter(const std::string& lhs, const std::string& rhs);
    RedisReply SInterStore(const std::string& dest, const std::string& lhs, const std::string& rhs);
    RedisReply SIsMember(const std::string& key, const std::string& member);
    RedisReply SMembers(const std::string& key);
    RedisReply SMove(const std::string& src, const std::string& dest, const std::string& member);
    RedisReply SPop(const std::string& key);
    RedisReply SRandMember(const std::string& key, const std::string& count);
    RedisReply SRem(const std::string& key, const std::string& count);
    RedisReply SUnion(const std::string& lhs, const std::string& rhs);
    RedisReply SUnionStore(const std::string& dest, const std::string& lhs, const std::string& rhs);
    RedisReply SScan();

    // sorted set
    RedisReply ZAdd(const std::string& key, const std::string& member);
    RedisReply ZCard(const std::string& key);

    // transaction
    RedisReply Discard();
    RedisReply Exec();
    RedisReply Multi();
    RedisReply Unwatch();
    RedisReply Watch(const StringVec& keyVec);



private:
    std::string BuildCommand(std::string&& cmd, const StringVec& vecParam);
	RedisReply Send(std::string&& cmd, const StringVec& vecParam);

private:
	redisContext*	m_pConn;
};

#endif // !__LIBREDIS_REDISCLIENT_H__
