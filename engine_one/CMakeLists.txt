cmake_minimum_required(VERSION 3.17)

project("engine_one"  VERSION 1.00 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)


set(SOURCES
    "./Engine/window.cpp"
    "./main.cpp"
    "./Vulkan/Vulkan_initialization/Vulkan_instance.cpp"

)

add_executable(${PROJECT_NAME} ${SOURCES})

set(internal_headers
    "./Engine_Window"
    "./Vulkan/Vulkan_initialization"


)

target_include_directories(${PROJECT_NAME} PRIVATE ${internal_headers})

target_link_libraries(${PROJECT_NAME} PRIVATE 

    Vulkan::Vulkan
    comdlg32



)

#process the shaders






