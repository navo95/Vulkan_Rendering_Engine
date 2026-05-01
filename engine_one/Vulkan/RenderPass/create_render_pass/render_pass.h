#pragma once
#include "logical_device.h"
#include"vulkan/vulkan.h"
#include"swapchain_option.h"

namespace Engine{
    class RenderPass{
        private:

            VkDevice logicaldevice = VK_NULL_HANDLE;
            
            VkRenderPass renderpass = VK_NULL_HANDLE;


        public:

            RenderPass(LogicalDevice& Logical_Device,swapchain_options& SwapchainOptions);
            ~RenderPass();
            VkRenderPass& Get_Render_pass(){return renderpass;}
    };
}