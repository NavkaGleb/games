#pragma once

#include <SFML/Graphics.hpp>

namespace ng {

	class Field : public sf::Drawable {
	public:
		// constructor / destructor
		Field(float x, float y, float width, float height, float outlineThickness);
		Field(float width, float height, const sf::VideoMode& vm, float outlineThickness);
		~Field() override;

		// accessors
		[[nodiscard]] sf::Vector2f getSize() const;
		[[nodiscard]] sf::Vector2f getPosition() const;

		// public methods

	protected:
		// protected methods
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		// variables
		sf::RectangleShape _shape;
		float _outlineThickness;

		// private methods

	};

} // namespace ng