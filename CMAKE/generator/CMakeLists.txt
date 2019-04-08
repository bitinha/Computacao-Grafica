cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
file(GLOB SOURCES
    *.h
    *.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

if  (WIN32)

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
else (WIN32) #Linux and Mac

	set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} Wno-deprecated")
	find_package(GLUT REQUIRED)
	include_directories(${GLUT_INCLUDE_DIR})
	link_directories(${GLUT_LIBRARY_DIRS})
	add_definitions(${GLUT_DEFINITIONS})
	target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
	if(NOT GLUT_FOUND)
	   message(ERROR ": GLUT not found!")
	endif(NOT GLUT_FOUND)
	
endif(WIN32)
