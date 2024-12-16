#pragma once

#include "AbstractCreator.h"


namespace Tetris::Model::Blocks
{
    /// @brief Шаблонный класс для создания объектов различных типов.
    /// @tparam Base Базовый класс создаваемых объектов.
    /// @tparam IdType Тип идентификатора создаваемого объекта.
    template <class Base, class IdType>
    class ObjectFactory
    {
    protected:
        /// @brief Базовый тип абстрактной фабрики для создания объектов.
        using AbstractFactory = AbstractCreator<Base>;

        /// @brief Тип мапы, связывающей идентификаторы объектов с соответствующими фабриками.
        using FactoryMap = std::map<IdType, AbstractFactory*>;

        /// @brief Мапа зарегистрированных объектов и их фабрик.
        FactoryMap _factory;

    public:
        /// @brief Конструктор
        ObjectFactory() {}

        /// @brief Виртуальный деструктор
        virtual ~ObjectFactory() 
        {
            for (auto& pair : _factory)
            {
                delete pair.second;
            }
        }

        /// @brief Добавить новый тип объекта в фабрику.
        /// @tparam C Тип создаваемого объекта.
        /// @param id Идентификатор объекта.
        template <class C>
        void add(const IdType& id)
        {
            registerClass(id, new Creator<C, Base>());
        }

    protected:
        /// @brief Зарегистрировать фабрику для создания объекта с заданным идентификатором.
        /// @param id Идентификатор объекта.
        /// @param p Указатель на фабрику объекта.
        void registerClass(const IdType& id, AbstractFactory* p)
        {
            typename FactoryMap::iterator it = _factory.find(id);
            if (it == _factory.end())
                _factory[id] = p;
            else
                delete p;
        }
    };
} // namespace Tetris::Model::Blocks