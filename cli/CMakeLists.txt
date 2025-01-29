# Create a library for cli
add_library(cli STATIC
    cli_state.cpp
    cli_manager.cpp
)

# Include headers
target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)