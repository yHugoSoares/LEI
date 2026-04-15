cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(class10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} main.cpp)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if  (WIN32)

	message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
	set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
		message(ERROR ": GLUT not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")	
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")
		message(ERROR ": GLEW not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/glew/GL/glew.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glew/glew32.lib")	
	
	if (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")
		message(ERROR ": DevIL not found")
	endif (NOT EXISTS "${TOOLKITS_FOLDER}/devil/IL/il.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/devil/devIL.lib")	
	
	include_directories(${TOOLKITS_FOLDER}/glut ${TOOLKITS_FOLDER}/glew ${TOOLKITS_FOLDER}/devil)
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} 
										  ${TOOLKITS_FOLDER}/glut/glut32.lib 
										  ${TOOLKITS_FOLDER}/devil/devIL.lib
										  ${TOOLKITS_FOLDER}/glew/glew32.lib )
	
	if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
													AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
		file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/devil/devil.dll DESTINATION ${CMAKE_BINARY_DIR})
		file(COPY ${TOOLKITS_FOLDER}/glew/glew32.dll DESTINATION ${CMAKE_BINARY_DIR})
	endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll" AND EXISTS "${TOOLKITS_FOLDER}/glew/glew32.dll"
													AND EXISTS "${TOOLKITS_FOLDER}/devil/devil.dll")
	
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	 
else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	
	if (NOT APPLE)
		find_package(GLEW REQUIRED)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif(NOT APPLE)
	
	find_package(DevIL)

	# Compatibility: different FindDevIL modules export different variable names.
	if(DEFINED IL_INCLUDE_DIRS)
		# Some FindDevIL variants return the path to the IL subdir (e.g. /opt/homebrew/include/IL).
		# Normalize to the parent include dir so `#include <IL/il.h>` works.
		foreach(_il_dir IN LISTS IL_INCLUDE_DIRS)
			# if _il_dir is .../include/IL, take its parent (.../include)
			get_filename_component(_il_parent ${_il_dir} DIRECTORY)
			include_directories(${_il_parent})
		endforeach()
	elseif(DEFINED IL_INCLUDE_DIR)
		get_filename_component(IL_INCLUDE_DIR_PARENT ${IL_INCLUDE_DIR} DIRECTORY)
		include_directories(${IL_INCLUDE_DIR_PARENT})
	endif()

	if(DEFINED IL_LIBRARIES)
		set(DEVIL_LIBS ${IL_LIBRARIES})
	elseif(DEFINED IL_LIBRARY)
		set(DEVIL_LIBS ${IL_LIBRARY})
	else()
		set(DEVIL_LIBS "")
	endif()

	# If DevIL wasn't found by find_package, try common Homebrew and /usr paths (macOS)
	if(NOT DEVIL_LIBS)
		find_path(IL_HEADER IL/il.h PATHS /opt/homebrew/include /usr/local/include /usr/include)
		if(IL_HEADER)
			# IL_HEADER is .../include/IL/il.h; include its parent (the include directory)
			get_filename_component(IL_HEADER_DIR ${IL_HEADER} DIRECTORY)
			get_filename_component(IL_INCLUDE_PARENT ${IL_HEADER_DIR} DIRECTORY)
			include_directories(${IL_INCLUDE_PARENT})
		endif()

		find_library(IL_LIB NAMES IL ILut ILU PATHS /opt/homebrew/lib /usr/local/lib /usr/lib)
		if(IL_LIB)
			set(DEVIL_LIBS ${IL_LIB})
		endif()
	endif()

	if(DEVIL_LIBS)
		link_libraries(${DEVIL_LIBS})
	endif()

	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${DEVIL_LIBS})
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)

file(COPY ${CMAKE_SOURCE_DIR}/relva.jpg DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/terreno.jpg DESTINATION ${CMAKE_BINARY_DIR})