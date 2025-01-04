#include <boost/program_options.hpp>
#include <iostream>

#include <Model/ModelGame.h>
#include <View/SFML/SFMLApplication.h>
#include <View/Qt/QtApplication.h>
#include <Controller/TimeController.h>

/**
@mainpage MultiTetris
Это классическая игра Tetris со множеством окон визуализации, в которой игроки управляют падающими блоками,
чтобы заполнять горизонтальные линии на игровом поле.
Игра выполнена в соответствии с требованиями [SRS системы Tetris](https://tetris.wiki/Super_Rotation_System).

Этот проект реализует Tetris с использованием библиотек SFML и Qt.
Также проект предоставляет возможность реализации собственной графической части, что требует реализациии собсвтенного приложения на основе класса `IApplication`,
Виджеты необходимо наследовать от `AbstractWidget` и регистрации вашего виджета в модели.
*/
namespace opt = boost::program_options;

void addApplication(std::list<Tetris::View::AbstractApplicationPtr>& applications, 
                    Tetris::View::AbstractModelPtr modelPtr, 
                    const std::string& appType, int count, const std::string& fontPath = "")
{
    if (count > 0)
    {
        if (appType == "SFML")
            applications.push_back(std::make_shared<Tetris::View::SFML::SFMLApplication>(modelPtr, count, fontPath));
        else if (appType == "Qt")
            applications.push_back(std::make_shared<Tetris::View::Qt::QtApplicaion>(modelPtr, count));
    }
}

int main(int argc, char *argv[])
{   
    opt::options_description desc("MultiTetris - multi-window tetris using STL and Qt graphics libraries.\nAll options");
    desc.add_options()
        ("QWidget", opt::value<int>(), "how many QWidgets, by default 1")
        ("SFMLWidget", opt::value<int>(), "how many SFMLWidget, by default 1")
        ("help", "produce help message");

    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);
    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }
    
    int countSfWidgets = 1, countQtWidgets = 1;
    if(!vm["SFMLWidget"].empty())
        countSfWidgets = vm["SFMLWidget"].as<int>();
    if(!vm["QWidget"].empty())
        countQtWidgets = vm["QWidget"].as<int>();

    std::list<Tetris::View::AbstractApplicationPtr> applications;
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();
    addApplication(applications, modelPtr, "SFML", countSfWidgets, "./Resources/arial_bolditalicmt.ttf");
    addApplication(applications, modelPtr, "Qt", countQtWidgets);
    Tetris::Controller::TimeController timer(modelPtr, std::chrono::seconds(1));

    while(!applications.empty())
    {
        applications.remove_if([](Tetris::View::AbstractApplicationPtr app){return !app->isExecution();});
        timer.CheckTimer();
    }
}
