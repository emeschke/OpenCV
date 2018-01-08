#include <iostream>
#include <string>
#include <map>
#include "opencv2/core.hpp"

bool operator<(cv::Point_<int> const& a, cv::Point_<int> const& b)
{
    std::cout << "(a.x < b.x) " << (a.x < b.x) << std::endl; 
    std::cout << "(a.x == b.x && a.y < b.y) " << (a.x == b.x && a.y < b.y) << std::endl; 
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
} 

class Patch{
    public:
    double x;
    double y;
    friend std::ostream & operator << (std::ostream &out, const Patch &c);
    Patch(double inputX, double inputY){
        x = inputX;
        y = inputY;
    }    
};

std::ostream & operator << (std::ostream &out, const Patch &c)
{
    out << "(" << c.x << "," << c.y << ")";
    return out;
}

bool operator<(Patch const& a, Patch const& b)
{
    std::cout << "(a.x < b.x) " << (a.x < b.x) << std::endl; 
    std::cout << "(a.x == b.x && a.y < b.y) " << (a.x == b.x && a.y < b.y) << std::endl; 
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

int main( int argc, const char** argv)
{
    Patch p1 = Patch(1, 2);
    Patch p2 = Patch(1, 3);

    std::cout << "Point 1: " << p1.x << std::endl << "Point 2: " << p2.x << std::endl;
    std::cout << "Point 1: " << p1.y << std::endl << "Point 2: " << p2.y << std::endl;

    if ((p1 < p2)){
        std::cout << "P1 is less: " << p1 << "," << p2 << std::endl;
    }
    
    if ((p1 < p2)){
        std::cout << "P1 is less: " << p1 << "," << p2 << std::endl;
    }

    std::map<Patch, int> pointMap;

    std::cout << pointMap.size() << std::endl;

    std::pair<Patch, int> pair1 = std::pair<Patch, int>(p1, 1);
    std::pair<Patch, int> pair2 = std::pair<Patch, int>(p2, 1);

    pointMap.insert(pair1);
    pointMap.insert(pair2);

    std::cout << pointMap.size() << std::endl;
}


