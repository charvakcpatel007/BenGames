#include "MainGame.h"
#include <string>
#include <iostream>

void fatalError( std::string errorString )
{
	std::cout << errorString << std::endl;
	std::cout << "Press Any Key To Quit..." << std::endl;
	int temp;
	std::cin >> temp;
	SDL_Quit();
}

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 800;
	_screenHeight = 600;
	_gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	testSprite.init( -1, -1, 1, 1 );
	gameLoop();
}

void MainGame::initSystems()
{
	//Initialize SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	_window = SDL_CreateWindow( "Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL );
	if ( _window == nullptr )
	{
		fatalError("SDL Window Could not be opened");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if ( glContext == nullptr )
	{
		fatalError("SDL_GL could not be created");
	}

	GLenum error = glewInit();
	if ( error != GLEW_OK )
	{
		fatalError("Glew could not be init");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
}

void MainGame::gameLoop()
{
	while ( _gameState != GameState::EXIT )
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while( SDL_PollEvent( &evnt ) )
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		}
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	testSprite.draw();

	SDL_GL_SwapWindow(_window);
}
