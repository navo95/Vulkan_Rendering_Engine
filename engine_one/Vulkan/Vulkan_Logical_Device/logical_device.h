#pragma once
#include<vulkan/vulkan.h>
#include <vector>





//create a logical device 
//but first enable the available features in the selectedd gpu

namespace Engine{
    class LogicalDevice{
        private:


        public:
            LogicalDevice(VkPhysicalDevice& gpu_handle,std::vector<VkDeviceQueueCreateInfo>& queues_vector);
            ~LogicalDevice();


            //logical device handle
            VkDevice logical_device; //remember it is an opaque handles

    };
}



