#include "ScoreBar.hpp"

#include <cmath>
#include <iostream>

namespace ng::gui {

	ScoreBar::ScoreBar(float x, float y, const sf::Font& font, unsigned characterSize, sf::Color color, short alignment)
		: _x(x), _alignment(alignment) {

		// init text
		this->_text.setFont(font);
		this->_text.setCharacterSize(characterSize);
		this->_text.setFillColor(color);
		this->_text.setString(std::to_string(0));
		this->_align(x, y);

	}

	ScoreBar::~ScoreBar() {



	}

	// public methods
	void ScoreBar::update(const int& score) {

		std::cout << this->_text.getGlobalBounds().height << std::endl;

		this->_text.setString(std::to_string(score));
		this->_align(this->_x, this->_text.getPosition().y);
	}

	// protected methods
	void ScoreBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->_text);

	}

	// private methods
	void ScoreBar::_align(const float& x, const float& y) {

		float width = this->_text.getGlobalBounds().width;

		if (this->_alignment == Alignment::Left)
			this->_text.setPosition(std::floor(x), std::floor(y));
		else if (this->_alignment == Alignment::Right)
			this->_text.setPosition(std::floor(x - width), std::floor(y));
		else if (this->_alignment == Alignment::Center)
			this->_text.setPosition(std::floor(x - (width / 2.f)), std::floor(y));

	}

} // namespace ng::gui