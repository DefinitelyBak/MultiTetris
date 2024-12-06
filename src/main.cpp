#include "Precompile.h"

#include "ModelGame.h"
#include "SFMLApplication.h"


int main()
{
    std::shared_ptr<Tetris::Model::ModelGame> modelPtr = std::make_shared<Tetris::Model::ModelGame>();

    Tetris::View::SFMLApplication appSfml(modelPtr, 2);
    
    std::thread thread(Tetris::View::SFMLApplication::Run,std::move(appSfml));

    thread.join();
}
