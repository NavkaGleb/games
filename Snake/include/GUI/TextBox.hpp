#pragma once

#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

namespace ng::gui {

	class TextBox : public sf::Drawable {
	public:
		// enums
		enum ReservedKey { Delete = 8, Enter = 13, Escape = 27 };

		// constructor / destructor
		TextBox(unsigned characterSize, bool active);
		~TextBox() override;

		// accessors
		[[nodiscard]] const bool& active() const;
		[[nodiscard]] std::string str() const;

		// modifiers
		void setPosition(const float& x, const float& y);
		void setFont(const sf::Font& font);
		void active(const bool& active);

		// public methods
		void input(const sf::Event& event);
		void update(const int& character);

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::Text _textBox;
		std::ostringstream _text;
		bool _active;

		// private methods
		void _deleteLast();

	}; // class TextBox

} // namespace ng::gui