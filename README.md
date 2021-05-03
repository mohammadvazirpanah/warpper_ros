# wrapper_ros
Wrapper -> SystemC and ROS 


g++ listener.cpp -o listener -I/opt/ros/noetic/include -L/opt/ros/noetic/lib -Wl,-rpath=/opt/ros/noetic/lib -lroscpp -lrosconsole -lrostime

g++ main.cpp -o main -I. -I/opt/ros/noetic/include -L. -L/opt/ros/noetic/lib -Wl,-rpath=/opt/ros/noetic/lib -lroscpp -lrosconsole -lrostime -lroscpp_serialization -lsystemc -lm