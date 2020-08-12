#pragma once

#include "GameState.hpp"
#include "GUI.hpp"
#include "TextBox.hpp"

namespace ng {

	class MainMenuState : public State {
	public:
		// constructor / destructor
		explicit MainMenuState(StateData& sdata);
		~MainMenuState() override;

		// accessors
		[[nodiscard]] const bool& quit() const override;

		// public methods
		void updateMousePosition(const sf::Vector2i& mousePosition) override;

		void keyPressed(const sf::Event& event) override;
		void mouseButtonPressed(const sf::Event& event, const sf::Vector2i& mousePosition) override;
		void textEntered(const sf::Event& event) override;

		void update(const float& dtime) override;
		void render(sf::RenderTarget& target) override;

		void end() override;

	private:
		// variables
		StateData& _sdata;
		bool _quit;
		sf::Font _font;
		gui::TextBox* _nicknameInput;
		std::map<std::string, gui::Button*> _buttons;

		// private methods
		void _initFont();
		void _initTextBox();
		void _initButtons();

	}; // class MainMenuState

} // namespace ng