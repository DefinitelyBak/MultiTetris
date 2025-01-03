# MultiTetris Game

## Описание
MultiTetris — это классическая игра Tetris с множеством окон визуализации, в которой игроки управляют падающими блоками, чтобы заполнять горизонтальные линии на игровом поле. Игра разработана в соответствии с требованиями [SRS системы Tetris](https://tetris.wiki/Super_Rotation_System).

Проект реализует Tetris с использованием библиотек SFML и Qt. Он также предоставляет возможность создания собственной графической части, что требует реализации пользовательского приложения на основе класса `IApplication`. Виджеты должны наследоваться от `AbstractWidget` и регистрироваться в модели.

## Установка

### Требования
- Qt 5.x
- Boost
- CMake (для сборки проекта)

### Клонирование репозитория
```bash
git clone https://github.com/DefinitelyBak/MultiTetris.git
cd MultiTetris
```

### Сборка проекта
```bash
mkdir build
cd build
cmake ..
make
```

## Параметры запуска
* `--help` - помощь
* `--QWidget` - количество виджетов на основе Qt (по умолчанию 1)
* `--SFMLWidget` - количество виджетов на основе SFML (по умолчанию 1)
```bash
./MultiTetris.exe --QWidget=3 --SFMLWidget=3
```

## Управление
- Стрелка влево: перемещение блока влево
- Стрелка вправо: перемещение блока вправо
- Стрелка вниз: ускорение падения блока
- Стрелка вверх: поворот блока

## Вклад
Если вы хотите внести свой вклад в проект, пожалуйста, создайте форк репозитория, внесите изменения и создайте pull request.

## Лицензия
Этот проект лицензирован под MIT License — смотрите файл [LICENSE](LICENSE.txt) для подробностей.