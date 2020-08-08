#include "Button.hpp"

#include <cmath>

namespace ng::gui {

	// constructor / destructor
	Button::Button(float x, float y, float width, float height, const std::string& text,
		sf::Color idle, sf::Color hover, sf::Color active, sf::Font& font)
		: _font(font), _state(STATES::IDLE) {

		this->_shape.setPosition(x, y);
		this->_shape.setSize(sf::Vector2f(width, height));
		this->_shape.setFillColor(idle);

		this->_text.setCharacterSize(30);
		this->_text.setFont(this->_font);
		this->_text.setString(text);
		this->_text.setFillColor(sf::Color(0, 0, 0, 255));
		this->_text.setPosition(
			std::floor(x + (width - this->_text.getGlobalBounds().width) / 2.f),
			std::floor(y + (height - this->_text.getGlobalBounds().height) / 2.f)
		);

		this->_colors["idle"] = idle;
		this->_colors["hover"] = hover;
		this->_colors["active"] = active;

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

		if (this->_state == STATES::IDLE)
			this->_shape.setFillColor(this->_colors["idle"]);
		else if (this->_state == STATES::HOVER)
			this->_shape.setFillColor(this->_colors["hover"]);
		else if (this->_state == STATES::ACTIVE)
			this->_shape.setFillColor(this->_colors["active"]);

	}

	void Button::render(sf::RenderTarget& target) {

		target.draw(this->_shape);
		target.draw(this->_text);

	}

	// private methods

} // namespace ng::gui