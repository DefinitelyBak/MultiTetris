#include "Qt/Widget.h"

#include "Qt/KeyPressFilter.h"
#include "Qt/PreviewBlock.h"


namespace Tetris::View::Qt
{
    Widget::Widget(QWidget* parent)
        : QWidget(parent), 
          _map(new Map(nullptr, true)), 
          _preview(new PreviewBlock(nullptr, true)), 
          _descriptionModel()
    {
        setAttribute(::Qt::WA_QuitOnClose);
        setFocusPolicy(::Qt::ClickFocus);
        setupMapContainer();
        setupPreviewContainer();
    }

    void Widget::setupMapContainer()
    {
        QWidget* container = QWidget::createWindowContainer(_map, this);
        container->setMinimumSize(420, 800);
        container->setFocusPolicy(::Qt::ClickFocus);

        KeyPressFilter* filter = new KeyPressFilter(this);
        _map->installEventFilter(filter);

        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(container);
        setLayout(layout);
    }

    void Widget::setupPreviewContainer()
    {
        QWidget* containerPrev = QWidget::createWindowContainer(_preview, this);
        containerPrev->setMinimumSize(180, 150);
        containerPrev->setMaximumSize(180, 150);
        containerPrev->setFocusPolicy(::Qt::NoFocus);

        QVBoxLayout* hLayout = new QVBoxLayout;
        hLayout->addWidget(containerPrev);
        hLayout->addWidget(createScoreLabel());

        auto temp = new QWidget(this);
        temp->setMaximumWidth(180);
        hLayout->addWidget(temp);

        qobject_cast<QHBoxLayout*>(layout())->addLayout(hLayout);
    }

    QLabel* Widget::createScoreLabel()
    {
        _text = new QLabel(this);
        _text->setMinimumSize(180, 100);
        _text->setMaximumSize(180, 100);
        _text->setTextFormat(::Qt::PlainText);
        _text->setFont(createScoreFont());
        _text->setAlignment(::Qt::AlignCenter | ::Qt::AlignVCenter);
        _text->setText(QString("Score:\n0"));
        return _text;
    }

    QFont Widget::createScoreFont()
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
                emit SignalUpdateModel(Model::Command::Left);
                break;
            case ::Qt::Key_W:
            case ::Qt::Key_Up:
                emit SignalUpdateModel(Model::Command::RotateRight);
                break;
            case ::Qt::Key_D:
            case ::Qt::Key_Right:
                emit SignalUpdateModel(Model::Command::Right);
                break;
            case ::Qt::Key_S:
            case ::Qt::Key_Down:
                emit SignalUpdateModel(Model::Command::Down);
                break;
            default:
                QWidget::keyPressEvent(event);
                break;
        }
    }

    void Widget::paintEvent(QPaintEvent* event)
    {
        Model::DescriptionModel descriptionModel = GetDescriptionModel();
        _map->SetMap(descriptionModel.map, descriptionModel.size);
        if (descriptionModel.nextBlock)
            _preview->SetBlock(descriptionModel.nextBlock);
        if (descriptionModel.score)
            _text->setText(QString("Score:\n") + QString::number(descriptionModel.score.value()));
    }

    void Widget::SlotUpdateView(Model::DescriptionModel descp)
    {
        {
            std::lock_guard<std::mutex> l(_mutex);
            _descriptionModel = descp;
        }
        update();
    }

    Model::DescriptionModel Widget::GetDescriptionModel()
    {
        std::lock_guard<std::mutex> l(_mutex);
        return _descriptionModel;
    }

}