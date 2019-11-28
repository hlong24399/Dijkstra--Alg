//
//  Graph.cpp
//  SFML_Again
//
//  Created by Long Hoang Nguyen on 11/27/19.
//  Copyright © 2019 Hoang Nguyen. All rights reserved.
//

#include "Graph.hpp"
Graph::Graph() {
    ifstream in;
    string name;
    cout << " Enter file name: ";
    getline(cin,name);
    in.open(name);
    while (1) {
        if ( in.fail() ) {
            cout << " Failed to open file " << endl;
            cout << " Enter the name again : ";
            cin.clear();
            getline(cin,name);
        }
        else break;
    }
    int sz;
    in >> sz;
    Vertex temp;
    while ( !in.eof() && in >> temp.order >> temp.cor_x >> temp.cor_y ) {
        vertices.push_back(temp);
    }
    for ( auto i : vertices)  {
        cout << i.order << "--" << i.cor_x << "--" << i.cor_y << endl;
    }
}
