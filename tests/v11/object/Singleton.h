//
// Created by zhangcheng on 2019-05-02.
//

#ifndef HIGH_PERFORMANCE_NETWORK_SERVER_SINGLETON_H
#define HIGH_PERFORMANCE_NETWORK_SERVER_SINGLETON_H

#include <utility>
#include <stdexcept>

/**
 * c++11 实现的单例 结合可变模板参数 实现任意参数构造函数的类型 的单例实现
 * @tparam T
 */
template <typename T>
class Singleton
{
public:
    //获取单例
    template <typename... Args>
    static T* Instance(Args&& ... args)
    {
        if(m_pInstance == nullptr)
            m_pInstance = new T(std::forward<Args>(args) ...); //完美转发

        return m_pInstance;
    }

    //获取单例
    static T* GetInstance()
    {
        if(m_pInstance == nullptr)
            throw std::logic_error("the instance is not init, please initialize the instance first");

        return m_pInstance;
    }

    static void DestroyInstance()
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }

private:
    Singleton(void);
    virtual ~Singleton(void);
    Singleton(const Singleton&);
    Singleton& operator = (const Singleton&);

private:
    static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;

#endif //HIGH_PERFORMANCE_NETWORK_SERVER_SINGLETON_H
