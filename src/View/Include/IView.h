#pragma once


namespace Tetris::View
{

	class IView
	{
	public:
		virtual ~IView() {};
		void virtual Update() = 0;
	};

}
