cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(class11)

if (NOT APPLE)
	if (WIN32)
		set(TOOLKITS_FOLDER "" CACHE PATH "Path to toolkits folder")
		include_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
		link_directories(
			${TOOLKITS_FOLDER}/glew
			${TOOLKITS_FOLDER}/glut
			${TOOLKITS_FOLDER}/devil)
	else(WIN32)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(WIN32)
endif(NOT APPLE)

if (NOT WIN32)
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})

	find_package(DevIL REQUIRED)
	link_libraries(${IL_LIBRARIES} )
	# Homebrew often sets IL_INCLUDE_DIR to .../include/IL, but code uses <IL/il.h>.
	if (EXISTS "${IL_INCLUDE_DIR}/il.h")
		get_filename_component(IL_INCLUDE_PARENT "${IL_INCLUDE_DIR}" DIRECTORY)
		include_directories(${IL_INCLUDE_PARENT})
	else()
		include_directories(${IL_INCLUDE_DIR})
	endif()
endif(NOT WIN32)	
	
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_executable(${PROJECT_NAME} main.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/Oil_Drum001h.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Concrete.jpg DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glut32 glew32 DevIL)
	file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
	file(COPY ${TOOLKITS_FOLDER}/devil/DevIL.dll DESTINATION ${CMAKE_BINARY_DIR})
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

else(WIN32)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif (WIN32)
