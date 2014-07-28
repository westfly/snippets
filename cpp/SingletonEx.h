#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <cassert>
#include <pthread.h>
/*
 * Usage:
 * LoadBalancer* ld = Singleton<LoadBalancer>::get_instance();
 * */
template <typename T>
class Singleton
{

   static T* get_instance()
   {
     pthread_once(&once_, &Singleton::init);
     return ( m_inst_ );
   }
private:
    static pthread_once_t once_;
    static T* m_inst_;
private:
    static void init()
    {
      static T value; // or m_inst_ = new T();
      m_inst_ = &value;
    }
    Singleton();
    ~Singleton();
    Singleton& operator=(const Singleton&);
    Singleton(const Singleton&);
};
template<typename T>
pthread_once_t Singleton<T>::once_ = PTHREAD_ONCE_INIT;
template<typename T>
T* Singleton<T>::m_inst_ = NULL;
#endif	// _SINGLETON_H_
