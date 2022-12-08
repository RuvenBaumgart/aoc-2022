#include "utils.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>

class File {
public:
  File(){};
  std::string name;
  size_t size;
};

class Dir {

  public:
    Dir(){};
    std::vector<Dir> dirs;
    std::vector<File> files;
    Dir* up;
    std::string name;
    size_t size;
};

Dir* root = new Dir();

void changedir(Dir** current_dir, std::string line){
  std::string next_dir{};
  if(line[5] == '/'){
    *current_dir = root;
  } else if(line[5] == '.'){
    *current_dir = (*current_dir)->up;
  } else if((next_dir = line.substr(5, line.length())) != ""){

    std::vector<Dir>::iterator it{};
    for(it = (*current_dir)->dirs.begin(); it < (*current_dir)->dirs.end(); it++){
      if(it->name.compare(next_dir) == 0){
        *current_dir = &(*it);
      }
    }
    if(it == (*current_dir)->dirs.end())
      std::cout << "No directory with the name " << next_dir << " found" << std::endl;
  }
}

void calcSize(Dir* current_dir){

    for(Dir& dir : current_dir->dirs)
      calcSize(&dir);

    for(File& file : current_dir->files)
      current_dir->size += file.size;

    if(current_dir->up != NULL){
      current_dir->up->size += current_dir->size;
    }
    return;
}

int depth = 1;
int sum = 0;
std::vector<Dir> possible_dirs{};
int unused_space = 0;

void printDirTree(Dir* current_dir){

  if(current_dir->name[0] == '/')
    std::cout << current_dir->name << " " << current_dir->size << std::endl;

  for(Dir dir : current_dir->dirs){
    for(int i = 0; i < depth; i++)
      std::cout << "--";
    std::cout << dir.name << " " << dir.size <<  std::endl;
    depth++;
    printDirTree(&dir);
  }

  for(File file : current_dir->files){
    for(int i = 0; i < depth; i++)
      std::cout << "--";
    std::cout << file.name << " " << file.size <<  std::endl;
  }

  if(current_dir->size <= 100000)
    sum += current_dir->size;

  if(current_dir->size >= (30000000 - unused_space))
    possible_dirs.push_back(*current_dir);

  depth--;
  return;
}

int main(int argc, char** argv){

  Dir* current_dir = root;
  current_dir->name = '/';
  current_dir->up = NULL;

  std::fstream input(argv[1], std::fstream::in);
  std::string line{};

  while(std::getline(input, line)){
    if(line[0] == '$'){
      if(line[2] == 'c')
        changedir(&current_dir, line);
    } else if(line[0] == 'd'){
        std::string dirname = line.substr(4, line.length());
        Dir new_dir = Dir();
        new_dir.name = dirname;
        new_dir.size = 0;
        new_dir.up = current_dir;
        current_dir->dirs.push_back(new_dir);
    } else if(isdigit(line[0])){
        char name[50];
        int size;
        sscanf(line.c_str(), "%d %s\n", &size, name);
        File new_file = File();
        new_file.name = name;
        new_file.size = size;
        current_dir->files.push_back(new_file);
    }
  }
  calcSize(root);
  unused_space = 70000000 - root->size;
  printDirTree(root);
  std::cout << "Puzzel 1: " << sum << std::endl;


  std::sort(possible_dirs.begin(), possible_dirs.end(), [](const Dir&a, const Dir&b)->bool{return a.size < b.size;});

  std::cout << "Puzzel 2: " << possible_dirs[0].size << std::endl;
  return 0;
}
