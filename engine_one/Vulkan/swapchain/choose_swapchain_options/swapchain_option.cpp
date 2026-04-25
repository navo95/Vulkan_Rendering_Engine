#include "swapchain_option.h"
#include<algorithm>
#include "Window.h"
#include<windows.h>

namespace Engine{
    swapchain_options::swapchain_options(SwapchainSupport& object,Windows& window){
        //object.swapchain_object

        //querry for the capabilities ie modify the default capabilities of the swapchain_object.capabilities returned by vulkan
        //object.swapchain_object.capabilities

        selected_swapchain_options.capabilities = modify_the_capability_obj(object.swapchain_object.capabilities,window);
        //querry for the formats
        //object.swapchain_object.format
        //select the preferred format from the default vector of the formats given by the vulkan
        selected_swapchain_options.surface_format = choose_the_best_format(object.swapchain_object.format);


        //querry for the presentModes 
        //object.swapchain_object.presentMode
        //select the preferred presentMode from the default vector of presentModes given by the vulkan
        selected_swapchain_options.presentMode = choose_the_best_present_mode(object.swapchain_object.presentMode);
        

        //after these functions being executed the SwapchainSupport::swapchain_struct new_struct shall only contain the filtered values

    }


    VkSurfaceCapabilitiesKHR swapchain_options::modify_the_capability_obj(VkSurfaceCapabilitiesKHR& capability_obj,Windows& window){
        VkSurfaceCapabilitiesKHR capabilities; //empty currentlly

        //use the default width and height if setted
        if(capability_obj.currentExtent.width!=UINT32_MAX){

            capabilities.currentExtent = capability_obj.currentExtent; //always use the default width and height
            
        }
        else{

            capabilities.currentExtent = select_dimension(capability_obj,window);

        }
        //choose the no of images that could be displayed
        uint32_t image_count = capability_obj.minImageCount + 1;
        if(capability_obj.maxImageCount>0 && image_count>capability_obj.maxImageCount){
            image_count = capability_obj.maxImageCount;
            min_image_count = image_count;

        }


        capabilities.minImageCount = image_count;
        min_image_count = image_count;

        return capabilities;

    }


    VkSurfaceFormatKHR swapchain_options::choose_the_best_format(std::vector<VkSurfaceFormatKHR>& format){

        VkSurfaceFormatKHR Format; //currentlly empty

        for(VkSurfaceFormatKHR& format_data : format){
            if(format_data.format == VK_FORMAT_B8G8R8A8_SRGB && format_data.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
                Format = format_data;
            }   
        }
        return Format;

    }

    VkPresentModeKHR swapchain_options::choose_the_best_present_mode(std::vector<VkPresentModeKHR>& presentMode){

        VkPresentModeKHR PresentMode; //currentlly empty
        for(VkPresentModeKHR& modes: presentMode){
            if(modes == VK_PRESENT_MODE_MAILBOX_KHR){ //best
                PresentMode = modes;
                return PresentMode;

            }
        }
        //fallback
        PresentMode = VK_PRESENT_MODE_FIFO_KHR;
        return PresentMode;


        

    }

    VkExtent2D swapchain_options::select_dimension(VkSurfaceCapabilitiesKHR& capability_obj,Windows& window){

        VkSurfaceCapabilitiesKHR capabilities; //empty currentlly
        //get the window width and height
        RECT rect;
        HWND hwnd = window.get_hwnd();

        //get the height and widht of the client window
        GetClientRect(hwnd,&rect);
        uint32_t width = rect.top - rect.left;
        uint32_t height = rect.bottom - rect.right;

        VkExtent2D dimensions = {width,height};

        if(dimensions.width < capability_obj.minImageExtent.width){
            dimensions.width = capability_obj.minImageExtent.width;
        }
        else if(dimensions.width >capability_obj.maxImageExtent.width){
            dimensions.width = capability_obj.maxImageExtent.width;
        }


        if(dimensions.height < capability_obj.minImageExtent.height){
            dimensions.height = capability_obj.minImageExtent.height;
        }
        else if(dimensions.height > capability_obj.maxImageExtent.height){
            dimensions.height = capability_obj.maxImageExtent.height;
        }

        capabilities.currentExtent = {dimensions.width,dimensions.height};
        return capabilities.currentExtent;

    }

    swapchain_options::~swapchain_options(){
        //nothing to estroyno instance created
    }


}