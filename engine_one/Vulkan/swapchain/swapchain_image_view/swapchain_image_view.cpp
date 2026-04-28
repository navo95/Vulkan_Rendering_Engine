#include"swapchain_image_view.h"

namespace Engine{
    swapchain_image_view::swapchain_image_view(std::vector<VkImage>& swapchain_images,swapchain_options& options,LogicalDevice& logicalDevice ):l_device(logicalDevice){
        std::cout<<"creating the VkImageViews per VkImage"<<std::endl;
        for(VkImage& Image: swapchain_images){
            //each of the VkImageViewCreateInfo attached to each of the VkImage is a intructrion to the gpu on how to use the 
            //VkImage to draw on it
            //here i am giving all the gpu same instruction across  all the VkImage
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image  = Image;
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = options.selected_swapchain_options.surface_format.format;

            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

            //now define which areas of the VkImage the graphics pipeline is allowed to see
            //giving the default values to it as i don't these attributes
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;


            //create the VkImageView instance
            VkImageView imageView;
            if(vkCreateImageView(logicalDevice.logical_device,&createInfo,NULL,&imageView)!=VK_SUCCESS){
                throw std::runtime_error("failled to create the ImageViews");
            };

            swapchain_imageView.push_back(imageView);
            
        }

    }//constructor
    swapchain_image_view::~swapchain_image_view(){
        //destroy the VkImageView Instances created

        for(VkImageView& ins:swapchain_imageView){
            vkDestroyImageView(l_device.logical_device,ins,nullptr);
        }
    }
}