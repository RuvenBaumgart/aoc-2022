#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char** argv){
    std::vector<std::string> lines{};
    std::string line;
    std::fstream input(argv[1], std::fstream::in);
    if(!input.is_open())
        std::cout << "Error opening the file " << argv[1] << std::endl;

    while(std::getline(input, line)){
        lines.push_back(line);
    }

    input.close();
    int result = 0;

    for(auto l : lines){
        std::string left;
        std::string right;
        
        left = l.substr(0, l.length()/2);
        right = l.substr(l.length()/2, l.length());


        for(char c : left){
            if(right.find(c) != std::string::npos){
                int prio = static_cast<int>(c);
                if(prio < 91)
                    prio = (prio - 38);
                if(prio > 91)
                    prio = (prio - 96);
                std::cout << c << ":" << prio << std::endl;
                result += prio;
                break;         
            }
        }
    }

    std::cout<<"Puzzel 1: " << result << std::endl;

    int result_2 = 0;
    for(int i = 0; i < lines.size(); i= i+3){
        std::string first = lines[i];
        std::string sec = lines[i + 1];
        std::string third = lines[i + 2];

        for(char c : first){
            if(sec.find(c) != std::string::npos){
                if(third.find(c) != std::string::npos){
                 int prio = static_cast<int>(c);
                if(prio < 91)
                    prio = (prio - 38);
                if(prio > 91)
                    prio = (prio - 96);
                std::cout << c << ":" << prio << std::endl;
                result_2 += prio;
                break;    
                }
            }
        }
    }
    std::cout << "Puzzel 2: " << result_2 << std::endl;

return 0;
}
