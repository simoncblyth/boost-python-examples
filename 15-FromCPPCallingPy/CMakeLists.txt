
set(name from_cpp_calling_py)

ADD_EXECUTABLE(${name} FromCPPCallingPy.cpp)

TARGET_LINK_LIBRARIES(${name} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

SET( ENV{PYTHONPATH} . )

ADD_TEST(15-FromCPPCallingPy ${name})

