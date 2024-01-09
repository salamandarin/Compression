/*
Name: Sam Sutton
Date: 12/14/2022
Purpose: Final Project
*/
#pragma once

#include <string>

struct Node {
    Node(std::string letters, int frequency, Node* left = nullptr,
            Node* right = nullptr)
        :letters{letters}, frequency{frequency}, left{left}, right{right} {}

    std::string letters;
    int frequency;
    Node *left, *right;
};