cmake_minimum_required( VERSION 3.15 )

set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" )

project( giflib VERSION 5.2.2 )

FILE( GLOB LIB_SOURCES 
    dgif_lib.c
    egif_lib.c
    gifalloc.c
    gif_err.c
    gif_font.c
    gif_hash.c
    openbsd-reallocarray.c
)

add_library( giflib ${LIB_SOURCES} )

target_include_directories( giflib PRIVATE
    "../../public"
)