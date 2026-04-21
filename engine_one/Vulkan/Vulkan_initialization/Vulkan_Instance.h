#pragma once
//this file is responsolve for creating and managing the vulkan Instance
#ifndef VK_KHR_win32_surface  //required macro to anable the Win32 surface extensions to come into play
#define VK_KHR_win32_surface
#endif()
#include<windows.h>
#include<vector>
#include<iostream>
#include<vulkan/vulkan.h>
#include"Window.h"

namespace Engine{

    class Vulkan_Instance{
        private:
        
            VkInstance v_hInstance = VK_NULL_HANDLE; //to avoid garbage value initialisation
            HINSTANCE m_hinstance=VK_NULL_HANDLE;

        public:
            Vulkan_Instance(const char* applicationname,HINSTANCE hinstance);
            ~Vulkan_Instance();
            //get the handle to the vulkan Instance
            VkInstance Get_vulkan_Instance_handle(){return v_hInstance;}
            //function to return the m_hinstance
            HINSTANCE Get_app_handle(){return m_hinstance;}
            //function to create the vulkan instance
            void Create_vulkan_instance(const char* applicationname);

            //vector to hold the names of the validaion layers
            std::vector<const char*> validation_layers{
                "VK_LAYER_KHRONOS_validation"
            };

            //function to check if vulkan supportd the validation layers mentioned in the 'validation_layers'

            bool check_validation_layer_ifexists(std::vector<const char*> layers);

            #ifndef NDEBUG
                bool m_enable_Validation_layers  = false;
            #else
                bool m_enable_Validation_layer = true;
            #endif()

    };
}

