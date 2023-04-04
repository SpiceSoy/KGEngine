// =================================================================================================
//  @file FRenderCore.ixx
// 
//  @brief 그래픽 렌더러 코어
//  
//  @date 2022/12/13
// =================================================================================================
module;

#include "Common/Define/GlobalMacro.h"

export module KG.Renderer.Core.RenderEventListener;

import KG.Platform.Core.PlatformCore;


namespace KG
{
	export struct FRenderSetting;

	//----------------------------------------------------------------------
	//! @brief 렌더러 코어 인터페이스
	//----------------------------------------------------------------------
	export class IRenderEventListener : public IKGType
	{
		DECLARE_KG_TYPE( IRenderEventListener )

	public:
		virtual void OnChangeRenderSetting( const FRenderSetting& InRenderSetting ) {}

		virtual void OnStopped() {}
	};
}
