#ifndef __GAME__
#define __GAME__

#include <glm/glm.hpp>

#include <EGL/Game.hpp>
#include <EGL/ShaderProgram.hpp>
#include <EGL/InputManager.hpp>
#include <EGL/Clock.hpp>

#include "Scene.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace EGL
{
	class RenderContext;
}

class Game : public EGL::Game
{
public:
	Game();
	virtual ~Game();

	virtual bool	initialize();
	virtual void	update();
	virtual void	draw();
	void			run();

private:
	EGL::RenderContext	*_context;
	EGL::ShaderProgram	_shaderProgram;
	EGL::InputManager	_inputs;
	EGL::Clock			_clock;
	glm::mat4			_cameraViewMatrix;
	glm::mat4			_cameraProjectionMatrix;
	Scene				_scene;
};

#endif