#include <iostream>
#include "my_queue.h"

using namespace std;

int main(int argc, char** argv){

    MyQueue<int> q;
    for(int i=0; i<4; i++)
        q.push(i);

    int oe,ie=2;

    bool ok1 = q.pop(oe);
    cout << oe << endl;
    bool ok2 = q.pop(oe);
    cout << oe << endl;

    q.push(ie);
    q.front(oe);
    cout << oe << endl;

    return 0;

}
