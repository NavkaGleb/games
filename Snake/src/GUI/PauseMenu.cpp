#include "PauseMenu.hpp"

namespace ng::gui {

	// constructor / destructor

	// public methods

	// protected methods
	void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates) const {

		target.draw(this->_background);

		for (const auto& p : this->_buttons)
			target.draw(*p.second);

	}

	// private methods

} // namespace ng::gui