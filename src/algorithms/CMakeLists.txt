add_library(linspace linspace.c)
target_include_directories(linspace PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_library(transform transform.c)
target_link_libraries(transform PUBLIC ranges)
target_include_directories(transform PUBLIC "${PROJECT_SOURCE_DIR}/include")
