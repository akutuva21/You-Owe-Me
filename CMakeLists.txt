cmake_minimum_required(VERSION 3.17)
project(nibbles)

set(CMAKE_CXX_STANDARD 20)

add_executable(nibbles src/main.cpp
headers/Interface.h src/Interface.cpp
headers/TextBox.h src/TextBox.cpp
headers/ScrollFrame.h src/ScrollFrame.cpp
headers/List.h src/List.cpp
headers/Matrix.h src/Matrix.cpp
headers/TextureManager.h src/TextureManager.cpp)

include_directories(headers /usr/include c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(nibbles ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build directory
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
