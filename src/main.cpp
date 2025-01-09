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
Также проект предоставляет возможность реализации собственной графической части, что требует реализациии собсвтенного приложения на основе класса `AbstractApplication`,
Виджеты необходимо наследовать от `AbstractWidget` и регистрации вашего виджета в модели.
*/
namespace opt = boost::program_options;

enum class TypeApplication : int
{
    SFML,
    Qt
};

[[nodiscard]] Tetris::View::AbstractApplicationPtr MakeApplication(const TypeApplication type, Tetris::View::AbstractModelPtr modelPtr,const int count)
{
    switch (type)
    {
    case TypeApplication::SFML:
        return std::make_shared<Tetris::View::SFML::SFMLApplication>(modelPtr, count, "./Resources/arial_bolditalicmt.ttf");
    case TypeApplication::Qt:
        return std::make_shared<Tetris::View::Qt::QtApplicaion>(modelPtr, count);
    default:
        return Tetris::View::AbstractApplicationPtr(nullptr);
    }
}

bool Initialization(int argc, char* argv[], int& countSfWidgets, int& countQtWidgets)
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
        return false;
    }

    if (!vm["SFMLWidget"].empty())
        countSfWidgets = vm["SFMLWidget"].as<int>();
    if (!vm["QWidget"].empty())
        countQtWidgets = vm["QWidget"].as<int>();

    return true;
}

int main(int argc, char *argv[])
{   
    int countSfWidgets = 1, countQtWidgets = 1;
    if (!Initialization(argc, argv, countSfWidgets, countQtWidgets))
        return 1;

    std::list<Tetris::View::AbstractApplicationPtr> applications;
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();
    if (countSfWidgets > 0)
        applications.push_back(MakeApplication(TypeApplication::SFML, modelPtr, countSfWidgets));
    if (countQtWidgets > 0)
        applications.push_back(MakeApplication(TypeApplication::Qt, modelPtr, countQtWidgets));
    Tetris::Controller::TimeController timer(modelPtr, std::chrono::milliseconds(500));

    while(!applications.empty())
    {
        applications.remove_if([](Tetris::View::AbstractApplicationPtr app){return !app->isExecution();});
        timer.CheckTimer();
    }
}
