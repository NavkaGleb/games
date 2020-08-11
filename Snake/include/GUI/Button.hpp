#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace ng::gui {

	class Button : public sf::Drawable {
	public:
		// enums
		enum States { Idle = 0, Hover, Active };
		enum Alignment { Left = 0, Right, Center };

		// constructor / destructor
		Button(float x, float y, float width, float height,
			const std::string& text, unsigned characterSize, sf::Font& font,
			sf::Color bidle, sf::Color bhover, sf::Color bactive,
			sf::Color tidle = sf::Color(0, 0, 0, 255),
			sf::Color thover = sf::Color(0, 0, 0, 255),
			sf::Color tactive = sf::Color(0, 0, 0, 255));
		~Button() override;

		// accessors
		bool isPressed() const;

		// modifiers

		void setFont(const sf::Font& font);
		void setText(const std::string& text);
		void setCharacterSize(const unsigned& size);

		// public methods
		void update(const sf::Vector2i& mousePosition);

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::RectangleShape _shape;
		std::map<std::string, sf::Color> _colors;
		sf::Text _text;
		short _state;

		// private methods

	}; // class Button

} // namespace ng::gui