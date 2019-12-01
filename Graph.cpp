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
	//getline(cin,name);
	//in.open(name);
	in.open("cor2.txt");
	while (1) {
		if (in.fail()) {
			cout << " Failed to open file " << endl;
			cout << " Enter the name again : ";
			cin.clear();
			getline(cin, name);
		}
		else break;
	}
	cout << endl;
	//Set up vertices
	Vertex temp;
	while (!in.eof() && in >> temp.order >> temp.cor_x >> temp.cor_y) vertices.push_back(temp);
	cout << endl;
	setDrawVertices();

	//Set up edges
	setEdge();
	setDrawEdges();
	setMatrix();
}


Edge Graph::addEdge(int weight, pair<Vertex, Vertex> n_edge)
{
	//Add those edges.
	Edge new_edge;
	new_edge.w = weight;
	new_edge.e = n_edge;
	return new_edge;
}

void Graph::setEdge()
{
	//This part needs to be updated if we update the Vertices List from the file//
	edges.push_back(addEdge(3, make_pair(vertices[0], vertices[1])));
	edges.push_back(addEdge(1, make_pair(vertices[1], vertices[2])));
	edges.push_back(addEdge(8, make_pair(vertices[1], vertices[5])));
	edges.push_back(addEdge(5, make_pair(vertices[2], vertices[5])));
	edges.push_back(addEdge(4, make_pair(vertices[0], vertices[4])));
	edges.push_back(addEdge(3, make_pair(vertices[2], vertices[4])));
	edges.push_back(addEdge(2, make_pair(vertices[4], vertices[5])));
	edges.push_back(addEdge(7, make_pair(vertices[0], vertices[3])));
	edges.push_back(addEdge(1, make_pair(vertices[1], vertices[3])));
	edges.push_back(addEdge(9, make_pair(vertices[3], vertices[4])));
	e_amounts = edges.size();
}

void Graph::setDrawEdges()
{
	//Set up the Graph::de to draw Edges as Lines.
	de.setPrimitiveType(sf::Lines);
	de.resize(e_amounts * 2);
	for (int i = 0; i < e_amounts; i++) {
		de[2 * i].position = sf::Vector2f(edges[i].e.first.cor_x + 7.f, edges[i].e.first.cor_y + 7.f);
		de[2 * i + 1].position = sf::Vector2f(edges[i].e.second.cor_x + 7.f, edges[i].e.second.cor_y + 7.f);
		de[2 * i].color = sf::Color::Black;
		de[2 * i + 1].color = sf::Color::Black;
	}
}

void Graph::setDrawVertices()
{
	//Set up number of CircleShape needed to draw
	v_amounts = vertices.size();
	d_vertices.resize(v_amounts);
	for (int i = 0; i < v_amounts; i++) {
		d_vertices[i].setPosition(vertices[i].cor_x, vertices[i].cor_y);
		d_vertices[i].setFillColor(sf::Color::Black);
		d_vertices[i].setRadius(7);
	}

}

void Graph::setMatrix()
{
	//Allocate the number of column and row is both equal to v_amounts.
	matrix = new column[v_amounts];
	for (int i = 0; i < v_amounts; i++) {
		(matrix + i)->row = new int[v_amounts];
	}
	for (int a = 0; a < e_amounts; a++) {
		matrix[edges[a].e.first.order].row[edges[a].e.second.order] = edges[a].w;
		matrix[edges[a].e.second.order].row[edges[a].e.first.order] = edges[a].w;
	}

	//To check the matrix by exporting it to a file ( in same folder with the main.cpp )
	/*ofstream out;
	out.open("Matrix.txt");*/

	/*Since the uninitialized matrix element will have a random gabbage number from buffer, which is always negative or very big.
	thus we need to initialize them as 0*/
	for (int i = 0; i < v_amounts; i++) {
		for (int t = 0; t < v_amounts; t++) {
			if (matrix[i].row[t] < 0 || matrix[i].row[t] > 1000) {
				matrix[i].row[t] = 0;
				matrix[t].row[i] = 0;
			}
			//out << matrix[i].row[t] << " - "; //This one is to verify the matrix table.
		}
		//out << endl;
	}
}

