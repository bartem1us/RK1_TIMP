cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" ON)

project(RK_TIMP)

add_library(RK_TIMP STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/count.cpp)

add_executable(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/demo.cpp
        )

target_include_directories(RK_TIMP PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(demo ${PROJECT_NAME})

if(BUILD_EXAMPLES)
    file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
        target_link_libraries(${EXAMPLE_NAME} RK_TIMP)
        install(TARGETS ${EXAMPLE_NAME}
                RUNTIME DESTINATION bin
                )
    endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS RK_TIMP
        EXPORT RK_TIMP-config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT RK_TIMP-config DESTINATION cmake)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
    add_executable(tests ${${PROJECT_NAME}_TEST_SOURCES})
    target_link_libraries(tests ${PROJECT_NAME} gtest_main)
    add_test(NAME tests COMMAND tests)
endif()