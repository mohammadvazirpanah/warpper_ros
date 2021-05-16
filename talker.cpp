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
        ros::Rate loop_rate(0.1);
        int count = 0;

       // while (ros::ok())
        while (count<20)

        {
                std_msgs::String msg;

                std::stringstream ss;

                ss << count;
            
                msg.data = ss.str();
                ROS_INFO("%s", msg.data.c_str());

                chatter_pub.publish(msg);
                ros::spinOnce();
                
                loop_rate.sleep();
           
                ++count;
                wait(SC_ZERO_TIME);
                 //cout<<"Passed spin"<<endl;
                //wait(10, SC_MS);
        }		
        
	}

	void subscribe()
	{
        cout<<("Start Subscriber in Talker\n");
		ros::NodeHandle n;
		ros::Subscriber sub ;
		sub = n.subscribe("receive", 1000, chatterCallback);
		//ros::master::V_TopicInfo master_topics;
		//ros::master::getTopics(master_topics);
        while (1)

        {
            wait(SC_ZERO_TIME);
        }
        
		//ros::spin();
        //n.shutdown();
        //next_trigger(4, SC_NS);
        //wait(SC_ZERO_TIME);
	}

	SC_CTOR(talker) 

	{	
		cout<<("Start CTOR Talker\n");

        int argc;
		char **argv;
		ros::init(argc, argv, "talker");
        
        
        SC_THREAD(publish);
    
        //sensitive << ;
		SC_THREAD(subscribe);
        
		

	}

};

int sc_main(int argc, char *argv[])
{
    talker talker1("talker");

    sc_start();
	
        
    return 0;
}

