#include <iostream>
#include <fstream>
#include "Building.h"
#include "MinHeap.h"
#include "RBTree.h"
#include <bits/stdc++.h>
#include "commands.h"
#include <string>
#include "queue"
#include <fstream>

using namespace std;

#define MAX_EXEC_TIME 5

/* function to input file*/
//TODO make it to some other class temporarily global
queue<command> cmd_que;
int tot_bldg_cnt = 0;
int completed_bldg_cnt = 0;
unsigned int timer = 0;
MinHeap MH;
RBTree RBT;
ofstream op;
// Function to remove all spaces from a given string
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

void insert_new_building()
{
    // pick from command from que
    command new_cmd = cmd_que.front();
    // form building object using cmd obj
    Building *b = new Building(new_cmd.arg1, new_cmd.arg2);
    RBNode * r = new RBNode(b);
    RBT.RBTree_insert(r);
    MH.insert_new(r);
    // insert it into RBT node
    // insert into min heap
    //MH.print_min_heap();
}

void print_building_wrapper()
{
    // pick up command from que
    command new_cmd = cmd_que.front();
    // check if arg2 is -1 if so call print(bid)
    if(new_cmd.arg2 == INVALID_ARG)
    {
        // call print single building
        RBT.print_single_building(new_cmd.arg1);
    }
    else
    {
        RBT.print_building_range(new_cmd.arg1, new_cmd.arg2);
    }
    // if arg2 present call print_range(b1,b2)
}
// main function to execute buildings

int execute_buildings()
{
    cout<<"\n--------------------- EXECUTE Buildings called -------------------"<<endl;
    //ofstream op;
    //op.open("../project_material/sample_op2/ak_op2.txt");
    op.open("../project_material/sample_op2/op2.txt");

    ofstream debug_op;
    debug_op.open("../project_material/sample_op2/op2_d.txt");
    bool execution_on = false;
    RBNode * curr;
    int days_remaining = 0, target = 0, start_time = 0, stop_time = 0;
    while(tot_bldg_cnt != completed_bldg_cnt || (!cmd_que.empty()))
    {
     // check whether any command ready at this point
     cout<<"\n ------------------------ Entered time : "<<timer<<"--------------------------"<<endl;
        cout<<"\n cmd que.front arrival time = "<<cmd_que.front().arrival_time<<endl;
        if((timer != 0) && (execution_on == true))
        {
            curr->get_building()->executed_time += 1;
        }

        if(cmd_que.front().arrival_time == timer)
     {
        // cmds in sorted order, so just check first command.
        // arrival time matches execute it
        if(cmd_que.front().cmd_type == INSERT)
        {
            insert_new_building();
            //completed_bldg_cnt ++;
            //cout<<"\n************ inserted a building ******"<<endl;
        }
        else{
            // command type in print
            print_building_wrapper();
        }
        cmd_que.pop();// remove it from command que as it is served

     }
if(timer!= 0)
{
    if(!execution_on)
    {

        // pick up a min building and start execution

        curr = MH.remove_min();
        if(curr == NULL)
        {
            cout<<"MIN HEAP IS EMPTY\n"<<endl;
            debug_op<<timer<<endl;

            timer ++;
            continue;
        }
        //cout<<"Buildin selected for execution = "<<curr->get_building()->get_building_num()<<endl;
        execution_on = true;
        start_time = timer;
        days_remaining = curr->get_building()->get_total_time() - curr->get_building()->executed_time;
        target = (days_remaining < MAX_EXEC_DAYS)? days_remaining: MAX_EXEC_DAYS;
        stop_time = start_time + target - 1;
        //cout<<"Start time = "<<start_time<<" Stop time = "<<stop_time<<endl;
        curr->get_building()->executed_time += 1;

    }
     else{
        // execuiton on
        //check whether to stpo execution
        if(timer == stop_time)
        {
            // stop time
            // update executed time
            //curr->get_building()->executed_time += target;
            //curr->get_building()->executed_time += 1;

            if(curr->get_building()->get_executed_time() == curr->get_building()->get_total_time())
            {
                // execution for the buildng complete remove it from RBT
                cout<<"\n"<<timer<<": _______________ Completed buildin _______________"<<endl;
                cout<<"("<<curr->get_building()->get_building_num()<<","<<timer<<")"<<endl;
                cout<<"\n___________________________________________________"<<endl;
                cout<<"_____________________________________________________\n\n"<<endl;
                op<<"\n"<<timer<<" : ("<<curr->get_building()->get_building_num()<<","<<timer<<")"<<endl;
                RBT.deleteNode(curr);
                completed_bldg_cnt ++;
            }
            else{
                // execution still remaining so put it back in min heap
                // with updated executed time
                MH.insert_new(curr);
                cout<<"Updated exec time of building "<<curr->get_building()->get_building_num()
                   <<"= "<<curr->get_building()->executed_time<<endl;
            }

            // clearing up variales for next instance
            execution_on = false;
            start_time = 0;
            curr = NULL;
            days_remaining = 0;
            target = 0;
            stop_time = 0;
        }
        else
        {
            //cout<<"ongoing"<<endl;
            //curr->get_building()->executed_time += 1;
        }

        }
     }
     debug_op<<timer<<endl;
     timer ++;

    }
    cout<<"------------- COMPLETED BUILDINGS = "<<completed_bldg_cnt<<endl;
    return 1;
}



