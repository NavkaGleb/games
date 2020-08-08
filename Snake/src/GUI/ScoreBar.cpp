#include "ScoreBar.hpp"

#include <cmath>

namespace ng::gui {

	ScoreBar::ScoreBar(float x, float y, sf::Font& font, unsigned characterSize, sf::Color color)
		: _font(font) {

		// init text
		this->_text.setFont(this->_font);
		this->_text.setFillColor(color);
		this->_text.setCharacterSize(characterSize);
		this->_text.setString(std::to_string(0));
		this->_text.setPosition(x, y);

	}

	ScoreBar::~ScoreBar() {



	}

	// public methods
	void ScoreBar::update(const int& score) {

		this->_text.setString(std::to_string(score));

	}

	void ScoreBar::render(sf::RenderTarget& target) {

		target.draw(this->_text);

	}

	// private methods


} // namespace ng::gui