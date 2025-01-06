#include <View/SFML/SFMLApplication.h>
#include <View/SFML/Widget.h>

namespace Tetris::View::SFML
{
    SFMLApplication::SFMLApplication(AbstractModelPtr model, unsigned int countWidgets, const std::string& fontPath)
        : _model(model), _count(countWidgets), _pathFont(fontPath)
    {}

    void SFMLApplication::CreateWidgets()
    {
        for (int i = 0; i < _count; ++i)
        {
            SFMLWidgetPtr widget = std::make_shared<SFML::Widget>(_model, _pathFont);
            _widgets.push_back(widget);
            _model->SetWidget(widget);
        }
    }

    void SFMLApplication::UpdateWidgets()
    {
        _widgets.remove_if([](const SFMLWidgetPtr& widget) { return !widget->IsOpen(); });

        if (_widgets.empty())
        {
            _execution = false;
            return;
        }

        for (auto& widget : _widgets)
            widget->Update();
    }

    void SFMLApplication::Run()
    {
        if (_count > 0)
        {
            CreateWidgets();

            while (_execution)
                UpdateWidgets();
        }
        _execution = false;
    }

}
