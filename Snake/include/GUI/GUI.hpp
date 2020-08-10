#pragma once

#include "Button.hpp"

namespace ng::gui {

	float p2px(const float& percentage, const sf::VideoMode& vm);
	float p2py(const float& percentage, const sf::VideoMode& vm);

} // namespace ng::gui