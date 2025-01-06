#include <View/Qt/Map.h>


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

    Map::Map(QWidget* parent): QWidget(parent), _rows(0), _columns(0)
    {}

    void Map::SetMap(const std::vector<Model::TypeColor>& map, Model::MapSize sizeMap)
    {
        if (map.empty() || sizeMap.rows <= 0 || sizeMap.columns <= 0)
            return;

        _map = map;
        _rows = sizeMap.rows;
        _columns = sizeMap.columns;
        _offsetX = size().width() / _columns;
        _offsetY = size().height() / _rows;
    }

    void Map::paintEvent(QPaintEvent* event)
    {
        if (isVisible())
            Render();
    }

    void Map::Render()
    {
        if (!isVisible())
            return;

        QRect rect(0, 0, width(), height());
        QPainter painter(this);
        painter.fillRect(rect, ::Qt::black);
        
        painter.setRenderHint(QPainter::Antialiasing);

        for (int row = 0; row < _rows; ++row)
        {
            for (int column = 0; column < _columns; ++column)
            {
                if (auto color = _map[row * _columns + column]; color != Model::TypeColor::None)
                {
                    painter.setBrush(QBrush(ColorFromTypeColor(color), ::Qt::BrushStyle::SolidPattern));
                    painter.drawRect(
                        column * _offsetX,
                        size().height() - row * _offsetY - _offsetY,
                        _offsetX,
                        _offsetY
                    );
                }
            }
        }

        painter.end();
    }

}