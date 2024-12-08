#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include "AbstractModel.h"
#include "MoveController.h"

#include <QWidget>
#include <QObject>


/// Состояние карты меняется только из методов UpdateView, просто надо какие соыбятие
/// создавляют перерисовывать содержимое
namespace Tetris::View::Qt
{

    class Widget final : public Model::AbstractWidget, public QWidget
    {
    public:
    
        Widget(AbstractModelPtr model);

        bool IsOpen() const override;

    protected:
        bool event(QEvent*) override;
        void keyPressEvent(QKeyEvent *event) override;
        /// Qt events из этих событий должен вызываться AbstractWidget::Update
        // а из него вызывается UpdateWidget
        // closeEvent(QCloseEvent *event) нужнен тут или нет? Думаю нет.

        /// AbstractWidget events
        void UpdateWidget() override;
        void ProcessingEvents() override;
        void UpdateView(Model::DescriptionModel descriptionModel) override;
        void CloseEvent() override;

    private:
        Controller::MoveController _controller;

        QEvent* _qtEvent{nullptr};
        std::stack<Tetris::Model::Command> _modelEvents;

        std::atomic<bool> _windowOpen{true};
    };
}