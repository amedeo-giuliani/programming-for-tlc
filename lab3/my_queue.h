#ifndef MY_QUEUE
#define MY_QUEUE

#include <queue>

template<class T>
class MyQueue{

    private:
    std::queue<T> m_queue;

    public:
    MyQueue() : m_queue() {}
    ~MyQueue() {}
    void push(T in_element) { m_queue.push(in_element); }
    bool pop(T& out_element){
        if(empty())
            return false;

        out_element = m_queue.front();
        m_queue.pop();
        return true;
    }
    bool front(T& out_element){
        if(empty())
            return false;

        out_element = m_queue.front();
        return true;
    }
    bool empty() const { return m_queue.empty(); }
    size_t size() const { return m_queue.size(); }

};

#endif
