#include <iostream>
#include <fstream>
#include "Building.h"
#include "MinHeap.h"
#include "RBTree.h"

using namespace std;

#define MAX_EXEC_TIME 5

/* function to input file*/
/*
int input_read()
{
   har data[100];
    ifstream ip_file;
    ip_file.open("../project_material/input.txt");
    string line;
    while (getline(ip_file, line)) {
        // using printf() in all tests for consistency
        printf("%s\n", line.c_str());
    }

    return 0;

}
*/

int main()
{
    cout << "Hello world!" << endl;
    MinHeap MH;
    RBTree RBT;
    Building b(7,30, 7);
    Building b1 (6,10 ,6);
    Building b2 (5,40, 5);
    Building b3 (4,20,4);
    Building b4 (3,50,3);
    Building b5 (2,50,2);
    Building b6 (1,50,1);


    RBNode r(&b);
    RBT.RBTree_insert(&r);
    MH.insert_new(&r);

    //MH.print_min_heap();

    RBNode r1(&b1);
    RBT.RBTree_insert(&r1);
    MH.insert_new(&r1);
    //MH.print_min_heap();


    RBNode r2(&b2);
    RBT.RBTree_insert(&r2);
    MH.insert_new(&r2);
    //MH.print_min_heap();


    RBNode r3(&b3);
    RBT.RBTree_insert(&r3);
    MH.insert_new(&r3);
    //MH.print_min_heap();


    RBNode r4(&b4);
    RBT.RBTree_insert(&r4);
    MH.insert_new(&r4);
    //MH.print_min_heap();


    RBNode r5(&b5);
    RBT.RBTree_insert(&r5);
    MH.insert_new(&r5);
    //MH.print_min_heap();


    RBNode r6(&b6);
    RBT.RBTree_insert(&r6);
    MH.insert_new(&r6);

    MH.print_min_heap();
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
    }
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }

    RBNode * min_node = MH.remove_min();
    cout<<"1) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
}
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }
    min_node = MH.remove_min();
    cout<<"2) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
    }
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }


    min_node = MH.remove_min();
    cout<<"3) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
}
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }

    min_node = MH.remove_min();
    cout<<"4) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
}
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }


    min_node = MH.remove_min();
    cout<<"5) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
}
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }


    min_node = MH.remove_min();
    cout<<"6) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
    }
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }

    min_node = MH.remove_min();
    cout<<"7) Removed min Bldg no : "<<min_node->get_building()->building_num<<" Exec time : "<<min_node->get_building()->get_executed_time()<<endl;
    MH.print_min_heap();
    RBT.deleteNode(min_node);
    if(RBT.RBRoot != NULL)
    {
    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
    }
    else{
        cout<<"\nRB TREE is empty"<<endl;
    }

/*
    //RBT.deleteByVal(4);
    //RBT.deleteNode(&r3);
    RBNode * remove_ptr = MH.remove_min();
    RBT.deleteNode(remove_ptr);
    cout<<" !! AFTER REMOVE MIN 1!!"<<endl;
    MH.print_min_heap();
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;



    //RBT.deleteByVal(2);
    //RBT.deleteNode(&r5);
    remove_ptr = MH.remove_min();
    RBT.deleteNode(remove_ptr);
    cout<<" !! AFTER REMOVE MIN 2 !!"<<endl;
    cout<<"\n ---------------- Printing tree in order ------------------"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\n -------------- Level order tree --------------------------"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    cout<<"\n-----------------------------------------------------"<<endl;
*/

    //RBNode r1(&b1, nullptr,nullptr,nullptr,BLACK);
    //RBTree_insert(&r1);
    //cout<<"done"<<endl;
   /* mh.insert_new(&b);
    mh.insert_new(&b1);
    mh.insert_new(&b2);
    mh.insert_new(&b3);
    mh.insert_new(&b4);


    cout<<" 0: "<<mh.min_heap[0]->building_num<<endl;
    cout<<" 1: "<<mh.min_heap[1]->building_num<<endl;
    cout<<" 2: "<<mh.min_heap[2]->building_num<<endl;
    cout<<" 3: "<<mh.min_heap[3]->building_num<<endl;
    cout<<" 4: "<<mh.min_heap[4]->building_num<<endl;

    for( int i = 0; i < mh.min_heap.size(); i ++)
    {
        cout<<i<<" = "<< mh.min_heap[i]->building_num<<endl;
    }

    /*int bid = b.Building::get_building_num();
    cout << "bid = "<<bid<<endl;
    cout<<" total time = "<<b.Building::get_total_time();
    cout<<"exec time = "<< b.Building::get_executed_time();
    */
   /* Building * temp = mh.remove_min();
    cout<< "Removed min building id = "<< temp->building_num<< "ET = "<<temp->executed_time<<endl;


    for( int i = 0; i < mh.min_heap.size(); i ++)
    {
        cout<<i<<" = "<< mh.min_heap[i]->building_num<<endl;
    }*/

    return 0;
}

/*
void executeBuilding(int bid)
{
 int start = global_timer;
 int target = bid.completeion_time - bid.executed_time;
 while(1)
 {
    global_timer ++;
    if(global_timer - start == MAX_EXEC_TIME)
    {
        // execution time reached 5 so update executed time of bldn in data structures and break
        // update executed time
        bid.executed_time += MAX_EXEC_TIME;
        // update this bid in MIN Heap
        break;
    }
    else if(global_timer - start == target)
    {
        // building got completed
        // Print it
        // remove from data strucures.
        break;
    }
 }

}
*/
