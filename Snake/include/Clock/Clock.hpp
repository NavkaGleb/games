#pragma once

namespace ng {

	class Clock {
	public:
		// constructor / destructor
		Clock(float maxTime, float delay);
		virtual ~Clock() = default;

		// accessors
		[[nodiscard]] bool getTime();
		[[nodiscard]] bool final() const;

		// public methods
		void reset();
		void decreaseSleepTime(const float& time);
		void update(const float& dtime);

	private:
		// variables
		float _time;
		float _maxTime;
		float _delay;

	}; // class Clock

} // namespace ng