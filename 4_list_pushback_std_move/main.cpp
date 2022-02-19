#include <list>
#include <iostream>

std::list<int> foo;

class like_list
{
    public:
        // like_list(const int &val)
        // {
        //     val = val;
        //     std::cout << "copy" << std::endl;
        // }
        // like_list(int &&val)
        // {
        //     val = val;
        //     std::cout << "move" << std::endl;
        // }
        void push_a(const int &val)
        {
            s_val = val;
            std::cout << "copy" << std::endl;
        }
        void push_a(int &&val)
        {
            s_val = val;
            std::cout << "move" << std::endl;
        }
        int get_val()
        {
            return s_val;
        }
    private:
        int s_val;
};

like_list temp;

int main(int argc, char *argv[])
{
    // {
    //     int bar = 42;
    //     foo.push_back(bar);
    // }
    // std::cout << "1:" << foo.back() << std::endl;
    // {
    //     int bar = 43;
    //     foo.push_back(std::move(bar));   
    // }
    // std::cout << "2:" << foo.back() << std::endl;

    {
        int bar = 42;
        temp.push_a(bar);
    }
    std::cout << "1:" << temp.get_val() << std::endl;
    {
        int bar = 43;
        temp.push_a(std::move(bar));
        std::cout << "org:" << bar << std::endl;
    }
    std::cout << "2:" << temp.get_val() << std::endl;
    return 0;
}