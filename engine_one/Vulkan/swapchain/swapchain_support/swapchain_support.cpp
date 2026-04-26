#include "swapchain_support.h"
#include <vulkan/vulkan.h>

namespace Engine {
SwapchainSupport::SwapchainSupport(VkPhysicalDevice gpu_device,VkSurfaceKHR surface) {
  swapchain_object = fill_the_struct(gpu_device, surface);
}

SwapchainSupport::swapchain_struct SwapchainSupport::fill_the_struct(VkPhysicalDevice gpu_device,VkSurfaceKHR surface) {
  swapchain_struct struct_object;
  // fill in the capabilities
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu_device, surface, &struct_object.capabilities);

  // fill in the surface

  uint32_t gpu_surface_extension;

  vkGetPhysicalDeviceSurfaceFormatsKHR(gpu_device, surface, &gpu_surface_extension, nullptr);
    if (gpu_surface_extension >= 1) {
        struct_object.format.resize(gpu_surface_extension); //we need to resize them according to the no of objects/struct to be filled in them or else will cause memory overload 
        vkGetPhysicalDeviceSurfaceFormatsKHR(gpu_device, surface, &gpu_surface_extension,struct_object.format.data());
    }

  // fill in the presentation modes
  uint32_t presentmodes_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(gpu_device, surface, &presentmodes_count, nullptr);
    if (presentmodes_count >= 1) {
        struct_object.presentMode.resize(presentmodes_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(gpu_device, surface, &presentmodes_count,struct_object.presentMode.data());
    }

  return struct_object;
}

SwapchainSupport::~SwapchainSupport() {
  // nothing to destroy as no objects were created
}
} // namespace Engine