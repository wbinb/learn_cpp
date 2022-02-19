#include <iostream>
#include <functional>
using namespace std;

//std::function< int (int)> Functional;

//using关键字的三种用法：
//1.命名空间的使用
//2.子类中引用基类成员
//3.别名指定类似于typedef
using invoke_cb = std::function< int (int)>;

int TestFunc(int a)
{
    return a;
}

auto lambda = [](int a)->int{return a;};

class Functor
{
    public:
        int operator()(int a)
        {
            return a;
        }
};

class TestClass
{
    public:
        int ClassMember(int a){ return a;}
        static int StaticMember(int a) { return a;}
};



int main(int argc, char *argv[])
{
    invoke_cb Functional;
    Functional = TestFunc;
    int result = Functional(10);
    cout << "普通函数：" << result <<endl;

    Functional = lambda;
    result = Functional(20);
    cout << "Lambda表达式：" << result << endl;

    Functor testFunctor;
    Functional = testFunctor;
    result = Functional(30);
    cout << "仿函数: " << result <<endl;

    TestClass testObj;
    Functional = std::bind(&TestClass::ClassMember, testObj, std::placeholders::_1);
    result = Functional(40);
    cout << "类成员函数：" << result <<endl;

    Functional = TestClass::StaticMember;
    result = Functional(50);
    cout << "类静态函数："<< result <<endl;

    return 0;
}