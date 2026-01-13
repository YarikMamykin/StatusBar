add_library(lifecycle OBJECT
	${CMAKE_CURRENT_SOURCE_DIR}/LifecycleHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Semaphore.cpp
)
target_include_directories(lifecycle PRIVATE
	${TARGET_INCLUDE_DIRECTORY}
)
target_link_libraries(lifecycle PUBLIC
	ui
	data
)
add_dependencies(lifecycle 
	ui
	data
)
