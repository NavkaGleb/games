#pragma once

#include <SFML/Graphics.hpp>

#include "Clock.hpp"

namespace ng {

	class Food {
	public:
		// constructor / destructor
		Food(float radius, unsigned pointCount, float x, float y, sf::Color color, bool active, ng::Clock* clock = nullptr);
		virtual ~Food();

		// accessors
		[[nodiscard]] sf::FloatRect getGlobalBounds() const;
		[[nodiscard]] float radius() const;
		[[nodiscard]] const bool& active() const;

		// modifiers
		void setPosition(const sf::Vector2f& position);
		void active(const bool& active);

		// public methods
		bool update(const float& dtime);
		void render(sf::RenderTarget& target);

	private:
		sf::CircleShape* _shape;
		float _radius;
		bool _active;
		ng::Clock* _lifeClock;

	};

} // namespace ng