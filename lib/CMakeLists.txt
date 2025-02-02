# Create a library for lib
add_library(lib STATIC
    sqlite3.c
)

set_source_files_properties(sqlite3.c PROPERTIES LANGUAGE C)

# Include headers
target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(lib PRIVATE 
    Threads::Threads 
    ${CMAKE_DL_LIBS}
)