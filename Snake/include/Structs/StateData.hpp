#pragma once

#include <stack>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace ng {

	class State;

	struct StateData {
		// variables
		sf::VideoMode vm;
		sf::ContextSettings settings;
		unsigned framerateLimit;
		std::stack<State*>& states;

		// constructor / destructor
		explicit StateData(std::stack<State*>& states);
		virtual ~StateData() = default;

	}; // struct StateData

} // namespace ng