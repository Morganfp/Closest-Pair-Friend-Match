/*
* FILE: main.cpp
* AUTHOR: Morgan Purcell
* DATE: 04/2023
* PURPOSE: main function for finding the closest pairs
*/

// Include the necessary libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

// Include the necessary header files
#include "Point.hpp"
#include "mergeSort.hpp"


// Struct to hold the resulting points names and distance between them
struct Result
{
    std::string name1;
    std::string name2;
    double delta;
};


// Function to calculate the distance/delta between two people
double distance(int h1, int s1, int h2, int s2)
{
    // The distance between two people
    double delta = sqrt(pow((h1-h2),2)+pow((s1-s2),2));
    // Return delta
    return delta;
}


// Brute force to find distance for 3 or less points
double brute(std::vector<Point> points, Result* result)
{
    // Initalize delta to the current best delta
    double delta = result->delta;

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i+1; j < points.size(); j++)
        {
            // Calculate the distance of the current points
            double dist = distance(points[i].height(), points[i].sci_fi(), points[j].height(), points[j].sci_fi());

            // Check if the computed distance is less than the current delta
            if (dist < result->delta)
            {
                // Update the current delta and names of the points 
                result->delta = dist;
                result->name1 = points[i].name();
                result->name2 = points[j].name();
            }
        }
        
    }

    // Return delta
    return delta;
}


// Find the closest points by x value
double closestPairX(std::vector<Point> points, Result* result)
{
    // Base case: If the number of points is <= 3 we can calculate the closest points by brute force
    if (points.size() <= 3)
    {
        // Set delta equal to the distance between the closest points
        double delta = brute(points, result);
        return delta;
    }

    // Find the midpoint
    int middle = points.size() / 2;

    // Initalize two sub vectors to store the left and right halves of the parent vector
    std::vector<Point> left_points(points.begin(), points.begin() + middle);
    std::vector<Point> right_points(points.begin() + middle, points.end());

    // Continue to half the sub vectors
    double delta_left = closestPairX(left_points, result);
    double delta_right = closestPairX(right_points, result);

    // Set delta equal to the minimum of the left and right deltas
    double delta = std::min(delta_left, delta_right);    

    return delta;
}


// Find the closest points within a distance of 2*delta from the midpoint
void closestPairY(std::vector<Point> points, int mid_x, Result* result)
{
    // Filter the points that are in the delta distance strip to the left or right of the midpoint
    std::vector<Point> strip_points;
    for (size_t i = 0; i < points.size(); i++)
    {
        // Check if the abosulte value of a points x/height is within the delta distance strip of the midpoint
        if (std::abs(points[i].height() - mid_x) <= result->delta)
        {
            // Push that point into the filtered points if so
            strip_points.push_back(points[i]);
        }   
    }
    
    // Sort the vector by y/sci-fi values
    // Passing false means the points are sorted by y/sci-fi
    mergeSort(strip_points, false);
 
    // Interate over the points in the delta distance strip
    for (int i = 0; i < strip_points.size(); i++)
    {
        // Iterate over the minimum of the next 12 months points or the size of the vector(if it contains less than 12 points)
        for (int j = i+1; j < std::min(i+12, (int)strip_points.size()); j++)
        {
            // Calculate the distance of the current points
            double dist = distance(strip_points[i].height(), strip_points[i].sci_fi(), strip_points[j].height(), strip_points[j].sci_fi());
            // Check if the computed distance is less than the current delta
            if(dist < result->delta) 
            {
                // Update the current delta and names of the points 
                result->delta = dist;
                result->name1 = strip_points[i].name();
                result->name2 = strip_points[j].name();
            }
        }
    } 
    
    return;
}


int main(int argc, char **argv)
{
    // Initialize the file name to element 1 on the command line
    std::string filename = argv[1];
    // Initlaize the file object
    std::ifstream ifile(filename);
    // Check if the file can be opened 
    if (!ifile.is_open())
    {
        std::cerr << "Error: could not open file\n";
        return 1;
    }
    // File was opened successfully
    else
    {
        // Variable to hold the number of people the file contains
        int num_people;
        ifile >> num_people;

        // Vector of Point objects to hold the points/people
        std::vector<Point> points;
        // Variables to hold the name, height, and sci-fi rating for points
        std::string name;
        int height;
        int sci_fi;

        // Read points from the file into the points vector
        for (int i = 0; i < num_people; i++)
        {
            // Store the name, height, and sci-fi score from the file
            ifile >> name >> height >> sci_fi;
            // Construct a point object
            Point point(name, height, sci_fi);
            // Push the current point into the points vector
            points.push_back(point);
        }

        // Sort the vector by x/height values
        // Passing true means the points are sorted by x/height
        mergeSort(points, true);

        // Initalize a struct object to hold the points with the closest distance
        Result result;
        // Initalize delta to the distance between the first and second point
        result.delta = distance(points[0].height(), points[0].sci_fi(), points[1].height(), points[1].sci_fi());

        // If there's less than 2 points, the closest points can not be calculated
        if (points.size() < 2)
        {
            std::cerr << "The file does not contain enough points to measure the distance";
            return 1;
        }

        // If there's 2 points, the closest points have been found
        else if (points.size() < 3)
        {
            result.name1 = points[0].name();
            result.name2 = points[1].name();
        }

        // If there's more than 2 points, calculate the closest points
        else
        {
            // Find the closest pair by x/height
            closestPairX(points, &result);

            // Find the midpoint
            int mid_x = points[points.size()/2].height();
            
            // Find the closest points within a distance of 2*delta from the midpoint
            closestPairY(points, mid_x, &result);
        }
 
        // Display the distance between the closest points and the name's of the points
        std::cout << "\nMin Distance: " << result.delta << "\n" << "Between " << result.name1 << " and " << result.name2 << "\n\n";

    }

    return 0;
}
