// =================================================================================================
//  @file RenderCore.ixx
// 
//  @brief 그래픽 렌더러 코어
//  
//  @date 2022/12/13
// =================================================================================================
export module KG.Renderer.Core.RenderSetting;

import KG.Common.Define;


namespace KG
{
    //----------------------------------------------------------------------
    //! @brief 렌더러 코어 인터페이스
    //----------------------------------------------------------------------
    export struct RenderSetting
    {
        FVector2DU DeviceResolution;
        FVector2DU WindowResolution;
        FVector2DU RenderResolution;
        bool       UseVSync;
        single     MaxFrameRate;
    };
}
