#pragma once

#include <SFML/Graphics.hpp>

namespace ng::gui {

	class ScoreBar : public sf::Drawable {
	public:
		// enums
		enum Alignment { Left = 0, Right, Center };

		// constructor / destructor
		ScoreBar(float x, float y, const sf::Font& font, unsigned characterSize, sf::Color color, short alignment = Alignment::Left);
		~ScoreBar() override;

		// public methods
		void update(const int& score);

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		float _x;
		sf::Text _text;
		short _alignment;

		// private methods
		void _align(const float& x, const float& y);

	}; // class ScoreBar

} // namespace ng::gui