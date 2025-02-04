# Create a library for database
add_library(database STATIC
    database_interface.cpp
)

# Include headers
target_include_directories(database PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against the SQLite library
target_link_libraries(database PRIVATE
    common    
    lib
)
