#include "utils.h"
#include "algorithm"
#include "numeric"

int main(int argc, char** argv)
{
  std::vector<std::string> lines = getLinesFromFile("input.txt");
  std::vector<std::vector<std::string>> elfs_cal{};
  std::vector<std::string> calories = {};

  for(auto line : lines){

    if(line.empty()){
      elfs_cal.push_back(calories);
      calories.clear();
    }
    calories.push_back(line);
  }

  if(!calories.empty())
    elfs_cal.push_back(calories);


  std::vector<int> calories_num{};
  for(auto calories : elfs_cal){
    int curr_cal = 0;
    for(auto calorie : calories){
      curr_cal += atoi(calorie.c_str());
    }
    calories_num.push_back(curr_cal);
  }

  sort(calories_num.begin(), calories_num.end(), std::greater<int>());
  std::cout << "Puzzel 1: " << calories_num[0] << std::endl;
  std::cout << "Puzzel 2: " << std::accumulate(calories_num.begin(), calories_num.begin() + 3, 0);
}
