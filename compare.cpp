/*
Name: Sam Sutton
Date: 12/14/2022
Purpose: Final Project
*/
#include "compare.h"

bool Compare::operator()(const Node* left, const Node* right) const {
    return left->frequency > right->frequency;
}
