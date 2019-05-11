//
// Created by zhangcheng on 2019-05-11.
//
#include "../common/tests_common.h"
#include <iostream>
#include "object/Singleton.h"

using namespace std;

class A
{
public:
    A(int a,int b)
    {
        TESTS_PRINT("class A")
        cout<< a << "- " << b << endl;
    }
};

class C
{
public:
    C(int a)
    {
        TESTS_PRINT("class C")
        cout << a << endl;
    }
};

/**
 * 测试 一个模板 应对 任意的单例对象
 * @return
 */
int main()
{
    A* classA = Singleton<A>::Instance(10,5);
    C* classC = Singleton<C>::Instance(10);

    return 0;
}