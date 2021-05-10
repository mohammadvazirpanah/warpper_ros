#include "ros/ros.h"
#include "std_msgs/String.h"
#include <systemc>
#include <sstream>
#include "chattercallback.hpp"

using namespace std;
using namespace sc_core;

SC_MODULE(top) 

{

    void talker()
	{

		cout<<("talker\n");
		int argc;
		char **argv;
		ros::init(argc, argv, "talker");
		ros::NodeHandle n;
        ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
        
        ros::Rate loop_rate(1);
        int count = 0;
        //ros::spinOnce();

        while (ros::ok())
        {
                std_msgs::String msg;

                std::stringstream ss;

                ss << "hello world " << count;
            
                msg.data = ss.str();
                ROS_INFO("%s", msg.data.c_str());

                chatter_pub.publish(msg);
                ros::spinOnce();
                
                loop_rate.sleep();
                
                ++count;
                //ros::spin();
        }		
	}

    SC_CTOR(top)
    {
        cout<<("Start\n");
        SC_THREAD(talker);

    }

};

int sc_main(int argc, char *argv[])


{
    top top1("top1");

    sc_start();
        
    return 0;
}


