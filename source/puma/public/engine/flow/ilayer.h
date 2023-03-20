#pragma once

#include <set>
#include <typeindex>

namespace puma
{
	class ILayer
	{
	public:
		virtual ~ILayer() {}

	protected:
		virtual const std::set<std::type_index>& getSystemsTypeIndices() const = 0;
	};

	template<class ...Sys>
	class Layer : public ILayer
	{
	public:
		Layer()
		{
			GetSystemTypeIndices<Sys...>::get( m_sysTypeIndices );
		}
		virtual ~Layer() {}

	protected:

		const std::set<std::type_index>& getSystemsTypeIndices() const final { return m_sysTypeIndices; }

	private:

		template<class... Args>
		struct GetSystemTypeIndices();

		template<>
		struct GetSystemTypeIndices<>()
		{
			static void get( std::set<std::type_index> _sysIndicesOut ) {}
		}

		template<class First, class...Rest>
		struct GetSystemTypeIndices<First, Rest...>()
		{
			static void get( std::set<std::type_index> _sysIndicesOut )
			{
				_sysIndicesOut.insert( std::type_index( typeid(First) ) );
				GetSystemTypeIndices<Rest...>::get( _sysIndicesOut );
			}
		}

		std::set<std::type_index> m_sysTypeIndices;
	};
}