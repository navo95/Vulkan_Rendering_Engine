#include"logical_device.h"
#include<stdexcept>
#include<iostream>

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
        

        //now create the logical device
        //create the info struct
        VkDeviceCreateInfo createInfo={};

        createInfo.sType =VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queues_vector.size());
        createInfo.pQueueCreateInfos = queues_vector.data();
        createInfo.pEnabledFeatures = &this_supported_gpu_features;


        //create the logical device handle
        if(vkCreateDevice(gpu_handle,&createInfo,nullptr,&logical_device)!=VK_SUCCESS){
            throw std::runtime_error("the logical device codn't be created");
        }
        else{
            std::cout<<"logical device created successfully"<<std::endl;
        }


    }

    //destroy the logical devie created
    LogicalDevice::~LogicalDevice(){
        if(logical_device!=VK_NULL_HANDLE){
            vkDestroyDevice(logical_device,nullptr);
            std::cout<<"the logical device is destroyed succesfully"<<std::endl;

        }
    }
}