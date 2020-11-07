cmake_minimum_required(VERSION 3.5)

project(thread_example LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL Network Concurrent )

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/mainWindow.cpp
    src/mainWindow.h
    src/mainWindow.ui
    src/workerObject.cpp
    src/workerObject.hpp
    src/workderQThread.hpp
    src/workderQThread.hpp
)

target_include_directories(
  ${CMAKE_PROJECT_NAME}
    PUBLIC
      src
)

target_link_libraries(
  ${CMAKE_PROJECT_NAME}
    PRIVATE
      Qt5::Widgets 
)

# execute windeployqt.exe
if(WIN32)
  set(WINDEPLOYQT_EXECUTABLE "${Qt5_BIN_DIR}/windeployqt.exe")
  message(" >> WINDEPLOYQT_EXECUTABLE")
  message(" WINDEPLOYQT_EXECUTABLE　>> ${WINDEPLOYQT_EXECUTABLE}")
  
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
  POST_BUILD
          COMMAND set PATH="${Qt5_BIN_DIR}"
          COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
)
endif()

if(WIN32)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
  include(InstallRequiredSystemLibraries)
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    install(TARGETS ${CMAKE_PROJECT_NAME}  
      DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
    INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} 
      DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
  elseif(CMAKE_BUILD_TYPE MATCHES Release)
    install(TARGETS ${CMAKE_PROJECT_NAME} 
      DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
    INSTALL(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} 
      DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
  endif()
endif()

