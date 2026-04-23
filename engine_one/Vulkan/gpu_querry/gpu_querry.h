//to get the queue indices of the selected gpu 
#pragma once

#include<vulkan/vulkan.h>
#include<vector>


#include"window.h"
#include"Vulkan_instance.h"
#include<functional>
#include "VulkanSurface.h"
#include "inspect_gpu.h"
#include "Vulkan_physicalDevice.h"

namespace Engine{
    

    class gpu_querry{
        public:

        uint32_t graphics_queue_familly_indice;
        uint32_t present_queue_family_indice;
        uint32_t compute_queue_family_indice;
        uint32_t transfer_queue_family_indice;

        //get the gpu handle
        gpu_querry(Inspect_Gpu& inspect_gpu,VulkanSurface& surface);
        ~gpu_querry();
        VkPhysicalDevice Gpu_Handle;
        
    };
}