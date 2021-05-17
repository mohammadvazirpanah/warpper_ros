//void chatterCallback (const ros::MessageEvent<std_msgs::String const>& event)
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
	
	
		//ROS_INFO("I heard: [%s]", msg->data.c_str());
	

	//const std::string& publisher_name = event.getPublisherName();
   	//const ros::M_string& header = event.getConnectionHeader();
   	//ros::Time receipt_time = event.getReceiptTime();
   	//const std_msgs::StringConstPtr& msg = event.getMessage();

	ROS_INFO("I heard: [%s]", msg->data.c_str());


	
 	
}
