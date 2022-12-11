#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

int counter = 1; // sprite position plus 2
int cycle = 1;
int num = 0;
int cur_inc = 0;
std::vector<int> increments = {
    0,
    40,
    80,
    120,
    160,
    200,
    240
};



bool lineBreak(){
    if(std::find(increments.begin(), increments.end(), cycle) != increments.end())
        return true;
    return false;
}

bool isSpritePosition(){
    if(counter <= cycle - increments[cur_inc] && cycle - increments[cur_inc] <= counter +2)
        return true;
    return false;
}

void increment(){
    if(isSpritePosition()){
        std::cout << "#";
    } else {
        std::cout << ".";
    };
    if(lineBreak()){
        std::cout << std::endl;
        cur_inc++;
    }
    cycle++;
}



int main(int argc, char** argv){
    std::fstream input(argv[1], std::fstream::in);
    std::string line;
    while(std::getline(input, line)){
        char opcode[50];
        int num = 0;
        sscanf(line.c_str(),  "%s %d", opcode, &num );
        if((strcmp(opcode, "noop") == 0)){
            increment();
        } else {
            increment();
            increment();
            counter += num;
            num = 0;
        };
    }
    
}
