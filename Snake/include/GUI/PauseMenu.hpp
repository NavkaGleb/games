#pragma once

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "Button.hpp"

namespace ng::gui {

	class PauseMenu : public sf::Drawable {
	public:
		// constructor / destructor

		// public methods

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::RectangleShape _background;
		std::map<std::string, Button*> _buttons;

		// private methods

	}; // class PauseMenu

} // namespace ng::gui