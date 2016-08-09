
set(name CToPy)

PYTHON_ADD_MODULE(${name} ${name}.cpp)

FILE(COPY ${name}.py DESTINATION .)

ADD_TEST(16-${name} ${name}.py)
