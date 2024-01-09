#pragma once

#include "Precompile.h"

#include "Events.h"
#include "view/IView.h"


/// @brief 
namespace Tetris::Controller
{

	/// @brief 
	class Controller
	{
	public:
		/// @brief 
		Controller();

		/// @brief 
		/// @param  
		void AddView(std::shared_ptr<IView>);

		/// @brief 
		/// @param  
		void AddEvent(Events event);

		/// @brief 
		void StartLoop();

		/// @brief 
		void Notify();

	private:
		std::list<std::shared_ptr<IView>> _views;
	};

}