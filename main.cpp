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

/* Queue to store all the commands read from the file*/
queue<command> cmd_que;
/* Maintains total building count according to the file commands */
int tot_bldg_cnt = 0;
/* Maintains count of buildings which have completed execution */
int completed_bldg_cnt = 0;
/* Global Timer to keep track of days */
unsigned int days_timer = 0;
/* Global instance of Min Heap */
MinHeap MH;
/* Global instance of RBTree */
RBTree RBT;
/* File stream for output */
ofstream op;

/* Function to remove all spaces from a given string */
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}


/* Creates new building instance based on command received
 * Inserts it into a node of Red Black Tree and insert the
 * RBTree Node into the Min heap vector */

void insert_new_building()
{
    // pick from command from que
    command new_cmd = cmd_que.front();
    // form building object using cmd object
    Building *b = new Building(new_cmd.arg1, new_cmd.arg2);
    RBNode * r = new RBNode(b);

    // insert it into RBT node
    RBT.RBTree_insert(r);

    // insert into min heap
    MH.insert_new(r);

}

/* Wrapper used when PRINT command is received from the file */
void print_building_wrapper()
{
    // pick up command from que
    command new_cmd = cmd_que.front();
    // check if arg2 is INVALID, if so call print(bid)
    // if arg2 is valid print range of buildings
    if(new_cmd.arg2 == INVALID_ARG)
    {
        // call function to print a single building
        RBT.print_single_building(new_cmd.arg1);
    }
    else
    {
        // call function to print rnage of buildings
        RBT.print_building_range(new_cmd.arg1, new_cmd.arg2);
    }
}

/* Main function to execute buildings */
int execute_buildings()
{
    cout<<"\n--------------------- EXECUTE Buildings called -------------------"<<endl;
    // Open Output file
    op.open("../output_file.txt");
    // Execution on - keeps track if any building is under execution or not
    // Building finished - Flag used to check if building has reached it's completion.
    bool execution_on = false, building_finished = false;

    RBNode * curr;
    // days_remaining - maintains number of days left for completion of building
    // target - value used to decide how many days to run the time for a building
    int days_remaining = 0, target = 0;

    // start_time - maintains the day when Building's execution starts
    // stop_time - maintains end date for an execution instance
    unsigned start_time = 0, stop_time = 0;

    // Loop till all inserted buildings are completed and command queue becomes empty
    while(tot_bldg_cnt != completed_bldg_cnt || (!cmd_que.empty()))
    {
        // check whether any command ready at this point
        /*cout<<"\n ------------------------ Entered time : "<<timer<<"--------------------------"<<endl;
        cout<<"\n cmd que.front arrival time = "<<cmd_que.front().arrival_time<<endl;*/

        // This condition is needed since we don't start construction on Day 0.
        if(days_timer != 0)
        {
            // If there is no ongoing execution currently , pick next building
            if(!execution_on)
            {
                // pick up a min building and start execution
                curr = MH.remove_min();
                if(curr == NULL)
                {
                    cout<<"MIN HEAP IS EMPTY\n"<<endl;
                    days_timer ++;
                    //continue;// TODO check if goto required
                    goto serve_command;
                }

                // Set execution instance
                execution_on = true;
                // Set start time
                start_time = days_timer;
                // Calculate remaining days depending upon total days and executed days
                days_remaining = curr->get_building()->get_total_time() - curr->get_building()->executed_time;
                // Select minimum of days_remaining of MAX EXECUTION DAYS(5)
                target = (days_remaining < MAX_EXEC_DAYS)? days_remaining: MAX_EXEC_DAYS;
                // Calculate end date from start date, -1 because present start day counted
                stop_time = start_time + target - 1;
                //cout<<"Start time = "<<start_time<<" Stop time = "<<stop_time<<endl;
                // Increment executed time , since current day when building starts is counted.
                curr->get_building()->executed_time += 1;

            }
            else
            {
                // There is an ongoing execution
                // check whether to stop execution depending upon end date reached
                if(days_timer == stop_time)
                {
                    // stop execution instance and update executed time
                    curr->get_building()->executed_time += 1;

                    // If the building is complete , then mark it as finished and remove it from min Heap
                    // Removal done in the end since, if any print command comes right now this building
                    // need to be printed first and then deleted.

                    if(curr->get_building()->get_executed_time() == curr->get_building()->get_total_time())
                    {
                        // execution for the buildng complete remove it from RBT
                        cout<<"\n"<<days_timer<<": _______________ Completed buildin _______________"<<endl;
                        cout<<"("<<curr->get_building()->get_building_num()<<","<<days_timer<<")"<<endl;
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
                        // Execution still remaining so put it back in min heap
                        // with the updated executed time
                        MH.insert_new(curr);
                        cout<<"Updated exec time of building "<<curr->get_building()->get_building_num()
                           <<"= "<<curr->get_building()->executed_time<<endl;

                        // Clearing up state variales for next execution instance
                        execution_on = false; // since one instance over
                        start_time = 0;
                        curr = NULL;
                        days_remaining = 0;
                        target = 0;
                        stop_time = 0;
                    }
                }
                else
                {
                    // End date not reached continue execution
                    curr->get_building()->executed_time += 1;
                }
            }
        }

serve_command:

        // Serving commands that come on this day

        // Commmands in sorted order, so we just check first command.
        // If arrival time matches execute it
        if(cmd_que.front().arrival_time == days_timer)
        {
            // Insert command
            if(cmd_que.front().cmd_type == INSERT)
            {
                insert_new_building();
                //cout<<"\n************ inserted a building ******"<<endl;
            }
            else
            {
                // Print command
                print_building_wrapper();
            }

            // Remove it from command que as it is served
            cmd_que.pop();
        }

        // If a building was marked finished previously, delete it from RBTree.
        // It was already removed from min heap during remove min operation
        if(building_finished == true)
        {
            // Write into the output file
            op<<days_timer<<" : ("<<curr->get_building()->get_building_num()<<","<<days_timer<<")"<<endl;

            // Delete Node
            RBT.delete_node(curr);

            // Update Completed building count
            completed_bldg_cnt ++;

            // clearing up variales for next instance
            building_finished = false;
            execution_on = false;
            start_time = 0;
            curr = NULL;
            days_remaining = 0;
            target = 0;
            stop_time = 0;
        }
     days_timer ++;

    }
    cout<<"------------- COMPLETED BUILDINGS = "<<completed_bldg_cnt<<endl;
    return 0;
}

