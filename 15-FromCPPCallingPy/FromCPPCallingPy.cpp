//  http://stackoverflow.com/questions/16486375/boost-python-calling-function-objects-with-a-namespace

#include <iostream>
#include <boost/python.hpp>

int main()
{
  Py_Initialize();

  namespace python = boost::python;
  python::object main = python::import("__main__");
  python::object main_namespace = main.attr("__dict__");

  //Put the function name runPyProg in the main_namespace
  python::exec(
    "def runPyProg(exp):\n"
    "    print exp\n"
    "    exec exp in globals()\n"
    "    return\n"
    "\n", main_namespace);

  // Now call the python function runPyProg with an argument
  python::object runPyProg = main.attr("runPyProg");

  // Set x in python and access from C++.
  runPyProg("x = 42");
  std::cout << python::extract<int>(main.attr("x")) << std::endl;

  // Set y from C++ and access within python.
  main.attr("y") = 100;
  runPyProg("print y");

  // Access and modify x in python, then access from C++.
  runPyProg("x += y");
  std::cout << python::extract<int>(main.attr("x")) << std::endl;
}

