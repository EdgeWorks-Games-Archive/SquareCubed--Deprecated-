#pragma once

#include <CommonLib/Logger.h>
#include <CommonLib/Events.h>

#include <memory>
#include <string>

namespace Utils { class ILoggingManager; }
namespace Content { class Content; }
namespace Context { class IContext; }
namespace Graphics { class IGraphics; }
namespace Input { class Input; }
namespace Network { class INetwork; }
namespace GUI { class IGUI; }
namespace StateEngine { class StateEngine; }

namespace Core {
	class Engine final {
		Utils::Logger m_Logger;
		Utils::EventScope m_EventScope;

	public: // Initialization/Uninitialization
		Engine(Utils::ILoggingManager *loggingManager);
		~Engine();

	private: // Properties
		bool m_Running;

	private: // Modules
		std::unique_ptr<Utils::ILoggingManager> m_LoggingManager;
		std::unique_ptr<Content::Content> m_Content;
		std::unique_ptr<Context::IContext> m_Context;
		std::unique_ptr<Graphics::IGraphics> m_Graphics;
		std::unique_ptr<Input::Input> m_Input;
		std::unique_ptr<Network::INetwork> m_Network;
		std::unique_ptr<GUI::IGUI> m_GUI;
		std::unique_ptr<StateEngine::StateEngine> m_StateEngine;

	public: // Module Setters
		/// <summary>Sets the Content Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="content">The Content Module</param>
		void SetContent(Content::Content *content);

		/// <summary>Sets the Context Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="context">The Context Module</param>
		void SetContext(Context::IContext *context);

		/// <summary>Sets the Graphics Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="graphics">The Graphics Module</param>
		void SetGraphics(Graphics::IGraphics *graphics);

		/// <summary>Sets the Input Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="input">The Input Module</param>
		void SetInput(Input::Input *input);

		/// <summary>Sets the Network Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="network">The Network Module</param>
		void SetNetwork(Network::INetwork *network);

		/// <summary>Sets the GUI Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="gui">The GUI Module</param>
		void SetGUI(GUI::IGUI *gui);

		/// <summary>Sets the State Engine Module to the parameter given. Transfers pointer ownership.</summary>
		/// <param name="stateEngine">The State Engine Module</param>
		void SetStateEngine(StateEngine::StateEngine *stateEngine);

	public: // Module Accessors
		/// <summary>Gets the Logging Manager</summary>
		/// <returns>The Logging Manager</returns>
		Utils::ILoggingManager& GetLoggingManager();

		/// <summary>Gets the Content Module</summary>
		/// <returns>The Content Module</returns>
		Content::Content& GetContent();

		/// <summary>Gets the Context Module</summary>
		/// <returns>The Context Module</returns>
		Context::IContext& GetContext();

		/// <summary>Gets the Graphics Module</summary>
		/// <returns>The Graphics Module</returns>
		Graphics::IGraphics& GetGraphics();

		/// <summary>Gets the Input Module</summary>
		/// <returns>The Input Module</returns>
		Input::Input& GetInput();

		/// <summary>Gets the Network Module</summary>
		/// <returns>The Network Module</returns>
		Network::INetwork& GetNetwork();

		/// <summary>Gets the GUI Module</summary>
		/// <returns>The GUI Module</returns>
		GUI::IGUI& GetGUI();

		/// <summary>Gets the State Engine Module</summary>
		/// <returns>The State Engine Module</returns>
		StateEngine::StateEngine& GetStateEngine();

	public: // Game Loop
		/// <summary>Executes this Instance</summary>
		void Execute();

	private: // Event Callbacks
		void OnQuitCall(const std::string &str);
	};
}