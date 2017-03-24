#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

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
      
  joints["joint_s"] = 0.12;
  joints["joint_l"] = -0.11;
  joints["joint_e"] = -0.17;
  joints["joint_u"] = -1.49;
  joints["joint_r"] = 0.18;
  joints["joint_b"] = 1.35;
  joints["joint_t"] = -0.42;
      
  group.setJointValueTarget(joints);

  // Adding obstacle
  moveit::planning_interface::PlanningSceneInterface planning_scene;
  std::vector<moveit_msgs::CollisionObject> collision_objects;
  
  moveit_msgs::CollisionObject obstacle;
  obstacle.header.frame_id = group.getPlanningFrame();
  sleep(5.0);
  // The id of the object is used to identify it. 
  obstacle.id = "obstacle";
  
  // Define a box to add to the world. 
  shape_msgs::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[0] = 0.4;
  primitive.dimensions[1] = 0.3;
  primitive.dimensions[2] = 0.05;

  // A pose for the box (specified relative to frame_id) 
  geometry_msgs::Pose obstacle_pose;
  obstacle_pose.orientation.w = 1.0;
  obstacle_pose.position.x =  0.45;
  obstacle_pose.position.y =  0.0;
  obstacle_pose.position.z =  0.45;

  obstacle.primitives.push_back(primitive);
  obstacle.primitive_poses.push_back(obstacle_pose);
  obstacle.operation = obstacle.ADD;

  collision_objects.push_back(obstacle);
  planning_scene.addCollisionObjects(collision_objects);
  
  // Running the moveit planning
  moveit::planning_interface::MoveGroup::Plan result_plan;
  group.plan(result_plan);
  
  return 0;
}
