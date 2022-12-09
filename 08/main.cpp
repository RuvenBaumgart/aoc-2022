#include <iostream>
#include "utils.h"

struct pos{
  int x;
  int y;
  pos(int x, int y): x{x}, y{y}{};
};

int checkVisibilityLeft(pos p, std::vector<std::vector<int>>& m){
  int left = p.x;
  int height = m[p.x][p.y];
  while(left > 0){
    if(m[--left][p.y] >= height)
      break;
  }
  return p.x - left;
}

int checkVisibilityTop(pos p, std::vector<std::vector<int>>& m){
  int top = p.y;
  int height = m[p.x][p.y];
  while(top > 0){
    if(m[p.x][--top] >= height)
      break;

  }
  return p.y - top;
}

int checkVisibilityRigth(pos p, std::vector<std::vector<int>>& m){
  int right = p.x;
  int height = m[p.x][p.y];
  while(right < m[p.x].size() - 1){
    if( m[++right][p.y] >= height)
      break;
  }
  return right  - p.x ;
}

int checkVisibilityBottom(pos p, std::vector<std::vector<int>>& m){
  int bottom = p.y;
  int height = m[p.x][p.y];
  while(bottom < m.size() - 1){
    if(m[p.x][++bottom] >= height)
      break;

  }
  return bottom  - p.y;
}

int checkVisibility(pos p, std::vector<std::vector<int>>& m){
  int scale = 1;
  scale *= checkVisibilityLeft(p, m);
  scale *= checkVisibilityTop(p, m);
  scale *= checkVisibilityBottom(p, m);
  scale *= checkVisibilityRigth(p, m);

  return scale;
}

int main(int argc, char** argv){
    std::vector<std::string> lines{};
    std::vector<int> numbers{};
    std::fstream input(argv[1], std::fstream::in);
    std::string line{};
    std::vector<std::vector<int>> trees{};

    while(std::getline(input, line)){
      lines.push_back(line);
    }

    trees.resize(lines.size(), std::vector<int>(lines[0].size()));

    for(int i = 0; i < lines.size(); i++){
      for(int j = 0; j < lines[0].size(); j++){
        const char num = lines[i][j];
        trees[i][j] = std::atoi(&num);
      }
    }


    int max_scale = 0;
    int visible = (trees.size() * 2) +  (trees[0].size() * 2) - 4 ;
    for(int i = 1; i < trees.size() -1; i++){
      for(int j = 1; j < trees[0].size() -1; j++){
        std::cout << "distance for: " << trees[i][j] << " " << checkVisibility(pos(i,j), trees) << std::endl;
        max_scale = std::max(max_scale, checkVisibility(pos(i,j), trees));
      }
    }

    std::cout << "Puzzel 2: " << max_scale << std::endl;




}
