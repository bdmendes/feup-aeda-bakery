cmake_minimum_required(VERSION 3.10.2)
project(feup-aeda-project)

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
        model/person/worker/worker_manager.cpp model/person/worker/worker_manager.h model/person/worker/worker.cpp model/person/worker/worker.h model/order/order_manager.cpp model/order/order_manager.h model/product/product_manager.cpp model/product/product_manager.h
        ui/ui.cpp ui/ui.h model/person/boss/boss.cpp model/person/boss/boss.h ui/menu/login_menu.cpp ui/menu/login_menu.h ui/dashboard/client_dashboard.cpp ui/dashboard/client_dashboard.h ui/dashboard/boss_dashboard.cpp ui/dashboard/boss_dashboard.h ui/dashboard/worker_dashboard.cpp ui/dashboard/worker_dashboard.h ui/overview/product_overview.cpp ui/overview/product_overview.h ui/overview/order_overview.cpp ui/overview/order_overview.h ui/overview/client_overview.cpp ui/overview/client_overview.h ui/overview/worker_overview.cpp ui/overview/worker_overview.h ui/menu/intro_menu.cpp ui/menu/intro_menu.h)

add_executable(application
        main.cpp model/product/product.h model/store/store.h model/order/order.h model/date/date.h exception/store_exception.h exception/person_exception.h
        exception/date_exception.h exception/product_exception.h exception/store_exception.h model/product/product.cpp model/store/store.cpp model/order/order.cpp model/date/date.cpp exception/store_exception.cpp exception/person_exception.cpp
        exception/date_exception.cpp exception/product_exception.cpp exception/store_exception.cpp exception/order_exception.h exception/order_exception.cpp model/order/order_manager.cpp model/order/order_manager.h model/product/product_manager.cpp model/product/product_manager.h model/person/worker/worker_manager.cpp model/person/worker/worker_manager.h model/person/worker/worker.cpp model/person/worker/worker.h model/person/client/client.cpp model/person/client/client.h model/person/person.cpp model/person/person.h model/person/client/client_manager.cpp model/person/client/client_manager.h util/util.cpp util/util.h
        ui/ui.cpp ui/ui.h model/person/boss/boss.cpp model/person/boss/boss.h ui/menu/login_menu.cpp ui/menu/login_menu.h ui/dashboard/client_dashboard.cpp ui/dashboard/client_dashboard.h ui/dashboard/boss_dashboard.cpp ui/dashboard/boss_dashboard.h ui/dashboard/worker_dashboard.cpp ui/dashboard/worker_dashboard.h ui/overview/product_overview.cpp ui/overview/product_overview.h ui/overview/order_overview.cpp ui/overview/order_overview.h ui/overview/client_overview.cpp ui/overview/client_overview.h ui/overview/worker_overview.cpp ui/overview/worker_overview.h ui/menu/intro_menu.cpp ui/menu/intro_menu.h)

target_include_directories(feup-aeda-project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(feup-aeda-project PUBLIC gtest_main coverage_config)