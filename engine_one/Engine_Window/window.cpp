#include "window.h"
#include<stdexcept>
#include "Vulkan_Instance.h"

namespace Engine{

    LRESULT CALLBACK Windows::WndProc(HWND hwnd,UINT uMsg,WPARAM wparam,LPARAM lparam){
        switch(uMsg){
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            case WM_CLEAR:
                PostQuitMessage(0);
                return 0;
            
            default :
                return DefWindowProc(hwnd,uMsg,wparam,lparam);
        }
    }
    
    Windows::Windows(const char* title,uint32_t width,uint32_t height):Title(title),m_width(width),m_height(height),m_hinstance(GetModuleHandle(nullptr)){
        //these events shall fire the moment a window class is formed
        //register the widnow

        WNDCLASS wc= {};

        wc.lpfnWndProc = &WndProc; //required
        wc.style = CS_HREDRAW| CS_VREDRAW;  //changes the entire widow accordinglly  if a change in the height or width occurs
        wc.cbClsExtra = 0; //field for extra memeory

        wc.lpszClassName = "Vulkan basic Renderer"; //register window name

        wc.hInstance  = m_hinstance; //rrequired
        wc.hbrBackground = CreateSolidBrush(134);
        

        //register the class
        RegisterClass(&wc);

        //set the window coordinates/dimensions 
        RECT rect = {0,0,m_width,m_height};
        AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,FALSE);

        //create the window

        m_hwnd = CreateWindowExA(

            0,
            "Vulkan basic Renderer",
            Title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,

            rect.right-rect.left,//widht ofthe  window
            rect.bottom-rect.top, //height of the window

            NULL,
            NULL,
            m_hinstance,
            NULL
        );

        //check if the window is created

        if(!m_hwnd){
            throw std::runtime_error("window creation failled");

        }
        //display the window
        ShowWindow(m_hwnd,SW_SHOW);


    }

    Windows::~Windows(){
        //a window object must have been created in the main or somewhere we need to clean that up for that the destroyer
        if(m_hwnd){
            DestroyWindow(m_hwnd);
            m_hwnd=nullptr;
            //unresgister the m_hinstance
            UnregisterClassA(Title,m_hinstance);
        }
    }
    //after ShowWindow
    void Windows::Process_Messages(){
        //get the loop 
        while(m_ShouldRunning){
            MSG msg{};
            PeekMessage(&msg,m_hwnd,0,0,PM_REMOVE);
            if(msg.message == WM_QUIT){
                m_ShouldRunning=false;
            }
            else{
                //start the game loop
                
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

}//namespace Engine