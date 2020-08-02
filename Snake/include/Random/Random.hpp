#pragma once

#include <random>
#include <ctime>

namespace ng {

	class rand {
	public:
		// public methods
		static int irand(const int& left, const int& right);
		static unsigned uirand(const unsigned& left, const unsigned& right);
		static float frand(const float& left, const float& right);

	}; // class rand

} // namespace ng