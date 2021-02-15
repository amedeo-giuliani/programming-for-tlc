#include <iostream>
#include <thread>
#include <chrono>
#include "concurrent-queue.h"


int main(int argc, char** argv){
    
    ConcQueue<int> *concq = new ConcQueue<int>();
    
    int times = 100;
    
    std::thread producer([concq,times](){
        for(int i = 1; i <= times && ! quit; i++) {
            concq->push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    std::thread consumer1([concq](int nt, std::string label){
        for(size_t i = 0; i < nt && ! quit; i++) {
            int elem;
            if(concq->wTPop(elem,std::chrono::milliseconds(0))){
                std::unique_lock<std::mutex> lck(coutmx);
                std::cout << label << elem << std::endl;
                lck.unlock();
            }
        }
    },50,"consumer1::");
    std::thread consumer2([concq](int nt, std::string label){
        for(int i = 0; i < nt && ! quit; i++) {
            int elem;
            if(concq->wTFront(elem,std::chrono::milliseconds(100))){
                std::unique_lock<std::mutex> lck(coutmx);
                std::cout << label << elem << std::endl;
                lck.unlock();
            }
        }
    },50,"consumer2::");
    
    
    
    if(consumer2.joinable())
        consumer2.join();
    if(producer.joinable())
        producer.join();
    if(consumer1.joinable())
        consumer1.join();
    
    return 0;
}
