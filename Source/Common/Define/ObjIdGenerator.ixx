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
	//----------------------------------------------------------------------
	//! @brief 
	//! @tparam  
	//----------------------------------------------------------------------
	export template <typename Ty>
	class TObjIdGenerator : public IKGType
	{
		DECLARE_KG_TYPE( TObjIdGenerator )

	public:
		using FObjIdType = Ty;

	private:
		const FObjIdType RangeStart;
		const FObjIdType RangeEnd;

		FObjIdType Cursor;

	public:
		//----------------------------------------------------------------------
		//! @brief 
		//! @param InRangeStart 
		//! @param InRangeEnd 
		//----------------------------------------------------------------------
		TObjIdGenerator( FObjIdType InRangeStart, FObjIdType InRangeEnd )
			: RangeStart( InRangeStart ), RangeEnd( InRangeEnd )
		{
		}

		//----------------------------------------------------------------------
		//! @brief 
		//----------------------------------------------------------------------
		void Initialize()
		{
			Cursor = RangeStart;
		}

		//----------------------------------------------------------------------
		//! @brief 
		//! @return 
		//----------------------------------------------------------------------
		FObjIdType AllocateId()
		{
			FObjIdType result = Cursor;

			Cursor += 1;

			return result;
		}
	};
}
