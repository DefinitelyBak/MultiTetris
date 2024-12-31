#pragma once

#include <thread>
#include <utility>
#include <stdexcept>
#include <atomic>

#include <boost/signals2.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <Qt>
#include <QEvent>
#include <QKeyEvent>
#include <QWindow>
#include <QBackingStore>
#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPainter>
#include <QResizeEvent>
