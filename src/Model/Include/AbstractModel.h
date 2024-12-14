#pragma once

#include "Forwards.h"
#include "Types.h"

#include "AbstractWidget.h"


namespace Tetris::Model
{
    class AbstractModel
    {
    public:

        virtual ~AbstractModel()
        {
            SignalCloseViews();
        }

        using TypeSignalUpdateView = boost::signals2::signal<void(Model::DescriptionModel)>;

        using TypeSignalCloseViews = boost::signals2::signal<void()>; 

        void SlotUpdate(Command command)
        {
            DescriptionModel desc;
            {
                std::lock_guard<std::mutex> l(_mutex);
                UpdateModel(command, desc);
                EmitSugnals(desc);
            }
        }

        void SetView(AbstractWidgetPtr view)
        {
            DescriptionModel desc;
            {
                std::lock_guard<std::mutex> l(_mutex);
                SetSignals(view, desc);
                EmitSugnals(desc);
            }
        }

    protected:

        TypeSignalUpdateView SignalUpdateView;

        TypeSignalCloseViews SignalCloseViews;

        virtual void UpdateModel(Command command, DescriptionModel& desc) = 0;

        virtual void EmitSugnals(DescriptionModel& desc) = 0;

        virtual void SetSignals(AbstractWidgetPtr& view, DescriptionModel& desc) = 0;

    private:
        std::mutex _mutex;
    };

} // namespace