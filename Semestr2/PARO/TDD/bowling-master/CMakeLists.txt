cmake_minimum_required(VERSION 2.8)
project(paro-tdd C CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

set(TSOURCES BowlingTDDProject.cpp)
set(CMAKE_BUILD_TYPE Debug)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/src/ ${CMAKE_CURRENT_LIST_DIR}/libs/)
    link_directories(${Boost_LIBRARY_DIRS})
    add_executable(${CMAKE_PROJECT_NAME} ${TSOURCES})
    target_link_libraries(${CMAKE_PROJECT_NAME}
                          ${Boost_LIBRARIES}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else()
    message(FATAL_ERROR, "Please install boost!")
endif()

add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME}
)

