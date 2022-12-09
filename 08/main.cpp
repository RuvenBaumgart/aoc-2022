#include <iostream>
#include "utils.h"

struct pos{
  int x;
  int y;
  pos(int x, int y): x{x}, y{y}{};
};

bool checkVisibilityLeft(pos p, std::vector<std::vector<int>>& m){
  int left = p.x;
  int height = m[p.x][p.y];
  while(left > 0){
    if(m[left - 1][p.y] >= height)
      return false;
    left--;
  }
  return true;
}

bool checkVisibilityTop(pos p, std::vector<std::vector<int>>& m){
  int top = p.y;
  int height = m[p.x][p.y];
  while(top > 0){
    if(m[p.x][top - 1] >= height)
      return false;
    top--;
  }
  return true;
}

bool checkVisibilityRigth(pos p, std::vector<std::vector<int>>& m){
  int right = p.x;
  int height = m[p.x][p.y];
  while(right < m[p.x].size() - 1){
    if( m[right + 1][p.y] >= height)
      return false;
    right++;
  }
  return true;
}

bool checkVisibilityBottom(pos p, std::vector<std::vector<int>>& m){
  int bottom = p.y;
  int height = m[p.x][p.y];
  while(bottom < m.size() - 1){
    if(m[p.x][bottom +1] >= height)
      return false;
    bottom++;
  }
  return true;
}

bool checkVisibility(pos p, std::vector<std::vector<int>>& m){
  if(checkVisibilityLeft(p, m))
        return true;
  if(checkVisibilityTop(p, m))
        return true;
  if(checkVisibilityBottom(p, m))
        return true;
  if(checkVisibilityRigth(p, m))
        return true;
  return false; 
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


    
    int visible = (trees.size() * 2) +  (trees[0].size() * 2) - 4 ;
    for(int i = 1; i < trees.size() -1; i++){
      for(int j = 1; j < trees[0].size() -1; j++){
          if(checkVisibility(pos(i,j), trees)){
            visible++; 
            std::cout << "\033[1;31m" << trees[i][j] << "\033[0m";
          } else {
            std::cout << trees[i][j];  
          }
      }
      std::cout << std::endl;
    }

    std::cout << "Puzzel 1: " << visible << std::endl;
}
