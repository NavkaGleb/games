#include "GUI.hpp"

#include <cmath>

namespace ng::gui {

	float p2px(const float& percentage, const sf::VideoMode& vm) {

		return std::floor(static_cast<float>(vm.width) * (percentage / 100.f));

	}

	float p2py(const float& percentage, const sf::VideoMode& vm) {

		return std::floor(static_cast<float>(vm.height) * (percentage / 100.f));

	}

} // namespace ng::gui