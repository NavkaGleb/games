#pragma once

#include "GameState.hpp"
#include "Button.hpp"

namespace ng {

	class MainMenuState : public State {
	public:
		// constructor / destructor
		MainMenuState();
		~MainMenuState() override;

		// public methods
		void updateInput(const sf::Event& event) override;
		void updateMouseClick(const sf::Event& event) override;
		void update(const float& dtime) override;
		void render(sf::RenderTarget& target) override;

	private:
		// variables
		std::map<std::string, gui::Button> _buttons;

		// private methods

	}; // class MainMenuState

} // namespace ng