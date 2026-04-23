#include<iostream>
#include<stdexcept>
#include "window.h"
#include"Vulkan_Instance.h"
#include"VulkanSurface.h"
#include"Vulkan_physicalDevice.h"
#include"inspect_gpu.h"
#include "gpu_querry.h"
#include "queueInfo.h"
#include "logical_device.h"
#include "queue_handle.h"

int main() {

	try{
		//--non-repetative tasks to be done once----------------
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
		//now get the Queue Indices of the selected gpu
		//gpu_querry(Inspect_Gpu& inspect_gpu,VulkanSurface& surface);
		Engine::gpu_querry  Queue_Indices(getting_desired_gpu,Vulkan_Window_Surface);
		Engine::Queue_Info_Struct queue_info_struct(Queue_Indices);

		//make the queues_Info_struct public globally
		//public vector
		
		std::vector<VkDeviceQueueCreateInfo> queue_Family_InfoStructs = queue_info_struct.queueFamilyInfoStructs; 

		Engine::LogicalDevice logical_device(global_gpu_handle,queue_Family_InfoStructs);	
		Engine::QueueHandle queue_handle_object(Queue_Indices,logical_device); //we only need the  Queue_Handles m_queue_handles={}; ie the handle to the gpu queues

		//since we have selected the queue familly at indice 0 we can just use any of the one of queue_handle_object.m_queue_handles.presenthandle ..or...m_queue_handles.transferhandle etc 
		//bcs they all point to the same queufamilly
		




		// -----non-repetative tasks to be done once----------------------------------------
		//now get the Process_Messages() function
		Window.Process_Messages();

	}
	catch(std::runtime_error& e){
		std::cerr<<e.what()<<std::endl;
		return -1;
	}

	return 0;
}