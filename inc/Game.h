#pragma once

#include "View.h"
#include "Model.h"
#include "Controller.h"

/// �������� ���������:
/// � Model ����� ���� ����� View.
/// � ������� View ���� Controller
/// ��� ������������� View ������������ ��������� ConfigModel

/// <summary>
/// ����� ����������� ���� ������
/// </summary>
class Game
{
public:
    Game();
	void run();
private:
    View view;
    Model model;
    Controller controller;
};

