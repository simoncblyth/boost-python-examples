set(name Property)

PYTHON_ADD_MODULE(${name} ${name}.cpp)

FILE(COPY ${name}.py DESTINATION .)

ADD_TEST(19-${name} ${name}.py)
