#include <iostream>
#include "utils.h"
#include <list>
#include <algorithm>


std::vector<char> parse(std::string line){
  std::vector<char> res{};
  std::string result{};
  char space = 'x';
  int new_block = 1;
  int blank = 0;
  char c;

  for(int i = 0; i < line.length(); i++){
    c = line[i];
    if(c == ' ' && new_block){
      new_block = 0;
    } else if(c == ' ' && !new_block){
      blank++;
    } else if(c == ']'){
      new_block = 1;
    } else if(c == '['){
      blank = 0;
    } else if(!isspace(c) && isalpha(c)){
      res.push_back(c);
    }

    if(blank == 3)
      res.push_back(c);
    if(blank == 4)
      blank = 0;
  }

  return res;
}

void rotateMatrix(char** arr, int width, int height){
  for (int i=0; height / 2; i++) {
    for (int j=i; j< height - i - 1; j++){
        // Swapping elements after each iteration in Clockwise direction
            int temp=arr[i][j];
            arr[i][j]=arr[height-1-j][i];
            arr[height-1-j][i]=arr[height-1-i][height-1-j];
            arr[height-1-i][height-1-j]=arr[j][height-1-i];
            arr[j][height-1-i]=temp;
    }
  }

}

int getHeight(std::vector<std::vector<char>>& m){
  int max_height = 0;
  for(auto row : m){
    max_height = std::max(max_height, (int)row.size());
  }
  return max_height;
}


int main(int argc, char** argv){
  std::vector<std::string> input = readLinesFromFile(argv[1]);
  std::vector<std::vector<char>> matrix{};
  std::vector<std::vector<int>> numbers {};
  int line = 0;
  for(; line < input.size(); ++line){
    if(input[line].empty()){
      break;
    }
    matrix.push_back(parse(input[line]));
  }
  matrix.pop_back();

  for(auto row : matrix){
    for(auto col : row){
      std::cout << col;
    }
    std::cout << std::endl;
  }

  const int width = matrix.size();
  const int height = getHeight(matrix);

  char** m = new char[width][height];

  for(int i = 0; i < matrix.size(); i++){
    for( int j = 0; j < matrix[i].size(); j++){
      m[i][j] = matrix[i][j];
      std::cout <<  matrix[i][j];
    }
    std::cout << std::endl;
  }

  rotateMatrix(m, width, height);

/*
  for(; line < input.size(); line++){
    numbers.push_back(getNumbersFromString(input[line]));
  }

  for(auto nums : numbers){
    for(int i = 0; i < nums[0]; ++i){
      //move(nums[1], nums[2], matrix);
    }
  }
  */
return 0;
}
