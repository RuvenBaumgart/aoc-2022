#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <regex>
#include <cmath>
#include <iostream>
#include <climits>

class Point{
    public:
        long long x;
        long long y;

        Point(){};
        Point(long long xx, long long yy): x{xx}, y{yy}{};
        bool operator==(Point& p){
            return ((p.x == this->x) && (p.y == this->y));
        }
        bool operator>(Point& p){
            return (std::sqrt(std::pow(p.x,2) + std::pow(p.y,2)) < std::sqrt(std::pow(this->x,2) + std::pow(this->y,2)));
        }
};

std::vector<std::string> split(std::string str, std::string delimeter){
   int found = 0;
    std::vector<std::string> result;
    while(found != std::string::npos){
        found = str.find(delimeter, 0);
        if(found != std::string::npos){
            std::string tmp = str.substr(0, found);
            str.erase(0, found + delimeter.length());
            result.push_back(tmp);
        }
    }
    result.push_back(str);
    return result;
}

std::vector<int> getNumbersFromLine(std::string str){
    std::vector<int> result;
    std::stringstream ss(str);
    std::string tmp;
    long long number;
    std::smatch match;
    const std::regex pattern(".=(-?\\d+).?");
    while(!ss.eof()){
        ss >> tmp;
        if(std::regex_match(tmp, match, pattern)){
            if((std::stringstream(match[1]) >> number))
                result.push_back(number);
        }
    }
    return result;
}

std::vector<std::string> readLines(const char* file){
    std::vector<std::string> input_lines;
    std::string line;
    std::ifstream input(file, std::ios::in);
    while(std::getline(input, line)){
        if(!line.empty())
            input_lines.push_back(line);
    }
    return input_lines;
}

std::pair<Point, Point> getPair(std::vector<int> numbers)
{
    std::pair<Point, Point> result;
    if(numbers.size() < 4)
        return result;
    Point p1(numbers.at(0), numbers.at(1));
    Point p2(numbers.at(2), numbers.at(3));
    result = std::pair(p1, p2);
    return result;
}

std::vector<std::pair<Point, Point>> getPairs(std::vector<std::string> str){
    std::vector<std::pair<Point, Point>> pairs;
    for(int i = 0; i < str.size(); i++){
        std::vector<int> numbers = getNumbersFromLine(str.at(i));
        std::pair<Point, Point> p = getPair(numbers);
        pairs.push_back(p);
    }
    return pairs;
}
long long getManDis(Point p1, Point p2){

    long long x = std::abs(p1.x - p2.x);
    long long y = std::abs(p1.y - p2.y);
    return x + y;
}


std::pair<Point, Point> getBoundary(std::vector<std::pair<Point, Point>>& pairs){
    long long min_x, min_y, max_x, max_y;
    min_x = INT_MAX;
    max_x = INT_MIN;


    for(int i = 0; i < pairs.size(); i++){
       int min_x_;
       int max_x_;

       min_x_ = pairs.at(i).first.x - getManDis(pairs.at(i).first, pairs.at(i).second);
       max_x_ = pairs.at(i).first.x + getManDis(pairs.at(i).first, pairs.at(i).second);

       min_x = min_x_ < min_x ? min_x_ : min_x;
       max_x = max_x_ > max_x ? max_x_ : max_x;

    }

   return std::pair<Point, Point>(Point(min_x, min_y), Point(max_x, max_y));
}



int init(int argc, char** argv, std::vector<std::pair<Point, Point>>& pp, std::vector<std::vector<char>>& matrix){
    std::vector<std::string> input_lines;
    if(argc < 2)
        return 1;
    input_lines = readLines(argv[1]);
    pp = getPairs(input_lines);

    return 0;
}

std::vector<Point> getAllPointsOnPerimeter(Point p, int peri){
    std::vector<Point> result;
    for(int i = 0; i < peri; i++){
        Point pOnP(p.x + i, p.y + peri - i);
        result.push_back(pOnP);
    }


    for(int i = 0; i < peri; i++){
        Point pOnP(p.x + i, p.y - peri - i);
        result.push_back(pOnP);
    }


    for(int i = 0; i < peri; i++){
        Point pOnP(p.x - i, p.y - peri - i);
        result.push_back(pOnP);
    }


    for(int i = 0; i < peri; i++){
        Point pOnP(p.x - i, p.y + peri - i);
        result.push_back(pOnP);
    }

    return result;
}


int main(int argc, char** argv){
    std::vector<std::vector<char>> matrix;
    std::vector<std::pair<Point, Point>> pp;
    init(argc, argv, pp, matrix);
    std::pair<Point, Point> boundary = getBoundary(pp);

    long long result = 0;

    for(int i = boundary.first.x; i <= boundary.second.x; i++){
        for(int j = 0; j < pp.size(); j++){
            Point current(i, 10);
            if(getManDis(current, pp.at(j).first) <= getManDis(pp.at(j).first, pp.at(j).second) && getManDis(current, pp.at(j).second) != 0){
                result++;
                break;
            }
        }
    }
    std::cout << "Puzzel 1: " << result << std::endl;

   /**
    * Trying to find the point that is not inside any sensors perimeter
    */

    for(int sensor = 0; sensor < pp.size(); sensor++){
        int perimeter = getManDis(pp.at(sensor).first, pp.at(sensor).second) + 1; // The point to search is outside the perimeter of every sensor.
        std::vector<Point> periPoints = getAllPointsOnPerimeter(pp.at(sensor).first, perimeter);
        for(int point = 0; point < periPoints.size(); point++){
            int nextSensor;
            Point currentPoint(periPoints.at(point).x, periPoints.at(point).y);

            for(nextSensor = 0; nextSensor < pp.size(); nextSensor++){
                if(nextSensor != sensor){
                    if(getManDis(currentPoint, pp.at(nextSensor).first) <= getManDis(pp.at(nextSensor).first, pp.at(nextSensor).second))
                        break;
                    }
            }
            if(nextSensor == pp.size())
                if(currentPoint.x <= 4000000 && currentPoint.x >= 0 && currentPoint.y <= 4000000 && currentPoint.y >= 0 )
                    result = currentPoint.x * 4000000 + currentPoint.y;
        }

    }
    std::cout << "Puzzel 2: " << result << std::endl;

    return 0;
}
