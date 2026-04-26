#pragma once
#include "swapchain_support.h"
#include"Window.h"

namespace Engine{
    class swapchain_options{
        private:

        public:
           // SwapchainSupport::swapchain_struct new_struct; can't use that beacuse we ned and object of SwapchainSupport for that
           struct Swapchain_Options{
                VkSurfaceCapabilitiesKHR capabilities;
                VkSurfaceFormatKHR surface_format;
                VkPresentModeKHR presentMode;
           };
           Swapchain_Options selected_swapchain_options;
            VkSurfaceCapabilitiesKHR modify_the_capability_obj(VkSurfaceCapabilitiesKHR& capability_obj,Windows& window);
            VkSurfaceFormatKHR choose_the_best_format(std::vector<VkSurfaceFormatKHR>& formats);
            VkPresentModeKHR choose_the_best_present_mode(std::vector<VkPresentModeKHR>& PresentModes);
            VkExtent2D select_dimension(VkSurfaceCapabilitiesKHR& object,Windows& window);
            uint32_t min_image_count;
            swapchain_options(SwapchainSupport& object,Windows& window);
            ~swapchain_options();
    
    };
}