#pragma once
#include"swapchain_images.h"
#include"swapchain_option.h"
#include"swapchain_instance.h"
#include<vector>
#include "logical_device.h"




namespace Engine{
    class swapchain_image_view{

        private:
        std::vector<VkImageView> swapchain_imageView;
        LogicalDevice& l_device;

        public:

        swapchain_image_view(std::vector<VkImage>& swapchain_images,swapchain_options& options,LogicalDevice& logicalDevice);
        ~swapchain_image_view();
        std::vector<VkImageView> Get_ImageView(){return swapchain_imageView;} //
        
    };
}