#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

class HeightPoint{
public:
  int x;
  int y;
  int dist;
  HeightPoint(int x_, int y_, int dist_):x{x_}, y{y_}, dist{dist_}{};
};


int minDistance(std::vector<std::string>& m, std::vector<std::vector<int>>& visited){
  std::queue<HeightPoint> points{};
  HeightPoint start(0,0,0);
  points.push(start);
  visited[start.x][start.y] = 1;
  m[0][0] = 'a';

  while(!points.empty()){
      HeightPoint current_point = points.front();
      points.pop();
      std::cout << m[current_point.x][current_point.y] << std::endl;

    if(current_point.x == 5 && current_point.y == 2){
      return current_point.dist;
    };

    // move left
    if(current_point.x - 1 >= 0 &&
      visited[current_point.x - 1][current_point.y] == false) {
      if ((m[current_point.x - 1][current_point.y] - m[current_point.x][current_point.y]) >= 0 ){
        points.push(HeightPoint(current_point.x - 1, current_point.y, current_point.dist + 1));
        visited[current_point.x - 1][current_point.y] = true;
      }
    }
    // move up
    if(current_point.y - 1 >= 0 &&
      visited[current_point.x][current_point.y - 1] == false) {
      if ((m[current_point.x][current_point.y -1] - m[current_point.x][current_point.y]) >= 0){
        points.push(HeightPoint(current_point.x, current_point.y - 1, current_point.dist + 1));
        visited[current_point.x][current_point.y -1] = true;
      }
    }
    // move right
    if(current_point.x + 1 < m.size() &&
      visited[current_point.x + 1][current_point.y] == false) {
      if ((m[current_point.x + 1][current_point.y] - m[current_point.x][current_point.y]) >= 0){
        points.push(HeightPoint(current_point.x + 1, current_point.y, current_point.dist + 1));
        visited[current_point.x + 1][current_point.y] = true;
      }
    }
    // move down
    if(current_point.y + 1 < m[0].size() &&
      visited[current_point.x][current_point.y + 1] == false) {
      if ((m[current_point.x][current_point.y + 1] - m[current_point.x][current_point.y]) >= 0){
        points.push(HeightPoint(current_point.x, current_point.y + 1, current_point.dist + 1));
        visited[current_point.x ][current_point.y + 1] = true;
      }
    }

    for(auto i : visited){
      for( auto n : i ){
        std::cout << n << " ";
      }
      std::cout << std::endl;
    }
  }
return -1;
}


int main(int argc, char** argv){
  std::fstream input(argv[1], std::fstream::in);
  std::vector<std::string> heigthMap{};
  std::string line;
  while(std::getline(input, line)){
    heigthMap.push_back(line);
  }


  std::vector<std::vector<int>> visited{};
  visited.resize(heigthMap.size());

  for(int i = 0; i < heigthMap.size(); i++){
    visited[i].resize(heigthMap[0].size());
    for( int j = 0; j < heigthMap[0].size(); j++){
      visited[i][j] = false;
    }
  }

  std::cout << minDistance(heigthMap, visited) << std::endl;
}
