#pragma once
#include"queue_handle.h"
#include"swapchain_option.h"
#include"Window.h"
#include"Vulkan_instance.h"
#include"logical_device.h"
#include"queueInfo.h"
#include"VulkanSurface.h"
#include"swapchain_support.h"
#include<functional>
#include"inspect_gpu.h"
#include"logical_device.h"






namespace Engine{
    class swapchain_instance{
        private:
        uint32_t min_images_in_swapchain;
        

        public:

        VkSwapchainKHR Swapchain_Instance;
        //VkDevice device; // this goes out of scope after the swapchain_instance goes out of scope resulting in the no swapchain instance creation
        VkDevice device;
        swapchain_instance(LogicalDevice& Logical_Device,VulkanSurface& surface,swapchain_options& swapchain_options_object,QueueHandle& queue_handle); //this would apply the setigns to the global 'createInfo'
        ~swapchain_instance();

    };
}
