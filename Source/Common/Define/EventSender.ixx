// =================================================================================================
//  @file CommonDefine.ixx
// 
//  @brief 상세 설명을 입력하시오
//  
//  @date 2022/12/25
// =================================================================================================
module;

#include "Common/Define/GlobalMacro.h"
#include <set>

export module KG.Common.Define.EventSender;

import KG.Platform.Core.PlatformCore;


namespace KG
{
	//----------------------------------------------------------------------
	//! @brief 
	//! @tparam  
	//----------------------------------------------------------------------
	export template <typename Ty> requires Concept::IsKGType<Ty>
	class TBaseEventSender : IKGType
	{
		DECLARE_KG_TYPE( TBaseEventSender<Ty> )

	private:
		std::set<Ty*> Listeners;

	public:
		//----------------------------------------------------------------------
		//! @brief 
		//! @param InObject 
		//! @return 
		//----------------------------------------------------------------------
		bool HasEventListener( const Ty& InObject ) const
		{
			return Listeners.contains( &InObject );
		}

		//----------------------------------------------------------------------
		//! @brief 
		//! @param InObject 
		//! @return 
		//----------------------------------------------------------------------
		void AddEventListener( const Ty& InObject )
		{
			if ( HasEventListener( InObject ) ) return;

			Listeners.insert( &InObject );
		}

		//----------------------------------------------------------------------
		//! @brief 
		//! @param InObject 
		//----------------------------------------------------------------------
		void RemoveEventListener( const Ty& InObject )
		{
			if ( !HasEventListener( InObject ) ) return;

			Listeners.erase( &InObject );
		}

		//----------------------------------------------------------------------
		//! @brief 
		//----------------------------------------------------------------------
		void NotifyEvent( void ( Ty::* InFunctionPtr )() )
		{
			for ( Ty* ptr : Listeners )
			{
				if ( !ptr ) continue;

				(ptr->*InFunctionPtr)();
			}
		}

		//----------------------------------------------------------------------
		//! @brief 
		//----------------------------------------------------------------------
		template<typename... Tys >
		void NotifyEvent( void ( Ty::* InFunctionPtr )( Tys... ), Tys... InArgs )
		{
			for ( Ty* ptr : Listeners )
			{
				if ( !ptr ) continue;

				(ptr->*InFunctionPtr)( InArgs... );
			}
		}
	};
}
