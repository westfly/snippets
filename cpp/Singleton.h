#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <cassert>
#include <stdio.h>
template <typename T, bool heap_alloc = true> class Singleton
{
protected:
    static T* m_inst_;
public:
    Singleton()
    {
        if (!heap_alloc)
        {
            assert( !m_inst_ );
            m_inst_ = static_cast<T*>(this);
        }
    }
    ~Singleton()
    {
        assert( m_inst_ );
        if (heap_alloc)
        {
          delete m_inst_;
        }
        m_inst_ = 0;
    }
    static T* instance()
    {
        if (heap_alloc && !m_inst_)
        {
            m_inst_ = new T();
        }
        return ( m_inst_ );
    }
private:
    Singleton& operator=(const Singleton&);
    Singleton(const Singleton&);
};
template <typename T, bool heap_alloc>
T* Singleton<T, heap_alloc>::m_inst_ = NULL;
#endif  // _SINGLETON_H_
