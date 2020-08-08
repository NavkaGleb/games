#pragma once

#include <SFML/Graphics.hpp>

namespace ng::gui {

	class StatusBar {
	public:
		// constructor / destructor
		StatusBar(float x, float y, float width, float height, sf::Color backgroundColor, sf::Color statusColor);
		virtual ~StatusBar();

		// accessors
		[[nodiscard]] const bool& active() const;

		// modifiers
		void active(const bool& active);

		// public methods
		void update(const float& value);
		void render(sf::RenderTarget& target);

	private:
		// variables
		sf::RectangleShape _background;
		sf::RectangleShape _status;
		bool _active;

		// private methods


	}; // class StatusBar

} // namespace ng::gui