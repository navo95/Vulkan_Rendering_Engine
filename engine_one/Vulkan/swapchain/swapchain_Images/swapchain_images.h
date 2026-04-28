#pragma once
#include"swapchain_instance.h"
#include<vector>
#include<iostream>


//once the swapchain instance is formed the vulkan produces many empty 3d and 2d images which are just empty memory slots we need a way to read and write into them


namespace Engine{
    class Get_Swapchain_Images{

        private:
            

        public:
            

            Get_Swapchain_Images(swapchain_instance& Instance,LogicalDevice& Logical_Device,uint32_t& no_of_images);
            ~Get_Swapchain_Images();
            //vector to hold the handles to all the VkImage-->raw memeory
            std::vector<VkImage> all_the_images; //fill it with all the handles
        
            
    };

}