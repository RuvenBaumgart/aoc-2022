#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <unistd.h>
#include <stdlib.h>

int min_x = INT_MAX;
int max_x = 0;

#define W_BOTTOM 1
#define WO_BOTTOM 0

typedef struct Point_s{
    int x;
    int y;
    Point_s();
    Point_s(int x, int y){
        this->x = x;
        this->y = y;
    }
    bool operator==(Point_s& p){
        if((p.x == this->x) && (p.y == this->y))
            return true;
        return false;
    }
} Point;

typedef struct Matrix_s{
    int height;
    int width;
    std::vector<char> m;
    Matrix_s(){};
    Matrix_s(Matrix_s& mm){
        this->height = mm.height;
        this->width = mm.width;
        this->m = mm.m;
    }
    Matrix_s(int x, int y){
        this->height = y;
        this->width = x;
        m.resize(x * y, '.');
    }
} Matrix;

std::vector<std::string> split(std::string str, std::string delim){
    std::vector<std::string> result;
    std::string tmp;
    int pos;
    while((pos = str.find(delim)) != std::string::npos){
        tmp = str.substr(0, pos);
        result.push_back(tmp);
        str.erase(0, delim.length() + pos);
    }
    tmp = str.substr(0, str.length());
    result.push_back(tmp);
    return result;
}

std::vector<std::string> getPointsAsString(std::string str){
    std::string delim = " -> ";
    std::vector<std::string> points_str = split(str, delim);
   return points_str;
}

std::vector<Point> getPoints(std::vector<std::string> pointsAsString){
    std::vector<Point> result;
    for(int i = 0; i < pointsAsString.size(); i++){
        int x, y;
        std::vector<std::string> points_str = split(pointsAsString.at(i), ",");
        x = std::atoi(points_str.at(0).c_str());
        y = std::atoi(points_str.at(1).c_str());
        Point* newPoint = new Point(x, y);
        result.push_back(*newPoint);
    };
    return result;
}

void printMatrix(Matrix& matrix){
    std::system("clear");
    int j = 0;
    std::cout << j << " \t";
    for(int i = 0; i < (matrix.height * matrix.width); i++){
        std::cout << matrix.m[i];
        if(i % matrix.width == 0){
                std::cout << std::endl;
                std::cout << ++j << "\t";
                i+=0;
        }
    }
    std::cout << std::endl;
}

void drawPoint(Matrix& matrix, Point p, char symbol){
    matrix.m[p.x + p.y * matrix.width] = symbol;
}

void drawPoint(Matrix& matrix, int x, int y, char symbol){
    matrix.m[x + y * matrix.width] = symbol;
}

void erasePoint(Matrix& matrix, Point p){
  drawPoint(matrix, p, '.');
}

void drawHorizontalLine(Matrix& matrix, Point start, Point end ){
    int len = end.x - start.x;
    if(len < 0)
        for(int i = len * -1; i >= 0; i--){
            drawPoint(matrix, start.x - i, start.y, '#');
        }
    else
        for(int i = 0; i <=len; i++){
            drawPoint(matrix, start.x + i, start.y, '#');
        }
}

void drawVerticalLine(Matrix& matrix, Point start, Point end ){
    int len = end.y - start.y;
    if(len < 0)
        for(int i = len * -1; i >= 0; i--){
            drawPoint(matrix, start.x, start.y - i, '#');
        }
    else
        for(int i = 0; i <=len; i++){
            drawPoint(matrix, start.x, start.y + i, '#');
        }
}

void drawLine(Matrix& matrix, Point s1, Point s2){
    if(s1.x == s2.x)
        drawVerticalLine(matrix, s1, s2);
    else
        drawHorizontalLine(matrix, s1, s2);
}

void drawRock(Matrix& matrix, std::vector<Point> rock){
    for(int i = 1; i < rock.size(); i++){
        drawLine(matrix, rock.at(i-1), rock.at(i));
    }
}

