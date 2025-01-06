#pragma once

#include <View/Precompile.h>
#include <View/Export.h>
#include <View/Forwards.h>

#include <Model/AbstractModel.h>
#include <View/AbstractApplication.h>
#include <View/Qt/Widget.h>
#include <View/Qt/QAdapterWidget.h>


namespace Tetris::View::Qt
{
    /// @brief Класс, реализующий интерфейс IApplication для графического приложения на базе Qt.
    class VIEW_EXPORT QtApplicaion final: public AbstractApplication
    {
    public:
        /// @brief Конструктор класса.
        /// @param model Указатель на модель, используемую приложением.
        /// @param countWidgets Количество виджетов, создаваемых приложением.
        QtApplicaion(AbstractModelPtr model, unsigned int countWidgets);
        
    private:
        /// @brief Метод, выполняющий основную логику приложения в отдельном потоке.
        /// Реализует основной цикл приложения.        
        void Run() override;

        unsigned int _count; ///< Количество виджетов, создаваемых приложением.
        AbstractModelPtr _model; ///< Указатель на модель, используемую приложением.

        std::list<std::shared_ptr<Qt::QAdapterWidget>> _widgets; ///< Виджеты qt
    };

} // namespace Tetris::View::Qt
