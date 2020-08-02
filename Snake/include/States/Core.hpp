#pragma once

#include "GameState.hpp"

namespace ng {

	class Core {
	public:
		// constructor / destructor
		Core();
		virtual ~Core();

		// public methods
		void run();

	private:
		// variables
		sf::RenderWindow* _window;
		sf::Cursor* _cursor;
		ng::StateData _sdata;
		sf::Color _clearColor;
		sf::Clock _clock;
		float _dtime;
		std::stack<State*> _states;

		// private methods
		void _initWindow();
		void _initStates();

		void _updateDtime();
		void _update(sf::Event& event);
		void _render();

		void _end() const;

	}; // class Core

} // namespace ng