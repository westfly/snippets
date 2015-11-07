//  Copyright (c) 2015	Free Inc.  ALL RIGHTS RESERVED.
//  Author: yweiyun@gmail.com (Young Ray)
//  Create  2015-11-07

#ifndef BASE_CACHEDBUFFER_H
#define BASE_CACHEDBUFFER_H
#include <string>
#include <map>
namespace base
{
class CachedBuffer
{
 public:
    CachedBuffer();
    ~CachedBuffer();
    const char* addtobuf(const char* str, size_t len);
    const char* addtobuf(const std::string& str);
 private:
    // typedef stdext::hash_map<uint64_t, const char*> StringBufferHash;
    typedef std::map<uint64_t, const char*> StringBufferHash;
    StringBufferHash buffer_hash_;
    // DISALLOW_COPY_AND_ASSIGN(CachedBuffer);
};
} // namespace base

#endif // BASE_CACHEDBUFFER_H

