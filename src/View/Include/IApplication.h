#pragma once


namespace Tetris::View
{
    class IApplication
    {
    public:
        virtual ~IApplication() = default;

        virtual void Run() = 0;

        virtual bool isExecution() const = 0; 
    };

} // namespace