#pragma once

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

namespace ng::gui {

	class TextBox : public sf::Drawable {
	public:
		// enums
		enum ReservedKey { Delete = 8, Enter = 13, Escape = 27 };
		enum Alignment { Left = 0, Right, Center };

		// constructor / destructor
		TextBox(float x, float y, float width, float height,
			unsigned characterSize, const sf::Font& font, const sf::Color& backgroundColor, short alignment = Alignment::Center);
		~TextBox() override;

		// accessors
		[[nodiscard]] const bool& active() const;
		[[nodiscard]] std::string str() const;

		// modifiers
		void setPosition(const float& x, const float& y);
		void setSize(const float& width, const float& height);
		void setFont(const sf::Font& font);
		void setBackgroundFillColor(const sf::Color& color);
		void setCharacterSize(const unsigned& characterSize);
		void setActive(const bool& active);
		void setLimit(const int& limit);

		// public methods
		void textEntered(const sf::Event& event);

		void update(const sf::Vector2i& mousePosition);

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::RectangleShape _shape;
		sf::Text _text;
		std::ostringstream _oss;
		bool _active;
		int _limit;
		short _alignment;

		// private methods
		void _addCharacter(const int& character);
		void _deleteLastCharacter();
		void _align();

	}; // class TextBox

} // namespace ng::gui