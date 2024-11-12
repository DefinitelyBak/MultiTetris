#include "Commands/MoveCommand.h"


namespace Tetris::Common
{

    MoveCommand::MoveCommand(Data::Command command): AbstractCommand(CommonType::MoveBlock), _command(command)
    {}


    Data::Command MoveCommand::GetTypeCommand() const
    {
        return _command;
    }

}