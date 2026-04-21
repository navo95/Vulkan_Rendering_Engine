#include"Vulkan_Instance.h"
#include<iostream>
#include<stdexcept>
#include "Window.h"
#include<cstdint>
#include<stdexcept>
#include<string>

namespace Engine{
    Vulkan_Instance::Vulkan_Instance(const char* applicationname,HINSTANCE hinstance):m_hinstance(hinstance){
        Create_vulkan_instance(applicationname);


    }//vullan_instance class
    //now when the Instance object is created it also needs to be destroyed
    
    Vulkan_Instance::~Vulkan_Instance(){
        if(Get_vulkan_Instance_handle()!=VK_NULL_HANDLE){
            vkDestroyInstance(v_hInstance,nullptr);
        }
    }

    //check if the vulkan supports the validation layers provided-->function defination
    bool Vulkan_Instance::check_validation_layer_ifexists(std::vector<const char*> layer){
        //get the no of layers currently vulkan sdk holds

        uint32_t no_of_layers=0;
        vkEnumerateInstanceLayerProperties(&no_of_layers,nullptr);


        //make a vector to store the all the available layers in the vulkan sdk,we will store structs each for one layer
        std::vector<VkLayerProperties>layer_prop_structs(no_of_layers);

        //fill the vector with the layers info structs

        vkEnumerateInstanceLayerProperties(&no_of_layers,layer_prop_structs.data());
        //find if our 'validation_layers' is present there or not
        for(const char* layer_name:layer){
            bool isFound=false;
            for(VkLayerProperties layer_struct:layer_prop_structs){
                if(strcmp(layer_name,layer_struct.layerName)==0){
                    
                    isFound = true; //layer is found break the inner loop
                    
                }   

            }
            if(isFound==false){

                throw std::runtime_error("a validation layer is not found");
            }
        }
        return true;

    }
   
    


    //check if the extensions are available if yes return them
    std::vector<const char*> Get_Extensions(){

        std::vector<const char*> required_extensions={
            "VK_KHR_surface","VK_KHR_win32_surface"
        };
        #ifdef DEBUG
        required_extensions.push_back("VK_EXT_debug_utils");
        #endif()
        //now check if the vulkan supports these wxtensions
        uint32_t available_extensions;
        vkEnumerateInstanceExtensionProperties(nullptr,&available_extensions,nullptr);

        //make a vector to hold all the available extensions in the form of info structs
        std::vector<VkExtensionProperties> all_extensions(available_extensions);
        vkEnumerateInstanceExtensionProperties(nullptr,&available_extensions,all_extensions.data());
        //make an empty vector to hold only those extensions that are supported by the vulkan in your systeam
        std::vector<const char*> supported_extensions;

        //chekc if our required extensions are present there or not if yes then return them
        for(const char* ext_name:required_extensions){
            bool is_found = false;
            for(VkExtensionProperties prop:all_extensions){
                if(strcmp(ext_name,prop.extensionName)==0){
                    is_found = true;
                    
                }
            }
            if(is_found = false){
                throw std::runtime_error("a extension is absent");
            }
        }
        return required_extensions;


    }

    //now create the instance function defination
    void Vulkan_Instance::Create_vulkan_instance(const char* applicationname){
        if(check_validation_layer_ifexists(validation_layers)){
            std::vector<const char*> extensions = Get_Extensions();
            if(sizeof(extensions)==0){
                throw std::runtime_error("no extenisons to add to the vulkan instance");
            }

            //create the application info
            VkApplicationInfo appinfo{};

              appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
              
              appinfo.pApplicationName = applicationname;
              appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
              appinfo.pEngineName = "No Engine";
              appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
              appinfo.apiVersion = VK_API_VERSION_1_0;

            //create the vulkan create info
            VkInstanceCreateInfo createinfo{};

            createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            
            createinfo.pApplicationInfo = &appinfo;
            createinfo.enabledExtensionCount = extensions.size();
            createinfo.ppEnabledExtensionNames = extensions.data();
            createinfo.ppEnabledLayerNames = validation_layers.data();
            createinfo.enabledLayerCount = 0;
            
            //create the instance
            if(vkCreateInstance(&createinfo,nullptr,& v_hInstance)!=VK_SUCCESS){
                throw std::runtime_error("error ocured in creation of the Vulkan instance");
                
            }


        }

    }

}//namespace Engine