cmake_minimum_required(VERSION 3.12)
project(app)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Threads REQUIRED)

file(GLOB QUICKJS_SRCS "quickjs/*.c")
file(STRINGS "quickjs/VERSION" QJS_CONFIG_VERSION LIMIT_INPUT 10)
set(QJS_CONFIG_VERSION \"${QJS_CONFIG_VERSION}\")

add_library(quickjs ${QUICKJS_SRCS})
target_compile_definitions(quickjs PUBLIC _GNU_SOURCE CONFIG_BIGNUM "CONFIG_VERSION=${QJS_CONFIG_VERSION}")

add_executable(main src/main.cpp)
target_compile_features(main PUBLIC cxx_std_11)
target_include_directories(main PUBLIC quickjs)
target_link_libraries(main PUBLIC quickjs Threads::Threads ${CMAKE_DL_LIBS})