// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
#include <iostream>
#include "Level.h"
#include "Framework/Menu.h"
#include "Framework/TileEditor.h"
#include "Framework/TileManager.h"
#include "Framework/GameState.h"
#include "Framework/World.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Framework/Utilities.h"
#include <Windows.h>
#include "Candle/RadialLight.hpp"
#include "Candle/DirectedLight.hpp"
#include "Candle/LightingArea.hpp"




void windowProcess(sf::RenderWindow* window, Input* in, Level* level)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);  // Let ImGui process the event first.

		if (!ImGui::GetIO().WantCaptureMouse) {  // Only handle mouse input if ImGui is not using the mouse.
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					in->setLeftMouse(Input::MouseState::DOWN);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					in->setRightMouse(Input::MouseState::DOWN);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					in->setLeftMouse(Input::MouseState::UP);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					in->setRightMouse(Input::MouseState::UP);
				}
				break;
			case sf::Event::MouseMoved:
				in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					in->setMouseWheelDelta(static_cast<int>(event.mouseWheelScroll.delta));
				}
				break;
			}
		}

		// Handle non-mouse specific events regardless of ImGui's interest in the mouse.
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			level->adjustViewToWindowSize(event.size.width, event.size.height);
			break;
		case sf::Event::KeyPressed:
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			in->setKeyUp(event.key.code);
			break;
		}
	}
}


int main()
{
	InitializeResolution();
	//Create the window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "NoobEngine-SFML");
	ImGui::SFML::Init(window);



	// Get the handle to the native window
	HWND hwnd = window.getSystemHandle();
	// Maximize the window
	ShowWindow(hwnd, SW_MAXIMIZE);

	sf::View view;
	sf::Vector2f viewSize = sf::Vector2f(window.getSize().x, window.getSize().y);
	view.setSize(viewSize.x, viewSize.y);
	view.setCenter(viewSize.x / 2, viewSize.y / 2);
	// Initialise input and level objects.
	Input input;
	World world;
	world.setGravity(sf::Vector2f(0, 980.f));

	TileManager tileManager;
	GameState gameState;

	Level level(&window, &input, &gameState,&view,&world,&tileManager);
	Menu menu(&window, &input, &gameState);
	TileEditor tileEditor(&window, &input, &gameState, &view, &world, &tileManager);


	gameState.setCurrentState(State::LEVEL);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;
	float FrameRate = 60.f;

	// Game Loop
	while (window.isOpen())
	{
		//Process window events
		windowProcess(&window, &input, &level);

		// Calculate delta time. How much time has passed
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();
		ImGui::SFML::Update(window, sf::seconds(deltaTime));

		if (deltaTime > 1.0f / FrameRate)
		{
			deltaTime = 1.0f / FrameRate;
		}
		//add tilemanger updatelighting function here #
		tileEditor.getTileManager()->updateLighting();

		//Doing this here rather than in the classes
		//Otherwise each class has its own window.clear and window.display
		//This interferes with the imgui window
		window.clear(sf::Color(18, 33, 43));

		switch (gameState.getCurrentState())
		{
		case(State::MENU):
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			break;

		case(State::LEVEL):
			world.UpdatePhysics(deltaTime);
			level.handleInput(deltaTime);
			level.update(deltaTime);
			level.render();
			break;

		case(State::TILEEDITOR):
			world.UpdatePhysics(deltaTime);
			tileEditor.handleInput(deltaTime);
			tileEditor.update(deltaTime);
			level.render();
			tileEditor.render();
			break;
		}

		// Update input class, handle pressed keys
		// Must be done last.
		//Render imgui and SFML RenderWindow

		//Add tileeditor renderlighting function here 
		tileEditor.getTileManager()->renderLighting();
		ImGui::SFML::Render(window);
		window.display();
		input.update();
	}
	ImGui::SFML::Shutdown();
}