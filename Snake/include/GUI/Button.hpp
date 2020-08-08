#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace ng::gui {

	enum STATES { IDLE = 0, HOVER, ACTIVE };

	class Button {
	public:
		// constructor / destructor
		Button(float x, float y, float width, float height,
			const std::string& text, unsigned characterSize, sf::Font& font,
			sf::Color bidle, sf::Color bhover, sf::Color bactive,
			sf::Color tidle = sf::Color(0, 0, 0, 255),
			sf::Color thover = sf::Color(0, 0, 0, 255),
			sf::Color tactive = sf::Color(0, 0, 0, 255));
		virtual ~Button();

		// accessors
		bool isPressed() const;

		// modifiers

		// public methods
		void update(const sf::Vector2i& mousePosition);
		void render(sf::RenderTarget& target);

	private:
		// variables
		sf::RectangleShape _shape;
		std::map<std::string, sf::Color> _colors;
		sf::Text _text;
		short _state;

		// private methods

	}; // class Button

} // namespace ng::gui