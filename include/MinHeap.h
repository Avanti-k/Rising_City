#ifndef MINHEAP_H
#define MINHEAP_H
#include "Building.h"
#include <vector>

#define MAX_SIZE_MIN_HEAP 2000
#define FIRST_INDEX 0

using namespace std;
enum error{
    ERROR,
    SUCCESS
};

class MinHeap
{
    public:
        MinHeap();
        virtual ~MinHeap();
        /* inserts new node at end of vector and and then
        * call heapify_up to adjust heap property */
        int insert_new(Building *);

        /* Remove min - pop topmost node and return it
        It will replace last element with node and then do heapify_down*/
        Building * remove_min();
        // Planning to make it a vector of RBTree pointers
        vector <Building *> min_heap;

    //protected:

    //private:

    /*when you insert new element and last then check if it has to go up*/
    void heapify_up(int index);

    /*when you do remove min, replace it with last element and delete last
    the new top i.e first might be larger so heapify downwards*/
    void heapify_down(int index);

    void copy_last_to_top(int first, int last);


};

#endif // MINHEAP_H
