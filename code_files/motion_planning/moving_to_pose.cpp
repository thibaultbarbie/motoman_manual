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
  geometry_msgs::Pose target;
  target.orientation.w = 1.0;
  target.position.x = 0.6;
  target.position.y = -0.1;
  target.position.z = 0.42;
  group.setPoseTarget(target);
  
  // Running the moveit planning
  moveit::planning_interface::MoveGroup::Plan result_plan;
  group.plan(result_plan);
  
  return 0;
}
