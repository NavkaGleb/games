#include "Random.hpp"

namespace ng {

	// public methods
	int rand::irand(const int& left, const int& right) {

		static std::random_device rd;
		static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
		static std::mt19937 mt(seq);

		std::uniform_int_distribution<int> dist(left, right);

		return dist(mt);

	}

	unsigned rand::uirand(const unsigned& left, const unsigned& right) {

		static std::random_device rd;
		static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
		static std::mt19937 mt(seq);

		std::uniform_int_distribution<unsigned> dist(left, right);

		return dist(mt);

	}

	float rand::frand(const float& left, const float& right) {

		static std::random_device rd;
		static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
		static std::mt19937 mt(seq);

		std::uniform_real_distribution<float> dist(left, right);

		return dist(mt);

	}

}