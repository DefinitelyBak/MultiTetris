#pragma once

#include "Types.h"

namespace Tetris::Model
{
    class AbstractWidget
    {
    public:
        virtual ~AbstractWidget() = default;

        virtual void Update()
        {
            {
                std::lock_guard<std::mutex> loc(_mutex);
                UpdateWidget();
            }
            ProcessingEvents(); 
        };

        virtual bool IsOpen() const = 0;

        void SlotUpdateView(Model::DescriptionMap descp)
        {
            std::lock_guard<std::mutex> loc(_mutex);
            UpdateView(descp);
        };

        virtual void SlotSetNextBlock(Tetris::Model::DescriptionBlock descpBlock)
        {
            std::lock_guard<std::mutex> loc(_mutex);
            SetNextBlock(descpBlock);
        };

        virtual void SlotSetScore(unsigned int score)
        {
            std::lock_guard<std::mutex> loc(_mutex);
            SetScore(score);
        };

    protected:

        virtual void UpdateWidget() = 0;

        virtual void ProcessingEvents() = 0;

        virtual void UpdateView(Model::DescriptionMap) = 0;

        virtual void SetNextBlock(Model::DescriptionBlock) = 0;

        virtual void SetScore(unsigned int) = 0;

    private:
        std::mutex _mutex;
    };
}