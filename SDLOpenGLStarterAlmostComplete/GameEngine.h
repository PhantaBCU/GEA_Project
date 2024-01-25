#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace GE {

	// Basic Game Engine class
	class GameEngine {
	public:
		GameEngine();			// Constructor

		virtual ~GameEngine();	// Destructor

		bool init();			// Object initialisation
		bool keep_running();	// Indicates if user has closed window and, hence, game
		void update();			// This is where we update game logic
		void draw();			// This is where a frame is rendered
		void shutdown();		// This is called when the game is ending
								// to release objects created during the game

		// Extra methods
		void setwindowtitle(const char*);

	private:
		// Private data
		// SDL window object to represent the frame
		SDL_Window* window;

		// SDL Gl context to represent OpenGL in the program
		SDL_GLContext glContext;
	};

	// Helper function
	void display_info_message(const char*);

}




