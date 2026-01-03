set(TARGET_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include(${CMAKE_SOURCE_DIR}/dependencies/raylib.cmake)

add_executable(${PROJECT_NAME} main.cpp)
add_dependencies(${PROJECT_NAME}
	raylib
)
target_include_directories(${PROJECT_NAME}
	PRIVATE
	${TARGET_INCLUDE_DIRECTORY}
	${RAYLIB_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
	raylib
)
target_compile_options(${PROJECT_NAME}
	PRIVATE
	$<$<CONFIG:DEBUG>:-g>
	$<$<CONFIG:RELEASE>:-O3>
	-fPIC
	-fno-rtti
	-Wall
	-Werror
	-Wextra
	-Wpedantic
)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
