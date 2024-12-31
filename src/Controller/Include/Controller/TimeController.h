#pragma once

#include <Controller/Precompile.h>
#include <Controller/Export.h>

#include <Model/Types.h>
#include <Model/AbstractModel.h>


namespace Tetris::Controller
{
	/// @brief Контроллер движения фигур
	class CONTROLLER_EXPORT TimeController
	{
	public:
		/// @brief Конструктор
		/// @param model Модель игры на которую воздействует контроллер
		/// @param interval Интервал времени перемещения блока
		TimeController(AbstractModelPtr model, std::chrono::seconds interval);

		/// @brief Проверка проверка промежутка времени между испускания прошлого сигнала и interval
		void CheckTimer();

    private:
		boost::signals2::signal<void(Model::Command)> SignalUpdateModel;

        std::chrono::seconds _interval;
        std::chrono::time_point<std::chrono::system_clock> _start;
	};

} // namespace Tetris::Controller