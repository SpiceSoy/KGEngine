// =================================================================================================
//  @file KGEngine.cpp
// 
//  @brief 엔진 구현 소스파일
//  
//  @date 2022/12/12
// =================================================================================================
import KG.Core.Engine;
import KG.Common.Define.MainModule;
import KG.Renderer.Core.RenderCore;

#include <compare>
#include <fstream>
#include <string_view>
#include <iostream>


//----------------------------------------------------------------------
//! @brief 초기화한다.
//----------------------------------------------------------------------
void KG::KGEngine::Initialize()
{
	LogFileStream.open( "Content/Log/KGEngine.log" );
	std::clog.rdbuf( LogFileStream.rdbuf() );


	FRenderCore* core = new FRenderCore();
}

//---------------------------------------------------------------------
//! @brief 게임 시작 전 로딩을 처리한다.
//! @param LoadScene 씬 로딩 여부
//! @param StartScene 씬 로딩 시 사용할 씬 파일 경로
//! @return 로딩 성공 여부
//----------------------------------------------------------------------
bool KG::KGEngine::PreLoad( bool LoadScene, const std::string_view StartScene )
{
	return false;
}


//----------------------------------------------------------------------
//! @brief 게임 시작을 처리한다.
//----------------------------------------------------------------------
void KG::KGEngine::Start()
{
}

//----------------------------------------------------------------------
//! @brief 게임 종료를 처리한다.
//! @param Shutdown 강제종료 여부
//----------------------------------------------------------------------
void KG::KGEngine::End( bool Shutdown )
{
	LogFileStream.close();
}

//----------------------------------------------------------------------
//! @brief 게임 Tick
//! @param DeltaTime 한 틱당 걸린 시간
//----------------------------------------------------------------------
void KG::KGEngine::Tick( float DeltaTime )
{
}

//----------------------------------------------------------------------
//! @brief 렌더링을 한다.
//! @param DeltaTime 한 틱당 걸린 시간
//----------------------------------------------------------------------
void KG::KGEngine::Render( float DeltaTime )
{
}
