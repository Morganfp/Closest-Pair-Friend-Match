/*
* FILE: mergeSort.hpp
* AUTHOR: Morgan Purcell
* DATE: 04/2023
* PURPOSE: Implementation of the merge sort algorithm to sort points by x/height or y/sci-fi values
*/

#ifndef _MERGESORT_HPP_
#define _MERGESORT_HPP_

// Include the necessary header files
#include "Point.hpp"


// Helper function to merge vectors
void merge(const std::vector<Point> left_sub_vec, const std::vector<Point> right_sub_vec, std::vector<Point> &sorted_vec, bool sort_by_height);


// Function which implements merge sort
void mergeSort(std::vector<Point> &vec_to_sort, bool sort_by_height);


#endif
