#include "GUI.hpp"

#include <cmath>

namespace ng::gui {

	float p2px(const float& percentage, const sf::VideoMode& vm) {

		return std::floor(static_cast<float>(vm.width) * (percentage / 100.f));

	}

	float p2py(const float& percentage, const sf::VideoMode& vm) {

		return std::floor(static_cast<float>(vm.height) * (percentage / 100.f));

	}

	sf::Color getColor(std::istream& istream) {

		unsigned short red;
		unsigned short green;
		unsigned short blue;
		unsigned short alpha;

		istream >> red >> green >> blue >> alpha;

		return sf::Color(red, green, blue, alpha);

	}

	void getColor(std::istream& istream, sf::Color& color) {

		unsigned short red;
		unsigned short green;
		unsigned short blue;
		unsigned short alpha;

		istream >> red >> green >> blue >> alpha;

		color.r = red;
		color.g = green;
		color.b = blue;
		color.a = alpha;

	}

} // namespace ng::gui