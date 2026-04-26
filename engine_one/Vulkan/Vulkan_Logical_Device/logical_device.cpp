#include"logical_device.h"
#include<stdexcept>
#include<iostream>
#include<functional>

namespace Engine{
    LogicalDevice::LogicalDevice(VkPhysicalDevice& gpu_handle,std::vector<VkDeviceQueueCreateInfo>& queues_vector){
        //create the info struct to  enable/disable gppu features
        VkPhysicalDeviceFeatures device_features = {};

        //fill the struct with all the gpu features vulkan enables the user to on/off on the gpu
        vkGetPhysicalDeviceFeatures(gpu_handle,&device_features);

        //now check which of all the features in the device_features your gpu actually supports


        //creat a different VkPhysicalDeviceFeatures to hold on to the features actually supported by your gpu

        VkPhysicalDeviceFeatures this_supported_gpu_features={};

        
        if(device_features.samplerAnisotropy){
            this_supported_gpu_features.samplerAnisotropy  = VK_TRUE;
        }

        if(device_features.fillModeNonSolid){
            this_supported_gpu_features.fillModeNonSolid = VK_TRUE;
        }
        //get the extensions required by our gpu to create the swapchain feature
        std::vector<const char*> swapchain_gpu_ext= {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
        

        };

        //check if the gpu supports these extensions

        uint32_t gpu_ext_all;

        vkEnumerateDeviceExtensionProperties(gpu_handle,nullptr,&gpu_ext_all,nullptr);

        std::vector<VkExtensionProperties> all_the_extensions(gpu_ext_all);

        vkEnumerateDeviceExtensionProperties(gpu_handle,nullptr,&gpu_ext_all,all_the_extensions.data());

        //check if the required ext is present in the 'all_the_extensions'
        bool is_found  = false;
        for(VkExtensionProperties prop_struct:all_the_extensions){
            
            for(const char* name:swapchain_gpu_ext){
                if(strcmp(prop_struct.extensionName,name)==0){
                    is_found = true;
                }
            }
        }
        

        //now create the logical device
        //create the info struct
        VkDeviceCreateInfo createInfo={};

        createInfo.sType =VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queues_vector.size());
        createInfo.pQueueCreateInfos = queues_vector.data();
        createInfo.pEnabledFeatures = &this_supported_gpu_features;

        if(is_found){  //not applying
            const char* extension_array[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};  //array form of the previous extension vector
            std::cout<<"implementing the  'VK_KHR_SWAPCHAIN_EXTENSION_NAME' to the logical device creation"<<std::endl;

            createInfo.enabledExtensionCount = static_cast<uint32_t>(swapchain_gpu_ext.size());

            createInfo.ppEnabledExtensionNames  = extension_array; //always in the array format

        } 


        //create the logical device handle
        if(vkCreateDevice(gpu_handle,&createInfo,nullptr,&logical_device)!=VK_SUCCESS){
            throw std::runtime_error("the logical device couldn't be created");
        }
        else{
            std::cout<<"logical device created successfully"<<std::endl;
        }


    }

    //destroy the logical devie created
    LogicalDevice::~LogicalDevice(){ //not applying
        if(logical_device!=VK_NULL_HANDLE){
            vkDestroyDevice(logical_device,nullptr);
            std::cout<<"the logical device is destroyed succesfully"<<std::endl;

        }
    }
}