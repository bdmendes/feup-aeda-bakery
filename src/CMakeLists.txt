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

add_library(feup-aeda-project main.cpp model/Product.cpp model/Product.h model/Store.cpp model/Store.h model/Person.cpp model/Person.h model/Order.cpp model/Order.h exceptions/PersonExceptions.cpp exceptions/PersonExceptions.h exceptions/StoreExceptions.cpp exceptions/StoreExceptions.h ../test/storeTest.cpp)

add_executable(application
        main.cpp model/Product.cpp model/Product.h model/Store.cpp model/Store.h model/Person.cpp model/Person.h model/Order.cpp model/Order.h model/date.cpp model/date.h exceptions/PersonExceptions.cpp exceptions/PersonExceptions.h exceptions/StoreExceptions.cpp exceptions/StoreExceptions.h ../test/storeTest.cpp)

target_include_directories(feup-aeda-project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(feup-aeda-project PUBLIC gtest_main coverage_config)