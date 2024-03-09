#include<iostream>
#include"Frame.h"
#include"Park.h"

//返回十个机器人的行动方向
std::vector<Axis> get_robot_behave(Frame& current){
    //第i个机器人选择第j个泊位
    for(int i=0;i<kMAX_ROBOT;i++){ //10
        for(int j=0;j<kMAX_PARK;j++){ //10
            for(auto goods:allGoods){ //most 200
                
            }           
        }
    }
}