// =================================================================================================
//  @file FRenderCore.cpp
// 
//  @brief 렌더 코드 CPP
//  
//  @date 2022/12/25
// =================================================================================================
import KG.Renderer.Core.RenderCore;

#include "Common/Define/GlobalMacro.h"

import KG.Common.Define.EventSender;
import KG.Renderer.Core.RenderEventListener;
import KG.Renderer.Core.RenderSetting;

IMPLEMENT_KG_OBJECT( KG::FRenderCore );

//----------------------------------------------------------------------
//! @brief 
//! @param InRenderSetting 
//! @return 
//----------------------------------------------------------------------
bool KG::FRenderCore::Initialize( const KG::FRenderSetting& InRenderSetting )
{
    return false;
}

//----------------------------------------------------------------------
//! @brief 
//----------------------------------------------------------------------
void KG::FRenderCore::SubmitRenderScene()
{
}

//----------------------------------------------------------------------
//! @brief
//----------------------------------------------------------------------
void KG::FRenderCore::StartRender()
{
}

//----------------------------------------------------------------------
//! @brief 
//----------------------------------------------------------------------
void KG::FRenderCore::WaitForRenderEnd()
{
}

//----------------------------------------------------------------------
//! @brief 
//! @param InRenderSetting 
//----------------------------------------------------------------------
void KG::FRenderCore::OnChangeSettings( const KG::FRenderSetting& InRenderSetting )
{
    NotifyEvent<const FRenderSetting&>( &IRenderEventListener::OnChangeRenderSetting, InRenderSetting );
}
