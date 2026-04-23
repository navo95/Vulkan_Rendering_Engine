#pragma once

#include "Vulkan_physicalDevice.h"
#include"Vulkan_Instance.h"
#include<functional>
#include<vulkan/vulkan.h>
#include<vector>
#include<optional>

namespace Engine{
    class Inspect_Gpu{
        private:




        public:
            Inspect_Gpu(){};
            ~Inspect_Gpu();
            //global gpu handle
            VkPhysicalDevice gpu_handle;

            

            //vector to hold all the final filtered device handles

            std::vector<VkPhysicalDevice> Gpu_Devices;

            //for a particula gpu we chekc it's 1,Properties,2.Features,3.QueueFamilies

            void Get_the_Handles(PhysicalDevice& Device,Vulkan_Instance& Instance);


            //function to check for the gpu's Features
            void gpu_properties(std::vector<VkPhysicalDevice>& device);


            //optional
            void  check_if_single(std::vector<VkPhysicalDevice>& devices); //1

            



    };
}