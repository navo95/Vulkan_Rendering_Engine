#include"gpu_querry.h"

namespace Engine{
    gpu_querry::gpu_querry(Inspect_Gpu& inspect_gpu,VulkanSurface& surface){
        //get the vulkansurface

        VkSurfaceKHR surface_handle = surface.Get_surface_khr(); //handle to the surface

        Gpu_Handle = inspect_gpu.gpu_handle;


        //get the no of queues in the selected gpu
        uint32_t no_of_queues;
        vkGetPhysicalDeviceQueueFamilyProperties(Gpu_Handle,&no_of_queues,nullptr);

        //now querry the gpu for thr available queues and get their indices
        std::vector<VkQueueFamilyProperties> queue_handles(no_of_queues);

        vkGetPhysicalDeviceQueueFamilyProperties(Gpu_Handle,&no_of_queues,queue_handles.data());

        //now we have the handles to all the queue families in this device
        //get the indices of each of them

        for(int i=0;i<queue_handles.size();++i){
            VkQueueFamilyProperties queue_handle = queue_handles[i];

            std::cout<<"the no of queues in this queue_family"<<"["<<i<<"]"<<queue_handle.queueCount<<std::endl;

            if(queue_handle.queueFlags & VK_QUEUE_GRAPHICS_BIT ){
                std::cout<<"the graphics queue is present in the queue familly at the index: "<<i<<std::endl;
                graphics_queue_familly_indice =i;
                
            }
            if(queue_handle.queueFlags & VK_QUEUE_COMPUTE_BIT){
                std::cout<<"the comute queue is present in the queue family at the index: "<<i<<std::endl;
                transfer_queue_family_indice = i;
                
            }
            if(queue_handle.queueFlags & VK_QUEUE_TRANSFER_BIT){
                std::cout<<"the transfer queue is present in the queue-family at index: "<<i<<std::endl;
                compute_queue_family_indice = i;
                
            }
            //check for the present queue
            VkBool32 PresentQueuePresent = VK_FALSE;
            bool is_found_PresentQueue   = false;
            
            vkGetPhysicalDeviceSurfaceSupportKHR(

                Gpu_Handle,
                i,
                surface_handle,

                &PresentQueuePresent
            );
            if(PresentQueuePresent){
                std::cout<<"the present queue is present at the Queue-family at index: "<<i<<std::endl;
                present_queue_family_indice = i;
            }

            if(PresentQueuePresent && (queue_handle.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queue_handle.queueFlags & VK_QUEUE_COMPUTE_BIT) && (queue_handle.queueFlags & VK_QUEUE_TRANSFER_BIT)){
                graphics_queue_familly_indice = present_queue_family_indice = compute_queue_family_indice = transfer_queue_family_indice = i;
                break;
            }
        }
   
    }

    gpu_querry::~gpu_querry(){
        //nothing to destroy no object created
    }
}