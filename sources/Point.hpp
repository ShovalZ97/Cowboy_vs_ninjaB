#pragma once
#include <string>
using namespace std;

namespace ariel
{

    class Point
    {
    private:
        double x1;
        double y1;

    public:
        Point();
        Point(double x_1, double y_1);
        double distance(Point point1) const;
        void print();
        //The function returns the closest point to the destination point, - is at most the given distance from the source point
        static Point moveTowards(Point source, Point destination, double distance);
        double getX() const;
        double getY() const;
    };
}