add_library(ui OBJECT
	${CMAKE_CURRENT_SOURCE_DIR}/StatusBarWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/WindowHandler.cpp
)
target_include_directories(ui PRIVATE
	${TARGET_INCLUDE_DIRECTORY}
)
