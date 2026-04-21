#include<iostream>
#include<stdexcept>
#include "window.h"
#include"Vulkan_Instance.h"
#include"VulkanSurface.h"
#include"Vulkan_physicalDevice.h"
#include"inspect_gpu.h"

int main() {

	try{
		//get the window loop running
		Engine::Windows Window("Vulkan Rendering Engine",1400,900);
		//create the vulkan Instance
        Engine::Vulkan_Instance m_Instance("vulkan Engine",GetModuleHandle(nullptr)); //it creates the instance

		//connect the instace to the  surface
		Engine::VulkanSurface Vulkan_Window_Surface(Window,m_Instance);
		//select the physical device
		Engine::PhysicalDevice physicaldevice;
		physicaldevice.allocate_the_vector_space(m_Instance);

		//get the  vector of the selected physical devices
		Engine::Inspect_Gpu getting_desired_gpu;
		getting_desired_gpu.Get_the_Handles(physicaldevice,m_Instance);

		getting_desired_gpu.check_if_single(getting_desired_gpu.Gpu_Devices);

		VkPhysicalDevice global_gpu_handle = getting_desired_gpu.gpu_handle;  ///global gpu handle for this Engine
		
		
		//now get the Process_Messages() function
		Window.Process_Messages();

		



	}
	catch(std::runtime_error& e){
		std::cerr<<e.what()<<std::endl;
		return -1;
	}



	return 0;
}