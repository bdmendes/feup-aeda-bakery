cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp Product.cpp Product.h Shipping.cpp Shipping.h Store.cpp Store.h Person.cpp Person.h)