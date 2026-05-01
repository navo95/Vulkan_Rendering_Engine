#include"render_pass.h"

namespace Engine{
    RenderPass::RenderPass(LogicalDevice& Logical_Device,swapchain_options& SwapchainOptions):logicaldevice(Logical_Device.logical_device),renderpass(VK_NULL_HANDLE){
        //create the VkAttachementDesciption,VkAttachementReference,VkSubpassDescription,VkSubpassDependency
        //these will be requied to create the renderpass infostruct VkRenderPassCreateInfo
        VkAttachmentDescription create_description_info{}; //colorAttachemnt
        create_description_info.format = SwapchainOptions.selected_swapchain_options.surface_format.format;
        create_description_info.samples  = VK_SAMPLE_COUNT_1_BIT;
        create_description_info.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        create_description_info.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        create_description_info.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        create_description_info.stencilLoadOp =  VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        create_description_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        create_description_info.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    


        VkAttachmentReference create_reference_to_des{};

        create_reference_to_des.attachment = 0;
        create_reference_to_des.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


        VkSubpassDescription create_subpass_info{};
        create_subpass_info.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        create_subpass_info.colorAttachmentCount = 1;
        create_subpass_info.pColorAttachments = &create_reference_to_des;


        VkSubpassDependency create_subpass_depen{};
        create_subpass_depen.srcAccessMask = 0;
        create_subpass_depen.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        create_subpass_depen.srcSubpass = VK_SUBPASS_EXTERNAL;
        create_subpass_depen.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        create_subpass_depen.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        create_subpass_depen.dstSubpass = 0;




        VkRenderPassCreateInfo render_pass_info_struct{};
        render_pass_info_struct.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        render_pass_info_struct.attachmentCount = 1;
        render_pass_info_struct.pAttachments = &create_description_info;
        render_pass_info_struct.subpassCount = 1;
        render_pass_info_struct.pSubpasses = &create_subpass_info;
        render_pass_info_struct.dependencyCount = 1;
        render_pass_info_struct.pDependencies = &create_subpass_depen;


        if(vkCreateRenderPass(logicaldevice,&render_pass_info_struct,nullptr,&renderpass)!=VK_SUCCESS){
            throw std::runtime_error("the rendrpass coudn't be created");
        }
        else{
            std::cout<<"Renderpass applied to the vulkan swapchain and surface"<<std::endl;
        }




    }
    RenderPass::~RenderPass(){
        //destroy the renerpassinstance crated
        if(renderpass!=VK_NULL_HANDLE){
            vkDestroyRenderPass(logicaldevice,renderpass,nullptr);
        }
    }
}


//next framebuffer
//graphics pipeline
//command pool and command buffers
//synchronization objects and semaphores


