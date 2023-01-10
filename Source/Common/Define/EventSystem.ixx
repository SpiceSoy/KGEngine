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

export module KG.Common.Define.EventSystem;

import KG.Common.Define.DelegateSystem;
import KG.Platform.Core.PlatformCore;


namespace KG
{
	using FEventHandle = uint64;

	//----------------------------------------------------------------------
	//! @brief 
	//! @tparam  
	//----------------------------------------------------------------------
	export template <typename Ty1 = void, typename Ty2 = void, typename Ty3 = void, typename Ty4 = void>
	class TBaseEvent : public IKGType
	{
		DECLARE_KG_TYPE( TBaseEvent )

	private:
		using FThisDelegate = TBaseDelegate<void, Ty1, Ty2, Ty3, Ty4>;
		using FThisDelegateList = std::list<FThisDelegate>;
		using FHandleDelegateMap = std::map<FEventHandle, FThisDelegate>;
		using FPtrDelegateMap = std::map<void*, FThisDelegate>;
		using FFunctionType = typename FThisDelegate::FFunctionType;

	private:
		FHandleDelegateMap HandleDelegateMap;
		FPtrDelegateMap PtrDelegateMap;

		FEventHandle LastHandle = 0;

	public:
		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		void AddEvent( Ty&& InFunctor )
		{
			while ( !AddEventByID( _GetNewId() ) );
		}

		template <typename Ty>  requires Concept::IsSame<Ty, FFunctionType>
		bool AddEventByID( FEventHandle InHandle, Ty&& InFunctor )
		{
			if( !HasHandle(InHandle) )
			{
				HandleDelegateMap[InHandle] = std::forward<Ty>( InFunctor );

				return true;
			}

			return false;
		}

		template <typename ListenerTyPtr, typename Ty>  requires Concept::IsSame<Ty, FFunctionType> && Concept::IsPointer<ListenerTyPtr>
		void AddEventByClass( ListenerTyPtr Ptr, Ty&& InFunctor )
		{
			PtrDelegateMap[Ptr].emplace_back( InFunctor );
		}

		bool HasHandle( FEventHandle InHandle ) const
		{
			return HandleDelegateMap.contains( InHandle ) != 0;
		}

		template <typename ListenerTyPtr>  requires Concept::IsPointer<ListenerTyPtr>
		bool HasClass( ListenerTyPtr InPtr ) const
		{
			return PtrDelegateMap.contains( InPtr );
		}

		void RemoveHandle( FEventHandle InHandle )
		{
			if ( HasHandle( InHandle ) )
			{
				HandleDelegateMap.erase( InHandle );
			}
		}

		template <typename ListenerTyPtr>  requires Concept::IsPointer<ListenerTyPtr>
		void RemoveClass( ListenerTyPtr InPtr )
		{
			if ( HasClass( InPtr ) )
			{
				PtrDelegateMap.erase( InPtr );
			}
		}

	private:
		FEventHandle _GetNewId()
		{
			do
			{
				LastHandle += 1;
				
			} while ( HasHandle( LastHandle ) );

			return LastHandle;
		}
	};
}
