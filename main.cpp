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
	

	SC_CTOR(top) 

	{	
		int argc;
		char **argv;
		cout<<("top ctor\n");
		ros::init(argc, argv, "listener");
		ros::NodeHandle n;
 		ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
 		ros::spin();
	}

};

int sc_main(int argc, char *argv[])
{
    top top1("top1");

    sc_start();
        
    return 0;
}

