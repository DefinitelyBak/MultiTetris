#pragma once

#include "Types.h"
#include <mutex>


namespace Tetris::Model
{
    class AbstractWidget
    {
    public:
        virtual ~AbstractWidget() = default;

        /// @brief Обновление виджета
        virtual void Update()
        {
            UpdateWidget();
        };
  
        Model::DescriptionModel GetDescriptionModel()
        {
            std::scoped_lock<std::mutex> loc(_mutex);
            return _desc;            
        }

        virtual void SlotUpdateView(Model::DescriptionModel descp)
        {
            std::scoped_lock<std::mutex> loc(_mutex);
            _desc = descp;
        };

        virtual bool IsOpen() const = 0;

        virtual void SlotCLoseEvent() = 0;

    protected:

        virtual void UpdateWidget() = 0;

    private:
        std::mutex _mutex;

        Model::DescriptionModel _desc;
    };
    
} // namespace