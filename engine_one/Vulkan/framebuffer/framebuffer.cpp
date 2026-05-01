#include"framebuffer.h"
#include<stdexcept>

namespace Engine{
    FrameBuffer::FrameBuffer(LogicalDevice& logical_Device,swapchain_options& Swapchain_Options,swapchain_image_view& image_view,RenderPass& render_pass,Get_Swapchain_Images& swapchain_images):Logical_Device(logical_Device){
        std::cout<<"creating the framebuffer objects for each VkImage"<<std::endl;
        //retrieving the VkImages
        std::vector<VkImage> V_K_Images = swapchain_images.all_the_images; //not std::vector<VkImage>& V_K_Images  beacuse the return type of rhs is a copy 

        //retrieving the VkImageViews-->this is where the frambuffer will attach the Renderpass onto 

        std::vector<VkImageView> V_K_Image_Views = image_view.Get_ImageView(); //not std::vector<VkImageView>& V_K_Image_Views beacuse the rhs return type is a copy


        //get the window context dimensions

        VkExtent2D frame_buffer_window_extent  = Swapchain_Options.selected_swapchain_options.capabilities.currentExtent;


        swapchain_framebuffers.resize(V_K_Image_Views.size());//get the vector to contain the framebuffers ready

        
        //prepare frambuffer objects for each of the VkImageViews
        int i=0;
        for(VkImageView& Images:V_K_Image_Views){
            VkImageView image_view_array[] = {Images};
            VkFramebufferCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            createInfo.renderPass = render_pass.Get_Render_pass();

            createInfo.attachmentCount = 1;
            createInfo.pAttachments = image_view_array;//had to pass here an array containing the VkImageView
            createInfo.width= frame_buffer_window_extent.width;
            createInfo.height = frame_buffer_window_extent.height;
            createInfo.layers = 1;

            if(vkCreateFramebuffer(Logical_Device.logical_device,&createInfo,nullptr,&swapchain_framebuffers[i])!=VK_SUCCESS){
                throw std::runtime_error("the frambuffer coudn't be creted ");
            }
            else if(i+1==V_K_Image_Views.size()){
                std::cout<<"frambuffer objects created for each of the VKImageViews";
            }

        }




    }//FrameBuffer cons

    FrameBuffer::~FrameBuffer(){
        for(VkFramebuffer& framebuffer_obj:swapchain_framebuffers){
            vkDestroyFramebuffer(Logical_Device.logical_device,framebuffer_obj,nullptr);
        }



    }//framebuffer dest
}