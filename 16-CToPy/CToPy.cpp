
// http://stackoverflow.com/questions/29119086/how-to-convert-c-objects-to-boostpythonobject

#include <boost/python.hpp>

// Mockup types.
class spam {};
class egg  {};

// Factory function that returns boost::python::objects.
boost::python::object make_object(std::string name)
{
  namespace python = boost::python;
   
  if (name == "spam")     return python::object(new spam);   // spam{} ; used C++11 brace-init before 
  else if (name == "egg") return python::object(new egg);    // egg{}  ; 
  else return python::object();
}

BOOST_PYTHON_MODULE(CToPy)
{
  namespace python = boost::python;

  // Expose models.
  python::class_<spam>("Spam", python::init<>());
  python::class_<egg>("Egg", python::init<>());

  // Expose factory function.
  python::def("make_object", &make_object);
}
