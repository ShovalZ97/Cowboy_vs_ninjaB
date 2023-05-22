#include "Point.hpp"
#include <cmath>
#include <iostream>

using namespace ariel;

// Default Constructor
Point::Point()
{
    this->x1 = 0.0;
    this->y1 = 0.0;
}
// Parameterized Constructor
Point::Point(double x11, double y11)
{
    this->x1 = x11;
    this->y1 = y11;
}
// Get a point and calculate the distance between the two points
double Point::distance(Point point) const
{
    double xN = this->x1 - point.x1;
    double yN = this->y1 - point.y1;
    return sqrt(pow(xN , 2) + pow(yN, 2));
}


//The function returns the closest point to the destination point, - is at most the given distance from the source point
Point Point::moveTowards(Point source, Point destination, double distance)
{
    if (distance < 0)
		throw invalid_argument("The distance cant be negative");
    
	double desClose = source.distance(destination);
	if (desClose <= distance)
		return destination;
    double x1n =(source.getX()+ (distance * (destination.getX() - source.getX()) / desClose));
    double y1n = (source.getY()+ (distance * (destination.getY() - source.getY()) / desClose));
	return Point(x1n,y1n);
}

void Point::print()
{
    std::cout << "(" << this->x1 << ", " << this->y1 << ")" << std::endl;
}

double Point ::getX() const
{
    return this->x1;
}
double Point ::getY() const
{
    return this->y1;
}
