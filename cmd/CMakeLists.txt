add_executable(${PROJECT_NAME} exporter.cpp)

if (NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE GSL gflags eb epwing format)
