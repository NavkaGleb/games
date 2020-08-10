#include "Field.hpp"

namespace ng {

	// constructor / destructor
	Field::Field(float x, float y, float width, float height, float outlineThickness) : _outlineThickness(outlineThickness) {

		this->_shape.setPosition(x, y);
		this->_shape.setSize(sf::Vector2f(width, height));
		this->_shape.setFillColor(sf::Color::Transparent);
		this->_shape.setOutlineThickness(this->_outlineThickness);
		this->_shape.setOutlineColor(sf::Color::White);

	}

	Field::Field(float width, float height, const sf::VideoMode& vm, float outlineThickness) : _outlineThickness(outlineThickness) {

		float x = (static_cast<float>(vm.width) - width) / 2.f;
		float y = (static_cast<float>(vm.height) - height) / 2.f;

		this->_shape.setPosition(x, y);
		this->_shape.setSize(sf::Vector2f(width, height));
		this->_shape.setFillColor(sf::Color::Transparent);
		this->_shape.setOutlineThickness(this->_outlineThickness);
		this->_shape.setOutlineColor(sf::Color::White);

	}

	Field::~Field() {



	}

	// accessors
	sf::Vector2f Field::getSize() const { return this->_shape.getSize(); }

	sf::Vector2f Field::getPosition() const { return this->_shape.getPosition(); }

	// public methods

	// protected methods
	void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->_shape);

	}

	// private methods

} // namespace ng