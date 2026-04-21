#include"Vulkan_physicalDevice.h"
#include "Vulkan_Instance.h"

namespace Engine{
    void PhysicalDevice::check_for_devices(Vulkan_Instance& Instance){
        vkEnumeratePhysicalDevices(Instance.Get_vulkan_Instance_handle(),&no_of_devices,nullptr);
        if(no_of_devices == 0){
            throw std::runtime_error("no gpus are present in this computer");
        }
    }

    void PhysicalDevice::allocate_the_vector_space(Vulkan_Instance& Instance){
        check_for_devices(Instance); //call this function to get the value of the 

        all_the_device_handles.resize(no_of_devices);

        if(vkEnumeratePhysicalDevices(Instance.Get_vulkan_Instance_handle(),&no_of_devices,all_the_device_handles.data())!=VK_SUCCESS){
            throw std::runtime_error("the handles coudn't be retrieved");

        };
        

    }   
    PhysicalDevice::~PhysicalDevice(){
       //nothing to destroy we didn't created anyhting just the physical devcie selected


    }
}