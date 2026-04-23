#include "queue_handle.h"
#include <utility>
#include<iostream>

namespace Engine{
    QueueHandle::QueueHandle(gpu_querry& queue_indices,LogicalDevice& logical_device_object){
        std::cout<<"Getting the Queue-handles"<<std::endl;

        Queue_Indices m_Queue_Indices={};
        m_Queue_Indices.graphics_indice = queue_indices.graphics_queue_familly_indice;
        m_Queue_Indices.present_indice = queue_indices.present_queue_family_indice;
        m_Queue_Indices.transfer_indice = queue_indices.transfer_queue_family_indice;
        m_Queue_Indices.compute_indice = queue_indices.compute_queue_family_indice;


        m_queue_indices = std::move(m_Queue_Indices); //tranfer to the global indices struct ibject

        Queue_Handles queue_handles={};

        if(m_queue_indices.graphics_indice){
            vkGetDeviceQueue(logical_device_object.logical_device,m_queue_indices.graphics_indice,0,&queue_handles.graphicshandle);

            
        }
        if(m_queue_indices.present_indice){
            vkGetDeviceQueue(logical_device_object.logical_device,m_queue_indices.present_indice,0,&queue_handles.presenthandle);
        }
        if(m_queue_indices.compute_indice){
            vkGetDeviceQueue(logical_device_object.logical_device,m_queue_indices.compute_indice,0,&queue_handles.computehandle);
        }
        if(m_queue_indices.transfer_indice){
            vkGetDeviceQueue(logical_device_object.logical_device,m_queue_indices.transfer_indice,0,&queue_handles.transferhandle);
        }


        m_queue_handles = std::move(queue_handles); //transfer to the global handles struct object



    }
    QueueHandle::~QueueHandle(){
        if(m_queue_handles.computehandle!=VK_NULL_HANDLE){
            delete m_queue_handles.computehandle;
            m_queue_handles.computehandle = nullptr;
        
        }
        if(m_queue_handles.graphicshandle!=VK_NULL_HANDLE){
            delete m_queue_handles.graphicshandle;
            m_queue_handles.computehandle = nullptr;
        }
        if(m_queue_handles.transferhandle!=VK_NULL_HANDLE){
            delete m_queue_handles.transferhandle;
            m_queue_handles.transferhandle = nullptr;
        }
        if(m_queue_handles.presenthandle!=VK_NULL_HANDLE){
            delete m_queue_handles.presenthandle;
            m_queue_handles.presenthandle  = nullptr;

        }
    }


}

