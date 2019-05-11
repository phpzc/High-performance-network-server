//
// Created by zhangcheng on 2019-05-11.
//

#ifndef HIGH_PERFORMANCE_NETWORK_SERVER_OBSERVER_H
#define HIGH_PERFORMANCE_NETWORK_SERVER_OBSERVER_H

//改进的观察者

class Noncopyable
{
protected:
    Noncopyable() = default;
    ~Noncopyable() = default;

    //禁用复制构造
    Noncopyable(const Noncopyable & ) = delete;
    //禁用赋值构造
    Noncopyable& operator = (const Noncopyable&) = delete;
};

#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

template <typename Func>
class Events: public Noncopyable
{
public:
    Events(){}
    ~Events(){}

    //注册观察者
    int Connect(Func&& f)
    {
        return Assign(f);
    }
    int Connect(const Func& f)
    {
        return Assign(f);
    }
    //移除观察者
    void Disconnect(int key)
    {
        m_connections.erase(key);
    }

    //通知所有的观察者
    template <typename ... Args>
    void Notify(Args&& ...args)
    {
        for(auto& it:m_connections)
        {
            //完美转发
            it.second( std::forward<Args>(args)...);
        }
    }

private:
    //保存观察者
    template <typename F>
    int Assign(F&& f)
    {
        int k=m_observerId++;
        m_connections.emplace(k, std::forward<F>(f));
        return k;
    }
    //
    int m_observerId = 0;//观察者对应的编号
    std::map<int,Func> m_connections;//观察者列表
};



#endif //HIGH_PERFORMANCE_NETWORK_SERVER_OBSERVER_H
