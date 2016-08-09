
#include <string>
#include <iostream>
#include <boost/python.hpp>

namespace bp = boost::python;


class Base 
{
public:
    virtual std::string name() const { return "Base"; }
    virtual ~Base() {}
};

void identify(Base *b) 
{
    std::cout << b->name() << " called." << std::endl;
}

#include <boost/python.hpp>
using namespace boost::python;







class Prop {
   public:
     //  Prop(std::string key) : m_key(key) {} 
       virtual std::string key() const {return m_key; }
       virtual bool set(bp::object& var) = 0;
       virtual ~Prop() {} 
   protected:
       std::string  m_key;
};


struct PropWrap : Prop, bp::wrapper<Prop>
{
     bool set(bp::object& var) {
#ifdef DEBUG
         std::cout << "PropWrap::set" << std::endl ;
#endif
         return this->get_override("set")(var);
     }

    virtual std::string key() const
    {   
        if (override n = this->get_override("key"))
            return n();
        return Prop::key();
    }   
    std::string default_key() const
    {   
        return this->Prop::key();
    }   

};

using namespace boost::python;

// cannot be instanciated from python
BOOST_PYTHON_MODULE(prop)
{
    class_<PropWrap, boost::noncopyable>("Prop")
         .def("key", &Prop::key, &PropWrap::default_key)
         .def("set",    pure_virtual(&Prop::set))
    ;   
};

// http://www.boost.org/doc/libs/1_61_0/libs/python/doc/html/tutorial/tutorial/exposing.html



