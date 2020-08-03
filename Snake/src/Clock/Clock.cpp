#include "Clock.hpp"

namespace ng {

	// constructor
	Clock::Clock(float maxTime, float delay) : _time(0.f), _maxTime(maxTime), _delay(delay) {}

	// accessors
	const float& Clock::currentTime() const { return this->_time; }

	const float& Clock::maxTime() const { return this->_maxTime; }

	bool Clock::getTime() {

		if (this->_time >= this->_maxTime) {

			this->_time = 0.f;
			return true;

		}

		return false;

	}

	bool Clock::final() const { return this->_time >= this->_maxTime; }

	// public methods
	void Clock::reset() { this->_time = 0.f; }

	void Clock::decreaseSleepTime(const float& time) { this->_delay += time; }

	void Clock::update(const float& dtime) {

		if (this->_time < this->_maxTime)
			this->_time += this->_delay * dtime;

	}

} // namespace ng