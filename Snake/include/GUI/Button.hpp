#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace ng {

	class Button {
	public:
		// constructor / destructor
		Button(float x, float y, float width, float height, sf::Color idle, sf::Color hover, sf::Color active, sf::Font& font);
		virtual ~Button();

		// public methods

	private:
		// variables
		sf::RectangleShape _shape;
		std::map<std::string, sf::Color> _colors;
		sf::Font& _font;

		// private methods

	}; // class Button

} // namespace ng