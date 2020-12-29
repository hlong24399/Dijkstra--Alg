//
//  Graph.cpp
//  SFML_Again
//
//  Created by Long Hoang Nguyen on 11/27/19.
//  Copyright © 2019 Hoang Nguyen. All rights reserved.
//

#include "Graph.h"

//Set the termination condition for the program to be false.
bool Graph::sentinel = false;

Graph::Graph() {



	ifstream in;
	string name;
	cout << " Enter file name: ";
	in.open("cor.txt");
	if (in.fail()) {
		cout << " Failed to open file " << endl;
	}
	cout << endl;
	//Set up vertices
	Vertex temp;
	while (!in.eof() && in >> temp.order >> temp.cor_x >> temp.cor_y) vertices.push_back(temp);
	cout << endl;
	setDrawVertices();

	//Set up font
	font.loadFromFile("opensans.ttf");

	//Set up texts
	setDrawTexts_v();

	//Set up edges
	setEdge();
	setDrawEdges();

	//Set up texts
	setDrawTexts_e();

	//Set up the adjacency matrix.
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
	ifstream in;
	in.open("edge.txt");
	if (in.fail()) {
		cout << " Failed to open file " << endl;
	}
	cout << endl;
	int temp_weight;
	int temp_start;
	int temp_end;
	while (!in.eof() && in >> temp_start >> temp_end >> temp_weight) {
		edges.push_back(addEdge(temp_weight, make_pair(vertices[temp_start], vertices[temp_end])));

	}
	cout << endl;
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

void Graph::setDrawTexts_v()
{
	// select the font
	v_texts.resize(v_amounts);
	for ( int i = 0; i < v_amounts; i++ ) {

		char c = vertices[i].order + '0';
		cout << c;
		v_texts[i].setFont(font);
		v_texts[i].setString(c);
		v_texts[i].setCharacterSize(24); // in pixels, not points!
		v_texts[i].setFillColor(sf::Color::Magenta);
		v_texts[i].setStyle(sf::Text::Bold);
		v_texts[i].setPosition(vertices[i].cor_x-13, vertices[i].cor_y-13);

	}

}

void Graph::setDrawTexts_e()
{
	e_texts.resize(e_amounts);
	for ( int i = 0; i < e_amounts; i++)
	{
		// de[2 * i].position
		// de[2 * i + 1].position

		e_texts[i].setFont(font);
		char c = edges[i].w + '0';
		e_texts[i].setString(c);
		e_texts[i].setCharacterSize(18); // in pixels, not points!
		e_texts[i].setFillColor(sf::Color::Red);
		e_texts[i].setStyle(sf::Text::Bold);
		e_texts[i].setPosition((de[2*i].position.x+de[2*i+1].position.x)/2, (de[2*i].position.y+de[2*i+1].position.y)/2);

	}
}

vector<sf::Text> Graph::getDrawTexts_e()
{
	return e_texts;
}


vector<sf::Text> Graph::getDrawTexts_v()
{
	return v_texts;
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

	resetShortestPath();
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
				pre_v[t] = c;		//Previous Vertex of t.
			}
		}
	}
	/*for (int a = 0; a < v_amounts; a++) {
		cout << d[a].dist << endl;
	}*/ //Uncm this to see list of distance.

	//If there is no edge connecting between the 2 vertices, it's distance will remain INF, which is less than 0
	if (d[e].dist < 0 || d[e].dist > 10000) {
		cout << " There is no way to connect these two. ";
		return;
	}
	cout << " Path from vertex " << s << " to vertex " << e << " has minimum cost of " <<
		d[e].dist << " Has the minimum route is ";

	print_route(pre_v, e);	//Set up vector Graph::path<int>
	reverse(path.begin(), path.end());	//After loading up the vector<int>path, it will be reversed, thus we have to reverse it back.
	for (auto i : path) cout << i << "......";
	cout << endl;
	DrawselectedPath(path);
}

void Graph::resetShortestPath()
{
	path.erase(path.begin(), path.end());
	for (int i = 0; i < de.getVertexCount(); i++) {
		de[i].color = sf::Color::Black;
	}
}

sf::VertexArray Graph::getDrawEdges()
{
	return de;
}

vector<sf::CircleShape> Graph::getDrawVertices()
{
	return d_vertices;
}

//This is the menu of obtions for the current graph.
void Graph::options_list()
{
	cout << " \n\n\n";
	cout << "Press\n";
	cout << "1 is add a vertex.";
	cout << "\n2 is add an edge.";
	cout << "\n3 is run Dijsktra to find shortest path from source to end vertex.";
	cout << "\n4 to end this thing.";
	cout << "\nYou choice : ";
	int c;
	cin >> c;
	while ( c <  1 || c > 4) {
		cout << " That's not one of those options, please try again :";
		cin >> c;
	}
	switch (c) {

	//Add new vertex
	case 1:
		newVertex();
		break;

	//Add new edge
	case 2:
		newEdge();
		break;

	//Run Dijkstra
	case 3:
		int a, b;
		cout << " Enter start and end vertex order: ";
		cin >> a >> b;
		ShortestPath(a, b);
		break;
	case 4:
		sentinel = true;  //Terminate if this one is true.
		break;
	default:
		break;
	}
}

void Graph::newVertex()
{
	//Add the new vertex into vector<Vertex>vertices and also add the new sf::CircleShape to draw.
	Vertex temp;
	cout << " The current newest vertex has order " << vertices.size()-1 << endl;
	cout << " Enter your vertices info by this order:\n ";
	cout << " (order)  (x coordinate)  (y coordinate) ";
	cin >> temp.order >> temp.cor_x >> temp.cor_y;
	vertices.push_back(temp);

	//Update value of v_amount since it's added one more now.
	v_amounts = vertices.size();
	sf::CircleShape temp_circle;
	temp_circle.setPosition(temp.cor_x, temp.cor_y);
	temp_circle.setFillColor(sf::Color::Black);
	temp_circle.setRadius(7);
	d_vertices.push_back(temp_circle);
	setMatrix(); //rebuild the matrix since the vertices structure has changed.
}

void Graph::newEdge()
{
	int o_v1, o_v2, w;			//Order of vertex 1 and 2, and the edge's weight
	cout << " Enter the 2 vertices it connects: ";
	cin >> o_v1 >> o_v2;
	cout << " Enter its weight : ";
	cin >> w;
	edges.push_back(addEdge(w, make_pair(vertices[o_v1], vertices[o_v2])));
	e_amounts = edges.size();		//Update e_amount since now there is one more edge.

	//Update the sf::VertexArray for drawing.
	sf::Vertex v1, v2;
	v1.position = sf::Vector2f(vertices[o_v1].cor_x + 7.f, vertices[o_v1].cor_y + 7.f);
	v1.color = sf::Color::Black;
	v2.position = sf::Vector2f(vertices[o_v2].cor_x + 7.f, vertices[o_v2].cor_y + 7.f);
	v2.color = sf::Color::Black;
	de.append(v1);
	de.append(v2);
	setMatrix(); //rebuild the matrix since the edge structure has changed.


}
