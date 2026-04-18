#include<iostream>
#include<stdexcept>
#include "window.h"

int main() {

	try{
		//get the window loop running
		Engine::Windows Window("Vulkan Rendering Engine",1400,900);
		//now get the Process_Messages() function
		Window.Process_Messages();


	}
	catch(std::runtime_error& e){
		std::cerr<<e.what()<<std::endl;
		return -1;
	}



	return 0;
}