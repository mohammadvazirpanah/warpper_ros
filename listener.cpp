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

		temp = msg->data.c_str();

}

SC_MODULE(listener) 
{



    void publish()
	{
		cout<<("Start Publisher in Listener\n");
		ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<std_msgs::String>("receive", 1000);
        ros::Rate loop_rate(0.1);
        int count = 0;

       // while (ros::ok())
	   while (1)
        {
                std_msgs::String msg;

                std::stringstream ss;

                //ss << "hello world " << count;
				ss << "-" << temp;
                msg.data = ss.str();
                //ROS_INFO("%s", msg.data.c_str());

                chatter_pub.publish(msg);
                ros::spinOnce();
                wait(SC_ZERO_TIME);
                loop_rate.sleep();
                
                //++count;
				
        }	
		
	
		
	
	}

	void subscribe()
	{       
		cout<<("Start Subscriber in Listener\n");
		ros::NodeHandle n;
		ros::Subscriber sub ;
		sub = n.subscribe("send", 1000, chatterCallback);
		//ros::master::V_TopicInfo master_topics;
		//ros::master::getTopics(master_topics);
		//ros::spin();
		//ros::shutdown();
		//ros::stop();
		while (1)
		{
			wait(SC_ZERO_TIME);
			ros::spinOnce();
		}
		//next_trigger(4, SC_NS);
		
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

