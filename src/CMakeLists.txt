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

add_library(feup-aeda-project main.cpp model/product.cpp model/product.h model/store.cpp model/store.h model/person.cpp model/person.h model/order.cpp model/order.h model/date.cpp model/date.h exception/store_exception.cpp exception/store_exception.h exception/person_exception.cpp exception/person_exception.h
        exception/date_exception.cpp exception/date_exception.h exception/product_exception.cpp exception/product_exception.h)

add_executable(application
        main.cpp model/product.cpp model/product.h model/store.cpp model/store.h model/person.cpp model/person.h model/order.cpp model/order.h model/date.cpp model/date.h exception/store_exception.cpp exception/store_exception.h exception/person_exception.cpp exception/person_exception.h
exception/date_exception.cpp exception/date_exception.h)

target_include_directories(feup-aeda-project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(feup-aeda-project PUBLIC gtest_main coverage_config)