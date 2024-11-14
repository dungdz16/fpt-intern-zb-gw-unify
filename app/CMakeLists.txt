# Add the library
add_library(app
    # List all source files here
    app.c
)

# Include directories
target_include_directories(app PUBLIC 
    .
    ../common
)
