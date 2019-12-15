#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Graph.hpp"
using namespace std;



int main() {
	
	sf::ContextSettings sets;
	sets.antialiasingLevel = 8; 
	sf::RenderWindow win(sf::VideoMode(1500, 1150), "Graph", sf::Style::Default, sets);
	win.setPosition(sf::Vector2i(100, 100));
	win.setFramerateLimit(60);
	Graph g;
	while (win.isOpen()) {
		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) win.close();
		}
		
		win.clear(sf::Color::White);
		for (auto i : g.getDrawVertices()) win.draw(i);
		win.draw(g.getDrawEdges());
		win.display();
		g.options_list(); //Ask for the selection.
		if (Graph::sentinel) break;
	}
	cout << " Program is ended. " << endl;





	return 0;
}
