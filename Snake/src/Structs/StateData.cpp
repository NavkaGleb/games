#include "StateData.hpp"

namespace ng {

	// constructor
	StateData::StateData(std::stack<State*>& states) : framerateLimit(0), states(states) {}

} // namespace ng