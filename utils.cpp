#include "utils.h"

std::vector<std::string> readLinesFromFile(std::string filename){
    std::vector<std::string> result{};
    std::ifstream infs (filename, std::ifstream::in);

    if(!infs.is_open()){
      std::cout << "ERROR: open file " << filename << std::endl;
      return result;
    }

    std::string line;
    while(std::getline(infs, line)){
      result.push_back(line);
    }
    return result;
}

void split(const std::string& str, const char c, std::vector<std::string>& res){
    std::string::size_type i = 0;
    std::string::size_type j = str.find(c);

    while( j != std::string::npos){
      res.push_back(str.substr(i, j-i));
      i = ++j;
      j = str.find(c, j);
    }
    if( j == std::string::npos){
      res.push_back(str.substr(i, str.length()));
    }
}

int count_occurenc_of(const char c, std::string s){
  int occurences = 0;
  for(int i = 0; i < s.size(); ++i){
    if(s[i] == c)
      occurences++;
  }
  return occurences;
}

std::vector<size_t> find_positions_of(const char c, std::string str){
    std::vector<size_t> result{};
    int pos = 0;
    while(1){
      pos = str.find(c, pos);
      if(pos == std::string::npos)
        break;

    }
    return result;
}

void group(std::vector<std::string>& input, std::vector<std::vector<std::string>>& result){
  std::vector<std::string> group{};

  for(auto line : input){

    if(line.empty()){
      result.push_back(group);
      group.clear();
    }
    group.push_back(line);
  }

  if(!group.empty())
    result.push_back(group);
}

std::vector<int> getNumbersFromString(std::string str){
  std::vector<int> result{};
  std::stringstream str_s (str);
  std::stringstream num_s{};
  while(!str_s.eof()){
    char c = str_s.get();
    if(isdigit(c))
      num_s << c;

    if((isspace(c) || isalpha(c)) && num_s.str().length() > 0){
      result.push_back(std::stoi(num_s.str()));
      num_s.str("");
    }
    c = ' ';
  }
  return result;
}
