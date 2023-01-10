// =================================================================================================
//  @file CommonDefine.ixx
// 
//  @brief 상세 설명을 입력하시오
//  
//  @date 2022/12/25
// =================================================================================================
module;

#include <unordered_map>

#include "Common/Define/GlobalMacro.h"
#include <memory>
#include <set>
#include <unordered_map>

export module KG.Common.Define.MainModule;

import KG.Platform.Core.PlatformCore;


namespace KG
{
    using EModuleFunctionType = uint16;
    export enum class EModuleFunction : EModuleFunctionType
    {
        Initialize = (0x01 << 0),
        Start      = (0x01 << 1),
        PreUpdate  = (0x01 << 2),
        Update     = (0x01 << 3),
        PostUpdate = (0x01 << 4),
        PreRender  = (0x01 << 5),
        Render     = (0x01 << 6),
        End        = (0x01 << 7),
        Destroy    = (0x01 << 8),
        MAX        = (0x01 << 9),
        MIN = Initialize, 
    };

    using FModuleFunctionFlag = uint16;

    export class FBaseModuleFuntion
    {
    };

    //
    export class FBaseModuleInitializeAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Initialize;

    public:
        FBaseModuleInitializeAble() = default;
        virtual ~FBaseModuleInitializeAble() = default;

		virtual int64 GetInitializePriority() const { return 0; };

        virtual void Initialize() = 0;
    };

    //
    export class FBaseModuleStartAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Start;

    public:
        FBaseModuleStartAble() = default;
        virtual ~FBaseModuleStartAble() = default;

        virtual int64 GetStartPriority() const { return 0; };

        virtual void Start() = 0;
    };

    //
    export class FBaseModuleEndAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::End;

    public:
        FBaseModuleEndAble() = default;
        virtual ~FBaseModuleEndAble() = default;

        virtual int64 GetEndPriority() const { return 0; };

        virtual void End() = 0;
    };

    //
    export class FBaseModuleDestroyAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Destroy;

    public:
        FBaseModuleDestroyAble() = default;
        virtual ~FBaseModuleDestroyAble() = default;

        virtual int64 GetDestroyPriority() const { return 0; };

        virtual void Initialize() = 0;
    };

    //
    export class FBaseModulePreUpdateAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::PreUpdate;

    public:
        FBaseModulePreUpdateAble() = default;
        virtual ~FBaseModulePreUpdateAble() = default;

        virtual int64 GetPreUpdatePriority() const { return 0; };

        virtual void PreUpdate( float DeltaTime ) = 0;
    };

    //
    export class FBaseModuleUpdateAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Update;

    public:
        FBaseModuleUpdateAble() = default;
        virtual ~FBaseModuleUpdateAble() = default;

        virtual int64 GetUpdatePriority() const { return 0; };

        virtual void Update( float DeltaTime ) = 0;
    };

    //
    export class FBaseModulePostUpdateAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::PostUpdate;

    public:
        FBaseModulePostUpdateAble() = default;
        virtual ~FBaseModulePostUpdateAble() = default;

        virtual int64 GetPostUpdatePriority() const { return 0; };

        virtual void PostUpdate( float DeltaTime ) = 0;
    };

	//
    export class FBaseModulePreRenderAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::PreRender;

    public:
        FBaseModulePreRenderAble() = default;
        virtual ~FBaseModulePreRenderAble() = default;

        virtual int64 GetPreRenderPriority() const { return 0; };

        virtual void Render() = 0;
    };

    //
    export class FBaseModuleRenderAble : public FBaseModuleFuntion
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Render;

    public:
        FBaseModuleRenderAble() = default;
        virtual ~FBaseModuleRenderAble() = default;

        virtual int64 GetRenderPriority() const { return 0; };

        virtual void Render() = 0;
    };

    template <typename... Tys>
    constexpr FModuleFunctionFlag GetModuleFunctionFlag()
    {
        return (static_cast<FModuleFunctionFlag>(Tys::FunctionFlag) | ... );
    }

    export class FBaseModule
    {
    };

    export template<typename ... Tys>
    class FModuleFunctionCombination : public FBaseModule, public Tys...
    {
    public:
        constexpr static FModuleFunctionFlag ThisFunctionFlag = GetModuleFunctionFlag<Tys...>();
    };

    export class FModuleContainer
    {
        struct FModuleElement
        {
            int64 Priority;
            FBaseModule* Module;

            bool operator<(const FModuleElement& other) const
            {
                return Priority < other.Priority;
            }
        };

        using FModuleFunctionList = std::set<FModuleElement>;

        using FModuleFunctionListMap = std::unordered_map<EModuleFunction, FModuleFunctionList>;

    private:
        FModuleFunctionListMap ModuleFunctionListMap;

    public:
        template<typename Ty> requires Concept::IsBaseOf<Ty, FBaseModule>
        void AddModule( Ty* InModulePtr )
        {
			for ( auto value = EnumToValue( EModuleFunction::MIN ); value != EnumToValue( EModuleFunction::MAX ); value = ( value << 1 ) )
            {
				if ( Ty::ThisFunctionFlag & value )
                {
					ModuleFunctionListMap[ValueToEnum<EModuleFunction>( value )].insert(
                        FModuleElement{
                            .Priority = Ty::ThisFunctionFlag,
                            .Module = InModulePtr
                        }
                    );
                }
            }
        }
		template <typename Ty, void( Ty::* Function )( ), typename... Tys  > requires Concept::IsBaseOf<Ty, FBaseModuleFuntion>
        void Call(Tys... InArgs)
        {
			for ( const FModuleElement& ModuleElement : ModuleFunctionListMap[Ty::FunctionFlag] )
            {
				( reinterpret_cast<Ty*>( ModuleElement.Module )->*Function )( InArgs... );
            }
        }

    };
}
