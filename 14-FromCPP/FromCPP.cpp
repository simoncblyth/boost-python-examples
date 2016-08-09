//  http://stackoverflow.com/questions/14179279/use-boost-python-in-c-to-access-to-array-of-functions-defined-in-python

#include <iostream>
#include <boost/python.hpp>

#include <functional>
#include <vector>

using namespace std;
namespace bp = boost::python;

typedef function<double(double, double, double)> CPP_Function;
typedef vector< CPP_Function > CPP_Function_vector; 

CPP_Function_vector convert_functions( bp::object const& functions ) 
{
    int l = bp::len( functions );
    CPP_Function_vector result;
    for (int i=0; i < l; i++ )
    {
        bp::object f = functions[i];
        result.push_back( [f]( double a, double b, double c)->double { return bp::extract<double>(f(a,b,c)); } );
    }
    return result;
}

int main( int argc, char* argv[] )
{

    Py_Initialize();

    bp::object main_module = bp::import("__main__");
    bp::object main_dict   = main_module.attr("__dict__");

    bp::exec(
        "from math import *\n"
        "def f1(x,y,z):\n"
        "  return  sin(x)*cos(y)*tan(z)\n"
        "def f2(x,y,z):\n"
        "  return  sin(x)*cos(z)\n"
        "f=[f1, f2]",
        main_dict
    );

    bp::object f = main_dict["f"];

    CPP_Function_vector function_vector = convert_functions( f );

    cout << function_vector[1](1.0, 0.2, 0.3) << endl;

    return 0;

}
