#pragma once

#include "Precompile.h"
#include "Forwards.h"

#include "AbstractModel.h"
#include "MoveController.h"
#include "Qt/Map.h"
#include "Qt/PreviewBlock.h"

#include <QWidget>
#include <QObject>
#include <QLabel>


/// Состояние карты меняется только из методов UpdateView, просто надо какие соыбятие
/// создавляют перерисовывать содержимое
namespace Tetris::View::Qt
{

    class Widget : public QWidget
    {
        Q_OBJECT 
    public:
    
        Widget(QWidget* parent = nullptr);

    public slots:

        void SlotUpdateView(Model::DescriptionModel descp)
        {
            _map->SetMap(descp.map, descp.size.rows, descp.size.columns);
            if (descp.nextBlock)
                _preview->SetBlock(descp.nextBlock->typeBlock, descp.nextBlock->color);
            if (descp.score)
                _text->setText(QString("Score:\n") + QString::number(*descp.score));
        }

    signals:

        void SignalUpdateModel(Model::Command);

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        /// Qt events из этих событий должен вызываться AbstractWidget::Update
        // а из него вызывается UpdateWidget
        // closeEvent(QCloseEvent *event) нужнен тут или нет? Думаю нет.

    private:
        Map* _map;

        QLabel* _text;
        
        PreviewBlock* _preview;

    };
}