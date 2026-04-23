#include "queueInfo.h"



namespace Engine{
    Queue_Info_Struct::Queue_Info_Struct(gpu_querry& m_gpu_querry){
        std::set<uint32_t> queue_Info_structs = {m_gpu_querry.graphics_queue_familly_indice,m_gpu_querry.present_queue_family_indice,m_gpu_querry.compute_queue_family_indice,m_gpu_querry.transfer_queue_family_indice};
        int j = 1;
        float queuePriority = 1.0f;
        for(uint32_t indice:queue_Info_structs){

            VkDeviceQueueCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            createInfo.queueFamilyIndex = indice;
            createInfo.queueCount = j;
            j++;
            createInfo.pQueuePriorities = &queuePriority;
            queueFamilyInfoStructs.push_back(createInfo);

        }
    }
    Queue_Info_Struct::~Queue_Info_Struct(){//nothing to destroy no object were created

    }
}