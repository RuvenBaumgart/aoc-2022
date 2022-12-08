#include "utils.h"
#include <map>
#include <cstring>
/**
* A : ROCK
* B : PAPER
* C : SCISSORS
*/

/**
* X : LOS
* Y : DRAW
* Z : WIN
*/

std::map<std::string, int> rules ={
  {"AX", 3}, {"AY", 6}, {"AZ", 0}, {"BX", 0}, {"BY", 3}, {"BZ", 6}, {"CX", 6}, {"CY", 0}, {"CZ", 3}
};

std::map<std::string, int> points = {
  {"X", 1}, {"Y", 2}, {"Z", 3}
};

std::map<std::string, int> strategy =  {
  {"X", 0}, {"Y", 3}, {"Z", 6}
};

int main(int argc, char** argv){


  std::vector<std::string> lines = readLinesFromFile("input.txt");


  int result = 0;
  for(auto line : lines){
    std::vector<std::string> answers{};
    split(line, ' ', answers);
    std::string res = answers[0];
    res.append(answers[1]);

    std::map<std::string, int>::iterator it = rules.find(res);
    result += it->second;

    it = points.find(answers[1]);
    result += it->second;
  }

std::cout << "Puzzel 1: " << result << std::endl;


std::map<std::string, int> valid_rules{};
int result_2 = 0;

for(auto line : lines){
  std::vector<std::string> answers {};
  int res{};
  int curr_strat{};

  split(line, ' ', answers);
  std::map<std::string, int>::iterator it;
  it = strategy.find(answers[1]);
  curr_strat = it->second;

  for(auto it = rules.begin(); it != rules.end(); it++){
    if(it->second == curr_strat)
      valid_rules.insert(make_pair(it->first, it->second));
  }

  for(auto it = valid_rules.begin(); it != valid_rules.end(); it++){
    std::map<std::string, int>::iterator itt{};
    const char* a = answers[0].c_str();
    if(it->first[0] == *a){
      std::string b = {it->first[1]};
      itt = points.find(b);
      res = itt->second;
      result_2 += res + curr_strat;
      valid_rules.clear();
      break;
    }
  }
}

  std::cout << "Puzzel 2: " << result_2 << std::endl;
}
