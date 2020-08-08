#include "GameState.hpp"

namespace ng {

	// constructor / destructor
	GameState::GameState(StateData& sdata)
		: _sdata(sdata), _gridSize(0.f), _snake(nullptr), _food(nullptr), _bfood(nullptr), _score(0), _scoreBar(nullptr),
			_bfoodLifeBar(nullptr), _quit(false), _keyClock(5.f, 1000.f) {

		this->_initFont();
		this->_initSnake();
		this->_initFood(this->_food, "../config/food.ini");
		this->_initFood(this->_bfood, "../config/big_food.ini");
		this->_initScoreBar();
		this->_initStatusBar();

	}

	GameState::~GameState() {

		delete this->_snake;
		delete this->_food;
		delete this->_bfood;
		delete this->_scoreBar;
		delete this->_bfoodLifeBar;

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

			this->_quit = true;

		}

	}

	void GameState::updateMouse(const sf::Event& event, const sf::Vector2i& mousePosition) {



	}

	void GameState::updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) {

		std::cout << mousePosition.x << "\t" << mousePosition.y << std::endl;

	}

	void GameState::update(const float& dtime) {

		this->_keyClock.update(dtime);
		this->_updateFood();
		this->_updateBfood();

		if (this->_bfood->active() && !this->_bfood->update(dtime)) {

			this->_snake->points(false);
			this->_bfood->active(false);
			this->_bfoodLifeBar->active(false);

		}

		if (!this->_snake->update(dtime))
			this->end();

		this->_scoreBar->update(this->_score);

		if (this->_bfoodLifeBar->active())
			this->_bfoodLifeBar->update(this->_bfood->life());

	}

	void GameState::render(sf::RenderTarget& target) {

		this->_snake->render(target);
		this->_food->render(target);

		if (this->_bfood->active())
			this->_bfood->render(target);

		this->_scoreBar->render(target);

		if (this->_bfoodLifeBar->active())
			this->_bfoodLifeBar->render(target);

	}

	void GameState::end() {

		this->_quit = true;

	}

	// private methods
	void GameState::_initFont() {

		this->_font.loadFromFile("../fonts/GUMDROP.ttf");

	}

	void GameState::_initSnake() {

		std::ifstream infile("../config/snake.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initSnake");

		float velocity;
		float x;
		float y;

		infile >> this->_gridSize;
		infile >> velocity;
		infile >> x >> y;

		this->_snake = new Snake(this->_gridSize, velocity, x, y);

	}

	void GameState::_initFood(Food*& food, const char* filepath) {

		std::ifstream infile(filepath);

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initFood");

		// food variables
		float radius;
		unsigned pointCount;
		unsigned short red;
		unsigned short green;
		unsigned short blue;
		unsigned short alpha;
		bool display;
		Clock* lifeClock = nullptr;
		float maxTime;
		float delay;

		// position variables
		float x;
		float y;

		infile >> radius >> pointCount;
		infile >> red >> green >> blue >> alpha;
		infile >> display;

		// if food is temporary
		if (!infile.eof()) {

			infile >> maxTime >> delay;
			lifeClock = new Clock(maxTime, delay);

		}

		this->_getFoodPosition(x, y, radius);
		food = new Food(radius, pointCount, x, y, sf::Color(red, green, blue, alpha), display, lifeClock);

	}

	void GameState::_initScoreBar() {

		std::ifstream infile("../config/score_bar.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | GameState::_initScoreBar");

		float x;
		float y;
		unsigned characterSize;
		unsigned short red;
		unsigned short green;
		unsigned short blue;
		unsigned short alpha;

		infile >> x >> y;
		infile >> characterSize;
		infile >> red >> green >> blue >> alpha;

		this->_scoreBar = new gui::ScoreBar(x, y, this->_font, characterSize, sf::Color(red, green, blue, alpha));

	}

	void GameState::_initStatusBar() {

		this->_bfoodLifeBar = new gui::StatusBar(10.f, 590.f, 580.f, 5.f, sf::Color(150, 150, 150, 150), sf::Color(47, 84, 255, 255));

	}

	void GameState::_randFoodPosition(float& x, float& y, const float& radius) const {

		static auto gridSize = static_cast<unsigned>(this->_gridSize);
		static float offset = (this->_gridSize - radius * 2.f) / 2.f;

		x = static_cast<float>(rand::uirand(0, this->_sdata.videoMode.width / gridSize - 1)) * this->_gridSize + offset;
		y = static_cast<float>(rand::uirand(0, this->_sdata.videoMode.width / gridSize - 1)) * this->_gridSize + offset;

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
			this->_bfoodLifeBar->active(true);

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
			this->_bfoodLifeBar->active(false);

		}

	}

} // namespace ng