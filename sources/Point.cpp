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


// The function returns the closest point to the destination point, - is at most the given distance from the source point
// Point Point::moveTowards(Point source, Point destination, double distance)
// {
//     if (distance < 0)
// 		throw invalid_argument("The distance cant be negative");
    
// 	double desClose = source.distance(destination);
// 	if (desClose <= distance)
// 		return destination;
//     double x1n =(source.getX()+ (distance * (destination.getX() - source.getX()) / desClose));
//     double y1n = (source.getY()+ (distance * (destination.getY() - source.getY()) / desClose));
// 	return Point(x1n,y1n);
// }

Point Point::moveTowards(Point source, Point destination, double distance)
{
    if (distance < 0)
        throw std::invalid_argument("The distance can't be negative");

    double dx = destination.getX() - source.getX();
    double dy = destination.getY() - source.getY();
    double current_distance = sqrt(dx * dx + dy * dy);

    // If the destination is near the source within the maximum distance
    if (current_distance <= distance) {
        return destination;
    }

    // Calculate the ratio between the current distance and the maximum distance (given)
    double ratio = distance / current_distance;
    double new_x = source.getX() + ratio * dx;
    double new_y = source.getY() + ratio * dy;

    return Point(new_x, new_y);
}


// Point Point::moveTowards(Point source , Point destination ,double distance)
// {
//     if (distance < 0)
//     {
//         __throw_invalid_argument("distance can't be negative");
//     }
    
//         double dx = destination.x1 - source.x1;
//         double dy = destination.y1 - source.y1;
//         double current_distance = sqrt(dx * dx + dy * dy);

//         //if destination is near me at radius of maximum distance
//         if (current_distance <= distance) {
//             return destination;
//         }

//         //calculate ratio between curr distance and max distance(given)
//         double ratio = distance / current_distance;
//         double new_x = source.x1 + ratio * dx;
//         double new_y = source.y1 + ratio * dy;

//         return Point(new_x, new_y);
// }
// Prints the two coordinates in parentheses.
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
