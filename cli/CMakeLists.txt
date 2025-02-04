# Create a library for cli
add_library(cli STATIC
    cli_state.cpp
    cli_manager.cpp
)

target_link_libraries(cli PRIVATE
    common
)

# Include headers
target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/database
    ${CMAKE_SOURCE_DIR}/core_model
)