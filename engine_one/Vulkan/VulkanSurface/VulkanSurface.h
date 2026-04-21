#pragma once

#include "window.h"
#include "Vulkan_Instance.h"
#define VK_USE_PALTFORM_WIN32_KHR
#include<vulkan/vulkan.h>


namespace Engine{
    class VulkanSurface{
        private:
        VkSurfaceKHR m_vulkan_window_surface = VK_NULL_HANDLE;
        //create an handle to to the vulkan Instance
        VkInstance v_instance;
        //create a handle to the  application
        HINSTANCE m_hinstance;

        
        public:
        //method to extract the surface variable
        VkSurfaceKHR Get_surface_khr(){return m_vulkan_window_surface;}

        VulkanSurface(Windows& window,Vulkan_Instance& instance);
        ~VulkanSurface();

        void CreateVulkanWindowSurface(Windows& window,Vulkan_Instance& instance);//function to create the surface
        
    };
}



