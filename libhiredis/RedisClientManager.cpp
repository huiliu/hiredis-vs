#include "RedisClientManager.h"
#include "RedisClient.h"


RedisClientManager::RedisClientManager()
    : m_seq(0)
    , m_clientMap()
{
}


RedisClientManager::~RedisClientManager()
{
}

ConnectNo RedisClientManager::CreateClient(const String & host, int port, long timeout)
{
    ConnectNo no = ++m_seq;
    RedisClient* pclient = new RedisClient();
    int ret = pclient->Connect(host, port, { 0, timeout });

    m_clientMap.emplace(no, pclient);
    return no;
}

void
RedisClientManager::DestructClient(ConnectNo no)
{
    delete FindClient(no);
}

RedisClient * RedisClientManager::FindClient(ConnectNo no)
{
    auto it = m_clientMap.find(no);
    if (m_clientMap.end() != it)
    {
        return it->second;
    }
    return nullptr;
}
