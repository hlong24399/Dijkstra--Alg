# Dijkstra-s-Alg - Build.For.Fun


# This program will be able to do 3 things:
  1.Add new vertex/vertices.                                                                                                               
  2.Add new edge(s).                                                                                                                       
  3.Run Dijkstra Algorithm from the selected source to selected destination.

#To run this project:
1. Install SFML
sudo apt-get install libsfml-dev

2. Compile all .cpp file together
g++ -c main.cpp -o main.o

3. Link all the compiled files with the used library ( this project uses 3 libraries )
g++ main.o Graph.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

4. Run the executable file
./sfml-app

g++ -c main.cpp -o main.o; g++ main.o Graph.o -o sfml.app -lsfml-graphics -lsfml-window -lsfml-system; ./sfml-app
