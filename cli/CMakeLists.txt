# Add the library
add_library(cli
    # List all source files here
    cli.c
    cli_time.c
    cli_utils.c
)

# Include directories
target_include_directories(cli PUBLIC 
    .
    ../common)
