#include "Button.hpp"

#include <cmath>
#include <iostream>

namespace ng::gui {

	// constructor / destructor
	Button::Button(float x, float y, float width, float height,
		const std::string& text, unsigned characterSize, sf::Font& font,
		sf::Color bidle, sf::Color bhover, sf::Color bactive,
		sf::Color tidle, sf::Color thover, sf::Color tactive)
		: _state(STATES::IDLE) {

		// init shape
		this->_shape.setPosition(x, y);
		this->_shape.setSize(sf::Vector2f(width, height));
		this->_shape.setFillColor(bidle);

		// init text
		this->_text.setCharacterSize(characterSize);
		this->_text.setFont(font);
		this->_text.setString(text);
		this->_text.setFillColor(sf::Color(0, 0, 0, 255));
		this->_text.setOrigin(
			this->_text.getGlobalBounds().left + this->_text.getGlobalBounds().width / 2.f,
			this->_text.getGlobalBounds().top + this->_text.getGlobalBounds().height / 2.f
		);
		this->_text.setPosition(
			x + width / 2.f,
			y + height / 2.f
		);

		std::cout << "x = " << this->_text.getPosition().x << ", y = " << this->_text.getPosition().y << std::endl;
		std::cout << "width = " << this->_text.getGlobalBounds().width << ", height = " << this->_text.getGlobalBounds().height << std::endl;

		// init colors
		this->_colors["buttonIdle"] = bidle;
		this->_colors["buttonHover"] = bhover;
		this->_colors["buttonActive"] = bactive;
		this->_colors["textIdle"] = tidle;
		this->_colors["textHover"] = thover;
		this->_colors["textActive"] = tactive;

	}

	Button::~Button() {



	}

	// accessors
	bool Button::isPressed() const { return this->_state == STATES::ACTIVE; }

	// modifiers

	// public methods
	void Button::update(const sf::Vector2i& mousePosition) {

		this->_state = STATES::IDLE;

		if (this->_shape.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {

			this->_state = STATES::HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				this->_state = STATES::ACTIVE;

		}

		if (this->_state == STATES::IDLE) {

			this->_shape.setFillColor(this->_colors["buttonIdle"]);
			this->_text.setFillColor(this->_colors["textIdle"]);

		} else if (this->_state == STATES::HOVER) {

			this->_shape.setFillColor(this->_colors["buttonHover"]);
			this->_text.setFillColor(this->_colors["textHover"]);

		} else if (this->_state == STATES::ACTIVE) {

			this->_shape.setFillColor(this->_colors["buttonActive"]);
			this->_text.setFillColor(this->_colors["textActive"]);

		}

	}

	void Button::render(sf::RenderTarget& target) {

		target.draw(this->_shape);
		target.draw(this->_text);

	}

	// private methods

} // namespace ng::gui