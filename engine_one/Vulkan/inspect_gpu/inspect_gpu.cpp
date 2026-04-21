#include"inspect_gpu.h"
#include"Vulkan_Instance.h"
#include"Vulkan_physicalDevice.h"

namespace Engine{

    
    void Inspect_Gpu::Get_the_Handles(PhysicalDevice& Device,Vulkan_Instance& Instance){

        Device.allocate_the_vector_space(Instance);
        std::vector<VkPhysicalDevice> all_gpus_handles = Device.all_the_device_handles;


        //call the 'Check_gpu_features' function to get the features linked with the gpu's
        gpu_properties(all_gpus_handles);

    }


    void Inspect_Gpu::gpu_properties(std::vector<VkPhysicalDevice>& handles){
        //checck for the available properties
        for(VkPhysicalDevice& device:handles){
            VkPhysicalDeviceProperties gpu_properties;
            //fill the Features with the features of the gpu rep by the handle devcie
            vkGetPhysicalDeviceProperties(device,&gpu_properties);
            std::cout<<"gpu name:"<<gpu_properties.deviceName<<std::endl;
            std::cout<<gpu_properties.deviceName<<" has the deriver"<<gpu_properties.driverVersion<<std::endl;

            //then check for it's properties

            VkPhysicalDeviceFeatures gpu_features;
            //fill the features of the gpu
            vkGetPhysicalDeviceFeatures(device,&gpu_features);

            if(gpu_features.geometryShader){
                std::cout<<"this gpu:"<<gpu_properties.deviceName<<" has the geometry shaders"<<std::endl;

            }
            else{
                std::cout<<"the gpu: "<<gpu_properties.deviceName<<" doesn't have gemoetry shaders"<<std::endl;
            }

            //then for its QUeueIndice
            //variable to store all the queue families in a gpu
            uint32_t no_of_queue_families;

            vkGetPhysicalDeviceQueueFamilyProperties(device,&no_of_queue_families,nullptr);

            if(no_of_queue_families<1){
                std::cout<<"the no of queue families here is less than 1";
                continue;
            }

            //make a vector to hold all the queue handles
            std::vector<VkQueueFamilyProperties> queue_handles(no_of_queue_families);
            //fill it with the queue handles of this gpu
            vkGetPhysicalDeviceQueueFamilyProperties(device,&no_of_queue_families,queue_handles.data());

            for(VkQueueFamilyProperties queue_handle:queue_handles){
                if((queue_handle.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queue_handle.queueFlags & VK_QUEUE_COMPUTE_BIT)){
                    //check if the gpu is dedicated or integrated

                    if(gpu_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
                        std::cout<<"this is the favourable gpu: "<<gpu_properties.deviceName<<std::endl;
                        //push it to the list of favoured gpus
                        Gpu_Devices.push_back(device);
                    }
                }   
            } 
               
        }

    }

    //optional
    void Inspect_Gpu::check_if_single(std::vector<VkPhysicalDevice>& devices){
        if(devices.size() == 1){
            //assign the gpu handle in devcies to the gpu_handle
            gpu_handle = devices[0];
        }
        

    }

    Inspect_Gpu::~Inspect_Gpu(){
        //nothing to destroy
    }
}