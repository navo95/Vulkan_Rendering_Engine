#include"swapchain_instance.h"
#include<set>

namespace Engine{
    swapchain_instance::swapchain_instance(LogicalDevice& Logical_Device,VulkanSurface& surface,swapchain_options& swapchain_options_object,QueueHandle& queue_handle):device(Logical_Device.logical_device){
        
            VkSwapchainCreateInfoKHR create_info{};

            create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            create_info.surface = surface.Get_surface_khr();
            create_info.minImageCount  = swapchain_options_object.selected_swapchain_options.capabilities.minImageCount;
            //or create_info.minImageCount = swapchain_optiona_object.selected_swapchain_options.min_image_count;

            create_info.imageFormat = swapchain_options_object.selected_swapchain_options.surface_format.format;
            create_info.imageColorSpace = swapchain_options_object.selected_swapchain_options.surface_format.colorSpace;
            //image resolution ie image's height and width
            create_info.imageExtent = swapchain_options_object.selected_swapchain_options.capabilities.currentExtent;

            create_info.imageArrayLayers = 1; //default 
            //to render color into the swpchain images
            create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;


            //handle the queue familly handles

            std::set<uint32_t> unique_indice = {queue_handle.m_queue_indices.graphics_indice,queue_handle.m_queue_indices.present_indice,queue_handle.m_queue_indices.transfer_indice,queue_handle.m_queue_indices.compute_indice};

            if(unique_indice.size()>1){
                //different queue families exists
                
                std::cout<<"implementing the VK_SHARING_MODE_CONCURRENT"<<std::endl;
                create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                create_info.queueFamilyIndexCount = unique_indice.size();
                uint32_t queue_indices_array[] = {queue_handle.m_queue_indices.graphics_indice,queue_handle.m_queue_indices.present_indice,queue_handle.m_queue_indices.transfer_indice,queue_handle.m_queue_indices.compute_indice};
                create_info.pQueueFamilyIndices = queue_indices_array; //it has to be array
                

            }
            else{
                std::cout<<"no unique queue-family-indices exists"<<std::endl;
                create_info.imageSharingMode  = VK_SHARING_MODE_CONCURRENT;
                create_info.queueFamilyIndexCount = 0;
                create_info.pQueueFamilyIndices = nullptr;

            }
            //surface transform capabilities ie rotation and translation

            create_info.preTransform = swapchain_options_object.selected_swapchain_options.capabilities.currentTransform;

            create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //usually blending with other windows is opaque ie another window is placed over our
            //rendering engine's window the contents of the rendering  engine becomes invisible
            create_info.presentMode = swapchain_options_object.selected_swapchain_options.presentMode;

            create_info.clipped = VK_TRUE;

            //create the swapchain Instance

            if(vkCreateSwapchainKHR(device,&create_info,nullptr,&Swapchain_Instance)!=VK_SUCCESS){  //not applying
                throw std::runtime_error("the swapchain instance coudn't be created");
            }
            else{
                std::cout<<"the swapchain instance is created"<<std::endl;
            }



    }//swapchain constructor's scope

    swapchain_instance::~swapchain_instance(){
        //destroy the swapchain instance created
        
        vkDestroySwapchainKHR(device,Swapchain_Instance,nullptr);

    }
}
