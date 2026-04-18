#pragma once

#ifndef WINDOW_LEAN_AND_MEAN
#define WINDOW_LEAN_AND_MEAN
#endif()
#include<windows.h>
#include<functional>
#include<cstdint>




namespace Engine{

    class Windows{
        private:
        HWND m_hwnd;
        HINSTANCE m_hinstance;
        static LRESULT WndProc(HWND hwnd,UINT uMsg,WPARAM wparam,LPARAm lparam);

        public:

        HWND get_hwnd(){return m_hwnd;}

        void Process_Messages();

        HINSTANCE get_hinstance(){return m_hinstance;}




    };

}