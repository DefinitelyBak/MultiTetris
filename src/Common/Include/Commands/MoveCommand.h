#pragma once

#include "Precompile.h"

#include "AbstractCommand.h"
#include "Data/Types.h"


namespace Tetris::Common
{

    class MoveCommand: public AbstractCommand
    {
    public:
        ///
        MoveCommand(Data::Command command);

        /// @brief 
        /// @return 
        Data::Command GetTypeCommand() const;

    private:
        Data::Command _command;
    };

}