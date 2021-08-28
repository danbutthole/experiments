
#include <functional>
#include <list>
#include <iostream>

class A
{
public:
    A(int a_)
        : m_a(a_)
    {
    }

    virtual ~A()
    {
    }

    int m_a;

    void fn(int a, int b, int c)
    {
        std::cout << "m_a: " << m_a << ", a: " << a << ", b: " << b
                << ", c: " << c << std::endl;
    }
};

class B
{
public:
    B(int a_)
        : m_a(a_)
    {
    }

    virtual ~B()
    {
    }

    int m_a;

    void fn(int a, int b, int c)
    {
        std::cout << "m_a: " << m_a << ", a: " << a << ", b: " << b
                << ", c: " << c << std::endl;
    }
};

class Caller
{
public:
    Caller(void)
    {
    }

    virtual ~Caller()
    {
    }

    std::list<void *> m_fns;
};

typedef void (*fn_type)(void);

int main() {
    A a(123);
    B b(321);

    auto fnab = std::bind(&A::fn, &a, 7, 8, 9);
    auto fnbb = std::bind(&B::fn, &b, 7, 8, 9);
    fnab();
    fnbb();

    Caller cally;
    cally.m_fns.push_back(&fnab);
    cally.m_fns.push_back(&fnbb);

    fn_type t = (fn_type)(&cally.m_fns.front());
    /**
     * Moral of the story:
     *
     * So, functors in c++ are quite unlike in python, whereas in python
     * they are first class objects, and can be passed around willy-nilly
     * with proper memory goodness in c++ they cannot.
     *
     * This was my last attempt at getting a call of a c++ functor to do
     * something. It segfaults.
     *
     * Two be honest I think something not very nice could be added to c++
     * to allow this code to work, but at its core, when lifecycle, memory
     * safety and perhaps locking a consider - probably not a good idea.
     *
     * Part of the reason I really like c++ for concrete and well thought
     * out problems is its type safety and ability to be optimised. I don't
     * think they can be fully maintained while adding the ability to code
     * such as is in this snippet.
     */
    t();

    return 0;
}
