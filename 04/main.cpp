#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>

std::vector<int> extractNumbers(std::string input){
    std::vector<int> numbers{};
    std::stringstream ss(input);
    char temp;
    std::stringstream  num_str{};

    while(!ss.eof()){
        ss.get(temp);   
        if(isdigit(temp)){;
            num_str << temp;
        } else if(!num_str.str().empty()){
            numbers.push_back(std::stoi(num_str.str()));
            num_str.str("");
        };
        temp = ' ';
    }
        
    if(!num_str.str().empty())
        numbers.push_back(stoi(num_str.str()));

return numbers;
}


int main(int argc, char** argv){
    std::vector<std::string> lines{};
    std::string line;
    std::fstream input(argv[1], std::fstream::in);


    if(!input.is_open())
        std::cout << "Error openin the file " << argv[1] << std::endl;

    while(std::getline(input, line)){
        lines.push_back(line);
    }

    std::vector<std::vector<int>> numbers{};
    for(auto l : lines){
        numbers.push_back(extractNumbers(l));
    }

 
    int result = 0;
    for(auto number : numbers){
        if((number[0] >= number [2] && number[1] <= number[3]) || 
                (number[0] <= number[2] && number[1] >= number[3]))
            result++;
    }

    std::cout <<  "Puzzel 1: " << result <<std::endl;

    int result2 = 0;
    for(auto number : numbers){
        if(number[0] <= number[3] && number[2] <= number[1]) 
            result2++;
    }

    std::cout << "Puzzel 2: " << result2 << std::endl;
    return 0;
}
