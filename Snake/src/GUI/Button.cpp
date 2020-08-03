#include "Button.hpp"

namespace ng {

	// constructor / destructor
	Button::Button(float x, float y, float width, float height,
				   sf::Color idle, sf::Color hover, sf::Color active, sf::Font& font)
		: _font(font) {

		this->_shape.setPosition(x, y);
		this->_shape.setSize(sf::Vector2f(width, height));

	}

	Button::~Button() {



	}

	// public methods

	// private methods

} // namespace ng