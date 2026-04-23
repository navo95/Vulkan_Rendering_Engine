#pragma once


#include "gpu_querry.h"
#include <functional>
//#include "inspect_gpu.h"
#include "logical_device.h"



//get the handle to the queufamilies that are indexed

//for that get the indices to the queuefamilies selected

namespace Engine{
    class QueueHandle{
        private:

        public:
            struct Queue_Indices{        //will hold the indices
                uint32_t graphics_indice;
                uint32_t present_indice;
                uint32_t transfer_indice;
                uint32_t compute_indice;
            };

            struct Queue_Handles{  //will hold the handle to the queues
                VkQueue graphicshandle;
                VkQueue presenthandle;
                VkQueue transferhandle;
                VkQueue computehandle;
            };
            Queue_Handles m_queue_handles={}; //holds thr handles
            Queue_Indices m_queue_indices= {}; //holds the indices
            
            QueueHandle(gpu_querry& querry_indice,LogicalDevice& logical_device_object);
            ~QueueHandle();
    };
}