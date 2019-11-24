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
    op.open("../output_file.txt");

    ofstream debug_op;
    debug_op.open("../project_material/sample_op2/op2_d.txt");
    bool execution_on = false, building_finished = false;
    RBNode * curr;
    int days_remaining = 0, target = 0, start_time = 0, stop_time = 0;
    while(tot_bldg_cnt != completed_bldg_cnt || (!cmd_que.empty()))
    {
        // check whether any command ready at this point
        cout<<"\n ------------------------ Entered time : "<<timer<<"--------------------------"<<endl;
        cout<<"\n cmd que.front arrival time = "<<cmd_que.front().arrival_time<<endl;

        if(timer != 0)
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
            else
            {
                // execuiton on
                //check whether to stpo execution
                if(timer == stop_time)
                {
                    // stop time
                    // update executed time
                    //curr->get_building()->executed_time += target;
                    curr->get_building()->executed_time += 1;

                    if(curr->get_building()->get_executed_time() == curr->get_building()->get_total_time())
                    {
                        // execution for the buildng complete remove it from RBT
                        cout<<"\n"<<timer<<": _______________ Completed buildin _______________"<<endl;
                        cout<<"("<<curr->get_building()->get_building_num()<<","<<timer<<")"<<endl;
                        cout<<"\n___________________________________________________"<<endl;
                        cout<<"_____________________________________________________\n\n"<<endl;
                        building_finished = true;
                        /*
                        op<<"\n"<<timer<<" : ("<<curr->get_building()->get_building_num()<<","<<timer<<")"<<endl;
                        RBT.deleteNode(curr);
                        completed_bldg_cnt ++;
                        */
                    }
                    else
                    {
                        // execution still remaining so put it back in min heap
                        // with updated executed time
                        MH.insert_new(curr);
                        cout<<"Updated exec time of building "<<curr->get_building()->get_building_num()
                           <<"= "<<curr->get_building()->executed_time<<endl;
                            // clearing up variales for next instance
                        execution_on = false;
                        start_time = 0;
                        curr = NULL;
                        days_remaining = 0;
                        target = 0;
                        stop_time = 0;
                    }
                }
                else
                {
                    curr->get_building()->executed_time += 1;
                }
            }
        }

        // SERVING COMMANDS
        if(cmd_que.front().arrival_time == timer)
        {
            // cmds in sorted order, so just check first command.
            // arrival time matches execute it
            if(cmd_que.front().cmd_type == INSERT)
            {
                insert_new_building();
                //cout<<"\n************ inserted a building ******"<<endl;
            }
            else{
                // command type in print
                print_building_wrapper();
            }
            cmd_que.pop();// remove it from command que as it is served
        }

        if(building_finished == true)
        {
            op<<timer<<" : ("<<curr->get_building()->get_building_num()<<","<<timer<<")"<<endl;
            RBT.deleteNode(curr);
            completed_bldg_cnt ++;
            building_finished = false;
            // clearing up variales for next instance
            execution_on = false;
            start_time = 0;
            curr = NULL;
            days_remaining = 0;
            target = 0;
            stop_time = 0;
        }
     debug_op<<timer<<endl;
     timer ++;

    }
    cout<<"------------- COMPLETED BUILDINGS = "<<completed_bldg_cnt<<endl;
    return 1;
}


int input_read( char * file_name)
{

    //TODO add error checks to not read blank lines
    ifstream ip_file;
    //TODO Add error check for file handling
    cout<<"File to open = "<<file_name<<endl;
    ip_file.open(file_name);
    string line;
    COMMAND_TYPE cmd_type;
    int arg1 = INVALID_ARG, arg2 = INVALID_ARG;

    cout<<"------- Before reading vector size = "<<cmd_que.size()<<endl;

    while (getline(ip_file, line)) {

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
            arg2 = INVALID_ARG;
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

int main(int argc, char * argv[])
{
    cout << "Hello world!" << endl;
    if(argc == 1)
    {
        cout<<"\n Please give file name\n"<<endl;
        return 0;
    }
    input_read(argv[1]);

    execute_buildings();

    cout <<"\nProgram Ended"<<endl;

    return 0;
}
