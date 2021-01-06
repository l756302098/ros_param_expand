#include <ros/ros.h>
#include "param_server/server.h"

void callback(param_server::SimpleType &config)
{
    for (auto &kv : config) {
        ROS_INFO("callback key:%s value:%s",kv.first.c_str(),kv.second.c_str());
    }
    
}

int main(int argc, char** argv){
  ros::init(argc, argv, "param_client_node");
  //package config
  param_server::Server server("param_client","cfg/config.yml");
  param_server::CallbackType f = boost::bind(&callback, _1); //绑定回调函数
  server.setCallback(f);
  bool b_value;
  float f_value;
  if(server.exist("boolean-value")){
    server.get("boolean-value",b_value);
  }
  if(server.exist("floating-value")){
    server.get("floating-value",f_value);
  }
  std::cout << "b_value:" << b_value << std::endl;
  std::cout << "f_value:" << f_value << std::endl;
  ros::spin();

  return 0;
}