int input_read()
{

//TODO add error checks to not read blank lines
    ifstream ip_file;
    //TODO Add error check for file handling
    //ip_file.open("../project_material/input.txt");
    ip_file.open("../project_material/sample_op2/Sample_input2.txt");

    string line;
    COMMAND_TYPE cmd_type;
    int arg1 = INVALID_ARG, arg2 = INVALID_ARG;

    cout<<"------- Before reading vector size = "<<cmd_que.size()<<endl;

    while (getline(ip_file, line)) {
        // using printf() in all tests for consistency
        //printf("%s\n", line.c_str());

        stringstream sstream(line);
        string arrival_time, cmd_string, arg1_str, arg2_str;

        // get arrival time
        getline(sstream, arrival_time, ':');
        //cout<<"Arrival time = "<<arrival_time<<endl;

        getline(sstream, cmd_string, '(');
        //cout<<"Command ="<<cmd_string<<endl;


        getline(sstream, arg1_str, ',');
        //cout<<"ARG 1 = "<<arg1_str<<endl;
        arg1 = atoi(arg1_str.c_str());
        //cout<<"ARG 1 int = "<<arg1<<endl;

        getline(sstream, arg2_str, ')');
        //cout<<"ARG 2 = "<<arg2_str<<endl;
        if(removeSpaces(arg2_str) != string(""))
            arg2 = atoi(arg2_str.c_str());
        else
            arg2 = -1;
        //cout<<"ARG 2 int = "<<arg2<<endl;

        if(removeSpaces(cmd_string) == string("Insert"))
        {
            //cout<<"------------insert command found"<<endl;
            cmd_type = INSERT;
            tot_bldg_cnt ++;
        }

        else
        {
            //cout<<"-----------print command found"<<endl;
            cmd_type = PRINT_BUILDING;
        }


    cmd_que.push(command(atoi(arrival_time.c_str()), cmd_type, arg1, arg2));
    }



    cout<<"-------------- Total buildings inserted = "<<tot_bldg_cnt<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------"<<endl;


    return 0;

}


/*void print_cmd_vector()
{
    cout<<"\n------- vector size = "<<cmd_que.size()<<endl;

    //printing cmd vector
    queue <command> iterator :: it;
    for(it = cmd_que.; i < cmd_vector.size();i ++)
    {
        cout<<"\nArrival time "<<i<<" = "<<cmd_que[i].arrival_time<<endl;
    }
}*/

int main()
{
    cout << "Hello world!" << endl;
    input_read();
    //print_cmd_vector();
    execute_buildings();

    //MinHeap MH;
    //RBTree RBT;
/*
    Building b(7,30, 0);
    Building b1 (6,10 ,15);
    Building b2 (5,40, 10);
    Building b3 (4,20,4);
    Building b4 (3,50,3);
    Building b5 (2,50,2);
    Building b6 (1,50,1);


    RBNode r(&b);
    RBT.RBTree_insert(&r);
    MH.insert_new(&r);

    MH.print_min_heap();

    RBNode r1(&b1);
    RBT.RBTree_insert(&r1);
    MH.insert_new(&r1);
    MH.print_min_heap();


    RBNode r2(&b2);
    RBT.RBTree_insert(&r2);
    MH.insert_new(&r2);
    MH.print_min_heap();


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

    while(RBT.RBRoot)
    {
    RBT.deleteNode(RBT.RBRoot);
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

    }


    RBT.deleteNode(&r2);
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
*/
    cout <<"endeeeeeddddd"<<endl;

return 0;
}
    /*

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
