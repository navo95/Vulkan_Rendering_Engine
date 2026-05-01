#include "VulkanSurface.h"
#include "Vulkan_Instance.h"
#include "Vulkan_physicalDevice.h"
#include "gpu_querry.h"
#include "inspect_gpu.h"
#include "logical_device.h"
#include "queueInfo.h"
#include "queue_handle.h"
#include "window.h"
#include <iostream>
#include <stdexcept>
#include "swapchain_support.h"
#include"swapchain_option.h"
#include"swapchain_instance.h"
#include"swapchain_images.h"
#include"swapchain_image_view.h"
#include"render_pass.h"



int main() {

  try {
    //--non-repetative tasks to be done once----------------
    // get the window loop running

    Engine::Windows Window("Vulkan Rendering Engine", 1400, 900);
    // create the vulkan Instance
    Engine::Vulkan_Instance m_Instance("vulkan Engine", GetModuleHandle(nullptr)); // it creates the instance

    // connect the instace to the  surface
    Engine::VulkanSurface Vulkan_Window_Surface(Window, m_Instance);
    // select the physical device
    Engine::PhysicalDevice physicaldevice;
    physicaldevice.allocate_the_vector_space(m_Instance);

    // get the  vector of the selected physical devices
    Engine::Inspect_Gpu getting_desired_gpu;
    getting_desired_gpu.Get_the_Handles(physicaldevice, m_Instance);

    getting_desired_gpu.check_if_single(getting_desired_gpu.Gpu_Devices);

    VkPhysicalDevice global_gpu_handle =
        getting_desired_gpu.gpu_handle; /// global gpu handle for this Engine
    // now get the Queue Indices of the selected gpu
    // gpu_querry(Inspect_Gpu& inspect_gpu,VulkanSurface& surface);
    Engine::gpu_querry Queue_Indices(getting_desired_gpu, Vulkan_Window_Surface);
    Engine::Queue_Info_Struct queue_info_struct(Queue_Indices);

    // make the queues_Info_struct public globally
    // public vector

    std::vector<VkDeviceQueueCreateInfo> queue_Family_InfoStructs =
        queue_info_struct.queueFamilyInfoStructs;

    Engine::LogicalDevice logical_device(global_gpu_handle, queue_Family_InfoStructs);
    Engine::QueueHandle queue_handle_object(Queue_Indices,logical_device); // we only need the  Queue_Handles m_queue_handles={};
    // ie the handle to the gpu queues

    // since we have selected the queue familly at indice 0 we can just use any
    // of the one of queue_handle_object.m_queue_handles.presenthandle
    // ..or...m_queue_handles.transferhandle etc bcs they all point to the same
    // queufamilly

    //get the color,format and capabilites of the images from the vulkan for the swapchain creation
    
    Engine::SwapchainSupport raw_values(global_gpu_handle,Vulkan_Window_Surface.Get_surface_khr());
    //querry the given values by vulkan for the best ones
    Engine::swapchain_options filtered_values(raw_values,Window);
    //queeired value
    
    std::cout<<"capabilities->width:"<<filtered_values.selected_swapchain_options.capabilities.currentExtent.width<<std::endl;
    std::cout<<"capabilities->height: "<<filtered_values.selected_swapchain_options.capabilities.currentExtent.height<<std::endl;
    std::cout<<"no of images that can be displayed in the swapchain:"<<filtered_values.min_image_count<<std::endl;
    std::cout<<"the filterred format for pixel format is:"<<filtered_values.selected_swapchain_options.surface_format.format<<std::endl;
    std::cout<<"the filtered forma for the coloSpace is  "<<filtered_values.selected_swapchain_options.surface_format.colorSpace<<std::endl;
    std::cout<<"the filtered present mode is "<<filtered_values.selected_swapchain_options.presentMode<<std::endl;

    //creating the swapchain Instance

    //swapchain_instance(LogicalDevice& Logical_Device,VulkanSurface& surface,swapchain_options& swapchain_options_object,QueueHandle& queue_handle)
    
    Engine::swapchain_instance swapchain(logical_device,Vulkan_Window_Surface,filtered_values,queue_handle_object);

    //get the swapchain images
    uint32_t no_of_swapchain_images;
    std::vector<VkImage> Raw_Images;

    Engine::Get_Swapchain_Images get_swapchain_images(swapchain,logical_device,no_of_swapchain_images);
    Raw_Images.resize(no_of_swapchain_images);

    Raw_Images = get_swapchain_images.all_the_images;

    if(Raw_Images.size()>0){
        for(const auto& image_handle:Raw_Images){
        std::cout<<"image_handle: "<<image_handle<<std::endl;
    }
    }
    else{
      throw std::runtime_error("image handles to the swapchain_images not done");
    }
    //now create  the VkImageView for each for the corresponding VkImage .this step is to be done only once
    
    Engine::swapchain_image_view VkImage_gpu_ins(Raw_Images,filtered_values,logical_device);
    //the VkImage instructions per VkImage in he vector for are

    std::vector<VkImageView> VkImage_gpu_instructions; //------------------------------->gpu instructions per VkImage
    VkImage_gpu_instructions.resize(VkImage_gpu_ins.Get_ImageView().size());
    VkImage_gpu_instructions = VkImage_gpu_ins.Get_ImageView();
    //--Render pass---------------------------------------------------
    //the blueprint for the gpu tom draw into the VkImage
    Engine::RenderPass(logical_device,filtered_values);
    
    // -----non-repetative tasks to be done-------------------
    // once----------------------------------------
    // now get the Process_Messages() function
    Window.Process_Messages();

  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}