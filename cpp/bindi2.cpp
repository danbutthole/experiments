
#include <iostream>
#include <functional>
#include <memory>

template <class classT, class retT, class arg0T, class arg1T>
class BinderTR1A2
{
public:
    BinderTR1A2()
    {
    }

    virtual ~BinderTR1A2()
    {
    }

    typedef std::shared_ptr<BinderTR1A2<classT,retT,arg0T,arg1T>> Ptr;

    std::shared_ptr<classT> m_obj_ptr;

    virtual retT operator() (arg0T a0, arg1T a1) = 0;
};

#define BinderR1A2T(classT,name,retT,arg0T,arg1T) \
    Binder_ ## classT ## _ ## name

#define BinderR1A2TPtr(classT,name,retT,arg0T,arg1T) \
    std::shared_ptr<BinderR1A2T(classT,name,retT,arg0T,arg1T)>

#define BinderR1A2(classT,name,retT,arg0T,arg1T) \
    class Binder_ ## classT ## _ ## name : \
        public BinderTR1A2<classT,retT,arg0T,arg1T> \
    { \
    public: \
        typedef std::shared_ptr<classT> ClassTPtr; \
         \
        Binder_ ## classT ## _ ## name(ClassTPtr obj_ptr) \
            : m_obj_ptr(obj_ptr) \
        { \
        } \
         \
        virtual ~Binder_ ## classT ## _ ## name() \
        { \
        } \
         \
        typedef std::shared_ptr<Binder_ ## classT ## _ ## name> Ptr; \
         \
        ClassTPtr m_obj_ptr; \
         \
        virtual retT operator() (arg0T a0, arg1T a1) \
        { \
            return m_obj_ptr->name(a0, a1); \
        } \
    };

#define MakeBinderR1A2(classT,name,retT,arg0T,arg1T,obj_ptr) \
    std::make_shared<Binder_ ## classT ## _ ## name>(obj_ptr)

class A
{
public:
    A()
        : m_d(111)
    {
    }

    virtual ~A()
    {
    }

    typedef std::shared_ptr<A> Ptr;

    int m_d;

    int fn(unsigned int a, char c)
    {
        return m_d + a + c;
    }
};

#define A_fn_sig    int,unsigned int,char

BinderR1A2(A,fn,int,unsigned int,char);

typedef BinderR1A2TPtr(A,fn,int,unsigned int,char) A_fn;

#define make_A_fn(obj_ptr) \
    MakeBinderR1A2(A,fn,int,unsigned int,char,obj_ptr)

int main()
{
    A::Ptr a = std::make_shared<A>();

    A_fn a_fd = make_A_fn(a);

    std::cout << (*a_fd)(1, 2) << std::endl;

    return 0;
}
