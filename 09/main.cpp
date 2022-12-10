#include <iostream>
#include <fstream>
#include <unordered_set>
#include <functional>
#include <cstdlib>
#include <string>
#include <cstdio>

#define DEPTH 10
struct Point
{
  int x;
  int y;

  Point() {};
  Point(int x, int y):x{x}, y{y}{};

  bool operator==(const Point& otherPoint) const{
    if (this->x == otherPoint.x && this->y == otherPoint.y) 
        return true;
    else 
        return false;
  };

  struct HashFunction
  {
    size_t operator()(const Point& point) const{
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};


struct Knot{
  Point current_pos;
  std::unordered_set<Point, Point::HashFunction> visited_points;
};

void move(Knot& h, int x_dir, int y_dir){
    Point temp(h.current_pos.x, h.current_pos.y);
    h.visited_points.insert(h.current_pos);
    h.current_pos = Point(temp.x + x_dir, temp.y + y_dir);
}

void move(Knot& t, Knot& h){
    int x_dir = h.current_pos.x - t.current_pos.x; 
    int y_dir = h.current_pos.y - t.current_pos.y;
    
    x_dir = x_dir > 1 ? 1 : x_dir;
    x_dir = x_dir < -1 ? -1 : x_dir;

    y_dir = y_dir > 1 ? 1 : y_dir;
    y_dir = y_dir < -1 ? -1 : y_dir;

    move(t, x_dir, y_dir);
}


bool isTouching(Knot& t, Knot& h){
    if(abs(t.current_pos.x - h.current_pos.x) <= 1 &&
        abs(t.current_pos.y -h.current_pos.y) <=1 )
        return true;
    return false;
}

int main(int argc, char** argv){
  Knot knots[DEPTH];
  
  for(int i = 0; i < DEPTH; i++){
      knots[i].current_pos = Point(0,0);
      knots[i].visited_points.insert(knots[i].current_pos);
  }

  std::fstream input(argv[1], std::fstream::in);
  std::string line;

  while(std::getline(input, line)){
      char direction[2];
      int distance;
      sscanf(line.c_str(), "%s %d", direction, &distance);
    
      if(strcmp(direction, "R") == 0){
          for(int i = 0; i < distance; i++){
              move(knots[0], 1, 0);
          for(int j = 1; j < DEPTH; j++){    
            if(!isTouching(knots[j], knots[j - 1]))
                move(knots[j], knots[j - 1]);
            }
          }
      };

    if(strcmp(direction, "L") == 0){
          for(int i = 0; i < distance; i++){
              move(knots[0], -1, 0);
          for(int j = 1; j < DEPTH; j++){    
            if(!isTouching(knots[j], knots[j - 1]))
                move(knots[j], knots[j - 1]);
            }
          }
      };

    if(strcmp(direction, "U") == 0){
          for(int i = 0; i < distance; i++){
              move(knots[0], 0, -1);
          for(int j = 1; j < DEPTH; j++){    
            if(!isTouching(knots[j], knots[j - 1]))
                move(knots[j], knots[j - 1]);
            }
          }
      };

    if(strcmp(direction, "D") == 0){
          for(int i = 0; i < distance; i++){
              move(knots[0], 0, 1);
          for(int j = 1; j < DEPTH; j++){    
            if(!isTouching(knots[j], knots[j - 1]))
                move(knots[j], knots[j - 1]);
            }
          }
      };
  };

  std::cout << "Puzzel 1: " << knots[9].visited_points.size() + 1 << std::endl;

  return 0;
}
