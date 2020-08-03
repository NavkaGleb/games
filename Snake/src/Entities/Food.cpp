#include "Food.hpp"

namespace ng {

	// constructor / destructor
	Food::Food(float radius, unsigned pointCount, float x, float y, sf::Color color, bool active, ng::Clock* lifeClock)
		: _radius(radius), _active(active), _lifeClock(lifeClock) {

		this->_shape = new sf::CircleShape(radius, pointCount);
		this->_shape->setPosition(x, y);
		this->_shape->setFillColor(color);

	}

	Food::~Food() {

		delete this->_shape;
		delete this->_lifeClock;

	}

	// accessors
	sf::FloatRect Food::getGlobalBounds() const { return this->_shape->getGlobalBounds(); }

	float Food::radius() const { return this->_shape->getRadius(); }

	const bool& Food::active() const { return this->_active; }

	float Food::life() const { return this->_lifeClock ? 1.f - this->_lifeClock->currentTime() / this->_lifeClock->maxTime() : 1.f; }

	// modifiers
	void Food::setPosition(const sf::Vector2f& position) { this->_shape->setPosition(position); }

	void Food::active(const bool& active) {

		this->_lifeClock->reset();
		this->_active = active;

	}

	// public methods
	bool Food::update(const float& dtime) {

		if (!this->_lifeClock)
			return true;

		this->_lifeClock->update(dtime);

		return !this->_lifeClock->final();

	}

	void Food::render(sf::RenderTarget& target) { target.draw(*this->_shape); }

	// private methods

} // namespace ng