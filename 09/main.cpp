#include <iostream>
#include <fstream>

struct Point
{
  int x;
  int y;

  Point() { }
  Point(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  bool operator==(const Point& otherPoint) const
  {
    if (this->x == otherPoint.x && this->y == otherPoint.y) return true;
    else return false;
  }

  struct HashFunction
  {
    size_t operator()(const Point& point) const
    {
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};


struct head{
  pos current_pos;
  pos last_pos;
};

struct tail{
  pos current_pos;
  std:: visited_pos;
}

int main(int argc, char** argv){
  std::fstream input(argv[1], std::fstream::in);
  std::string line;
  return 0;
}
