#include "TextBox.hpp"

namespace ng::gui {

	// constructor / destructor
	TextBox::TextBox(unsigned characterSize, bool active) : _active(active) {

		if (this->_active)
			this->_textBox.setString("_");

	}

	TextBox::~TextBox() {



	}

	// accessors
	const bool& TextBox::active() const { return this->_active; }

	std::string TextBox::str() const { return this->_text.str(); }

	// modifiers
	void TextBox::setPosition(const float& x, const float& y) { this->_textBox.setPosition(x, y); }

	void TextBox::setFont(const sf::Font& font) { this->_textBox.setFont(font); }

	void TextBox::active(const bool& active) {

		this->_active = active;

		if (!this->_active)
			this->_textBox.setString(this->_text.str());

	}

	// public methods
	void TextBox::input(const sf::Event& event) {

		if (this->_active && event.text.unicode < 128) {

			this->update(event.text.unicode);

		}

	}

	void TextBox::update(const int& character) {

		if (character != ReservedKey::Delete && character != ReservedKey::Enter && character != ReservedKey::Escape) {

			this->_text << static_cast<char>(character);

		} else if (character == ReservedKey::Delete){

			this->_deleteLast();

		} else if (character == ReservedKey::Enter) {



		}


		this->_textBox.setString(this->_text.str() + "_");

	}

	// protected methods
	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates) const {

		target.draw(this->_textBox);

	}

	// private methods
	void TextBox::_deleteLast() {

		std::string newStr = this->_text.str();

		if (!newStr.empty())
			newStr.pop_back();

		this->_text.str(newStr);
		this->_textBox.setString(this->_text.str());

	}

} // namespace ng::gui