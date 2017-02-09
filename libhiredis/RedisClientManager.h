#ifndef __LIBHIREDIS_REDIS_CLIENT_MANAGER_H__
#define __LIBHIREDIS_REDIS_CLIENT_MANAGER_H__
#include "common_type.h"
#include <map>

class RedisClient;
typedef int64_t     ConnectNo;

class RedisClientManager
{
public:
    RedisClientManager();
    ~RedisClientManager();

    RedisClientManager(const RedisClientManager&) = delete;
    RedisClientManager& operator=(const RedisClientManager&) = delete;

public:
    ConnectNo CreateClient(const String& host, int port, long timeout);
    void      DestructClient(ConnectNo no);

    RedisClient*    FindClient(ConnectNo no);

public:
    ConnectNo   m_seq;
    std::map<ConnectNo, RedisClient*> m_clientMap;
};

#endif // !__LIBHIREDIS_REDIS_CLIENT_MANAGER_H__

