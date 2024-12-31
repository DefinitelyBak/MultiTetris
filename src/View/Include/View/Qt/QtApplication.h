#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <Model/AbstractModel.h>
#include <View/IApplication.h>
#include <View/Qt/Widget.h>


namespace Tetris::View::Qt
{
    /**
     * @class QtApplicaion
     * @brief Класс, реализующий интерфейс IApplication для создания приложения Tetris.
     */
    class VIEW_EXPORT QtApplicaion final: public IApplication
    {
    public:
        /**
         * @brief Конструктор класса.
         * @param model Указатель на модель, используемую приложением.
         * @param countWidgets Количество виджетов, создаваемых приложением.
         */
        QtApplicaion(AbstractModelPtr model, unsigned int countWidgets);
        
        /**
         * @brief Деструктор класса.
         * Освобождает ресурсы, связанные с приложением.
         */
        ~QtApplicaion();

        /**
         * @brief Метод, выполняющий основную логику приложения в отдельном потоке.
         * Реализует основной цикл приложения.
         */
        void Run() override;

        /**
         * @brief Метод для проверки состояния выполнения приложения.
         * @return true, если приложение выполняется; false в противном случае.
         */
        bool isExecution() const override; 

    private:
        unsigned int _count; ///< Количество виджетов, создаваемых приложением.
        
        AbstractModelPtr _model; ///< Указатель на модель, используемую приложением.

        std::thread _thread; ///< Поток, в котором выполняется основной цикл приложения.
        std::atomic<bool> _execution; ///< Флаг, указывающий на текущее состояние выполнения приложения.
    };

} // namespace Tetris::View::Qt
