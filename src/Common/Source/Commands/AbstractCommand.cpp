#include "Commands/AbstractCommand.h"


namespace Tetris::Common
{

    AbstractCommand::AbstractCommand(CommonType type): _type(type)
    {}

    CommonType AbstractCommand::GetType() const
    {
        return _type;
    }

}