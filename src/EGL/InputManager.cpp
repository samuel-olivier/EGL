#include "EGL/InputManager.hpp"

namespace EGL
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	void	InputManager::clear()
	{
		this->_keyInputs.clear();
	}

	void	InputManager::addKeyPressed(int key)
	{
		this->_keyInputs.insert(key);
		this->_keyStates[key] = true;
	}

	void	InputManager::addKeyReleased(int key)
	{
		this->_keyStates[key] = false;
	}

	void	InputManager::setMousePosition(glm::ivec2 const& position)
	{
		this->_mouseDelta = position - this->_mousePosition;
		this->_mousePosition = position;
	}

	void	InputManager::setMouseWheel(glm::ivec2 const& delta)
	{
		this->_mouseWheelDelta = delta;
	}

	bool	InputManager::hasKeyInput(int key, bool handled)
	{
		auto	it = this->_keyInputs.find(key);

		if (it == this->_keyInputs.end()) {
			return false;
		} else if (handled == true) {
			this->_keyInputs.erase(it);
		}
		return true;
	}

	bool	InputManager::isKeyPressed(int key)
	{
		auto	it = this->_keyStates.find(key);

		if (it == this->_keyStates.end()) {
			return false;
		}
		return it->second;
	}

	glm::ivec2 const&	InputManager::getMousePosition() const
	{
		return this->_mousePosition;
	}

	glm::ivec2 const&	InputManager::getMouseDelta() const
	{
		return this->_mouseDelta;
	}

	glm::ivec2 const&	InputManager::getMouseWheel() const
	{
		return this->_mouseWheelDelta;
	}
}