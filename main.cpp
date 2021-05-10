#include <ros/ros.h>
#include "std_msgs/String.h"
#include <systemc>
#include "chattercallback.hpp"
#include <iostream>
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
		ros::Subscriber sub ;
		sub = n.subscribe("chatter", 1000, chatterCallback);
		//ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
		//ROS_INFO("%s", "Test"); 
		ros::master::V_TopicInfo master_topics;
		ros::master::getTopics(master_topics);
		
		for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++) 
		{
  			const ros::master::TopicInfo& info = *it;

  			//cout << "topic_" << it - master_topics.begin() << ": " << info.name << endl;
			//cout <<info.name << std::endl;

			string TopicName1 ="/chatter";
			string TopicName2 = info.name;	
			cout<<TopicName1<<endl<<TopicName2<<endl;

			if (TopicName1==TopicName2)
				ros::spin();

			
		}
	
		sub.shutdown();
		
		//ros::unsubscribe();
		ros::SubscribeOptions ops;
		 
		wait();
		//ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter1", 1000);
		//ros::Rate loop_rate(1);

		output.write(1);
		//ros::spin();

		
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

