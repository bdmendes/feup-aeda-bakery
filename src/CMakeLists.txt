# Use C++14
set(CMAKE_CXX_STANDARD 14)
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

add_library(feup-aeda-project main.cpp model/product/product.h model/store/store.h model/order/order.h model/date/date.h exception/store_exception.h exception/person_exception.h
        exception/date_exception.h exception/product_exception.h exception/store_exception.h model/product/product.cpp model/store/store.cpp model/order/order.cpp model/date/date.cpp exception/store_exception.cpp exception/person_exception.cpp
        exception/date_exception.cpp exception/product_exception.cpp exception/store_exception.cpp exception/order_exception.h exception/order_exception.cpp model/person/client/client.cpp model/person/client/client.h
        model/person/worker/worker_manager.cpp model/person/worker/worker_manager.h model/person/worker/worker.cpp model/person/worker/worker.h model/order/order_manager.cpp model/order/order_manager.h model/product/product_manager.cpp model/product/product_manager.h)

add_executable(application
        main.cpp model/product/product.h model/store/store.h model/order/order.h model/date/date.h exception/store_exception.h exception/person_exception.h
        exception/date_exception.h exception/product_exception.h exception/store_exception.h model/product/product.cpp model/store/store.cpp model/order/order.cpp model/date/date.cpp exception/store_exception.cpp exception/person_exception.cpp
        exception/date_exception.cpp exception/product_exception.cpp exception/store_exception.cpp exception/order_exception.h exception/order_exception.cpp model/order/order_manager.cpp model/order/order_manager.h model/product/product_manager.cpp model/product/product_manager.h model/person/worker/worker_manager.cpp model/person/worker/worker_manager.h model/person/worker/worker.cpp model/person/worker/worker.h model/person/client/client.cpp model/person/client/client.h model/person/person/person.cpp model/person/person/person.h model/person/client/client_manager.cpp model/person/client/client_manager.h ui/command/command.cpp ui/command/command.h util/util.cpp util/util.h exception/command_exception.cpp exception/command_exception.h)

target_include_directories(feup-aeda-project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(feup-aeda-project PUBLIC gtest_main coverage_config)