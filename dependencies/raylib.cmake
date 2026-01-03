include(ExternalProject)

ExternalProject_Add(raylib_external
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
    PREFIX ${CMAKE_BINARY_DIR}/raylib
    BINARY_DIR ${CMAKE_BINARY_DIR}/raylib/build
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/raylib
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_EXAMPLES=OFF 
        -DBUILD_SHARED_LIBS=OFF
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --parallel
    INSTALL_COMMAND ${CMAKE_COMMAND} --install <BINARY_DIR>

    UPDATE_DISCONNECTED TRUE
    LOG_DOWNLOAD TRUE
    LOG_CONFIGURE TRUE
    LOG_BUILD TRUE
    LOG_INSTALL TRUE
)

ExternalProject_Get_property(raylib_external INSTALL_DIR)

# Create imported target for raylib
add_library(raylib STATIC IMPORTED GLOBAL)
add_dependencies(raylib raylib_external)

set(RAYLIB_INCLUDE_DIR ${CMAKE_BINARY_DIR}/lib/raylib/include CACHE PATH "Raylib include directory")
set(RAYLIB_LIBRARY_DIR ${CMAKE_BINARY_DIR}/lib/raylib/lib CACHE PATH "Raylib library directory")

file(MAKE_DIRECTORY ${RAYLIB_INCLUDE_DIR})
file(MAKE_DIRECTORY ${RAYLIB_LIBRARY_DIR})

set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION ${RAYLIB_LIBRARY_DIR}/libraylib.a
    INTERFACE_INCLUDE_DIRECTORIES ${RAYLIB_INCLUDE_DIR}
)
