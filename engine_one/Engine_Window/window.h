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
        const char* Title;
        uint32_t m_width;
        uint32_t m_height;
        bool m_ShouldRunning= true;

        static LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wparam,LPARAM lparam);

        public:
        Windows(const char* title,uint32_t width,uint32_t height);
        ~Windows();

        HWND get_hwnd(){return m_hwnd;}

        void Process_Messages();

        HINSTANCE get_hinstance(){return m_hinstance;}


    };

}