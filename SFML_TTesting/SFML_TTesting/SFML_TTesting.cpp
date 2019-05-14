// SFML_TTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// SFML_Test.cpp : snake game

#include "pch.h"
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>
#include <iostream>
#include <cstdlib>

//dimensions for window size and background
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox; //background number of pixels in width == 320
int h = size * num_vertBox;    //background number of pixels in height == 480


int main()
{
	//Setting pseudorandom time, TODO:discuss true random vs pseudorandom 
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(w, h), "Space Collision");
	

	//Textures load an image into the GPU Memory
	sf::Texture  t5, t6, t7, t8;
	t5.loadFromFile("images/spaceShip.png");//ship
	t6.loadFromFile("images/outerSpace.png");//background
	t7.loadFromFile("images/ohNo.png");//losing screen
	t8.loadFromFile("images/star.png"); //star


	//Sprite has physical dimmensions that can be set in 
	//coordinate system, setPosition(x,y), and drawn on screen
	sf::Sprite ship(t5);
	sf::Sprite background(t6);//background
	sf::Sprite duck(t7); //psyduck
	sf::Sprite star(t8);//star

	//place the star 
	int starX = rand() % w, starY = 0;
	star.setPosition(starX, 0);

	//starting point for the space ship at the bottom center of the screen
	int x = 120; // sprite is only moving on x axis
	int y = 400;
	int changeX = 0;
	ship.setPosition(x, y);// absolute position
	background.setPosition(0, 0);//background
	sf::Clock clock;
	float timer = 0.0f, delay = 0.1f;
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				break;
			}
		}

		//controls for ship
		//moves ship left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			ship.move(-.3f, 0);
		}
		//moves ship right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			ship.move(.3f, 0);
		}


		//controls for star
		//moves star left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			//move(x,y)
			star.move(-.4f, 0);
		}
		//moves star right 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			star.move(.4f, 0);
		}
		//moves star up
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			star.move(0,-.4f);
		}
		//moves star down
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			star.move(0, .4f);
		}

		duck.setPosition(0, 0);
		if (ship.getGlobalBounds().intersects(star.getGlobalBounds()))
		{
			window.clear(); //clears window for new frame
			window.draw(duck);
			window.display(); //losing screen
			std::cout << "collision" << std::endl;
			break;
		}
		else
			std::cout << "no collision" << std::endl;

		window.clear();
		window.draw(background);
		window.draw(ship);
		window.draw(star);

		window.display();
	}
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
