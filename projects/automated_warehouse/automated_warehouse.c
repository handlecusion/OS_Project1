#include <stdio.h>
#include <string.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "projects/automated_warehouse/aw_manager.h"

#include "projects/automated_warehouse/aw_message.h"

struct robot* robots;
int robot_num;

// test code for central control node thread
void test_cnt(){
        boxes_from_central_control_node = malloc(sizeof(struct messsage_box) * robot_num);
        boxes_from_robots = malloc(sizeof(struct messsage_box) * robot_num);

        while(1){
                //if(check_block_message())
                print_map(robots, 4);
                thread_sleep(1000);
                block_thread();
        }
}

// test code for robot thread
void test_thread(void* aux){
        int idx = *((int *)aux);
        int test = 0;
        while(1){
                printf("thread %d : %d\n", idx, test++);
                thread_sleep(idx * 1000);
        }
}

// thread 가 cnt 1, 2, 3 로봇 순서대로 진행되므로 cnt가 로봇 위치 읽으면서 어디로 갈지 정하고 쓰레도 차례대로 돌면 됨(thread_sleep)
void cnt_thread(char *misson)
{
        while(1)
        {
                boxes_from_central_control_node = malloc(sizeof(struct messsage_box) * robot_num);
                boxes_from_robots = malloc(sizeof(struct messsage_box) * robot_num);

                while(1){
                        //if(check_block_message())
                        print_map(robots, robot_num);
                        thread_sleep(1000);
                        block_thread();
                }
        }
        
}

void robot_thread()
{
        while(1){
                printf("thread\n");
                thread_sleep(1000);
        }
}

// entry point of simulator
void run_automated_warehouse(char **argv)
{
        init_automated_warehouse(argv); // do not remove this

        printf("implement automated warehouse!\n");

        // test case robots
        /*
        robots = malloc(sizeof(struct robot) * 4);
        setRobot(&robots[0], "R1", 5, 5, 0, 0);
        setRobot(&robots[1], "R2", 0, 2, 0, 0);
        setRobot(&robots[2], "R3", 1, 1, 1, 1);
        setRobot(&robots[3], "R4", 5, 5, 0, 0);
        */
        robot_num = atoi(argv[1]);
        char _robotname[10];

        printf("%s %d\n", argv[1], robot_num);

        robots = malloc(sizeof(struct robot) * robot_num);
        for (int i=0; i<robot_num; i++)
        {
                fprintf(_robotname, "R%d", i+1);
                printf("%s\n", _robotname);
                setRobot(&robots[i], _robotname, 5, 5, 1, 0);
        }

       

        // example of create thread
        /*
        tid_t* threads = malloc(sizeof(tid_t) * 4);
        int idxs[4] = {1, 2, 3, 4};
        threads[0] = thread_create("CNT", 0, &test_cnt, NULL);
        threads[1] = thread_create("R1", 0, &test_thread, &idxs[1]);
        threads[2] = thread_create("R2", 0, &test_thread, &idxs[2]);
        threads[3] = thread_create("R3", 0, &test_thread, &idxs[3]);
        */

        tid_t* threads = malloc(sizeof(tid_t) * (robot_num + 1));
        threads[0] = thread_create("CNT", 0, &cnt_thread, &argv[2]);
        for (int i=1; i<robot_num+1; i++)
        {
                fprintf(_robotname, "R%d", i);
                threads[i] = thread_create(_robotname, i, &robot_thread, NULL);
        }

        // if you want, you can use main thread as a central control node
        
}