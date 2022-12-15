#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>

class HeithPoint{
public:
  int x;
  int y;
  int dist;
  HeithPoint(){};
  HeithPoint(int x_, int y_, int dist_):x{x_}, y{y_}, dist{dist_}{};

  struct Compare{
      bool operator()(const HeithPoint& p1, const HeithPoint& p2) const{
              return p1.dist > p2.dist; 
            }
  };;
};
 
HeithPoint start;
HeithPoint end;
std::vector<std::string> heithMap{};
std::priority_queue<HeithPoint, std::vector<HeithPoint>, HeithPoint::Compare> points{};
int moves[4][2]= {
    { 0, -1},
    { 0,  1},
    {-1,  0},
    { 1,  0}
};

bool move(HeithPoint cp, HeithPoint* np, int x, int y){
    if((cp.x + x >= 0) && (cp.x + x < heithMap[0].size()) && (cp.y + y >= 0) && (cp.y + y < heithMap.size())){
        np->x = cp.x + x, np->y = cp.y + y, np->dist = cp.dist + 1;
        return true;
    }
    return false;
}


int minDistance(std::vector<std::string>& m, std::vector<std::vector<int>>& visited){
points.push(start);

  while(!points.empty()){
      HeithPoint current_point = points.top();
      points.pop();

    if(current_point.x == end.x && current_point.y == end.y){
        return current_point.dist;
    };


    if(visited[current_point.y][current_point.x])
        continue;

    visited[current_point.y][current_point.x] = true;

    for(int i = 0; i < 4; i++){
        HeithPoint* np = new HeithPoint(0,0,0);
        if(move(current_point, np, moves[i][0], moves[i][1]) && !visited[np->y][np->x]) {
            if ((int)m[np->y][np->x] <= (int)m[current_point.y][current_point.x] + 1){
                points.push(*np);
               
            }
        }
    }

    system("clear");
    for(size_t i = 0; i < visited.size(); i++){
        for(size_t j = 0; j < visited[0].size(); j++){
            std::cout << visited[i][j];
        }
        std::cout << std::endl;
    }
}
   return -1;
}


int main(int argc, char** argv){
   std::fstream input(argv[1], std::fstream::in);
   std::string line;
   int i = 0;
  while(std::getline(input, line)){
      for(int j = 0; j < line.length(); j++){
            if(line[j] == 'E'){
            end.y = i;
            end.x = j;
            line[j] = 'z';
        }

        if(line[j] == 'S'){
            start.y = i;
            start.x = j;
            line[j] = 'a';
        }

        if(line[j] == 'a'){
            points.push({j,i,0});
        }
      }
    
    heithMap.push_back(line);
    i++;
  }

  std::vector<std::vector<int>> visited{};
  visited.resize(heithMap.size());

  for(int i = 0; i < heithMap.size(); i++){
    visited[i].resize(heithMap[i].size());
    for( int j = 0; j < heithMap[i].size(); j++){
      visited[i][j] = false;
    }
  }

  std::cout << minDistance(heithMap, visited) << std::endl;


}
