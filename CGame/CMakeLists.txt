file(GLOB_RECURSE SOURCES ./*.c)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glad)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ./)