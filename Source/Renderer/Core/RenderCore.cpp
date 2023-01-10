// =================================================================================================
//  @file RenderCore.cpp
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

IMPLEMENT_KG_OBJECT( KG::RenderCore );

//----------------------------------------------------------------------
//! @brief 
//! @param InRenderSetting 
//! @return 
//----------------------------------------------------------------------
bool KG::RenderCore::Initialize( const KG::RenderSetting& InRenderSetting )
{
    return false;
}

void KG::RenderCore::Update()
{
}

void KG::RenderCore::PreRender()
{
}

void KG::RenderCore::Render()
{
}

//----------------------------------------------------------------------
//! @brief 
//! @param InRenderSetting 
//----------------------------------------------------------------------
void KG::RenderCore::OnChangeSettings( const KG::RenderSetting& InRenderSetting )
{
    NotifyEvent<const RenderSetting&>( &IRenderEventListener::OnChangeRenderSetting, InRenderSetting );
}
