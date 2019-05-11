//
// Created by zhangcheng on 2019-05-11.
//
#include "../common/tests_common.h"
#include <iostream>
#include <functional>
#include "object/Observer.h"

using namespace std;

struct stA
{
    int a,b;
    void print(int a, int b)
    {
        cout << a << "," << b << endl;
    }
};

void the_print(int a, int b)
{
    cout << a << "," << b << endl;
}


/**
 * 测试 c++11实现的观察者模式 通知接口 使用的可变模板参数  支持任意参数
 * @return
 */
int main()
{
    Events<std::function<void(int,int)>> myevent;

    auto key = myevent.Connect(the_print);
    stA t;
    auto lambdaKey = myevent.Connect( [&t] (int a,int b){ t.a =a; t.b = b;});

    //std::function 注册
    std::function< void(int,int)> f = std::bind(&stA::print, &t, std::placeholders::_1, std::placeholders::_2);
    myevent.Connect(f);

    int a = 1, b = 2;
    myevent.Notify(a, b);

    myevent.Disconnect(key);
    myevent.Disconnect(lambdaKey);

    return 0;

}