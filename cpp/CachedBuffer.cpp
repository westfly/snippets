//  Copyright (c) 2015	Free Inc.  ALL RIGHTS RESERVED.
//  Author: yweiyun@gmail.com (Young Ray)
//  Create  2015-11-07

#include "CachedBuffer.h"
namespace base
{
uint64_t create_sign_64(const char* buf, size_t len)
{
    // over write me
  return 0;
}
CachedBuffer::CachedBuffer() {}
CachedBuffer::~CachedBuffer() {}
const char* CachedBuffer::addtobuf(const std::string& str)
{
  return addtobuf(str.c_str(), str.size());
}
const char* CachedBuffer::addtobuf(const char * str, size_t len)
{
    static const char* null_str = "";
    if (len <= 0)
    {
        return null_str;
    }
    uint64_t sign = create_sign_64(str, len);
    StringBufferHash::const_iterator it;
    if ((it = buffer_hash_.find(sign)) != buffer_hash_.end())
    {
        return it->second;
    }
    const char* new_buffer = strndup(str, len);
    buffer_hash_.insert(std::make_pair(sign, new_buffer));
    return new_buffer;
}
} // namespace base
