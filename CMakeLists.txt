cmake_minimum_required(VERSION 3.3)
project(TP_LOGO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/src/lex.yy.c)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
            OUTPUT ${FlexOutput}
            COMMAND ${FLEX_EXECUTABLE}
            --outfile=${FlexOutput}
            ${CMAKE_SOURCE_DIR}/src/logo.l
            COMMENT "Generating scanner.cpp"
    )
ENDIF()

set(SOURCE_FILES main.cpp)
add_executable(test-logo src/logo.c src/logo.h test/test_logo.c)
add_executable(test-lexic ${FlexOutput})