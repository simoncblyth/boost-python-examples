set(name prop)

PYTHON_ADD_MODULE(${name} ${name}.cpp)

FILE(COPY ${name}.py DESTINATION .)

ADD_TEST(17-PropWrap ${name}.py)
