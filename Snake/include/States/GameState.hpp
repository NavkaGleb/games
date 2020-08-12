#pragma once

#include "State.hpp"
#include "StateData.hpp"
#include "Field.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "ScoreBar.hpp"
#include "StatusBar.hpp"
#include "GUI.hpp"
#include "PauseMenu.hpp"

namespace ng {

	class GameState : public State {
	public:
		// constructor / destructor
		explicit GameState(StateData& sdata);
		~GameState() override;

		// accessors
		[[nodiscard]] const bool& quit() const override;

		// public methods
		void updateInput(const sf::Event& event) override;
		void updateMousePosition(const sf::Vector2i& mousePosition) override;
		void updateMouseClick(const sf::Event& event, const sf::Vector2i& mousePosition) override;
		void textEntered(const sf::Event& event) override;

		void update(const float& dtime) override;
		void render(sf::RenderTarget& target) override;

		void end() override;

	private:
		// variables
		StateData& _sdata;
		ng::Clock _keyClock;
		sf::Font _font;
		float _gridSize;
		Field* _field;
		Snake* _snake;
		Food* _food;
		Food* _bfood;
		int _score;
		gui::ScoreBar* _scoreBar;
		gui::StatusBar* _statusBar;
		gui::PauseMenu* _pauseMenu;
		bool _paused;
		bool _quit;

		// private methods
		void _initFont();
		void _initField();
		void _initSnake();
		void _initFood(ng::Food*& food, const char* filepath);
		void _initScoreBar();
		void _initStatusBar();
		void _initPauseMenu();

		void _randFoodPosition(float& x, float& y, const float& radius) const;
		void _getFoodPosition(float& x, float& y, const float& radius) const;

		void _updateFood();
		void _updateBfood();

	}; // class GameState

} // namespace ng