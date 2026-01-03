set(TARGET_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME}
	PRIVATE
	${TARGET_INCLUDE_DIRECTORY}
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
