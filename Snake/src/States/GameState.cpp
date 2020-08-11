#include "GameState.hpp"

namespace ng {

	// constructor / destructor
	GameState::GameState(StateData& sdata)
		: _sdata(sdata), _keyClock(5.f, 1000.f), _gridSize(0.f), _field(nullptr), _snake(nullptr), _food(nullptr), _bfood(nullptr),
			_score(0), _scoreBar(nullptr), _statusBar(nullptr), _pauseMenu(nullptr), _paused(false), _quit(false) {

		this->_initFont();
		this->_initField();
		this->_initSnake();
		this->_initFood(this->_food, "../config/food.ini");
		this->_initFood(this->_bfood, "../config/big_food.ini");
		this->_initScoreBar();
		this->_initStatusBar();
		this->_initPauseMenu();

	}

	GameState::~GameState() {

		delete this->_field;
		delete this->_snake;
		delete this->_food;
		delete this->_bfood;
		delete this->_scoreBar;
		delete this->_statusBar;
		delete this->_pauseMenu;

	}

	// accessors
	const bool& GameState::quit() const { return this->_quit; }

	// public methods
	void GameState::updateInput(const sf::Event& event) {

		if (event.key.code == sf::Keyboard::Key::W && this->_keyClock.getTime()) {

			this->_snake->dir(DIR::UP);

		} else if (event.key.code == sf::Keyboard::Key::S && this->_keyClock.getTime()) {

			this->_snake->dir(DIR::DOWN);

		} else if (event.key.code == sf::Keyboard::Key::A && this->_keyClock.getTime()) {

			this->_snake->dir(DIR::LEFT);

		} else if (event.key.code == sf::Keyboard::Key::D && this->_keyClock.getTime()) {

			this->_snake->dir(DIR::RIGHT);

		} else if (event.key.code == sf::Keyboard::Escape) {

			this->_paused = !this->_paused;

		}

	}

	void GameState::updateMousePosition(const sf::Vector2i& mousePosition) {

		if (this->_paused)
			this->_pauseMenu->updateMousePosition(mousePosition);

	}

