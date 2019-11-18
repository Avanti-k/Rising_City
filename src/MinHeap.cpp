#include "MinHeap.h"
#include <iostream>

using namespace std;
MinHeap::MinHeap()
{
    //ctor
}

MinHeap::~MinHeap()
{
    //dtor
}

/* Heapify up */

void MinHeap::heapify_up(int index)
{
    if(index == FIRST_INDEX)
        return;

    int parent_index = (index-1)/2;
    bool is_smaller = Building::compare_executed_time(min_heap[index], min_heap[parent_index]);
    if(is_smaller)
    {
        Building* temp = min_heap[parent_index];
        min_heap[parent_index] = min_heap[index];
        min_heap[index] = temp;
        heapify_up(parent_index);
    }
}

/* Heapify down */
void MinHeap::heapify_down(int index)
{
    int length = min_heap.size();
    int left_child = 2*index + 1;
    int right_child = 2*index + 2;

    if(left_child >= length)
        return; //index is a leaf

    int smallest = index;
    bool is_smaller = Building::compare_executed_time(min_heap[left_child], min_heap[smallest]);

    if(is_smaller)
    {
        smallest = left_child;
    }
    is_smaller = Building::compare_executed_time(min_heap[right_child], min_heap[smallest]);

    if((right_child < length) && (is_smaller))
    {
        smallest = right_child;
    }

    if(smallest != index)
    {
        //need to swap
        Building * temp = min_heap[index];
        min_heap[index] = min_heap[smallest];
        min_heap[smallest] = temp;
        heapify_down(smallest); // further call recursivly
    }

}

/* copies last element to top. Used internally by remove_min */
void MinHeap::copy_last_to_top(int first, int last)
{
    min_heap[first] = min_heap[last]; // copies last element to first index
    min_heap.pop_back(); // delete the last element
}

/* inserts new building node in minheap
* return type 0 - if error like capaicuty full
*             1 - success */
int MinHeap::insert_new(Building * b)
{

    int new_index = min_heap.size();

    if(new_index == MAX_SIZE_MIN_HEAP)
    {
        // Heap already full
        cout<<"Error : Min heap capacity full\n"<<endl;
        return ERROR;
    }

    // always insert at last
    //min_heap[new_index] = &temp;
    min_heap.push_back(b);

    // might disturb the heap property of heapify up
    // starting from index = length
    heapify_up(new_index);

    cout<<"insert new inside";
    return SUCCESS;
}

/* remove min i.e top element
* and then replace last element with first and remove back*/

Building * MinHeap::remove_min()
{
    // copy min element to pointer
    Building * ret_node = min_heap.front();

    int last_index = min_heap.size() - 1;

    copy_last_to_top(FIRST_INDEX, last_index);

    // to adjust heap property
    heapify_down(FIRST_INDEX);

    return ret_node;
}
