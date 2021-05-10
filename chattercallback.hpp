/*#include <systemc>

SC_MODULE(chatterCallback)
{

}*/


void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
 	ROS_INFO("I heard: [%s]", msg->data.c_str());
}
