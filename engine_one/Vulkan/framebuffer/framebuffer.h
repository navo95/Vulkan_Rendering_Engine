//Renderpass defines how to carry out the rendering using the VkImageView
//but to define where to carry out the rendering the framebuffer is required
//the framebuffer shall bind the Renderpass to the VkImageViews
//one frambuffer is created for each of the VkImageview



#pragma once
#include<vector>

#include<vulkan/vulkan.h>

#include"swapchain_option.h" //to get the vulkan-surface capabilites struct
#include"swapchain_support.h"
#include"swapchain_images.h"  //to get the VkImage
#include"swapchain_image_view.h" //to get the VkImageViews
#include "render_pass.h" //the bluprint for the VkImageView rendering onto



namespace Engine{
    class FrameBuffer{
        private:
            std::vector<VkFramebuffer> swapchain_framebuffers;  //vector to hold the frambuffer to each of the VkImage created by the swapchain object
            LogicalDevice& Logical_Device;

        public:
            FrameBuffer(LogicalDevice& Logical_Device,swapchain_options& Swapchain_Options,swapchain_image_view& image_view,RenderPass& render_pass,Get_Swapchain_Images& swapchain_images);
            ~FrameBuffer();
            std::vector<VkFramebuffer>& Get_Framebuffers(){return swapchain_framebuffers;}


    };
}