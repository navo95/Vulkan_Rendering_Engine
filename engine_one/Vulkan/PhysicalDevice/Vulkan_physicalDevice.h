#pragma once
#include "VulkanSurface.h"
#include "Vulkan_Instance.h"
#include<functional>
#include <cstring>



namespace Engine{
    class PhysicalDevice{
        private:
            uint32_t no_of_devices = 0;


        public:


            PhysicalDevice(){};
            ~PhysicalDevice();
            //get the no of devices
            void check_for_devices(Vulkan_Instance& Instance);

            //now allocate an vector with the space of no_of_devices to hold that many handles and with all the available handles
            std::vector<VkPhysicalDevice> all_the_device_handles;
            void allocate_the_vector_space(Vulkan_Instance& Instance);

            
    };
}