#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <cassert>
// From CEGUI
/* Usage
 class LoadBalancer : private Singleton<LoadBalancer>
 {

 };
 LoadBalancer::get_instance();
 */
template <typename T> class Singleton
{
protected:
    static T* m_inst_;
public:
    Singleton()
    {
        assert( !m_inst_ );
        m_inst_ = static_cast<T*>(this);
    }
   ~Singleton()
   {
     assert( m_inst_ );
     m_inst_ = 0;
   }
   static T* get_instance()
   {
     return ( m_inst_ );
   }
private:
    Singleton& operator=(const Singleton&);
    Singleton(const Singleton&);
};
#endif	// _SINGLETON_H_
