//
//  Graph.hpp
//  SFML_Again
//
//  Created by Long Hoang Nguyen on 11/27/19.
//  Copyright © 2019 Hoang Nguyen. All rights reserved.
//
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
    int order;
    int cor_x;
    int cor_y;

};

class Graph {
private:
    vector<Vertex>vertices;
    vector<pair<int,int>>edges;
public:
    Graph();
    
    
};
