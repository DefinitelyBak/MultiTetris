#include "SFML/SFMLApplication.h"

#include "SFML/SFMLWidget.h"


namespace Tetris::View
{

        SFMLApplication::SFMLApplication(AbstractModelPtr model, unsigned int countWidgets): _model(model), _count(countWidgets)
        {
            _pathFont = "C:\\Projects\\ProjectTetris\\Tetris\\src\\view\\Resources\\tuffy.ttf"; // Будет исправлено как разберусь с тем как работать с ресурсами в cmake
            _execution = true;
            _thread = std::thread(Tetris::View::SFMLApplication::Run, this);
        }

        SFMLApplication::~SFMLApplication()
        {
            _thread.join();
        }

        void SFMLApplication::Run()
        {
            /// проверка на дурака
            if (!_widgets.empty())
                return;

            for(int i = 0; i < _count; ++i)
            {
                _widgets.push_back(std::make_shared<SFMLWidget>(_model, _pathFont));
                _model->SetView(_widgets.back());
            }

            while(!_widgets.empty())
            {
                for(auto iter = _widgets.begin(); iter != _widgets.end();)
                {
                    if(!(*iter)->IsOpen())
                        iter = _widgets.erase(iter);
                    else
                    {
                        (*iter)->Update();
                        ++iter;
                    }
                }
            }

            _execution = false;
        }

        bool SFMLApplication::isExecution() const
        {
            return _execution;
        }
}