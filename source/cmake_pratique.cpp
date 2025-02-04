// cmake_pratique.cpp : définit le point d'entrée de l'application.
//

#include "cmake_pratique.h"
#include "Maths.h"
#include "Vector2.h"
#include "SFML/Graphics.hpp"

using namespace std;

int main()
{
	sf::Vector2f vecSfml(2.8f, 7.4f);
	cout << "Valeur du vecteur : " << vecSfml.x << " / " << vecSfml.y << endl;
	Dll::Vector2 vec(82, 421);
	vec.print(vec);
	cout << "Hello CMake." << endl;
	system("Pause");
	return 0;
}
