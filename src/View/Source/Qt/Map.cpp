#include "Qt/Map.h"
#include <QPainter>
#include <QResizeEvent>

namespace Tetris::View::Qt
{

    QColor ColorFromTypeColor(Model::TypeColor color)
    {
        switch (color)
        {
        case Model::TypeColor::Blue:
            return ::Qt::blue;
        case Model::TypeColor::Green:
            return ::Qt::green;
        case Model::TypeColor::Red:
            return ::Qt::red;
        case Model::TypeColor::Yellow:
            return ::Qt::yellow;
        default:
            return ::Qt::black;
        }
    }

    Map::Map(QWindow *parent, bool withBorder)
        : QWindow(parent), m_backingStore(new QBackingStore(this)), _borderWidth(0), _rows(0), _columns(0)
    {
        if (withBorder)
        {
            InitializeBorders();
        }
    }

    void Map::InitializeBorders()
    {
        // Граница будет 0.01 от ширины или высоты.  
        float borderY = float(size().height()) / 100;
        float borderX = float(size().width()) / 100;

        _borderWidth = std::max(borderY, borderX);

        // Инициализация вертикальных и горизонтальных границ
        _borders = {
            QRect(0, 0, _borderWidth, size().height()), // Левый
            QRect(size().width() - _borderWidth, 0, _borderWidth, size().height()), // Правый
            QRect(0, 0, size().width(), _borderWidth), // Верхний
            QRect(0, size().height() - _borderWidth, size().width(), _borderWidth) // Нижний
        };
    }

    void Map::SetMap(const std::vector<Model::TypeColor>& map, Model::MapSize sizeMap)
    {
        if (map.empty() || sizeMap.rows <= 0 || sizeMap.columns <= 0)
            return;

        _map = map;
        _rows = sizeMap.rows;
        _columns = sizeMap.columns;
        _offsetX = (size().width() - 2 * _borderWidth) / _columns;
        _offsetY = (size().height() - 2 * _borderWidth) / _rows;

        renderNow();
    }

    bool Map::event(QEvent *event)
    {
        if (event->type() == QEvent::UpdateRequest) {
            renderNow();
            return true;
        }
        return QWindow::event(event);
    }

    void Map::resizeEvent(QResizeEvent *resizeEvent)
    {
        m_backingStore->resize(resizeEvent->size());
        if (isExposed())
        {
            renderNow();
        }
    }

    void Map::exposeEvent(QExposeEvent *)
    {
        if (isExposed())
        {
            renderNow();
        }
    }

    void Map::renderLater()
    {
        requestUpdate();
    }

    void Map::renderNow()
    {
        if (!isExposed())
        {
            return;
        }

        QRect rect(0, 0, width(), height());
        m_backingStore->beginPaint(rect);

        QPainter painter(m_backingStore->paintDevice());
        painter.fillRect(rect, ::Qt::black);
        render(&painter);

        painter.end();
        m_backingStore->endPaint();
        m_backingStore->flush(rect);
    }

    void Map::render(QPainter* painter)
    {
        painter->setRenderHint(QPainter::Antialiasing);

        if (!_borders.empty())
        {
            QBrush borderBrush(::Qt::white);
            painter->setBrush(borderBrush);
            painter->drawRects(_borders);
        }

        for (int row = 0; row < _rows; ++row)
        {
            for (int column = 0; column < _columns; ++column)
            {
                if (auto color = _map[row * _columns + column]; color != Model::TypeColor::None)
                {
                    painter->setBrush(QBrush(ColorFromTypeColor(color), ::Qt::BrushStyle::SolidPattern));
                    painter->drawRect(
                        _borderWidth + column * _offsetX,
                        size().height() - row * _offsetY - _offsetY - _borderWidth,
                        _offsetX,
                        _offsetY
                    );
                }
            }
        }
    }

}