#ifndef __LIBHIREDIS_COMMON_TYPE_H__
#define __LIBHIREDIS_COMMON_TYPE_H__
#include "src/hiredis.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

typedef std::string                 String;
typedef std::vector<std::string>    StringVec;

inline void destruct_redis_context(redisContext* p)
{
    if (nullptr != p)
    {
        redisFree(p);
    }
}

#endif // !__LIBHIREDIS_COMMON_TYPE_H__
