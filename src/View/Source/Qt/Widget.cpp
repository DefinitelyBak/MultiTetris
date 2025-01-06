#include <View/Qt/Widget.h>


namespace Tetris::View::Qt
{
    Widget::Widget(AbstractModelPtr model, QWidget* parent): QWidget(parent),
        _map(new Map(this)),
        _preview(new WidgetPreviewBlock(this)),
        _controller(model)
    {
        setFocusPolicy(::Qt::ClickFocus);
        SetupMapContainer();
        SetupPreviewContainer();
    }

    void Widget::SetupMapContainer()
    {
        _map->setMinimumSize(420, 800);
        _map->setFocusPolicy(::Qt::NoFocus);

        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(_map);
        setLayout(layout);
    }

    void Widget::SetupPreviewContainer()
    {
        _preview->setMinimumSize(180, 150);
        _preview->setMaximumSize(180, 150);
        _preview->setFocusPolicy(::Qt::NoFocus);

        QVBoxLayout* hLayout = new QVBoxLayout;
        hLayout->addWidget(_preview);
        hLayout->addWidget(CreateScoreLabel());

        auto temp = new QWidget(this);
        temp->setMaximumWidth(180);
        hLayout->addWidget(temp);

        QWidget* shell = new QWidget(this);
        shell->setLayout(hLayout);

        layout()->addWidget(shell);
    }

    void Widget::SetMementoModel(MementoModelPtr descp)
    {
        _mementoModel = descp;
        update();
    }

    QLabel* Widget::CreateScoreLabel()
    {
        _text = new QLabel(this);
        _text->setMinimumSize(180, 100);
        _text->setMaximumSize(180, 100);
        _text->setTextFormat(::Qt::PlainText);
        _text->setFont(CreateScoreFont());
        _text->setAlignment(::Qt::AlignCenter | ::Qt::AlignVCenter);
        _text->setText(QString("Score:\n0"));
        return _text;
    }

    QFont Widget::CreateScoreFont()
    {
        QFont font;
        font.setFamily("Arial");
        font.setPointSize(24);
        font.setBold(true);
        return font;
    }

    void Widget::keyPressEvent(QKeyEvent* event)
    {
        switch (event->key())
        {
            case ::Qt::Key_A:
            case ::Qt::Key_Left:
                _controller.Move(Model::Command::Left);
                break;
            case ::Qt::Key_W:
            case ::Qt::Key_Up:
                _controller.Move(Model::Command::RotateRight);
                break;
            case ::Qt::Key_D:
            case ::Qt::Key_Right:
                _controller.Move(Model::Command::Right);
                break;
            case ::Qt::Key_S:
            case ::Qt::Key_Down:
                _controller.Move(Model::Command::Down);
                break;
            default:
                QWidget::keyPressEvent(event);
                break;
        }
    }

    void Widget::paintEvent(QPaintEvent* event)
    {
        if(_mementoModel)
        {
            _map->SetMap(_mementoModel->map, _mementoModel->size);
            _preview->SetBlock(_mementoModel->nextBlock);
            _text->setText(QString("Score:\n") + QString::number(_mementoModel->score));
        }
    }

}