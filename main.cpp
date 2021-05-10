#include <ros/ros.h>
#include "std_msgs/String.h"
#include <systemc>
#include "chattercallback.hpp"

using namespace std;
using namespace sc_core;

//using namespace ros;

/*void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("I heard: [%s]", msg->data.c_str());
}*/

SC_MODULE(top) 
{
	//std_msgs::String msg;
	//sc_fifo_in <std_msgs::String> input;
	//sc_fifo_in<int> input;
	sc_fifo<int> output;

	void listener()
	{

		cout<<("InGet In\n");
		int argc;
		char **argv;
		ros::init(argc, argv, "listener");
		ros::NodeHandle n;
		ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
		output.write(1);
		ros::spin();

		wait();
		cout<<("InGet Out\n");

	}

	SC_CTOR(top) :output("out")

	{	
		cout<<("Start\n");

		
		//sensitive << output.data_read(); 

		
		cout<<("Top Ctor\n");

		SC_THREAD(listener);
		//sensitive << output.data_read_event(); 

		
 		//void chatterCallback();
	}

};

int sc_main(int argc, char *argv[])
{
    top top1("top1");

    sc_start();
        
    return 0;
}

