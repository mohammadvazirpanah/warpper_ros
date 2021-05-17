#include <ros/ros.h>
#include "std_msgs/String.h"
#include <systemc>
//#include "chattercallback.hpp"
#include <iostream>

using namespace std;
using namespace sc_core;

string temp;
	
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
		ROS_INFO("I heard: [%s]", msg->data.c_str());

		temp = msg-> data.c_str();

}

SC_MODULE(listener) 
{



    void publish()
	{
		cout<<("Start Publisher in Listener\n");
		ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<std_msgs::String>("receive", 1000);
        ros::Rate loop_rate(1);

	   while (1)
        {
                std_msgs::String msg;

                stringstream ss;

                //ss << "hello world " << count;
				ss << "-" << temp;
                msg.data = ss.str();
                ROS_INFO("%s", msg.data.c_str());

                chatter_pub.publish(msg);
                ros::spinOnce();
				loop_rate.sleep();

                wait(SC_ZERO_TIME);
                
				
        }	
		
	
		
	
	}

	void subscribe()
	{       
		cout<<("Start Subscriber in Listener\n");
		ros::NodeHandle n;
		ros::Subscriber sub ;
		sub = n.subscribe("send", 1000, chatterCallback);
		while (1)
		{
			//ros::spinOnce();
			wait(SC_ZERO_TIME);
			
		}
		
	}

	SC_CTOR(listener) 

	{	
		cout<<("Start CTOR Listener\n");

		int argc;
		char **argv;
		ros::init(argc, argv, "listener");

		SC_THREAD(publish);
		SC_THREAD(subscribe);
	

	}

};

int sc_main(int argc, char *argv[])
{
    listener listener1("listener");

    sc_start();

    return 0;
}

