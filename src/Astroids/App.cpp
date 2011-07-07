#include <SFML/Window.hpp>

int main()
{
	sf::Window App(sf::VideoMode(800,600,32),"SFML Window");


	while(true)
	{
		App.Display();
	}
}
