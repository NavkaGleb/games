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
	void MainMenuState::updateMousePosition(const sf::Vector2i& mousePosition) {

		this->_nicknameInput->update(mousePosition);

		for (const auto& p : this->_buttons)
			p.second->update(mousePosition);

	}

	void MainMenuState::keyPressed(const sf::Event& event) {

		if (!this->_nicknameInput->active()) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

				std::cout << "set active to input from KEY" << std::endl;
				this->_nicknameInput->setActive(true);

			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->_nicknameInput->setActive(false);

	}

	void MainMenuState::mouseButtonPressed(const sf::Event& event, const sf::Vector2i& mousePosition) {

		if (this->_buttons["game"]->isPressed())
			this->_sdata.states.emplace(new GameState(this->_sdata));

		if (this->_buttons["exit"]->isPressed())
			this->_quit = true;

	}

	void MainMenuState::textEntered(const sf::Event& event) {

		if (this->_nicknameInput->active())
			this->_nicknameInput->textEntered(event);

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

		std::cout << "!!!!!!!!!!!!!!!!  " << this->_font.getGlyph(102, 30, false).bounds.height << std::endl;

	}

	void MainMenuState::_initTextBox() {

		float width = ng::gui::p2px(50.f, this->_sdata.vm);
		float height = ng::gui::p2py(7.f, this->_sdata.vm);
		float x = (static_cast<float>(this->_sdata.vm.width) - width) / 2.f;
		float y = ng::gui::p2py(10.f, this->_sdata.vm);

		this->_nicknameInput = new gui::TextBox(x, y, width, height, 30, this->_font,
										  sf::Color(150, 150, 150, 100), gui::TextBox::Alignment::Center);
//		this->_nicknameInput->setCharacterSize(30);
//		this->_nicknameInput->setFont(this->_font);
//		this->_nicknameInput->setBackgroundFillColor(sf::Color(150, 150, 150, 100));
//		this->_nicknameInput->setPosition(x, y);
//		this->_nicknameInput->setSize(width, height);
		this->_nicknameInput->setLimit(13);

	}

	void MainMenuState::_initButtons() {

		float width = ng::gui::p2px(50.f, this->_sdata.vm);
		float height = ng::gui::p2py(7.f, this->_sdata.vm);
		float x = (static_cast<float>(this->_sdata.vm.width) - width) / 2.f;
		float y = ng::gui::p2py(10.f, this->_sdata.vm);
		float offsety = ng::gui::p2py(10.f, this->_sdata.vm);

		this->_buttons["game"] = new gui::Button(
			x, y + offsety * 1, width, height, "game", 30, this->_font,
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150)
		);

		this->_buttons["leaderboard"] = new gui::Button(
			x, y + offsety * 2, width, height, "leaderboard", 30, this->_font,
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150)
		);

		this->_buttons["exit"] = new gui::Button(
			x, y + offsety * 3, width, height, "exit", 30, this->_font,
			sf::Color(150, 150, 150, 150), sf::Color(200, 200, 200, 150), sf::Color(255, 255, 255, 150)
		);

	}

} // namespace ng