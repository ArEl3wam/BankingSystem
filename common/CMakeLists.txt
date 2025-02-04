# Create a library for common
add_library(common INTERFACE)

# Include headers
target_include_directories(common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)