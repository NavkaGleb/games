#pragma once

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "Button.hpp"

namespace ng::gui {

	class PauseMenu : public sf::Drawable {
	public:
		// constructor / destructor
		PauseMenu(const sf::VideoMode& vm, unsigned characterSize, const sf::Font& font, float y);
		~PauseMenu() override;

		// accessors
		[[nodiscard]] const bool& active() const;
		[[nodiscard]] bool isButtonPressed(const std::string& key) const;

		// modifiers
		void active(const bool& active);

		// public methods
		void addButton(const float& y, const float& offsety, const float& width, const float& height, const
			std::string& text, const unsigned& characterSize,
			const sf::Color& bidle, const sf::Color& bhover, const sf::Color& bactive);

		void updateMousePosition(const sf::Vector2i& mousePosition);
		void update(const sf::Vector2i& mousePosition);

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::RectangleShape _background;
		std::map<std::string, Button*> _buttons;
		const sf::Font& _font;
		sf::Text _text;
		bool _active;

		// private methods

	}; // class PauseMenu

} // namespace ng::gui