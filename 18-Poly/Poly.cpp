// http://www.boost.org/doc/libs/1_61_0/libs/python/doc/html/reference/high_level_components/boost_python_wrapper_hpp.html#high_level_components.boost_python_wrapper_hpp.class_template_wrapper

//#include <boost/python/module.hpp>
//#include <boost/python/class.hpp>
//#include <boost/python/wrapper.hpp>
//#include <boost/python/call.hpp>

#include <boost/python.hpp>

using namespace boost::python;

// Class with one pure virtual function
struct P
{
    virtual ~P(){}
    virtual char const* f() = 0;
    char const* g() { return "P::g()"; }
};

struct PCallback : P, wrapper<P>
{
    char const* f()
    {
        return this->get_override("f")();
    }
};

// Class with one non-pure virtual function
struct A
{
    virtual ~A(){}
    virtual char const* f() { return "A::f()"; }
};

struct ACallback :  A, wrapper<A>
{
    char const* f()
    {
        if (override f = this->get_override("f"))
            return f();
        return A::f();
    }

    char const* default_f() { return this->A::f(); }
};

BOOST_PYTHON_MODULE(Poly)
{
    using namespace boost::python;

    class_<PCallback,boost::noncopyable>("P")
        .def("f", pure_virtual(&P::f))
        ;

    class_<ACallback,boost::noncopyable>("A")
        .def("f", &A::f, &ACallback::default_f)
        ;
}
