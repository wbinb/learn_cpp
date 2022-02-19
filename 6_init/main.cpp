/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 该例程用于介绍C++的各种初始化机制
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define DEFAULT_INIT    0
#define VALUE_INIT      1
#define DIRECT_INIT     2
#define COPY_INIT       3
#define LIST_INIT       4

#define TEST_TYPE   DEFAULT_INIT

class like
{
    public:
        //默认构造函数
        /**
         * @brief 
         * C++ 默认构造函数是对类中的参数提供默认值的构造函数，
         * 一般情况下，是一个没有参数值的空函数，也可以提供一些的默认值的构造函数，
         * 如果用户没有定义构造函数，那么编译器会给类提供一个默认的构造函数，
         * 但是只要用户自定义了任意一个构造函数，那么编译器就不会提供默认的构造函数，
         * 这种情况下，容易编译报错，所以正确的写法就是用户在定义构造函数的时候，也需要添加一个默认的构造函数，这样就不会造成编译报错。
         */
        #if 1
        like():x(0), y(0)                                   //<za>
        {
            cout << "默认构造函数" << endl;
        } 
        #else
        like() = default;
        #endif
        like(int _x, int _y) : x(_x), y(_y)                 //<zb>
        {
            //带有参数的构造函数，使用列表初始化的方式
            cout << "普通构造函数" << endl;
        }
        like(const like &lk)
        {
            x = lk.x;
            y = lk.y;
            cout << "拷贝构造函数" << endl;
        }

        ~like()
        {
            //cout << "" << endl;
        }
        int x;
        int y;
};

int main(int argc, char *argv[])
{
    #if (TEST_TYPE == DEFAULT_INIT)
    /**
     * @brief 
     * 1 默认初始化：是指定义变量时没指定初值的初始化操作
     * 内置类型：全局变量为0，局部变量未定义
     * 类类型：执行默认构造函数，没有默认构造函数则不能进行初始化
     */
    cout << "默认初始化"  << endl;
    int a;              //内置类型
    like b;             //类类型
    int *p = new int;   //采用动态内存分配的初始化
    cout << "a:"  << a << endl;
    cout << "b:"  << b.x << b.y << endl;
    cout << "*p:"  << *p << endl;
    #elif (TEST_TYPE == VALUE_INIT)
    /**
     * @brief 
     * 2 值初始化：是使用了初始化器（圆括号或者花括号）但却没提供初始值的情况
     * 内置类型：全局变量为0，局部变量未定义
     * 类类型：执行默认构造函数，没有默认构造函数则不能进行初始化
     */
    cout << "值初始化"  << endl;
    int a = int();              //内置类型
    like b = like();            //类类型 
    int *p = new int();         //采用动态内存分配的初始化
    cout << "a:"  << a << endl;
    cout << "b:x&y "  << b.x << "&"<< b.y << endl;
    cout << "*p:"  << *p << endl;

    #elif (TEST_TYPE == DIRECT_INIT)
    /**
     * @brief 
     * 3 直接初始化
     * 直接初始化是指采用小括号的方式进行变量初始化（小括号里一定要有初始值，如果没提供初始值，那就是值初始化了！）
     */
    cout << "直接初始化"  << endl;
    int a = int(1);              //内置类型
    like b = like(1,1);          //类类型 like b{1,1};
    int *p = new int(10);         //采用动态内存分配的初始化
    cout << "a:"  << a << endl;
    cout << "b:x&y "  << b.x << "&"<< b.y << endl;
    cout << "*p:"  << *p << endl;

    #elif (TEST_TYPE == COPY_INIT)
    /**
     * @brief 
     * 4 拷贝初始化
     * 拷贝初始化是指采用等号（=）进行初始化的方式。
     * 例如int a=12;string s=string("123456");等等。
     * 拷贝初始化看起来像是给变量赋值，实际上是执行了初始化操作，与先定义再赋值本质不同。
     * 内置类型：与直接直接初始化类似
     * 类类型：调用类的拷贝构造函数
     */
    cout << "拷贝初始化"  << endl;
    int a = 1;              //内置类型
    like b = like(1,1);     //类类型    直接初始化 
    like c = b;             //类类型    拷贝初始化
    cout << "a:"  << a << endl;
    cout << "c:x&y "  << c.x << "&"<< c.y << endl;

    #elif (TEST_TYPE == LIST_INIT)
    /**
     * @brief 
     * 5 列表初始化
     * 列表初始化是C++ 11 新引进的初始化方式，它采用一对花括号（即｛｝）进行初始化操作。
     * 能用直接初始化和拷贝初始化的地方都能用列表初始化，而且列表初始化能对容器进行方便的初始化，
     * 因此在新的C++标准中，推荐使用列表初始化的方式进行初始化。
     * 
     * 
     * 在这里做下区分：初始化列表和列表初始化
     * 
     * 初始化列表：是声明在构造函数中来实现的，相当于初始化，而不是复制操作，如注解 <za>,<zb>
     *            初始化列表是由其必要性的，比如const变量、引用、禁止复制构造函数的类、没有默认构造函数的类
     *            避免调用多次构造函数
     * 
     * 列表初始化：直接使用{}定义且赋值的操作其实就可以称之为列表初始化
     * 
     */
    cout << "列表初始化"  << endl;
    int a = {1};            //内置类型
    like b = like{1,1};     //类类型
    string s = {"I'm string"};
    vector<int> v = {1,2,3};
    cout << "a:"  << a << endl;
    cout << "b:x&y "  << b.x << "&"<< b.y << endl;
    cout << "s:"  << s << endl;
    #endif

    return 0;
}