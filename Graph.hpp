//
//  Graph.hpp
//  SFML_Again
//
//  Created by Long Hoang Nguyen on 11/27/19.
//  Copyright © 2019 Hoang Nguyen. All rights reserved.
//
#pragma once
#include <fstream>
#include <utility>
#include <iostream>
#include <iterator>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
using namespace std;


//To represent a Vertex
struct Vertex {
    int order;
	float cor_x;
    float cor_y;

};

//To represent an Edge
struct Edge {
	//This overload is to compare the edge later on.
	bool operator== (const Edge& ob1) {
		return (ob1.e.first.order == e.first.order && ob1.e.second.order == e.second.order || 
			ob1.e.second.order == e.first.order && ob1.e.first.order == e.second.order);
	}
	int w{}; //Weight
	pair<Vertex, Vertex>e; //Head and Tail
};

//To build 2d dynamic matrix
struct column {
	int* row;
};

//Initialize every vertices with its distance to be INF and visited status is false
struct Dijkstra_Utility {
	bool visited = false;
	int dist = INT_MAX;
};


class Graph {
public:
    //These are to store
	vector<Vertex>vertices;
    vector<Edge>edges;
	
	//These are to save number of vertices and edges counted from input
	int v_amounts;
	int e_amounts;

	//These are to draw
	vector<sf::CircleShape>d_vertices;
	sf::VertexArray de;
	
	//This one is to create dynamic 2d adjacency matrix.
	column* matrix;

	//Save the shortest path
	vector<int>path;
	
public:
	Graph(); //Initialization
	Edge addEdge(int, pair<Vertex,Vertex>);
	void setEdge();	//Set up all the edges ( work together with addEdge )
	void setDrawVertices();	//Set up the SFML vertices
	void setMatrix();		//Adjacent matrix builder
	void setDrawEdges();	//Set up the SFML edges
	
	
	void print_route(vector<int>& prev, int i);		//Recursion for the previous vertices trace. ( work with Graph::ShortestPath(int,int) only)
	int minVertex(Dijkstra_Utility*);				//To find the minimum distance to the current vertex ( work with Graph::ShortestPath(int,int) only)
	void ShortestPath(int s, int e);				//Dijsktra Algorithm
	void resetShortestPath();
	
	
	void DrawselectedPath(vector<int> v);			//Draw the path.
	vector<sf::CircleShape>getDrawVertices();		//Return the SFML 
	sf::VertexArray getDrawEdges();					//	drawing shapes.
	
	void options_list();
	void newVertex();
	void newEdge();
    
};
