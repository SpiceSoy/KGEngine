// =================================================================================================
//  @file RenderCore.ixx
// 
//  @brief 그래픽 렌더러 코어
//  
//  @date 2022/12/13
// =================================================================================================
module;

#include "Common/Define/GlobalMacro.h"

export module KG.Renderer.Core.RenderCore;

import KG.Renderer.Core.RenderEventListener;
import KG.Platform.Core.PlatformCore;
import KG.Common.Define.MainModule;
import KG.Common.Define.EventSender;


namespace KG
{
	//----------------------------------------------------------------------
	//! @brief 렌더러 코어 인터페이스
	//----------------------------------------------------------------------
	export class RenderCore : public IKGObject, public TBaseEventSender< IRenderEventListener >,
		public FModuleFunctionCombination<
		FBaseModuleRenderAble
	>
	{
		DECLARE_KG_OBJECT( RenderCore )

		//----------------------------------------------------------------------
		//! @brief 초기화한다.
		//! @return 초기화 성공 여부
		//----------------------------------------------------------------------
		bool Initialize( const RenderSetting& InRenderSetting );

		//----------------------------------------------------------------------
		//! @brief 
		//----------------------------------------------------------------------
		void Update();

		//----------------------------------------------------------------------
		//! @brief 
		//----------------------------------------------------------------------
		void PreRender();

		//----------------------------------------------------------------------
		//! @brief 
		//----------------------------------------------------------------------
		virtual void Render() override;

		//----------------------------------------------------------------------
		//! @brief 
		//! @param InRenderSetting 
		//----------------------------------------------------------------------
		void OnChangeSettings( const RenderSetting& InRenderSetting );
	};
}
