#include <iostream>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include <string>
#include <vector>
#include <map>
#include <iomanip>


namespace bp = boost::python;

class Property
{
    public :

        Property(const std::string& key);

        virtual ~Property();

        //return the property key name
        const std::string& key() {return m_key; }

        //set property value as var
        virtual bool set(bp::object& var) = 0;

        //append var to vector/map property
        virtual bool append(bp::object& var);

        //show the value of the property
        void show() { write_info(std::cout, 0); }

        //write the value to an ostream
        virtual std::ostream& write_info(std::ostream& os, int indent) = 0;

    protected :

        // offer a better look for write_info
        void make_indent(std::ostream& os, int indent);

        const std::string  m_key;

        static const std::string badType;
        static const std::string cannotAppend;
};



const std::string Property::badType = "Cann't match type for property ";
const std::string Property::cannotAppend = "Cann't append to property ";

Property::Property(const std::string& key)
    : m_key(key)
{
}

Property::~Property()
{
}

bool Property::append(bp::object& /*var*/) {
    std::cerr << cannotAppend+m_key << std::endl ;
    return false ; 
}

void Property::make_indent(std::ostream& os, int indent)
{
    if ( indent != 0 ) {
        for ( int i = 0; i < indent-1; ++i ) {
            os << "   |  ";
        }
        os << "   +--";
    }
}








struct PropertyWrap : Property, bp::wrapper<Property>
{
    bool set(bp::object& var) {
#ifdef DEBUG
         std::cout << "PropertyWrap::set" << std::endl ; 
#endif
        return this->get_override("set")(var);
    }

    bool append(bp::object& var) {
#ifdef DEBUG
         std::cout << "PropertyWrap::append" << std::endl ; 
#endif

        if ( bp::override f = this->get_override("append") )
            return f(var);
        return Property::append(var);
    }

    bool default_append(bp::object& var) {
#ifdef DEBUG
         std::cout << "PropertyWrap::default_append" << std::endl ; 
#endif
        return this->Property::append(var);
    }
};


BOOST_PYTHON_MODULE(Property)
{
    using namespace boost::python;

    class_<PropertyWrap, boost::noncopyable>("Property", no_init)
        .def("set",    pure_virtual(&Property::set))
        .def("append", &Property::append, &PropertyWrap::default_append)
        .def("show",   &Property::show)
        ;




}
