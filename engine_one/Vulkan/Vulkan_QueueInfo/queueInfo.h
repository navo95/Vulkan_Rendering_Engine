#pragma once


#include<set>
#include "gpu_querry.h"
#include "inspect_gpu.h"
#include "Vulkan_physicalDevice.h"
#include "Vulkan_Instance.h"

namespace Engine{
    class Queue_Info_Struct{
        private:

        public:
            //vector to hold the QueueInfos of the Various Queuefamily or 1 queuefamily <goal is to fill this>
            std::vector<VkDeviceQueueCreateInfo> queueFamilyInfoStructs; 
            
            Queue_Info_Struct(gpu_querry& m_gpu_querry);

            ~Queue_Info_Struct();

    };
}
