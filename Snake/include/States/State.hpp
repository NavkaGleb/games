#pragma once

#include <iostream>
#include <queue>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Random.hpp>

namespace ng {

	class State {
	public:
		// constructor / destructor
		State() = default;
		virtual ~State() = default;

		// accessors
		[[nodiscard]] virtual const bool& quit() const = 0;

		// public methods
		virtual void updateInput(const sf::Event& event) = 0;
		virtual void updateMousePosition(const sf::Vector2i& mousePosition) = 0;
		virtual void updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) = 0;
		virtual void update(const float& dtime) = 0;
		virtual void render(sf::RenderTarget& target) = 0;

		virtual void end() = 0;

	}; // class State

} // namespace ng