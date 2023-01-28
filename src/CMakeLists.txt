add_library(memory memory.c)
target_include_directories(memory PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(io io.c)
target_include_directories(io PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(str str.c)
target_link_libraries(str PUBLIC memory)
target_include_directories(str PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(ranges ranges.c)
target_include_directories(ranges PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(algorithms)

add_library(algorithm algorithm.c)
target_link_libraries(algorithm PUBLIC linspace transform)
target_include_directories(algorithm PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(common_math common_math.c)
target_link_libraries(common_math PUBLIC m)
target_include_directories(common_math PUBLIC "${PROJECT_SOURCE_DIR}/include")
