cmake_minimum_required(VERSION 3.17)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src src/main.cpp src/Product.cpp src/Product.h src/Shipping.cpp src/Shipping.h src/Store.cpp src/Store.h src/Person.cpp src/Person.h)