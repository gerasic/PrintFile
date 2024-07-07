add_executable(PrintFile main.cpp)

target_link_libraries(PrintFile PRIVATE Parse)
target_include_directories(PrintFile PUBLIC ${PROJECT_SOURCE_DIR})