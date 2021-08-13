include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src)

add_executable(CDemo
    CDemo.c
    test.cpp)

target_link_libraries(CDemo
    slvs)
