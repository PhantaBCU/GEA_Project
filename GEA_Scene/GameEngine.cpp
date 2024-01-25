#include "GameEngine.h"
#include <iostream>

namespace GE {

	GameEngine::GameEngine() {

	}

	GameEngine::~GameEngine()
	{
	}

	bool GameEngine::init(bool vSyncEnabled) {
		// Initialise SDL video subsystem
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cerr << "Unable to initialise SDL! SDL error : " << SDL_GetError() << std::endl;
			return false;
		}

		// Set the OpenGL version for the program
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Set the type of profile which is core meaning modern OpenGL
		// means no legacy features for backwards compatibility
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		// Create the window and frame features
		// In this case window has a fixed size and prepares window for OpenGL to render into
		window = SDL_CreateWindow("SDL OpenGL", 50, 50, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		// Check window was created
		if (window == nullptr) {
			// Display an error if window wasn't created
			// Could log the errors to a file or create more robust error handling
			// e.g. give specific errors a number
			std::cerr << "Unable to create window! SDL error: " << SDL_GetError() << std::endl;

			// Return failure so caller can work out what to do
			return false;
		}

		// Creates the OpenGL context and links it to the window object
		// Context represents OpenGL for program such as objects and drawing
		glContext = SDL_GL_CreateContext(window);

		// Check context object was created
		if (glContext == nullptr) {
			//Display error and return failure
			std::cerr << "Unable to create GL Context! SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		// Initialise GLEW.  GLEW solves a problem with OpenGL on windows
		// as default API supported by Windows is 1.1 (from 1997)
		// GLEW binds latest extensions that can be used
		GLenum status = glewInit();


		// Check GLEW initialised ok
		if (status != GLEW_OK) {
			//Display error and return failure
			std::cerr << "Unable to create GLEW! GLEW error: " << glewGetErrorString(status) << std::endl;
			return false;
		}

		// Try to turn on VSync (bool passed through from Main to determine Vsync on or off)
		if (vSyncEnabled == true) {
			if (SDL_GL_SetSwapInterval(1) != 0) {
				std::cerr << "Unable to set Vsync! SDL error: " << SDL_GetError() << std::endl;
			}
		}
		// Got this far then must have been successful setting up SDL and OpenGL
		return true;
	}

	// A game would call this function to check if the user closed the window
	// resulting in a SQL_QUIT message
	bool GameEngine::keep_running() {
		// Need to do this keep the event queue up to date
		SDL_PumpEvents();

		SDL_Event evt;

		// Check for quit event
		if (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			// If user quit program, then return false meaning
			// don't keep running
			return false;
		}

		// Got this far means no quit event so keep running
		return true;
	}

	// Update method which updates the game logic
	// Does nothing for this example
	void GameEngine::update() {
	

	}

	// Draw method.  Will modify this to render more complex scenes
	// For now clears the background
	void GameEngine::draw() {
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw a primitive (triangle) using immediate mode OpenGL
		// immediate mode involves sending graphics commands to OpenGL
		// to render.  Easy to use but not very efficient because
		// OpenGL is getting commands on an ad-hoc basis.  Makes it
		// difficult for OpenGL to optimise rendering because doesn't
		// know what's coming next.  Immediate mode is not to be used
		// for the assignment
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-1.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2f(0.0f, 1.0f);
		glEnd();



		SDL_GL_SwapWindow(window);

	}

	// Shutdown method closes OpenGL and SDL down
	// Will need to modify when we create additional objects
	void GameEngine::shutdown() {
		SDL_DestroyWindow(window);

		window = nullptr;

		SDL_Quit();
	}

	void GameEngine::clean()
	{

	}

	// Simple helper method to set the text in window title bar
	void GameEngine::setwindowtitle(const char* new_title) {
		SDL_SetWindowTitle(window, new_title);
	}

	// Simple helper function to display program information
	// Note it is separate from the GameEngine class as it doesn't depend on it
	void display_info_message(const char* msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Basic Game Engine", msg, nullptr);
	}

}