#pragma once

#include "GameState.hpp"
#include "Button.hpp"

namespace ng {

	class MainMenuState : public State {
	public:
		// constructor / destructor
		explicit MainMenuState(StateData& sdata);
		~MainMenuState() override;

		// accessors
		[[nodiscard]] const bool& quit() const override;

		// public methods
		void updateInput(const sf::Event& event) override;
		void updateMouse(const sf::Event& event, const sf::Vector2i& mousePosition) override;
		void updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) override;
		void update(const float& dtime) override;
		void render(sf::RenderTarget& target) override;

		void end() override;

	private:
		// variables
		bool _quit;
		sf::Font _font;
		std::map<std::string, gui::Button*> _buttons;

		// private methods
		void _initFont();
		void _initButtons();

	}; // class MainMenuState

} // namespace ng