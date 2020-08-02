#pragma once

#include <vector>
#include <map>
#include <string>
#include <queue>

#include <SFML/Graphics.hpp>

#include "Clock.hpp"

namespace ng {

	enum DIR { NONE = 0, UP, DOWN, LEFT, RIGHT };

	class Snake {
	public:
		// constructor / destructor
		Snake(float size, float velocity, float x, float y);
		virtual ~Snake();

		// accessors
		[[nodiscard]] int length() const;
		[[nodiscard]] const bool& points() const;
		[[nodiscard]] bool intersects(const sf::FloatRect& position, bool head = true) const;

		// modifiers
		void points(const bool& points);
		void dir(const short& dir);

		// public methods
		void increaseLength();

		bool update(const float& dtime);
		void render(sf::RenderTarget& target);

	private:
		// variables
		float _size;
		float _velocity;
		short _dir;
		std::queue<short> _dirs;
		mutable ng::Clock _velocityClock;
		bool _increase;
		bool _points;
		sf::Vector2f _position;
		std::map<std::string, sf::Color> _colors;
		std::vector<sf::RectangleShape*> _shape;

		// private methods
		bool _suitableDir(const short& currentDir) const;

		void _increaseLength(const float& x, const float& y);
		void _increaseLength(const float& x, const float& y, const sf::Color& color);
		void _increaseLength(const sf::Vector2f& position, const sf::Color& color);

	}; // class Snake

} // namespace ng