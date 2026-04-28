#include"swapchain_images.h"
#include "logical_device.h"
#include"queueinfo.h"
#include"VulkanSurface.h"
#include"Vulkan_physicalDevice.h"


namespace Engine{

    Get_Swapchain_Images::Get_Swapchain_Images(swapchain_instance& Instance,LogicalDevice& Logical_Device,uint32_t& no_of_images){
        vkGetSwapchainImagesKHR(Logical_Device.logical_device,Instance.Swapchain_Instance,&no_of_images,nullptr);

        //get the handles
        all_the_images.resize(no_of_images);

        vkGetSwapchainImagesKHR(Logical_Device.logical_device,Instance.Swapchain_Instance,&no_of_images,all_the_images.data());

    
        std::cout<<"the swapchain images handles receiving succesfull"<<std::endl;

       
        
    }

    Get_Swapchain_Images::~Get_Swapchain_Images(){
        //nothing to destroy no object/Instance created
    }


}