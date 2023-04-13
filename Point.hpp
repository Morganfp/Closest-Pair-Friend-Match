/*
* FILE: Point.hpp
* AUTHOR: Morgan Purcell
* DATE: 04/2023
* PURPOSE: Class to describe a Point
*/

#ifndef _POINT_HPP_
#define _POINT_HPP_

// Include the necessary libraries
#include <string>

class Point
{
private:
    // Instance variables
    std::string _name;
    int _height;
    int _sci_fi;

public:
    // Default constructor
    Point(std::string name, int height, int sci_fi):_name(name), _height(height), _sci_fi(sci_fi) {}

    // Accessor methods
    std::string name() const { return _name; }
    int height() const { return _height; }
    int sci_fi() const { return _sci_fi; }
};


#endif
