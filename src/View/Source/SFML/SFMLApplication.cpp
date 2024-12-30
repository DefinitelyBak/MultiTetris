#include <View/SFML/SFMLApplication.h>
#include <View/SFML/Widget.h>

namespace Tetris::View::SFML
{
    SFMLApplication::SFMLApplication(AbstractModelPtr model, unsigned int countWidgets, const std::string& fontPath)
        : IApplication(), _model(model), _count(countWidgets), _pathFont(fontPath), _execution(true)
    {
        _thread = std::thread(&SFMLApplication::Run, this);
    }

    SFMLApplication::~SFMLApplication()
    {
        _execution = false;
        if (_thread.joinable())
            _thread.join();
    }

    void SFMLApplication::CreateWidgets()
    {
        for (int i = 0; i < _count; ++i)
        {
            AbstractWidgetPtr widget = std::make_shared<SFML::Widget>(_model, _pathFont);
            _widgets.push_back(widget);
            _model->SetWidget(widget);
        }
    }

    void SFMLApplication::UpdateWidgets()
    {
        _widgets.erase(std::remove_if(_widgets.begin(), _widgets.end(),
            [](const AbstractWidgetPtr& widget) { return !widget->IsOpen(); }), _widgets.end());

        if(_widgets.empty())
            _execution = false;

        for (auto& widget : _widgets)
        {
            widget->Update();
        }
    }

    void SFMLApplication::Run()
    {
        CreateWidgets();

        while (_execution)
        {
            UpdateWidgets();
        }
    }

    bool SFMLApplication::isExecution() const
    {
        return _execution;
    }
}
