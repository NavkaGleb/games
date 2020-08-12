#include "TextBox.hpp"

#include <cmath>
#include <iostream>

namespace ng::gui {

	// constructor / destructor
	TextBox::TextBox(float x, float y, float width, float height,
		unsigned characterSize, const sf::Font& font, const sf::Color& backgroundColor, short alignment)
		: _active(false), _limit(0), _alignment(alignment) {

		// init shape
		this->_shape.setPosition(x, y);
		this->_shape.setSize(sf::Vector2f(width, height));
		this->_shape.setFillColor(backgroundColor);

		// init text
		this->_text.setCharacterSize(characterSize);
		this->_text.setFont(font);
		this->_text.setString("");

		std::cout << this->_text.getGlobalBounds().height << std::endl;

		this->_text.setOrigin(
			std::floor(this->_text.getGlobalBounds().left + this->_text.getGlobalBounds().width / 2.f),
			std::floor(this->_text.getGlobalBounds().top + this->_text.getGlobalBounds().height / 2.f)
		);

		std::cout << "width = " << this->_text.getGlobalBounds().width << ", height = " << this->_text.getGlobalBounds().height << std::endl;

		// init oss
//		this->_oss << "nickname";

		this->_align();

	}

	TextBox::~TextBox() {



	}

	// accessors
	const bool& TextBox::active() const { return this->_active; }

	std::string TextBox::str() const { return this->_oss.str(); }

	// modifiers
	void TextBox::setPosition(const float& x, const float& y) {

		this->_shape.setPosition(x, y);
//		this->_text.setPosition(x, y);

	}

	void TextBox::setSize(const float& width, const float& height) {

		this->_shape.setSize(sf::Vector2f(width, height));

		this->_text.setOrigin(
			std::floor(this->_text.getGlobalBounds().left + this->_text.getGlobalBounds().width / 2.f),
			std::floor(this->_text.getGlobalBounds().top + this->_text.getGlobalBounds().height / 2.f)
		);

		this->_text.setPosition(
			std::floor(this->_shape.getPosition().x + this->_shape.getGlobalBounds().width / 2.f),
			std::floor(this->_shape.getPosition().y + this->_shape.getGlobalBounds().height / 2.f)
		);

		std::cout << std::floor(this->_text.getGlobalBounds().left + this->_text.getGlobalBounds().width / 2.f) << " "
				  << std::floor(this->_text.getGlobalBounds().top + this->_text.getGlobalBounds().height / 2.f) << std::endl;

//		this->_align();

	}

	void TextBox::setFont(const sf::Font& font) { this->_text.setFont(font); }

	void TextBox::setBackgroundFillColor(const sf::Color& color) { this->_shape.setFillColor(color); }

	void TextBox::setCharacterSize(const unsigned& characterSize) { this->_text.setCharacterSize(characterSize); }

	void TextBox::setActive(const bool& active) {

		this->_active = active;

		if (!this->_active)
			this->_text.setString(this->_oss.str());

		this->_align();

	}

	void TextBox::setLimit(const int& limit) { this->_limit = limit; }

	// public methods
	void TextBox::textEntered(const sf::Event& event) {

		if (event.text.unicode < 128) {

			this->_addCharacter(event.text.unicode);
			this->_align();

		}

	}

	void TextBox::update(const sf::Vector2i& mousePosition) {



	}

	// protected methods
	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates) const {

		target.draw(this->_shape);
		target.draw(this->_text);

	}

	// private methods
	void TextBox::_addCharacter(const int &character) {

		std::cout << character << std::endl;

		if ((this->_limit == 0 || this->_oss.str().length() < this->_limit) &&
			character != ReservedKey::Delete && character != ReservedKey::Enter && character != ReservedKey::Escape)
			this->_oss << static_cast<char>(character);
		else if ((this->_limit == 0 || this->_oss.str().size() <= this->_limit) && character == ReservedKey::Delete)
			this->_deleteLastCharacter();

		this->_text.setString(this->_oss.str() + "_");

	}

	void TextBox::_deleteLastCharacter() {

		std::string str = this->_oss.str();

		if (!str.empty())
			str.pop_back();

		this->_oss.str(str);
		this->_text.setString(this->_oss.str());

	}

	void TextBox::_align() {

		std::cout << "fuck this shit" << std::endl;

		if (this->_alignment == Alignment::Left) {

			this->_text.setPosition(
				std::floor(this->_shape.getPosition().x),
				std::floor(this->_shape.getPosition().y + this->_shape.getGlobalBounds().height / 2.f)
			);

		} else if (this->_alignment == Alignment::Right) {

			this->_text.setPosition(
				std::floor(this->_shape.getPosition().x + this->_shape.getGlobalBounds().width - this->_text.getGlobalBounds().width),
				std::floor(this->_shape.getPosition().y + this->_shape.getGlobalBounds().height / 2.f)
			);

		} else if (this->_alignment == Alignment::Center) {

			std::cout << "x = " <<
				std::floor(this->_shape.getPosition().x + (this->_shape.getGlobalBounds().width - this->_text.getGlobalBounds().width) / 2.f)
				<< std::endl;

			this->_text.setPosition(
				std::floor(this->_shape.getPosition().x + (this->_shape.getGlobalBounds().width - this->_text.getGlobalBounds().width) / 2.f),
				std::floor(this->_shape.getPosition().y + this->_shape.getGlobalBounds().height / 2.f)
			);

		}

	}

} // namespace ng::gui