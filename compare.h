/*
Name: Sam Sutton
Date: 12/14/2022
Purpose: Final Project
*/
#pragma once

#include "node.h"

class Compare {
public:
    bool operator()(const Node* left, const Node* right) const;
};