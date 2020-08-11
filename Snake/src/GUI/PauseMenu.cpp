#include "PauseMenu.hpp"

#include <cmath>

namespace ng::gui {

	// constructor / destructor
	PauseMenu::PauseMenu(const sf::VideoMode& vm, unsigned characterSize, const sf::Font& font, float y)
		: _font(font), _active(false) {

		// init background
		this->_background.setPosition(0.f, 0.f);
		this->_background.setSize(sf::Vector2f(vm.width, vm.height));
		this->_background.setFillColor(sf::Color(50, 50, 50, 200));

		// init text
		this->_text.setCharacterSize(characterSize);
		this->_text.setFont(font);
		this->_text.setString("pause");
		this->_text.setOrigin(
			std::floor(this->_text.getGlobalBounds().left + this->_text.getGlobalBounds().width / 2.f),
			std::floor(this->_text.getGlobalBounds().top + this->_text.getGlobalBounds().height / 2.f)
		);

		this->_text.setPosition(
			std::floor(this->_background.getPosition().x + this->_background.getGlobalBounds().width / 2.f),
			std::floor(y)
		);

	}

	PauseMenu::~PauseMenu() {

		for (const auto& p : this->_buttons)
			delete p.second;

	}

	// accessors
	const bool& PauseMenu::active() const { return this->_active; }

	bool PauseMenu::isButtonPressed(const std::string& key) const { return this->_buttons.at(key)->isPressed(); }

	// modifiers
	void PauseMenu::active(const bool& active) { this->_active = active; }

	// public methods
	void PauseMenu::addButton(const float& y, const float& offsety, const float& width, const float& height,
		const std::string& text, const unsigned& characterSize,
		const sf::Color& bidle, const sf::Color& bhover, const sf::Color& bactive) {

		this->_buttons[text] = new Button(
			(this->_background.getGlobalBounds().width - width) / 2.f, y + offsety * this->_buttons.size(),
			width, height, text, characterSize, this->_font, bidle, bhover, bactive
		);

	}

	void PauseMenu::updateMousePosition(const sf::Vector2i& mousePosition) {

		for (const auto& p : this->_buttons)
			p.second->update(mousePosition);

	}

	void PauseMenu::update(const sf::Vector2i& mousePosition) {



	}

	// protected methods
	void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates) const {

		target.draw(this->_background);

		for (const auto& p : this->_buttons)
			target.draw(*p.second);

		target.draw(this->_text);

	}

	// private methods

} // namespace ng::gui