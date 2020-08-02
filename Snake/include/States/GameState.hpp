#pragma once

#include "State.hpp"
#include "Snake.hpp"
#include "Food.hpp"

namespace ng {

	class GameState : public State {
	public:
		// constructor / destructor
		explicit GameState(StateData& sdata);
		~GameState() override;

		// accessors
		[[nodiscard]] const bool& quit() const override;

		// public methods
		void updateInput(const float& dtime, sf::Event& event) override;
		void update(const float& dtime) override;
		void render(sf::RenderTarget& target) override;

		void end() override;

	private:
		// variables
		StateData& _sdata;
		float _gridSize;
		Snake* _snake;
		Food* _food;
		Food* _bfood;
		ng::Clock _keyClock;
		bool _quit;

		// private methods
		void _initSnake();
		void _initFood(ng::Food*& food, const char* filepath);

		void _randFoodPosition(float& x, float& y, const float& radius) const;
		void _getFoodPosition(float& x, float& y, const float& radius) const;

		void _updateFood();
		void _updateBfood();

	}; // class GameState

} // namespace ng