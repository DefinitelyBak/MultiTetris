#include "Qt/Map.h"
#include <QPainter>
#include <QResizeEvent>

namespace Tetris::View::Qt
{

    QColor ColorFromTypeColor(Model::TypeColor color)
    {
        switch (color)
        {
        case Model::TypeColor::Blue :
            return ::Qt::blue;
        case Model::TypeColor::Green :
            return ::Qt::green;
        case Model::TypeColor::Red :
            return ::Qt::red;
        case Model::TypeColor::Yellow :
            return ::Qt::yellow;
        default:
            break;
        }
        return ::Qt::black;
    }

    Map::Map(QWindow *parent, bool withBorder): QWindow(parent), m_backingStore(new QBackingStore(this))
    {
        if(withBorder)
        {
            // Граница будет 0.01 от ширины или высоты.  
            float borderY = float(size().height())/100;
            float borderX = float(size().width())/100;

            _borderWidth = std::max(borderY, borderX);

            /// Вертикальные границы
            _borders.push_back(QRect(0,0, _borderWidth, size().height()));
            _borders.push_back(QRect(size().width() - _borderWidth, 0, _borderWidth, size().height()));
            
            /// Горизонтальные границы
            _borders.push_back(QRect(0,0, size().width(), _borderWidth));
            _borders.push_back(QRect(0,size().height() - _borderWidth, size().width(), _borderWidth));
        }
    }

    void Map::SetMap(Model::DataMap map, int rows, int columns)
    {
        // Проверка на дурака
        if(map.empty() || rows == 0 || columns == 0 )
            return;

        _map = map;
        _rows = rows;
        _columns = columns;
        _offsetX = (size().width() - 2*_borderWidth)/_columns;
        _offsetY = (size().height()- 2*_borderWidth)/_rows;

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
        // Изменяем размер буфера кадра, чтобы он совпадал с размером окна
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

        QPaintDevice *device = m_backingStore->paintDevice();
        QPainter painter(device);

        painter.fillRect(0, 0, width(), height(), ::Qt::black);
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


        int i = 0;
        for(int row = 0; row < _rows; ++row)
        {
            for(int column = 0; column < _columns; ++column)
            {
                if (auto color = _map[row * _columns + column]; color != Model::TypeColor::None)
                {
                    painter->setBrush(QBrush(ColorFromTypeColor(color), ::Qt::BrushStyle::SolidPattern));
                    painter->drawRect(_borderWidth + column * _offsetX,  size().height() - row * _offsetY - _offsetY - _borderWidth, _offsetX, _offsetY);
                    ++i;
                }
            }
        } 
        /*
        // Устанавливаем режим устранения ступенчатости фигур (anti-aliasing mode)
        painter->setRenderHint(QPainter::Antialiasing);

        // Устанавливаем кисть жёлтого цвета (цвет задан в RGB)
        painter->setBrush(QBrush(QColor(0xFA, 0xFE, 0x78)));

        // Рисуем эллипс на всё окно с отступом 5 пикселей
        painter->drawEllipse(QRect(5, 5, width() - 10, height() - 10));
        */
    }

}