#include <moveit/move_group_interface/move_group.h>

int main(int argc, char** argv)
{
  // Initialization of the ROS node
  ros::init(argc, argv, "moving_the_robot");

  // Initialization of moveit 
  moveit::planning_interface::MoveGroup group("arm");

  // Setting the start position
  group.setStartState(*group.getCurrentState());

  // Setting the goal position
  std::map<std::string, double> joints;
      
  joints["joint_s"] = -0.8;
  joints["joint_l"] = 0.2;
  joints["joint_e"] = 0.0;
  joints["joint_u"] = -0.4;
  joints["joint_r"] = 0.35;
  joints["joint_b"] = 0.6;
  joints["joint_t"] = 0.4;
      
  group.setJointValueTarget(joints);

  // Running the moveit planning
  moveit::planning_interface::MoveGroup::Plan result_plan;
  group.plan(result_plan);
  
  return 0;
}
