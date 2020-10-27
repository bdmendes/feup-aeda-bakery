# Use C++11
set(CMAKE_CXX_STANDARD 11)
# Require (at least) it
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Don't use e.g. GNU extension (like -std=gnu++11) for portability
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    link_libraries(wsock32 ws2_32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32")
    SET(CMAKE_CXX_FLAGS -Wcpp)
endif (WIN32)

include_directories(../src/)

add_library(feup-aeda-project main.cpp model/product.h model/store.h model/person.h model/order.h model/date.h exception/store_exception.h exception/person_exception.h
        exception/date_exception.h exception/product_exception.h exception/store_exception.h model/product.cpp model/store.cpp model/person.cpp model/order.cpp model/date.cpp exception/store_exception.cpp exception/person_exception.cpp
        exception/date_exception.cpp exception/product_exception.cpp exception/store_exception.cpp exception/order_exception.h exception/order_exception.cpp)

add_executable(application
        main.cpp model/product.h model/store.h model/person.h model/order.h model/date.h exception/store_exception.h exception/person_exception.h
        exception/date_exception.h exception/product_exception.h exception/store_exception.h model/product.cpp model/store.cpp model/person.cpp model/order.cpp model/date.cpp exception/store_exception.cpp exception/person_exception.cpp
        exception/date_exception.cpp exception/product_exception.cpp exception/store_exception.cpp exception/order_exception.h exception/order_exception.cpp)

target_include_directories(feup-aeda-project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(feup-aeda-project PUBLIC gtest_main coverage_config)