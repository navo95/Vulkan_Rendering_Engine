//Renderpass defines how to carry out the rendering using the VkImage
//but to define where to carry out the rendering the framebuffer is required
//the framebuffer shall bind the Renderpass to the VkImage
//one frambuffer is created for each of the VkImage



#pragma once
#include<vector>

#include<vulkan/vulkan.h>


namespace Engine{
    class FrameBuffer{
        private:
            std::vector<VkFramebuffer> swapchain_framebuffers;  //vector to hold the frambuffer to each of the VkImage created by the swapchain object

        public:
            FrameBuffer();
            ~FrameBuffer();


    };
}