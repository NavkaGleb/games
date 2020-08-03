#pragma once

#include <SFML/Graphics.hpp>

namespace ng {

	class ScoreBar {
	public:
		// constructor / destructor
		ScoreBar(float x, float y, sf::Font& font, unsigned characterSize, sf::Color color);
		virtual ~ScoreBar();

		// public methods
		void update(const int& score);
		void render(sf::RenderTarget& target);

	private:
		// variables
		sf::Font& _font;
		sf::Text _text;

		// private methods

	}; // class ScoreBar

} // namespace ng