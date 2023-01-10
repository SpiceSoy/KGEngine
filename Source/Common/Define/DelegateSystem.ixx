// =================================================================================================
//  @file CommonDefine.ixx
// 
//  @brief 상세 설명을 입력하시오
//  
//  @date 2022/12/25
// =================================================================================================
module;

#include "Common/Define/GlobalMacro.h"
#include <map>
#include <functional>

export module KG.Common.Define.DelegateSystem;

import KG.Platform.Core.PlatformCore;


namespace KG
{
	//
	template<typename ReturnType, typename Ty1, typename Ty2, typename Ty3, typename Ty4> requires Concept::IsNotVoids<Ty1, Ty2, Ty3, Ty4>
	class _BaseTDelegate
	{
	public:
		using FFunctionType = std::function<ReturnType(Ty1, Ty2, Ty3, Ty4)>;

	protected:
		FFunctionType Functor;

	public:
		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		void Add( Ty&& InFunctor )
		{
			Functor = std::forward<Ty>( InFunctor );
		}

		ReturnType Invoke( const Ty1& InOne, const Ty2& InTwo, const Ty3& InThree, const Ty4& InFour )
		{
			return Functor( InOne, InTwo, InThree, InFour );
		}
	};

	//
	template<typename ReturnType, typename Ty1, typename Ty2, typename Ty3> requires Concept::IsNotVoids<Ty1, Ty2, Ty3>
	class _BaseTDelegate<ReturnType, Ty1, Ty2, Ty3, void>
	{
	public:
		using FFunctionType = std::function<ReturnType(Ty1, Ty2, Ty3)>;

	protected:
		FFunctionType Functor;

	public:
		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		void Add( Ty&& InFunctor )
		{
			Functor = std::forward<Ty>( InFunctor );
		}

		ReturnType Invoke( const Ty1& InOne, const Ty2& InTwo, const Ty3& InThree )
		{
			return Functor( InOne, InTwo, InThree );
		}
	};

	//
	template<typename ReturnType, typename Ty1, typename Ty2> requires Concept::IsNotVoids<Ty1, Ty2>
	class _BaseTDelegate<ReturnType, Ty1, Ty2, void, void>
	{
	public:
		using FFunctionType = std::function<ReturnType(Ty1, Ty2)>;

	protected:
		FFunctionType Functor;

	public:
		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		void Add( Ty&& InFunctor )
		{
			Functor = std::forward<Ty>( InFunctor );
		}

		ReturnType Invoke( const Ty1& InOne, const Ty2& InTwo )
		{
			return Functor( InOne, InTwo );
		}
	};

	//
	template<typename ReturnType, typename Ty1> requires Concept::IsNotVoid<Ty1>
	class _BaseTDelegate<ReturnType, Ty1, void, void, void>
	{
	public:
		using FFunctionType = std::function<ReturnType(Ty1)>;

	protected:
		FFunctionType Functor;

	public:
		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		void Add( Ty&& InFunctor )
		{
			Functor = std::forward<Ty>( InFunctor );
		}

		ReturnType Invoke( const Ty1& InOne )
		{
			return Functor( InOne );
		}
	};

	//
	template<typename ReturnType>
	class _BaseTDelegate<ReturnType, void, void, void, void>
	{
	public:
		using FFunctionType = std::function<ReturnType(void)>;

	protected:
		FFunctionType Functor;

	public:
		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		void Add( Ty&& InFunctor )
		{
			Functor = std::forward<Ty>( InFunctor );
		}

		ReturnType Invoke()
		{
			return Functor();
		}
	};


	//----------------------------------------------------------------------
	//! @brief 
	//! @tparam  
	//----------------------------------------------------------------------
	export template <typename ReturnType = void, typename Ty1 = void, typename Ty2 = void, typename Ty3 = void, typename Ty4 = void>
	class TBaseDelegate : public IKGType, public _BaseTDelegate<ReturnType, Ty1, Ty2, Ty3, Ty4>
	{
		DECLARE_KG_TYPE( TBaseDelegate )
	};
}
