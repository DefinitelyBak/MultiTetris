#include "SFMLApplication.h"

#include "SFMLWidget.h"


namespace Tetris::View
{

        SFMLApplication::SFMLApplication(std::shared_ptr<Model::AbstractModel> model, unsigned int countWidgets): _model(model), _count(countWidgets)
        {
            _pathFont = "C:\\Projects\\ProjectTetris\\Tetris\\src\\view\\Resources\\tuffy.ttf";
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

        }

}