#pragma once

#include "Forwards.h"
#include "Types.h"

#include "AbstractWidget.h"


namespace Tetris::Model
{
    class AbstractModel
    {
    public:

        using TypeSignalUpdateView = boost::signals2::signal<void(Model::DescriptionModel)>;

        using TypeSignalCloseViews = boost::signals2::signal<void()>; 

        AbstractModel(): _stack(128)
        {
            _worker = std::thread(&AbstractModel::run, this);
        }

        virtual ~AbstractModel()
        {
            _done = true;
            _worker.join();
            SignalCloseViews();
        }

        void SlotUpdate(Command command)
        {
            while(!_stack.push(command))
                ;
        }

        void SetView(AbstractWidgetPtr view)
        {
            SignalUpdateView.connect(TypeSignalUpdateView::slot_type(&AbstractWidget::SlotUpdateView, view.get(), boost::placeholders::_1).track_foreign(view));
            SignalCloseViews.connect(TypeSignalCloseViews::slot_type(boost::bind(&AbstractWidget::SlotCLoseEvent, view.get())).track_foreign(view));
        }

    protected:

        TypeSignalUpdateView SignalUpdateView;

        TypeSignalCloseViews SignalCloseViews;

        virtual void UpdateModel(Command command, DescriptionModel& desc) = 0;

    private:

        void run()
        {
            Command cmd;
            while(!_done)
            {
                if(_stack.pop(cmd))
                {
                    DescriptionModel desc;
                    UpdateModel(cmd, desc);
                    SignalUpdateView(desc);
                }
            }
        }

        std::thread _worker;

        std::atomic<bool> _done{false};

        boost::lockfree::stack<Command> _stack;
    };

} // namespace