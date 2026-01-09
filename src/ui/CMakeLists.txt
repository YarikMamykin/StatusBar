add_library(ui OBJECT
	${CMAKE_CURRENT_SOURCE_DIR}/StatusBarWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/WindowHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/DataRenderingVisitor.cpp
)
target_include_directories(ui PRIVATE
	${TARGET_INCLUDE_DIRECTORY}
	${RAYLIB_INCLUDE_DIR}
)
target_link_libraries(ui PUBLIC
	raylib
)
add_dependencies(ui 
	raylib
)
