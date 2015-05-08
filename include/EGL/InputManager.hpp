#ifndef __EGL_INPUT_MANAGER__
#define __EGL_INPUT_MANAGER__

#include <glm/glm.hpp>
#include <unordered_set>
#include <unordered_map>

namespace EGL
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void	clear();
		void	addKeyPressed(int key);
		void	addKeyReleased(int key);
		void	setMousePosition(glm::ivec2 const& position);
		void	setMouseWheel(glm::ivec2 const& delta);

		bool				hasKeyInput(int key, bool handled = false);
		bool				isKeyPressed(int key);
		glm::ivec2 const&	getMousePosition() const;
		glm::ivec2 const&	getMouseDelta() const;
		glm::ivec2 const&	getMouseWheel() const;

	private:
		std::unordered_set<int>			_keyInputs;
		std::unordered_map<int, bool>	_keyStates;
		glm::ivec2						_mousePosition;
		glm::ivec2						_mouseDelta;
		glm::ivec2						_mouseWheelDelta;
	};
}

#endif