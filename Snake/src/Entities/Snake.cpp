#include "Snake.hpp"

#include <iostream>

namespace ng {

	// constructor / destructor
	Snake::Snake(float size, float velocity, float x, float y)
		: _size(size), _velocity(velocity), _dir(DIR::NONE), _velocityClock(50.f, 200.f), _increase(false), _points(false) {

		this->_dirs.emplace(DIR::DOWN);

		this->_colors["head"] = sf::Color(118, 186, 27, 150);
		this->_colors["default"] = sf::Color(118, 186, 27, 255);

		this->_increaseLength(x, y, this->_colors["head"]);

		for (int i = 0; i < 4; ++i)
			this->_increaseLength(x, y - static_cast<float>(i + 1) * size);

	}

	Snake::~Snake() {

		for (auto& rect : this->_shape)
			delete rect;

	}

	// accessors
	int Snake::length() const { return this->_shape.size(); }

	const bool& Snake::points() const { return this->_points; }

	bool Snake::intersects(const sf::FloatRect& position, bool head) const {

		if (head)
			return this->_shape.front()->getGlobalBounds().intersects(position);

		for (const auto& rect : this->_shape)
			if (rect->getGlobalBounds().intersects(position))
				return true;

		return false;

	}

	// modifiers
	void Snake::points(const bool& points) { this->_points = points; }

	void Snake::dir(const short& dir) {

		if (this->_suitableDir(dir))
			this->_dirs.emplace(dir);

	}

	// public methods
	void Snake::increaseLength() { this->_increase = true; }

	bool Snake::update(const float& dtime) {

		this->_velocityClock.update(dtime);

		if (this->_velocityClock.getTime()) {

			// save last position of tail to add new item to the end
			this->_position = this->_shape.back()->getPosition();

			// move shape in the direction
			for (int i = static_cast<int>(this->_shape.size()) - 1; i > 0; --i)
				this->_shape[i]->setPosition(this->_shape[i - 1]->getPosition());

			// get last direction from queue
			if (!this->_dirs.empty()) {

				this->_dir = this->_dirs.front();
				this->_dirs.pop();

			}

			// set new position to snake head
			if (this->_dir == DIR::UP)
				this->_shape.front()->setPosition(this->_shape.front()->getPosition().x, this->_shape.front()->getPosition().y - this->_size);
			else if (this->_dir == DIR::DOWN)
				this->_shape.front()->setPosition(this->_shape.front()->getPosition().x, this->_shape.front()->getPosition().y + this->_size);
			else if (this->_dir == DIR::LEFT)
				this->_shape.front()->setPosition(this->_shape.front()->getPosition().x - this->_size, this->_shape.front()->getPosition().y);
			else if (this->_dir == DIR::RIGHT)
				this->_shape.front()->setPosition(this->_shape.front()->getPosition().x + this->_size, this->_shape.front()->getPosition().y);

			// check collision
			for (int i = 1; i < this->_shape.size(); ++i)
				if (this->_shape.front()->getGlobalBounds().intersects(this->_shape[i]->getGlobalBounds()))
					return false;

			// add new item to the end
			if (this->_increase) {

				this->_increase = false;
				this->_increaseLength(this->_position, this->_colors["default"]);

				if (this->_shape.size() % 5 == 0)
					this->_velocityClock.decreaseSleepTime(20.f);

			}

			this->_position = this->_shape.front()->getPosition();

			// transfer
			if (this->_position.x < 0)
				this->_shape.front()->setPosition(600.f - 30.f, this->_position.y);
			if (this->_position.x > 570.f)
				this->_shape.front()->setPosition(0.f, this->_position.y);
			if (this->_position.y < 0)
				this->_shape.front()->setPosition(this->_position.x, 570.f);
			if (this->_position.y > 570.f)
				this->_shape.front()->setPosition(this->_position.x, 0.f);

		}

		return true;

	}

	void Snake::render(sf::RenderTarget& target) {

		for (const auto& rect : this->_shape)
			target.draw(*rect);

	}

	// private methods
	bool Snake::_suitableDir(const short& currentDir) const {

		short prevDir = this->_dirs.empty() ? this->_dir : this->_dirs.front();

		return currentDir == DIR::UP && prevDir != DIR::DOWN ||
		       currentDir == DIR::DOWN && prevDir != DIR::UP ||
		       currentDir == DIR::LEFT && prevDir != DIR::RIGHT ||
		       currentDir == DIR::RIGHT && prevDir != DIR::LEFT;

	}

	void Snake::_increaseLength(const float& x, const float& y) { this->_increaseLength(x, y, this->_colors["default"]); }

	void Snake::_increaseLength(const float& x, const float& y, const sf::Color& color) {

		this->_increaseLength(sf::Vector2f(x, y), color);

	}

	void Snake::_increaseLength(const sf::Vector2f& position, const sf::Color& color) {

		this->_shape.emplace_back(new sf::RectangleShape(sf::Vector2f(this->_size, this->_size)));
		this->_shape.back()->setPosition(position);
		this->_shape.back()->setFillColor(color);

	}

} // namespace ng