void Graph::DrawselectedPath(vector<int> v)
{
	/*Drawing edges by selectedPath from the Algorithm. Detect the edges connected from 2 vertices saved in v[i] and v[i+1] */
	for (size_t i = 0; i < v.size() - 1; i++) {
		Edge temp;
		temp.e.first.order = v[i];
		temp.e.second.order = v[i + 1];
		for (int t = 0; t < e_amounts; t++) {
			if (edges[t] == temp) {				// == overloaded to compare 2 edges.
				/*Since every edge has 2 sf::vertex, so 10 edges will be 20 sf::vertex (for drawing purpose).
				Thus we need to multiply t by 2 to get the sf::vertex that need to change color*/
				de[t * 2].color = sf::Color::Red;
				de[t * 2 + 1].color = sf::Color::Red;
			}
		}
	}
}

/*When we initialize the previou_vertex tracks (vector<int>pre_v), we set it to be -1, thus the starting point value will only be -1 since it is the one that
 start first, no vertex will visit it as a neighbor. That's also why the base case is < 0, ( -1 < 0 ). So the recursion will read the position ( subscript ) of the
 end vertex ( parameter: int i ), push into vector<int>path, and then recurse with the same vector (pre_v), but now we want the value of that position, so that
 it will become the position of the next vertex ( subscript of the next vertex ). Keep continute the progress until it reaches the starting vertex which is -1.
*/
void Graph::print_route(vector<int>& prev, int i)
{
	if (i < 0) return;
	path.push_back(i);
	print_route(prev, prev[i]);
}
int Graph::minVertex(Dijkstra_Utility* vd)
{
	int minTempDist = INT_MAX;
	int minV{};
	for (int i = 0; i < v_amounts; i++) {
		if (vd[i].dist <= minTempDist && vd[i].visited == false) {		//Search the minimum dist from those vertices that is not visitied.
			minTempDist = vd[i].dist;
			minV = i;
		}
	}
	return minV;
}
void Graph::ShortestPath(int s, int e) //s is starting vertex. (s = 0)
{
	vector<int>pre_v(v_amounts, -1);
	Dijkstra_Utility* d = new Dijkstra_Utility[v_amounts]; //Data of Vertex
	d[s].dist = 0; //Inital Node distance is known as 0.
	int c{}; //Current Vertex
	for (int i = 0; i < v_amounts - 1; i++) {
		c = minVertex(d);			//Move to the neighbor vertex with the smallest weight
		//cout << " The current minimum vertex is " << c << endl;
		d[c].visited = true;		//To check that this vertex is visited already
		for (int t = 0; t < v_amounts; t++) {
			//Only update the dist when the edge between them exist, and the total distance is shorter than the current known distance.
			if (matrix[c].row[t] && !d[t].visited && (d[c].dist + matrix[c].row[t] < d[t].dist)) {
				d[t].dist = d[c].dist + matrix[c].row[t];
				//cout << " Just update the distance of " << t << endl;
				//cout << " Update the connected edge " << c << "--" << t << " to be " << d[t].dist << endl;
				pre_v[t] = c;
				for (auto i : pre_v) cout << i << " ***** ";
				cout << endl;
			}
		}
	}
	/*for (int a = 0; a < v_amounts; a++) {
		cout << d[a].dist << endl;
	}*/ //Uncm this to see list of distance.
	cout << " Path from vertex 0 to vertex " << e << " has minimum cost of " <<
		d[e].dist << " Has the minimum route is ";

	print_route(pre_v, e);	//Set up vector Graph::path<int>
	reverse(path.begin(), path.end());	//After loading up the vector<int>path, it will be reversed, thus we have to reverse it back.
	for (auto i : path) cout << i << "......";
	cout << endl;
	DrawselectedPath(path);
	cout << ". \n That is it, After several hours. Man!" << endl;
}

sf::VertexArray Graph::getDrawEdges()
{
	return de;
}

vector<sf::CircleShape> Graph::getDrawVertices()
{
	return d_vertices;
}
