#pragma once

#include <Controller/Precompile.h>
#include <Controller/Export.h>

#include <Model/Types.h>
#include <Model/AbstractModel.h>


namespace Tetris::Controller
{
	/// @brief Контроллер движения фигур
	class CONTROLLER_EXPORT MoveController
	{
	public:
		/// @brief Конструктор
		/// @param model Модель игры на которую воздействует контроллер
		MoveController(AbstractModelPtr model);

		/// @brief Переместить фигуру
		/// @param cmn Комманда 
		void Move(Model::Command cmn);

	private:
		boost::signals2::signal<void(Model::Command)> SignalUpdateModel;
	};

} // namespace Tetris::Controller