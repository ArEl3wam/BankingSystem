# Create a library for core_model
add_library(core_model STATIC
    user.cpp
    account.cpp
)

# Include headers
target_include_directories(core_model PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)