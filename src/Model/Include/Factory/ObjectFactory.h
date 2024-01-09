#pragma once

#include "AbstractCreator.h"


namespace Tetris::Model::Blocks
{
	/// @brief Виртуальный конструктор
	/// @tparam Base Базовый класс создаваемых объектов
	/// @tparam IdType ID создаваемого объекта
	template <class Base, class IdType>
	class ObjectFactory
	{
	protected:
		/// @brief Базовый тип абстрактной фабрики 
		using AbstractFactory = AbstractCreator<Base>;

		/// @brief Тип мапы ID объектов и фабрики данного объекта
		using FactoryMap = std::map<IdType, AbstractFactory*>;

		/// @brief Мапа зарегестрированных объектов
		FactoryMap _factory;

	public:
		/// @brief Конструктор
		ObjectFactory() {}

		/// @brief Виртуальный деструктор
		virtual ~ObjectFactory() {};

		/// @brief Добавить тип объекта в фабрику
		/// @tparam C Тип создаваемого объекта
		/// @param id ID объекта
		template <class C>
		void add(const IdType& id)
		{
			registerClass(id, new Creator<C, Base>());
		}

	protected:
		/// @brief Зарегестрировать фабрику для создания объекта
		/// @param id ID объекта
		/// @param p Фабрика объекта
		void registerClass(const IdType& id, AbstractFactory* p)
		{
			typename FactoryMap::iterator it = _factory.find(id);
			if (it == _factory.end())
				_factory[id] = p;
			else
				delete p;
		}
	};

} // namespace