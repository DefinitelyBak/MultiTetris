#pragma once

#include "Qt/Widget.h"
#include <Qt>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>
#include "Qt/KeyPressFilter.h"
#include "Qt/Widget.h"
#include <QDebug>

#include "Qt/Adapter.h"
#include "Qt/Widget.h"
#include <QWidget>


namespace Tetris::View::Qt
{

    class QAdapterWidget: public  Model::AbstractWidget
    {
    public:
        QAdapterWidget(AbstractModelPtr model);

        bool IsOpen() const override;

        void SetWidget();

        void SlotCLoseEvent() override;

        void SlotUpdateView(Model::DescriptionModel descp) override;

    protected:

        void UpdateWidget() override;

    private:
        Adapter* _adapter;
    };

}