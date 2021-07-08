cmake_minimum_required(VERSION 3.17)
project(XGL VERSION 1.0) 

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} 
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(APPLE)
  set(CMAKE_INSTALL_NAME_DIR @executable_path)
  set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif(APPLE)

file(GLOB XGLFiles 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/XGL/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/XGL/*.cpp)
file(GLOB XGLHeaders ${CMAKE_CURRENT_SOURCE_DIR}/src/XGL/*.h)

add_library(XGL SHARED ${XGLFiles})

set_target_properties(XGL PROPERTIES 
    FRAMEWORK FALSE
    FRAMEWORK_VERSION A 
    MACOSX_FRAMEWORK_IDENTIFIER com.luk2010.xgl 
    PUBLIC_HEADER "${XGLHeaders}"
)

find_package(GLM REQUIRED)
target_include_directories(XGL PUBLIC ${GLM_INCLUDE_DIRS})

add_executable(helloworld
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/helloworld.cpp 
)

target_link_libraries(helloworld XGL)
target_include_directories(helloworld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(
    TARGETS XGL helloworld
    RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
    LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
    FRAMEWORK DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
    PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/XGL
)
