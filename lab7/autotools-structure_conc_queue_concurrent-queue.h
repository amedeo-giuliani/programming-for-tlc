#ifndef H_CONCQ
#define H_CONCQ

#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

std::mutex coutmx;
std::atomic<bool> quit(false);

template<typename T>
class ConcQueue {
    public:
    ConcQueue() : queue{}, qmx{}, cv{}, {}
    ~ConcQueue() {
        quit = true;
        cv.notify_all();
    }
    
    bool wPop(T& i) {
        std::unique_lock<std::mutex> lck(qmx);
        cv.wait(lck,[&] {
            return quit || ! queue.empty();
        });
        if(queue.empty()) {
            return false;
        }
        i = queue.front();
        queue.pop();
        return true;
    }
    
    bool wTPop(T& i, std::chrono::milliseconds t_o) {
        std::unique_lock<std::mutex> lck(qmx);
        if(!cv.wait_for(lck,t_o,[&] {return quit || ! queue.empty();})){
            std::unique_lock<std::mutex> lck1(coutmx);
            std::cout << "Time out" << std::endl;
            lck1.unlock();
            return false;
        }
        if(queue.empty()) {
            return false;
        }
        i = queue.front();
        queue.pop();
        return true;
    }
    
    bool wFront(T& i) { 
        std::unique_lock<std::mutex> lck(qmx);
        cv.wait(lck,[&] {
            return quit || ! queue.empty();
        });
        if(queue.empty()) {
            return false;
        }
        i = queue.front();
        return true; 
    }
    
    bool wTFront(T& i, std::chrono::milliseconds t_o){
        std::unique_lock<std::mutex> lck(qmx);
        if(!cv.wait_for(lck,t_o,[&] {return quit || ! queue.empty();})){
            std::unique_lock<std::mutex> lck1(coutmx);
            std::cout << "Time out" << std::endl;
            lck1.unlock();
            return false;
        }
        if(queue.empty()) {
            return false;
        }
        i = queue.front();
        return true;
    }
            
    void push(T i) { 
        std::unique_lock<std::mutex> lck(qmx);
        queue.push(i);
        lck.unlock();
        cv.notify_one();
    }
    
    bool pop(T& i) {
        if(queue.empty())
            return false;
            
        i = queue.front();
        queue.pop();
        return true;
    }
    
    bool front(T& i) {
        if(queue.empty())
            return false;
            
        i = queue.front();
        return true;
    }
    
    private:
    std::queue<T> queue;
    std::mutex qmx;
    std::condition_variable cv;
};

#endif
