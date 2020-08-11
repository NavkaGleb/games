#pragma once

#include <SFML/Graphics.hpp>

namespace ng::gui {

	class StatusBar : public sf::Drawable {
	public:
		// constructor / destructor
		StatusBar(float x, float y, float width, float height, sf::Color backgroundColor, sf::Color statusColor);
		~StatusBar() override;

		// accessors
		[[nodiscard]] const bool& active() const;

		// modifiers
		void active(const bool& active);

		// public methods
		void update(const float& value);

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::RectangleShape _background;
		sf::RectangleShape _status;
		bool _active;

		// private methods


	}; // class StatusBar

} // namespace ng::gui