#include "MainMenuState.hpp"

namespace ng {

	// constructor / destructor
	MainMenuState::MainMenuState(StateData& sdata)
		: _quit(false) {

		this->_initFont();
		this->_initButtons();

	}

	MainMenuState::~MainMenuState() {

		for (auto& p : this->_buttons)
			delete p.second;

	}

	// accessors
	const bool& MainMenuState::quit() const { return this->_quit; }

	// public methods
	void MainMenuState::updateInput(const sf::Event& event) {



	}

	void MainMenuState::updateMouse(const sf::Event& event, const sf::Vector2i& mousePosition) {

		for (const auto& p : this->_buttons)
			p.second->update(mousePosition);

	}

	void MainMenuState::updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) {

		for (const auto& p : this->_buttons)
			p.second->update(mousePosition);

	}

	void MainMenuState::update(const float& dtime) {



	}

	void MainMenuState::render(sf::RenderTarget& target) {

		for (const auto& p : this->_buttons)
			p.second->render(target);

	}

	void MainMenuState::end() {

		this->_quit = true;

	}

	// private methods
	void MainMenuState::_initFont() {

		this->_font.loadFromFile("../fonts/GUMDROP.ttf");

	}

	void MainMenuState::_initButtons() {

		this->_buttons["game"] = new gui::Button(50.f, 50.f, 300.f, 40.f, "game",
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150), this->_font);

	}

} // namespace ng