void initMatrix(Matrix& matrix, std::vector<std::vector<Point>> rocks, int bottom){

    for(int i = 0; i < rocks.size(); i++){
        for(int j = 0; j < rocks.at(i).size(); j++){
            int x = rocks[i][j].x;
            int y = rocks[i][j].y + 1;
             min_x = x < min_x ? x : min_x;
             matrix.width = x > matrix.width ? x : matrix.width;
             matrix.height = y > matrix.height ? y : matrix.height;
        }
    }

    if(bottom){
        matrix.height += 2;
        matrix.width += 500;
    }

    matrix.m.resize((matrix.height) * matrix.width, '.');

    for(int i = 0; i < rocks.size(); i++){
        drawRock(matrix, rocks.at(i));
    }

    if(bottom){
        drawLine(matrix, Point(1, matrix.height - 1), Point(matrix.width, matrix.height -1 ));
    }
}

void init(char** argv, Matrix& matrix, Point startPoint, int bottom){
    std::ifstream input(argv[1], std::ios::in);
    std::string line;
    std::vector<std::string> lines;
    while(getline(input, line)){
        if(!line.empty())
            lines.push_back(line);
    };

    std::vector<std::vector<Point>> rocks;
    for(int i = 0; i < lines.size(); i++){
        rocks.push_back(getPoints(getPointsAsString(lines.at(i))));
    }

    initMatrix(matrix, rocks, bottom);
}

int moveSand(Matrix& m, Point& currentPos ){
    long ypos = (currentPos.y + 1) * m.width;
    long stepDown =         currentPos.x + 0 + ypos;
    long stepDownLeft =     currentPos.x - 1 + ypos;
    long stepDownRight =    currentPos.x + 1 + ypos;
    int res = 0; // no move possible

        if(m.m[stepDown] == '.'){
        }else if(m.m[stepDownLeft] == '.' ){
                currentPos.x -= 1;
        } else if (m.m[stepDownRight] == '.'){
            currentPos.x += 1;
        } else if(currentPos.y + 1 >= m.height){
            res = 2;
        }else {
            res = 1; // no move possible
        }

    if(res == 0)
        currentPos.y += 1;

    return res;
}

int run(int argc, char** argv, Matrix& matrix, Point startPoint){
    Point lastPoint = startPoint;
    Point currentPos = startPoint;
    int rest_count = 0;
    char symbol = '+';
    int produceNewSand = 0;

    while(1){
        lastPoint = currentPos;
        int rest = moveSand(matrix, currentPos);
        if(rest == 1){
            symbol = 'o';
            produceNewSand = 1;
            rest_count++;

        } else if(rest == 2) {
            break;
        } else {
            symbol = '+';
            erasePoint(matrix, lastPoint);
            produceNewSand = 0;
        }

        drawPoint(matrix, currentPos, symbol);

        if(currentPos == startPoint)
            break;

        if(produceNewSand)
            currentPos = startPoint;

        if(argc == 3 && (strcmp(argv[2],"show") == 0)){
            printMatrix(matrix);
            usleep(5 * 1e3); // millisec
        };
    }
return rest_count;
}

int main(int argc, char** argv){
    Matrix matrix;
    Point startPoint(500,0);
    int rest_count;

    init(argv, matrix, startPoint, 0);
    drawPoint(matrix, startPoint, '+');
    rest_count = run(argc, argv, matrix, startPoint);
    //printMatrix(matrix);
    std::cout << "Puzzel 1:" << rest_count << std::endl;

    matrix.m.clear();
    matrix.height = 1;
    matrix.width = 1;

    init(argv, matrix, startPoint, 1);
    drawPoint(matrix, startPoint, '+');
    rest_count = run(argc, argv, matrix, startPoint);
   // printMatrix(matrix);
    std::cout << "Puzzel 2:" << rest_count << std::endl;

}
