#include "MainMenuState.hpp"

namespace ng {

	// constructor / destructor
	MainMenuState::MainMenuState(StateData& sdata)
		: _sdata(sdata), _quit(false), _nicknameInput(nullptr) {

		this->_initFont();
		this->_initTextBox();
		this->_initButtons();

	}

	MainMenuState::~MainMenuState() {

		delete this->_nicknameInput;

		for (auto& p : this->_buttons)
			delete p.second;

	}

	// accessors
	const bool& MainMenuState::quit() const { return this->_quit; }

	// public methods
	void MainMenuState::updateInput(const sf::Event& event) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			this->_nicknameInput->active(true);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->_nicknameInput->active(false);

	}

	void MainMenuState::updateMousePosition(const sf::Vector2i& mousePosition) {

		for (const auto& p : this->_buttons)
			p.second->update(mousePosition);

	}

	void MainMenuState::updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) {

		if (this->_buttons["game"]->isPressed())
			this->_sdata.states.emplace(new GameState(this->_sdata));

		if (this->_buttons["exit"]->isPressed())
			this->_quit = true;

	}

	void MainMenuState::textEntered(const sf::Event& event) {

		this->_nicknameInput->input(event);

	}

	void MainMenuState::update(const float& dtime) {



	}

	void MainMenuState::render(sf::RenderTarget& target) {

		target.draw(*this->_nicknameInput);

		for (const auto& p : this->_buttons)
			target.draw(*p.second);

	}

	void MainMenuState::end() {

		this->_quit = true;

	}

	// private methods
	void MainMenuState::_initFont() {

		if (!this->_font.loadFromFile("../fonts/RubikMonoOne-Regular.ttf"))
			throw std::invalid_argument("failed to open the file | MainMenuState::_initFont");

	}

	void MainMenuState::_initTextBox() {

		this->_nicknameInput = new gui::TextBox(30, false);
		this->_nicknameInput->setPosition(300.f, 500.f);
		this->_nicknameInput->setFont(this->_font);

	}

	void MainMenuState::_initButtons() {

		float width = ng::gui::p2px(50.f, this->_sdata.vm);
		float height = ng::gui::p2py(7.f, this->_sdata.vm);
		float x = (static_cast<float>(this->_sdata.vm.width) - width) / 2.f;
		float y = ng::gui::p2py(10.f, this->_sdata.vm);
		float offsety = ng::gui::p2py(10.f, this->_sdata.vm);

		this->_buttons["game"] = new gui::Button(
			x, y + offsety * 0, width, height, "game", 30, this->_font,
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150)
		);

		this->_buttons["leaderboard"] = new gui::Button(
			x, y + offsety * 1, width, height, "leaderboard", 30, this->_font,
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150)
		);

		this->_buttons["exit"] = new gui::Button(
			x, y + offsety * 2, width, height, "exit", 30, this->_font,
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150)
		);

	}

} // namespace ng