set(name Poly)

PYTHON_ADD_MODULE(${name} ${name}.cpp)

FILE(COPY ${name}.py DESTINATION .)

ADD_TEST(18-${name} ${name}.py)
