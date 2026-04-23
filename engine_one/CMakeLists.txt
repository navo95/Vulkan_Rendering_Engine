cmake_minimum_required(VERSION 3.17)

project("engine_one"  VERSION 1.00 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)


set(SOURCES
    "./Engine_Window/window.cpp"
    "./main.cpp"
    "./Vulkan/Vulkan_initialization/Vulkan_instance.cpp"
    
    "./Vulkan/PhysicalDevice/Vulkan_physicalDevice.cpp"
    "./Vulkan/inspect_gpu/inspect_gpu.cpp"
    "./Vulkan/VulkanSurface/VulkanSurface.cpp"
    "./Vulkan/gpu_querry/gpu_querry.cpp"
    "./Vulkan/Vulkan_QueueInfo/queueInfo.cpp"
    "./Vulkan/Vulkan_Logical_Device/logical_device.cpp"
    "./Vulkan/Queue_Handles/queue_handle.cpp"

)

add_executable(${PROJECT_NAME} ${SOURCES})

set(internal_headers
    "./Engine_Window"
    "./Vulkan/Vulkan_initialization"
    "./Vulkan/physical_device"
    "./third_party/glm"
    "./Vulkan/VulkanSurface"
    "./Vulkan/PhysicalDevice"
    "./Vulkan/inspect_gpu"
    "./Vulkan/gpu_querry"
    "./Vulkan/Vulkan_QueueInfo"
    "./Vulkan/Vulkan_Logical_Device"
    "./Vulkan/Queue_Handles"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${internal_headers})

target_link_libraries(${PROJECT_NAME} PRIVATE 

    Vulkan::Vulkan
    comdlg32



)

#process the shaders