	void GameState::updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) {

		if (this->_paused) {

			if (this->_pauseMenu->isButtonPressed("resume"))
				this->_paused = false;

			if (this->_pauseMenu->isButtonPressed("quit game"))
				this->_quit = true;

		}

	}

	void GameState::update(const float& dtime) {

		this->_keyClock.update(dtime);

		if (!this->_paused) {

			this->_updateFood();
			this->_updateBfood();

			if (this->_bfood->active() && !this->_bfood->update(dtime)) {

				this->_snake->points(false);
				this->_bfood->active(false);
				this->_statusBar->active(false);

			}

			if (!this->_snake->update(dtime))
				this->end();

			this->_scoreBar->update(this->_score);

			if (this->_statusBar->active())
				this->_statusBar->update(this->_bfood->life());

		}

	}

	void GameState::render(sf::RenderTarget& target) {


		target.draw(*this->_field);
		this->_snake->render(target);
		this->_food->render(target);

		if (this->_bfood->active())
			this->_bfood->render(target);

		target.draw(*this->_scoreBar);

		if (this->_statusBar->active())
			target.draw(*this->_statusBar);

		if (this->_paused)
			target.draw(*this->_pauseMenu);


	}

	void GameState::end() {

		this->_quit = true;

	}

	// private methods
	void GameState::_initFont() {

		if (!this->_font.loadFromFile("../fonts/GUMDROP.ttf"))
			throw std::invalid_argument("failed to open the file | GameState::_initFont");

	}

	void GameState::_initField() {

		std::ifstream infile("../config/field.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initField");

		float percentageGridSize;
		float outlineThickness;

		infile >> percentageGridSize;
		infile >> outlineThickness;

		this->_gridSize = gui::p2px(percentageGridSize, this->_sdata.vm);

		float x = this->_gridSize * 2.f;
		float y = this->_gridSize * 2.f;
		float width = static_cast<float>(this->_sdata.vm.width) - (4.f * this->_gridSize);
		float height = static_cast<float>(this->_sdata.vm.height) - (4.f * this->_gridSize);

		this->_field = new Field(x, y, width, height, outlineThickness);

		infile.close();

	}

	void GameState::_initSnake() {

		std::ifstream infile("../config/snake.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initSnake");

		float velocity;
		float x;
		float y;

		infile >> velocity;
		infile >> x >> y;

		this->_snake = new Snake(x, y, this->_gridSize, velocity, sf::FloatRect(this->_field->getPosition(), this->_field->getSize()));

		infile.close();

	}

	void GameState::_initFood(Food*& food, const char* filepath) {

		std::ifstream infile(filepath);

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initFood");

		// food variables
		float radius;
		unsigned pointCount;
		sf::Color color;
		bool display;
		Clock* lifeClock = nullptr;

		// position variables
		float x;
		float y;

		infile >> radius >> pointCount;
		gui::getColor(infile, color);
		infile >> display;

		// if food is temporary
		if (!infile.eof()) {

			float maxTime;
			float delay;

			infile >> maxTime >> delay;
			lifeClock = new Clock(maxTime, delay);

		}

		this->_getFoodPosition(x, y, radius);
		food = new Food(radius, pointCount, x, y, color, display, lifeClock);

		infile.close();

	}

	void GameState::_initScoreBar() {

		std::ifstream infile("../config/score_bar.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initScoreBar");

		float percentageX;
		float percentageY;
		unsigned characterSize;
		sf::Color color;

		infile >> percentageX >> percentageY;
		infile >> characterSize;
		gui::getColor(infile, color);

		std::cout << "x = " << gui::p2px(percentageX, this->_sdata.vm) << ", y = " <<  gui::p2py(percentageY, this->_sdata.vm) << std::endl;

		this->_scoreBar = new gui::ScoreBar(
			gui::p2px(percentageX, this->_sdata.vm), gui::p2py(percentageY, this->_sdata.vm),
			this->_font, characterSize, color, gui::ScoreBar::Alignment::Right
		);

		infile.close();

	}

	void GameState::_initStatusBar() {

		std::ifstream infile("../config/status_bar.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initStatusBar");

		float percentageWidth;
		float percentageHeight;
		sf::Color backgroundColor;
		sf::Color statusColor;

		infile >> percentageWidth >> percentageHeight;
		gui::getColor(infile, backgroundColor);
		gui::getColor(infile, statusColor);

		float width = gui::p2px(percentageWidth, this->_sdata.vm);
		float height = gui::p2py(percentageHeight, this->_sdata.vm);
		float x = (static_cast<float>(this->_sdata.vm.width) - width) / 2.f;
		float y = this->_field->getPosition().y + this->_field->getSize().y +
			(static_cast<float>(this->_sdata.vm.height) - this->_field->getPosition().y - this->_field->getSize().y) / 2.f;

		this->_statusBar = new gui::StatusBar(x, y, width, height, backgroundColor, statusColor);

		infile.close();

	}

	void GameState::_initPauseMenu() {

		std::ifstream infile("../config/pause_menu.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initPauseMenu");

		unsigned characterSize;
		float textY;
		float percentageY;
		float percentageOffsetY;
		float percentageButtonWidth;
		float percentageButtonHeight;
		unsigned buttonCharacterSize;
		sf::Color bidle;
		sf::Color bhover;
		sf::Color bactive;

		infile >> characterSize;
		infile >> textY;
		infile >> percentageY;
		infile >> percentageOffsetY;
		infile >> percentageButtonWidth >> percentageButtonHeight;
		infile >> buttonCharacterSize;
		gui::getColor(infile, bidle);
		gui::getColor(infile, bhover);
		gui::getColor(infile, bactive);

		float y = gui::p2py(percentageY, this->_sdata.vm);
		float offsety = gui::p2py(percentageOffsetY, this->_sdata.vm);
		float width = gui::p2px(percentageButtonWidth, this->_sdata.vm);
		float height = gui::p2py(percentageButtonHeight, this->_sdata.vm);

		this->_pauseMenu = new gui::PauseMenu(this->_sdata.vm, characterSize, this->_font, gui::p2py(textY, this->_sdata.vm));

		this->_pauseMenu->addButton(y, offsety, width, height, "resume", buttonCharacterSize, bidle, bhover, bactive);
		this->_pauseMenu->addButton(y, offsety, width, height, "save", buttonCharacterSize, bidle, bhover, bactive);
		this->_pauseMenu->addButton(y, offsety, width, height, "quit game", buttonCharacterSize, bidle, bhover, bactive);

		infile.close();

	}

	void GameState::_randFoodPosition(float& x, float& y, const float& radius) const {

		static auto gridSize = static_cast<unsigned>(this->_gridSize);
		static unsigned left = static_cast<unsigned>(this->_field->getPosition().x) / gridSize;
		static unsigned right = static_cast<unsigned>(this->_field->getPosition().x + this->_field->getSize().x) / gridSize - 1;
		static float offset = (this->_gridSize - radius * 2.f) / 2.f;

		x = static_cast<float>(rand::uirand(left, right)) * this->_gridSize + offset;
		y = static_cast<float>(rand::uirand(left, right)) * this->_gridSize + offset;

	}

	void GameState::_getFoodPosition(float& x, float& y, const float& radius) const {

		this->_randFoodPosition(x, y, radius);

		while (this->_snake->intersects(sf::FloatRect(x, y, radius * 2.f, radius * 2.f), false))
			this->_randFoodPosition(x, y, radius);

	}

	void GameState::_updateFood() {

		if (this->_snake->intersects(this->_food->getGlobalBounds())) {

			this->_score += 10;
			this->_snake->increaseLength();

			float x;
			float y;

			this->_getFoodPosition(x, y, this->_food->radius());
			this->_food->setPosition(sf::Vector2f(x, y));

			// time to display big food
			if ((this->_snake->length() + 1) % 5 == 0)
				this->_snake->points(true);

		}

	}

	void GameState::_updateBfood() {

		if (!this->_bfood->active() && this->_snake->points()) {

			// set active to big food
			this->_bfood->active(true);
			this->_statusBar->active(true);

			float x;
			float y;

			this->_getFoodPosition(x, y, this->_bfood->radius());
			this->_bfood->setPosition(sf::Vector2f(x, y));

		}

		if (this->_bfood->active() && this->_snake->intersects(this->_bfood->getGlobalBounds())) {

			this->_score += static_cast<int>(100 * this->_bfood->life());
			this->_snake->increaseLength();
			this->_snake->points(false);
			this->_bfood->active(false);
			this->_statusBar->active(false);

		}

	}

} // namespace ng