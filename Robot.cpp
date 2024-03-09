#include "Robot.h"
#include "Grid.h"
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <cstring>

void Robot::input() {
  std::cin >> object_;
  pos_.input();
  std::cin >> status_;
}

int dx[4],dy[4];
bool vis[kMAX_GRID][kMAX_GRID]; 
Axis pre[kMAX_GRID][kMAX_GRID]; 
std::vector<Axis> Robot::get_path(Axis destination) {
    std::queue<Axis> q;
    q.push(pos_);
    for(int i=0;i<kMAX_GRID;i++){
        for(int j=0;j<kMAX_GRID;j++){
            pre[i][j]={-1,-1};
            vis[i][j]=0;
        }
    }
    vis[pos_.x_][pos_.y_]=1;
    while(q.size()){
        Axis u=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int x=u.x_+dx[i],y=u.y_+dy[i];
            if(x<0 || y<0 || x>=kMAX_GRID || y>=kMAX_GRID)continue;
            if( grid.grid_[x][y]==grid.barrier || grid.grid_[x][y]==grid.ocean )continue;
            q.push({x,y});
            vis[x][y]=1;
            pre[x][y]={x,y};
        }
    }
    std::vector<Axis> v;
    int x=destination.x_,y=destination.y_;
    if(!vis[x][y])return v;
    v.push_back({x,y});
    while(pre[x][y] != Axis(-1,-1) ){  
        x=pre[x][y].x_,y=pre[x][y].y_;
        v.push_back({x,y});
    }
    return v;
}