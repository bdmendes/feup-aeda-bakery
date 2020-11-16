project(feup-aeda-project)
cmake_minimum_required(VERSION 3.10.2)

SET(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()

include_directories(../src/)

# Link against gtest or gtest_main as needed

add_executable(testing order_test.cpp date_test.cpp product_test.cpp person_test.cpp store_test.cpp ../src/model/order/order.cpp ../src/model/order/order.h ../src/model/person/worker/worker.cpp ../src/model/person/worker/worker.h ../src/model/person/person.cpp ../src/model/person/person.h ../src/model/person/client/client_manager.cpp ../src/model/person/client/client_manager.h ../src/util/util.cpp ../src/util/util.h ../src/ui/ui.cpp ../src/ui/ui.h ../src/model/person/boss/boss.cpp ../src/model/person/boss/boss.h)

target_link_libraries(testing PRIVATE gtest_main feup-aeda-project)

add_test(NAME testing COMMAND testing)
