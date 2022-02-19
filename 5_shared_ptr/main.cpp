#include <list>
#include <iostream>
#include <memory>

using namespace std;

typedef void (*callback)(void);

class like
{
    public:
    like(int x, callback call) : a(x), p_callback(call)
    {
        cout << "default gouzao" << endl;
        cout << "a:" << a << endl;
        printf("p_callback %p\n", p_callback);
    };
    ~like()
    {
        cout << "xigou" <<endl;
    }
    int a;
    callback p_callback;
};

list<shared_ptr<like>> g_like_list;

void callback_fun()
{
    cout << "I'm callback" << endl;    
}


void fun2(shared_ptr<like> &like)
{
    //注意这个地方会将智能指针的内部计数值再+1,
    //也就是说结束最顶层的调用之后，智能指针指向的对象并不会自动释放
    //还得在该list中擦除以及引用计数值确实为0，才会完全释放掉
    printf("fun2:push list\n");
    g_like_list.push_back(like);
}

void fun(shared_ptr<like> ptr)
{
    cout << "fun1:ptr point value is: " << ptr->a << endl;
    printf("fun1:p_callback %p\n", ptr->p_callback);
    fun2(ptr);
}

void test(like *plike)
{
    
        cout << "22222222222222222" <<endl;
        plike->p_callback();
        fun(shared_ptr<like>(plike));
        cout << "33333333333333333" <<endl;
        
#if 1
        //取决与fun函数中有没有对该智能指针继续引用计数
        //如果没有，这个地方plike指针对象已经被指针指针释放掉了，callback和a的值未知
        //如果有，比如将该智能指针push到list中去，那么智能指针的引用计数值会+1，这里对象依然存在
        cout << "plike point value is: " << plike->a << endl;
        plike->p_callback();    
        printf("p_callback %p\n", plike->p_callback);
#endif

        if(!g_like_list.empty())
        {
            shared_ptr<like> p_like;
            cout << "list size:" << g_like_list.size() <<endl;
            p_like = g_like_list.back();
            p_like->p_callback();
#if 1
            //这里尝试将list中的对象删掉
            g_like_list.pop_back();
            //g_like_list.clear();

#if 1
            //讲道理，这个地方已经被释放掉了，运行起来应该会出问题，但是实际没问题？？？
            //是不是编译器优化导致？？

            //这个地方理解错了
            //首先将list的元素返回给 p_like 这个临时智能指针对象，这里会对p_like重新构造，计数值又+1了
            //然后将list的元素给删掉，计数值-1，但并不为0，因为p_like这个临时对象仍然持有着
            //只有等该程序段结束，才完整释放掉
            cout << "plike point value is: " << plike->a << endl;
            plike->p_callback();    
            printf("p_callback %p\n", plike->p_callback);
#endif

#endif
        }

#if 0
        //到这里，已经没有该对象的引用了，因为该释放的都已经释放了，必出问题！！！
        cout << "plike point value is: " << plike->a << endl;
        plike->p_callback();    
        printf("p_callback %p\n", plike->p_callback);
#endif
        cout << "end test" << endl;
}


int main(int argc, char *argv[])
{
    cout << "11111111111111111" <<endl;
    like *bad = new like(12, callback_fun);
    test(bad);
    cout << "end main" <<endl;
    return 0;
}