/* Reads lines from given file and parses them,
 * forms command objects and adds them to command
 * queue */
int input_read( char * file_name)
{

    //TODO add error checks to not read blank lines
    // Input file object
    ifstream ip_file;
    //TODO Add error check for file handling
    //cout<<"File to open = "<<file_name<<endl;
    ip_file.open(file_name);
    string line;

    COMMAND_TYPE cmd_type;
    int arg1 = INVALID_ARG, arg2 = INVALID_ARG;

    cout<<"------- Before reading vector size = "<<cmd_que.size()<<endl;

    while (getline(ip_file, line)) {

        stringstream sstream(line);
        string arrival_time, cmd_string, arg1_str, arg2_str;

        // Get arrival time
        getline(sstream, arrival_time, ':');
        //cout<<"Arrival time = "<<arrival_time<<endl;

        // Get comand stirng
        getline(sstream, cmd_string, '(');
        //cout<<"Command ="<<cmd_string<<endl;

        // Get Argument 1
        getline(sstream, arg1_str, ',');
        //cout<<"ARG 1 = "<<arg1_str<<endl;

        arg1 = atoi(arg1_str.c_str());
        //cout<<"ARG 1 int = "<<arg1<<endl;

        // Get Argument 1
        getline(sstream, arg2_str, ')');
        //cout<<"ARG 2 = "<<arg2_str<<endl;

        // Remove spaces if any before string compare
        if(removeSpaces(arg2_str) != string(""))
            arg2 = atoi(arg2_str.c_str());
        else
            arg2 = INVALID_ARG;
        //cout<<"ARG 2 int = "<<arg2<<endl;

        if(removeSpaces(cmd_string) == string("Insert"))
        {
            //cout<<"------------insert command found"<<endl;
            cmd_type = INSERT;
            // Keep track of total buildings to be built
            tot_bldg_cnt ++;
        }
        else
        {
            //cout<<"-----------print command found"<<endl;
            cmd_type = PRINT_BUILDING;
        }

        // Add the command object to command queue
        cmd_que.push(command(atoi(arrival_time.c_str()), cmd_type, arg1, arg2));
    }

    cout<<"-------------- Total buildings inserted = "<<tot_bldg_cnt<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------"<<endl;

    return 0;
}

int main(int argc, char * argv[])
{
    cout << "Program Started !" << endl;
    if(argc == 1)
    {
        cout<<"\n Please give file name\n"<<endl;
        return 0;
    }

    input_read(argv[1]);

    execute_buildings();

    cout <<"\nProgram Ended !"<<endl;

    return 0;
}
