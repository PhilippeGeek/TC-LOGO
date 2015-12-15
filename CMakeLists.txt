cmake_minimum_required(VERSION 3.3)
project(TP_LOGO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(BisonOutput ${CMAKE_SOURCE_DIR}/src/logo.tab.c)
FIND_PACKAGE(BISON REQUIRED)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
            SOURCE ${CMAKE_SOURCE_DIR}/src/logo.y
            COMMAND ${BISON_EXECUTABLE}
            ARGS --defines=${CMAKE_SOURCE_DIR}/src/logo.tab.h
            -o ${BisonOutput}
            ${CMAKE_SOURCE_DIR}/src/logo.y
            COMMENT "Generating parser.c"
            OUTPUT ${BisonOutput}
    )
ENDIF(BISON_FOUND)
FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/src/logo.yy.c)
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
add_executable(test-logo src/logo.c src/logo.h src/test_logo.c)
TARGET_LINK_LIBRARIES(test-logo m)
add_executable(test-lexic ${FlexOutput} ${BisonOutput})