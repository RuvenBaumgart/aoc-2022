#include <iostream>
#include <fstream>

int main(int argc, char** argv){
      std::fstream input(argv[1], std::ifstream::in);
      std::string line{};
      std::getline(input, line);
      std::cout << line << std::endl;

      int i;
      for( i = 0; i < line.size() - 4; i++){
        std::string cur_stream{};
        for(int j = 0; j < 4; j++){
          cur_stream += line [i + j];
        }

        int unequal = 1;
        int k;
        for(int j = 0; j < cur_stream.size() - 1; j++){
          for(k = j + 1; k < cur_stream.size(); k++){
            if(cur_stream[j] == cur_stream[k])
              unequal = 0;
          }
        }
        if(unequal == 1){
          std::cout << i + 4 << std::endl;
          break;
        }
      }

      for( i = 0; i < line.size() - 14; i++){
        std::string cur_stream{};
        for(int j = 0; j < 14; j++){
          cur_stream += line [i + j];
        }

        int unequal = 1;
        int k;
        for(int j = 0; j < cur_stream.size() - 1; j++){
          for(k = j + 1; k < cur_stream.size(); k++){
            if(cur_stream[j] == cur_stream[k])
              unequal = 0;
          }
        }
        if(unequal == 1){
          std::cout << i + 14 << std::endl;
          break;
        }
      }

      return 0;
}
