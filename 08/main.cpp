#include <iostream>
#include "utils.h"

struct pos{
  int x;
  int y;
  pos(int x, int y): x{x}, y{y}{};
};

bool checkVisibilityLeft(pos p, std::vector<std::vector<int>>& m){
  int left = p.x;
  while(left > 0){
    if(m[left - 1][p.y] > m[left][p.y])
      return false;
    left--;
  }
  return true;
}

bool checkVisibilityTop(pos p, std::vector<std::vector<int>>& m){
  int top = p.y;
  while(top > 0){
    if(m[p.x][top - 1] > m[p.y][top])
      return false;
    top--;
  }
  return true;
}

bool checkVisibilityRigth(pos p, std::vector<std::vector<int>>& m){
  int right = p.x;
  while(right < m[p.x].size()){
    if(m[right][p.y] < m[right + 1][p.y])
      return false;
    right++;
  }
  return true;
}

bool checkVisibilityBottom(pos p, std::vector<std::vector<int>>& m){
  int bottom = p.y;
  while(bottom < m.size()){
    if(m[p.x][bottom] < m[p.x][bottom +1])
      return false;
    bottom++;
  }
  return true;
}

bool checkVisibility(pos p, std::vector<std::vector<int>>& m){
  return checkVisibilityTop(p, m) || checkVisibilityLeft(p, m) || checkVisibilityRigth(p,m) || checkVisibilityBottom(p,m);
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

    trees.resize(lines.size());

    for(int i = 0; i < lines.size(); i++){
      for(int j = 0; j < lines[0].size(); j++){
        trees[i].push_back(lines[i][j]);
      }
    }

    int visible = (trees.size() * 2) +  (trees[0].size() * 2) - 4 ;
    for(int i = 1; i < trees.size() -1; i++){
      for(int j = 1; j < trees[0].size() - 1; j++){
        if(checkVisibility(pos(i,j), trees))
          visible++;
      }
    }

    std::cout << "Puzzel 1: " << visible << std::endl;
}
