# ros_param_expand
dynamic update/save pram

#  Depend

* ubuntu(18.04)
* ros(melodic)
* yaml-cpp(0.6)

#  Install﻿
* install yaml-cpp
** git clone https://github.com/jbeder/yaml-cpp
** mkdir build
** cmake .. -DYAML_BUILD_SHARED_LIBS=ON
** make -j4 && sudo make install
* install param_extend
** cd ~/your_workspace/src
** git clone https://github.com/l756302098/ros_param_expand.git
** cd ~/your_workspace
** catkin_make -j4

#  Use
param_client is demo node
```c++
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
  server.get("boolean-value",b_value);
  server.get("floating-value",f_value);
  std::cout << "f_value:" << f_value << std::endl;
  ros::spin();

  return 0;
}
```
### roscore
### rosrun param_client client
* add/update
rosservice call /param_client_node/param_server/set
* del
rosservice call /param_client_node/param_server/del
