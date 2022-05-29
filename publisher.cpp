
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <iostream>

geometry_msgs::PoseStamped pose_in;
void pub_pose(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_in.pose = msg->pose;
    std::cout << "GOT POSITION\n";
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<geometry_msgs::PoseStamped>
            ("/slam_out_pose", 10, pub_pose);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("/mavros/vision_pose/pose", 10);


    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // wait for FCU connection
    while(ros::ok()){
        ros::spinOnce();
        rate.sleep();
    }

   
    geometry_msgs::PoseStamped pose_out;
    pose_out.pose.position.x = pose_in.pose.position.x;
    pose_out.pose.position.y = pose_in.pose.position.x;
    pose_out.pose.position.z = pose_in.pose.position.x;

 
    local_pos_pub.publish(pose_out);
    ros::spinOnce();
    rate.sleep();


    return 0;
}


