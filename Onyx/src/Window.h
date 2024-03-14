#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core.h"
#include "ErrorHandler.h"
#include "Camera.h"
#include "Math.h"
#include "InputHandler.h"
#include "TextRenderer.h"

namespace Onyx
{
	/*
	 * @brief A class to represent a window.
	 * A window must be created and initialized for anything related to OpenGL to occur.
	 * Window creation and initialization be the first thing done before any other Onyx functions.
	 * This class is disposable.
	 */
	class Window : public Disposable
	{
		friend class InputHandler;
		friend class TextRenderer;

	public:
		/*
		 * @brief Creates an uninitialized 800x600 window with the name "Onyx Window"
		 */
		Window();

		/*
		 * @brief Creates an uninitialized window with the specified title and dimensions.
		 * @param title The title of the window, usually shown on the left of the top border.
		 * @param width The width of the window, in pixels.
		 * @param height The height of the window, in pixels.
		 */
		Window(const char* title, int width, int height);

		/*
		 * @brief Initializes the window.
		 * This initializes the backends, including GLFW and OpenGL.
		 * This function needs to be called before anything related to OpenGL occurs.
		 * This function may cause errors, it is recommended to use the overload with an error handler.
		 */
		void init();

		/*
		 * @brief Initializes the window.
		 * Passes any OpenGL or GLFW initialization errors to the specified error handler.
		 * This initializes the backends, including GLFW and OpenGL.
		 * This function needs to be called before anything related to OpenGL occurs.
		 * @param errorHandler The error handler to use.
		 */
		void init(ErrorHandler& errorHandler);

		/*
		 * @brief Prepares to render the current frame.
		 * This function clears the screen to the background color, clears buffers, and polls GLFW events.
		 */
		void startRender();

		/*
		 * @brief Finishes rendering the current frame.
		 * This function swaps the buffers of the window.
		 */
		void endRender();

		/*
		 * @brief Closes the window.
		 * Once called, isOpen() will return false.
		 */
		void close();

		/*
		 * @brief Sets the window to fullscreen mode.
		 */
		void setFullscreen();

		/*
		 * @brief Sets the window to windowed mode.
		 */
		void setWindowed();

		/*
		 * @brief Toggles fullscreen mode.
		 */
		void toggleFullscreen();

		/*
		 * @brief Gets the GLFW window pointer.
		 * Access to the GLFW window is provided for the library, as well as for advanced users.
		 * @return A pointer to the GLFW window.
		 */
		GLFWwindow* getGlfwWindowPtr();

		/*
		 * @brief Gets the title of the window.
		 * @return The title of the window.
		 */
		const char* getTitle();

		/*
		 * @brief Gets the width of the window.
		 * @return The width of the window.
		 */
		int getWidth();

		/*
		 * @brief Gets the height of the window.
		 * @return The height of the window.
		 */
		int getHeight();

		/*
		 * @brief Gets the width of the rendering frame of the window, not including borders.
		 * @return The buffer width of the window, explained above.
		 */
		int getBufferWidth();

		/*
		 * @brief Gets the height of the rendering frame of the window, not including borders.
		 * @return The buffer height of the window, explained above.
		 */
		int getBufferHeight();

		/*
		 * @brief Gets the initialization status of the window.
		 * @return Whether the window has been initialized.
		 */
		bool isInitialized();

		/*
		 * @brief Gets the open/closed status of the window.
		 * @return Whether the window is open.
		 */
		bool isOpen();

		/*
		 * @brief Sets the background color of the window.
		 * This is what color the window clears to at the start of each frame.
		 * @param rgb The color, specified as red, green, and blue values ranging from 0 to 1.
		 */
		void setBackgroundColor(Onyx::Math::Vec3 rgb);

		/*
		 * @brief Sets the input handler for the window.
		 * Input handling is dependent on the window.
		 * Because of this, input callback funcs need to be set in the window class.
		 * With a reference to the input handler, the callbacks can be sent to said handler.
		 * @param inputHandler The input handler to send callbacks to.
		 */
		void setInputHandler(InputHandler& inputHandler);

		/*
		 * @brief Sets the camera for the window.
		 * The only thing the window does with this is update the aspect ratio of the camera's projection matrix, if it is perspective.
		 * @param cam The camera whose projection matrix to update upon window resize.
		 */
		void setCamera(Camera& cam);

		/*
		 * @brief Gets the input handler of the window.
		 * @return The input handler associated with the window.
		 */
		InputHandler* getInputHandlerPtr();

		/*
		 * @brief Gets the camera of the window.
		 * @return The camera associated with the window.
		 */
		Camera* getCameraPtr();

		/*
		 * @brief Disposes of the window.
		 * This clears up any memory that the object was using.
		 * This function should be used when the object is no longer needed, such as just before the program ends or the object goes out of scope.
		 */
		void dispose() override;

	private:
		GLFWwindow* p_window;
		static GLFWmonitor* p_primaryMonitor;
		static GLFWvidmode* p_primaryMonitorInfo;
		const char* title;
		int width, height, bufferWidth, bufferHeight;
		Onyx::Math::Vec3 background;

		InputHandler* p_inputHandler;
		Camera* p_cam;
		TextRenderer* p_textRenderer;

		bool fullscreen;
		bool initialized;

		static void CB_framebufferSize(GLFWwindow* p_window, int width, int height);
		static void CB_key(GLFWwindow* p_window, int key, int scancode, int action, int mods);
		static void CB_mouseButton(GLFWwindow* p_window, int button, int action, int mods);
		static void CB_cursorPos(GLFWwindow* p_window, double x, double y);
	};
}