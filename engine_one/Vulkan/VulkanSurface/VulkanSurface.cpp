#include <iostream>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include<windows.h>
#include "VulkanSurface.h"
#include<stdexcept>


namespace Engine{

    VulkanSurface::VulkanSurface(Windows& window,Vulkan_Instance& instance){

        
        m_hinstance = window.get_hinstance(); //handle to the hinstance for the aplication

        v_instance = instance.Get_vulkan_Instance_handle(); //handle to the vulkan instance created earlier

        //call the function to create the vulkan surface instance
        CreateVulkanWindowSurface(window,instance);

        


    }
    VulkanSurface::~VulkanSurface(){
        if(m_vulkan_window_surface!=VK_NULL_HANDLE){
            vkDestroySurfaceKHR(v_instance,m_vulkan_window_surface,nullptr);
        
        }
    }

    void VulkanSurface::CreateVulkanWindowSurface(Windows& window,Vulkan_Instance& instance){
        //create the surface create info struct
        VkWin32SurfaceCreateInfoKHR createinfo{};

        createinfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createinfo.hwnd = window.get_hwnd();
        createinfo.hinstance = window.get_hinstance();


        //create the instance
        if(vkCreateWin32SurfaceKHR(v_instance,&createinfo,nullptr,&m_vulkan_window_surface)!=VK_SUCCESS){
            throw std::runtime_error("surface coudn't be created");
        }   

        

    }

}