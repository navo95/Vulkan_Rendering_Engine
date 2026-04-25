#pragma once
#include "VulkanSurface.h"
#include "Vulkan_physicalDevice.h"
#include <vector>
#include <vulkan/vulkan.h>

// to find what presentation modes,capabilities,formats it supports for a given
// window surface

namespace Engine {
class SwapchainSupport {
private:
public:
  struct swapchain_struct {
    VkSurfaceCapabilitiesKHR
        capabilities; // this includes the no of image count and the height and
                      // width of the images
    std::vector<VkSurfaceFormatKHR> format;
    std::vector<VkPresentModeKHR> presentMode;
  };
  swapchain_struct swapchain_object;
  // querry the values for the swapchain_object from the vulkan these shall
  // contain the raw values

  SwapchainSupport(VkPhysicalDevice gpu_device, VkSurfaceKHR surface);
  ~SwapchainSupport();

  swapchain_struct fill_the_struct(VkPhysicalDevice gpu_device,VkSurfaceKHR surface);
};
} // namespace Engine