/*
* FILE: mergeSort.cpp
* AUTHOR: Morgan Purcell
* DATE: 04/2023
* PURPOSE: Define merge sort functions
*/

// Included the libraries needed
#include <vector>
#include <string>

// Include the necessary header files
#include "mergeSort.hpp"

// Helper function to merge vectors
void merge(const std::vector<Point> left_sub_vec, const std::vector<Point> right_sub_vec, std::vector<Point> &sorted_vec, bool sort_by_height)
{
    // Get the size of left and right sub vectors
    int left_size = left_sub_vec.size();
    int right_size = right_sub_vec.size();
    int i = 0, l = 0, r = 0;

    // Populate the sorted vector
    // While there are still elements in the left and right sub vectors
    while(l < left_size && r < right_size)
    {
        // Sort by height
        if(sort_by_height)
            // Compare elements in the left and right sub vectors and add the smaller element to the sorted vector
            // Increment the index position in the left or right sub vector depending on which is smaller
            if(left_sub_vec[l].height() < right_sub_vec[r].height())
            {
                sorted_vec[i++] = left_sub_vec[l++];
            }
            else
            {
                sorted_vec[i++] = right_sub_vec[r++];
            }
        // Sort by sci_fi
        else
        {
            // Compare elements in the left and right sub vectors and add the smaller element to the sorted vector
            // Increment the index position in the left or right sub vector depending on which is smaller
            if(left_sub_vec[l].sci_fi() < right_sub_vec[r].sci_fi())
            {
                sorted_vec[i++] = left_sub_vec[l++];
            }
            else
            {
                sorted_vec[i++] = right_sub_vec[r++];
            }   
        }
    }

    // Check if theres any element left over and add them to the sorted vector
    while(l < left_size)
    {
        sorted_vec[i++] = left_sub_vec[l++];
    }
    while(r < right_size)
    {
        sorted_vec[i++] = right_sub_vec[r++];
    }
}


// Function which implements merge sort
void mergeSort(std::vector<Point> &vec_to_sort, bool sort_by_height)
{
    // Base case: if the vectors size is 1 or less
    if (vec_to_sort.size() <= 1) return;
    
    // Find the middle of the vector
    int middle = vec_to_sort.size() / 2;

    // Initalize two sub vectors to store the left and right halves of the main vector
    std::vector<Point> left_sub_vec(vec_to_sort.begin(), vec_to_sort.begin() + middle);
    std::vector<Point> right_sub_vec(vec_to_sort.begin() + middle, vec_to_sort.end());

    // Recursive calls to the left and right sub vectors to split them up further
    mergeSort(left_sub_vec, sort_by_height);
    mergeSort(right_sub_vec, sort_by_height);

    // Merge the vectors while sorting them once the base case has been met
    merge(left_sub_vec, right_sub_vec, vec_to_sort, sort_by_height);
}
