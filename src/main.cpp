#include <boost/program_options.hpp>
#include <iostream>

#include <Model/ModelGame.h>
#include <View/SFML/SFMLApplication.h>
#include <View/Qt/QtApplication.h>
#include <Controller/TimeController.h>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{   
    opt::options_description desc("All options");
    desc.add_options()
    ("apples", opt::value<int>(), "how many apples do you have")
    ("oranges", opt::value<int>(), "how many oranges do you have")
    ("help", "produce help message")
    ;
    // Переменная для хранения аргументов нашей командной строки
    opt::variables_map vm;
    // Парсинг и сохранение аргументов
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    // Эта функция должна вызываться после парсинга и сохранения.
    opt::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    std::cout << "Fruits count: "
    << vm["apples"].as<int>() + vm["oranges"].as<int>()
    << std::endl;

    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();

    Tetris::View::SFML::SFMLApplication sfmlApp(modelPtr, 1, "./Resources/arial_bolditalicmt.ttf");
    Tetris::View::Qt::QtApplicaion qtApp(modelPtr, 1);

    Tetris::Controller::TimeController timer(modelPtr, std::chrono::seconds(1));

    while(sfmlApp.isExecution() || qtApp.isExecution())
    {
        timer.CheckTimer();
    }
}
