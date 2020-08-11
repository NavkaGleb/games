#include "StatusBar.hpp"

#include <cmath>

namespace ng::gui {

	// constructor / destructor
	StatusBar::StatusBar(float x, float y, float width, float height, sf::Color backgroundColor, sf::Color statusColor)
		: _active(false) {

		// init background
		this->_background.setPosition(x, y);
		this->_background.setSize(sf::Vector2f(width, height));
		this->_background.setFillColor(backgroundColor);

		// init status
		this->_status.setPosition(x, y);
		this->_status.setSize(sf::Vector2f(width, height));
		this->_status.setFillColor(statusColor);

	}

	StatusBar::~StatusBar() {



	}

	// accessors
	const bool& StatusBar::active() const { return this->_active; }

	// modifiers
	void StatusBar::active(const bool& active) { this->_active = active; }

	// public methods
	void StatusBar::update(const float& percentage) {

		this->_status.setSize(sf::Vector2f(
			std::floor(this->_background.getGlobalBounds().width * percentage),
			this->_status.getGlobalBounds().height
		));

	}

	// protected methods
	void StatusBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->_background);
		target.draw(this->_status);

	}

	// private methods

} // namespace ng::gui