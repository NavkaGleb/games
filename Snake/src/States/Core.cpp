#include "Core.hpp"

namespace ng {

	// constructor / destructor
	Core::Core() : _window(nullptr), _cursor(nullptr), _sdata(this->_states), _dtime(0.f) {

		this->_initWindow();
		this->_initStates();

	}

	Core::~Core() {

		while (!this->_states.empty()) {

			delete this->_states.top();
			this->_states.pop();

		}

		delete this->_window;

	}

	// public methods
	void Core::run() {

		while (this->_window->isOpen()) {

			sf::Event event{};

			this->_updateDtime();
			this->_update(event);
			this->_render();

		}

	}

	// private methods
	void Core::_initWindow() {

		std::ifstream infile("../config/window.ini");

		if (!infile.is_open())
			throw std::invalid_argument("failed to open the file | Core::_initWindow");

		std::string title;
		unsigned style;

		infile >> this->_sdata.vm.width >> this->_sdata.vm.height;
		infile >> title;
		infile >> style;
		infile >> this->_sdata.settings.antialiasingLevel;
		infile >> this->_sdata.framerateLimit;
		gui::getColor(infile, this->_clearColor);

		this->_window = new sf::RenderWindow(this->_sdata.vm, title, style, this->_sdata.settings);
		this->_window->setFramerateLimit(this->_sdata.framerateLimit);
//		this->_window->setKeyRepeatEnabled(true);

		infile.close();

	}

	void Core::_initStates() {

		this->_states.emplace(new MainMenuState(this->_sdata));

	}

	void Core::_updateDtime() {

		this->_dtime = this->_clock.restart().asSeconds();

	}

	void Core::_update(sf::Event& event) {

		if (!this->_states.empty())
			this->_states.top()->updateMousePosition(sf::Mouse::getPosition(*this->_window));

		while (this->_window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				this->_window->close();

			}

			if (event.type == sf::Event::KeyPressed) {

				if (!this->_states.empty())
					this->_states.top()->updateInput(event);

			}

			if (event.type == sf::Event::MouseButtonPressed) {

				if (!this->_states.empty())
					this->_states.top()->updateMouseClick(event, sf::Mouse::getPosition(*this->_window));

				std::cout << "button pressed!" << std::endl;

			}

			if (event.type == sf::Event::TextEntered) {

				if (!this->_states.empty())
					this->_states.top()->textEntered(event);

			}

		}

		if (!this->_states.empty()) {

			this->_states.top()->update(this->_dtime);

			if (this->_states.top()->quit()) {

				this->_states.top()->end();
				delete this->_states.top();
				this->_states.pop();

			}

		} else {

			this->_end();
			this->_window->close();

		}

	}

	void Core::_render() {

		this->_window->clear(this->_clearColor);

		if (!this->_states.empty())
			this->_states.top()->render(*this->_window);

		this->_window->display();

	}

	void Core::_end() const {

		std::cout << "the end of the game" << std::endl;

	}

} // namespace ng