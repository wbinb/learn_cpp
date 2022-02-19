#include <iostream>
//#include <thread>
#include <vector>
#include <memory>
#include <string>

using namespace std;


class Rvalue
{
    public:
    Rvalue():source("hello!!!")
    {
        std::cout << "默认构造函数" <<std::endl;
    }
    Rvalue(const Rvalue& a)
    {
        std::cout << "拷贝构造函数" << std::endl;
        source = a.source;
    }
    Rvalue(Rvalue &&a)
    {
        std::cout << "移动构造函数" << std::endl;
        source = std::move(a.source);
    }
    void operator=(const Rvalue &a)
    {
        std::cout << "拷贝复制运算符" << std::endl;
        source = a.source;
    }
    void operator=(Rvalue &&a)
    {
        std::cout << "移动复制运算符" << std::endl;
        source = a.source;
    }
    string source;
};

Rvalue get()
{
    Rvalue a;
    return a;
}

void put(Rvalue)
{

}

int main(int argc, char *argv[])
{
    // int i;
    // int&& j = i++;
    // int&& k = ++i;       //error
    // int& m = i++;        //error
    // int& l = ++i;       
    Rvalue a = get();
    std::cout << "----------------" << std::endl;
    return 0;
}
