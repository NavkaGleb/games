#pragma once

#include "Button.hpp"

namespace ng::gui {

	float p2px(const float& percentage, const sf::VideoMode& vm);
	float p2py(const float& percentage, const sf::VideoMode& vm);

	sf::Color getColor(std::istream& istream);
	void getColor(std::istream& istream, sf::Color& color);

} // namespace ng::gui