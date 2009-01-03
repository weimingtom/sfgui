/****************************
 * Auteur :Tanguy Arnaud
 * Date :
 * Version : 1.0
 *
 * Copyright (C) 2008 TANGUY Arnaud
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 ******************************/

#include "button.hpp"
#include "textedit.hpp"
#include <iostream>

sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML GUI");
sfgui::Button Sprite(&App);

void clickedCallBack() {
	static float size = 10;
	Sprite.SetTextSize(size);
	size++;
	std::cerr<<"The button text is : " << Sprite.GetText();
}
void textChangeCallback(std::string &sr) {
	std::cerr<<"Modif : " << sr << "\n";
}
int main() {

	// Create the main rendering window
	sf::Color col(235,235,235);

	// Create the sprite
	Sprite.SetText("The text");
	Sprite.SetClickCallback(&clickedCallBack);
	Sprite.SetTheme("data/button/");
	Sprite.Resize(300, 50);

	Sprite.SetPosition(200, 100);
	Sprite.SetTextAlignment(sfgui::Right);
	Sprite.SetTextRightMargin(20);

	sfgui::TextEdit But(&App);
	But.SetPosition(400,400);
	But.SetTheme("data/button/");
	But.SetTextChangedCallback(&textChangeCallback);
	But.Resize(400, 40);
	// Start game loop
	while (App.IsOpened())
	{
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			Sprite.CheckEvent(Event);
			But.CheckEvent(Event);
			// Close window : exit
			if (Event.Type == sf::Event::Closed) {
				App.Close();
			}
		}

		// Get elapsed time
		float ElapsedTime = App.GetFrameTime();

		// Move the sprite
		if (App.GetInput().IsKeyDown(sf::Key::Left)) Sprite.Move(-100 * ElapsedTime, 0);
		if (App.GetInput().IsKeyDown(sf::Key::Right)) Sprite.Move( 100 * ElapsedTime, 0);
		if (App.GetInput().IsKeyDown(sf::Key::Up))    Sprite.Move(0, -100 * ElapsedTime);
		if (App.GetInput().IsKeyDown(sf::Key::Down))  Sprite.Move(0,  100 * ElapsedTime);

		// Rotate the sprite
		if (App.GetInput().IsKeyDown(sf::Key::Add))      Sprite.Rotate(- 100 * ElapsedTime);
		if (App.GetInput().IsKeyDown(sf::Key::Subtract)) Sprite.Rotate(+ 100 * ElapsedTime);

		// Clear screen
		App.Clear(col);

		// Display sprite in our window
		Sprite.Show();
		But.Show();
		// Display window contents on screen
		App.Display();
	}

	return EXIT_SUCCESS;
}
