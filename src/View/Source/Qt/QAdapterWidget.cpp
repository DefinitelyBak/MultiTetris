#include "Qt/QAdapterWidget.h"

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


        QAdapterWidget::QAdapterWidget(AbstractModelPtr model): AbstractWidget()
        {
            _adapter = new Adapter(model);

        }

        bool QAdapterWidget::IsOpen() const
        {
            return true;
        }

        void QAdapterWidget::SetWidget()
        {
            _adapter->SetWidget();
        }

        void QAdapterWidget::SlotCLoseEvent()
        {
            _adapter->Close();
        }

        void QAdapterWidget::SlotUpdateView(Model::DescriptionModel descp)
        {
            _adapter->UpdateView(descp);
        }


        void QAdapterWidget::UpdateWidget()
        {};

}