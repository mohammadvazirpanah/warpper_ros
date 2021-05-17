#include <ros/ros.h>
#include "std_msgs/String.h"
#include <systemc>
#include "chattercallback.hpp"
#include <iostream>

using namespace std;
using namespace sc_core;

SC_MODULE(talker) 
{


    void publish()
	{
        cout<<("Start Publisher in Talker\n");
		ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<std_msgs::String>("send", 1000);
        ros::Rate loop_rate(1);
        int count = 1;


        while (count<=20)

        {
                std_msgs::String msg;

                stringstream ss;

                ss << count;
            
                msg.data = ss.str();
                ROS_INFO("%s", msg.data.c_str());

                chatter_pub.publish(msg);
                ros::spinOnce();
                
                loop_rate.sleep();
           
                ++count;
                wait(SC_ZERO_TIME);
        }		
       
	}

	void subscribe()
	{
        cout<<("Start Subscriber in Talker\n");
		ros::NodeHandle n;
		ros::Subscriber sub ;
		sub = n.subscribe("receive", 1000, chatterCallback);

        while (1)

        {  
            //ros::spinOnce();
            wait(SC_ZERO_TIME);
        }
    

	}

	SC_CTOR(talker) 

	{	
		cout<<("Start CTOR Talker\n");

        int argc;
		char **argv;
		ros::init(argc, argv, "talker");
        
        
        SC_THREAD(publish);
		SC_THREAD(subscribe);
        
		

	}

};

int sc_main(int argc, char *argv[])
{
    talker talker1("talker");

    sc_start();

    return 0;
}

