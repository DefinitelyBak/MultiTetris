#pragma once


namespace Tetris::Common
{
    /// @brief 
    enum class CommonType:  int
    {
        None,
        UpdateMap,
        MoveBlock
    };

    /// @brief 
    class AbstractCommand
    {
    public:
        /// @brief 
        /// @param type 
        AbstractCommand(CommonType type = CommonType::None);

        /// @brief 
        virtual ~AbstractCommand() = default;

        /// @brief 
        /// @return 
        CommonType GetType() const;

    private:
        /// @brief 
        CommonType _type;
    };

}