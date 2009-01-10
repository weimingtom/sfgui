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
#include "checkbox.hpp"
#include <iostream>

sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML GUI");
sfgui::Button Sprite(&App,"data/button-test/");

void textChangeCallback(std::string &sr) {
	std::cerr<<"Modif : " << sr << "\n";
}
void textDeletedCallback(unsigned int pos, char str) {
	std::cerr<<"Deleted at "<<pos<<" char : "<<str<<std::endl;
}
void checkedCallback(){
	std::cout<<"checked"<<std::endl;
}
void uncheckedCallback(){
	std::cout<<"unchecked"<<std::endl;
}
int main() {

	// Create the main rendering window
	sf::Color col(235,235,235);

	// Create the sprite
	Sprite.SetText("The text");
	Sprite.Resize(300, 50);

	Sprite.SetPosition(200, 100);
	Sprite.SetTextAlignment(sfgui::Right);
	Sprite.SetTextRightMargin(20);

	sfgui::TextEdit But(&App);
	But.SetText("Texte de base");
	But.SetPosition(100,400);
	But.SetTextChangedCallback(&textChangeCallback);
	But.SetCharDeletedCallback(&textDeletedCallback);
	But.Resize(100, 40);
	But.SetMode(sfgui::TextEdit::ModePassword);

	sfgui::Checkbox Chek(&App);
	Chek.SetPosition(100,100);
	Chek.SetState(true);
	Chek.SetCheckedCallback(&checkedCallback);
	Chek.SetUncheckedCallback(&uncheckedCallback);
	Chek.Resize(30,30);

	// Start game loop
	while (App.IsOpened())
	{
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			Sprite.CheckEvent(Event);
			But.CheckEvent(Event);
			Chek.CheckEvent(Event);
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
		Chek.Show();
		// Display window contents on screen
		App.Display();
	}

	return EXIT_SUCCESS;
}
