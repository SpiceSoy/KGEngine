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
#include <functional>
#include <memory>
#include <set>
#include <unordered_map>

export module KG.Common.Define.MainModule;

import KG.Platform.Core.PlatformCore;


namespace KG
{
    using EModuleFunctionType = uint16;
    enum class EModuleFunction : EModuleFunctionType
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

    export class FBaseModuleFunction
    {
    };

    
    template <EModuleFunction Flag> struct FFlagModuleFunction { typedef nullptr_t Type; };

    template<EModuleFunction Flag>
    using FFlagModuleFunctionTy = typename FFlagModuleFunction<Flag>::Type;

#define ADD_MODULE_FUNCTION_FLAG( Flag, Ty ) template <> struct FFlagModuleFunction<Flag> { typedef Ty Type; };

#define ADD_MODULE_FUNCTION( Ty ) template <> struct FFlagModuleFunction<Ty::FunctionFlag> { typedef Ty Type; };

    //
    export class FBaseModuleInitializeAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Initialize;

    public:
		virtual int64 GetInitializePriority() const { return 0; };

        virtual void Initialize() = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModuleInitializeAble );

    //
    export class FBaseModuleStartAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Start;

    public:
        virtual int64 GetStartPriority() const { return 0; };

        virtual void Start() = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModuleStartAble );

    //
    export class FBaseModuleEndAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::End;

    public:
        virtual int64 GetEndPriority() const { return 0; };

        virtual void End() = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModuleEndAble );

    //
    export class FBaseModuleDestroyAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Destroy;

    public:
        virtual int64 GetDestroyPriority() const { return 0; };

        virtual void Destroy( bool InByShutdown ) = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModuleDestroyAble );

    //
    export class FBaseModulePreUpdateAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::PreUpdate;

    public:
        virtual int64 GetPreUpdatePriority() const { return 0; };

        virtual void PreUpdate( float DeltaTime ) = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModulePreUpdateAble );

    //
    export class FBaseModuleUpdateAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Update;

    public:
        virtual int64 GetUpdatePriority() const { return 0; };

        virtual void Update( float DeltaTime ) = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModuleUpdateAble );

    //
    export class FBaseModulePostUpdateAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::PostUpdate;

    public:
        virtual int64 GetPostUpdatePriority() const { return 0; };

        virtual void PostUpdate( float DeltaTime ) = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModulePostUpdateAble );

	//
    export class FBaseModulePreRenderAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::PreRender;

    public:
        virtual int64 GetPreRenderPriority() const { return 0; };

        virtual void PreRender() = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModulePreRenderAble );

    //
    export class FBaseModuleRenderAble : public FBaseModuleFunction
    {
    public:
        constexpr static EModuleFunction FunctionFlag = EModuleFunction::Render;

    public:
        virtual int64 GetRenderPriority() const { return 0; };

        virtual void Render() = 0;
    };

    ADD_MODULE_FUNCTION( FBaseModuleRenderAble );

    template <typename... Tys>
    consteval FModuleFunctionFlag GetModuleFunctionFlag()
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

        virtual ~FModuleFunctionCombination() = default;
    };


    template < typename SrcTy, typename DstTy >
    DstTy* TryModuleCast( SrcTy* InModulePtr )
    {
		if constexpr ( KG::Concept::IsBaseOf<SrcTy, DstTy> )
        {
            return static_cast<DstTy*>( InModulePtr );
        }
        else
        {
            return nullptr;
        }
    }

    export class FModuleContainer
    {
        using FBaseModuleDeleter = std::function<void()>;

        struct FBaseModuleElement
        {
            FBaseModule* ModulePtr;
            FBaseModuleDeleter Deleter;

            bool operator<(const FBaseModuleElement& other) const
            {
                return ModulePtr < other.ModulePtr;
            }
        };

        template<typename Ty> requires Concept::IsBaseOf<Ty, FBaseModuleFunction>
        struct FModuleElement
        {
            int64 Priority;
            FBaseModule* ModulePtr;
            Ty* TypeModulePtr;

            bool operator<(const FModuleElement& other) const
            {
                return Priority < other.Priority;
            }
        };

        template <typename Ty> requires Concept::IsBaseOf<Ty, FBaseModuleFunction>
        using FModuleFunctionList = std::set<FModuleElement<Ty>>;

        using FBaseModuleSet = std::set<FBaseModuleElement>;

    private:
#define DECLARE_MODULE_FUNCTION_CONTAINER( ENUM ) FModuleFunctionList<FBaseModule ##ENUM ##Able> Module##ENUM;
#define TRY_ADD_MODULE( FLAG, PTR, ENUM ) if constexpr ( FLAG & (EModuleFunctionType)EModuleFunction::##ENUM ) { Module##ENUM.emplace( FModuleElement<FBaseModule ##ENUM ##Able>{.Priority = PTR->Get##ENUM ##Priority(), .ModulePtr = static_cast<FBaseModule*>( PTR ), .TypeModulePtr = static_cast<FBaseModule ##ENUM ##Able*>( PTR ) } );  }
#define TRY_DELETE_MODULE( PTR, ENUM ) std::erase_if( Module##ENUM, [InModulePtr]( const auto& InModuleElement )->bool {return InModuleElement.TypeModulePtr == TryModuleCast<std::remove_pointer_t<decltype( InModulePtr )>, FBaseModule ##ENUM ##Able>( InModulePtr ); } );
#define TRY_CLEAR_MODULE( ENUM ) Module##ENUM.clear();
#define DECLARE_CALL_MODULE_FUNCTION( ENUM ) template< typename... Args> void ENUM( Args... args ) { for ( const FModuleElement<FBaseModule ##ENUM ##Able>& element : Module##ENUM ) { FBaseModule ##ENUM ##Able* modulePtr = element.TypeModulePtr; if ( !modulePtr ) { continue; } modulePtr->##ENUM ( args... ); }       }

        DECLARE_MODULE_FUNCTION_CONTAINER( Initialize );
        DECLARE_MODULE_FUNCTION_CONTAINER( Start      );
        DECLARE_MODULE_FUNCTION_CONTAINER( PreUpdate  );
        DECLARE_MODULE_FUNCTION_CONTAINER( Update     );
        DECLARE_MODULE_FUNCTION_CONTAINER( PostUpdate );
        DECLARE_MODULE_FUNCTION_CONTAINER( PreRender  );
        DECLARE_MODULE_FUNCTION_CONTAINER( Render     );
        DECLARE_MODULE_FUNCTION_CONTAINER( End        );
        DECLARE_MODULE_FUNCTION_CONTAINER( Destroy    );

        FBaseModuleSet Modules;

    public:
        FModuleContainer()
        {
        }

        ~FModuleContainer()
        {
            Clear();
        }

        template<typename Ty> requires Concept::IsBaseOf<Ty, FBaseModule>
        void AddModule( Ty* InModulePtr )
        {
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, Initialize );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, Start      );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, PreUpdate  );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, Update     );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, PostUpdate );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, PreRender  );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, Render     );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, End        );
            TRY_ADD_MODULE( Ty::ThisFunctionFlag, InModulePtr, Destroy    );

            Modules.insert( 
                FBaseModuleElement
                {
                    .ModulePtr =  static_cast<FBaseModule*>(InModulePtr),
                    .Deleter   =  [InModulePtr]() { delete InModulePtr; }
                }
            );
        }

        template<typename Ty, typename... TyArgs>
        void MakeModule( TyArgs... InArgs )
        {
			AddModule<Ty>( new Ty( InArgs... ) );
        }

        template<typename Ty> requires Concept::IsBaseOf<Ty, FBaseModule>
        void DeleteModule( Ty* InModulePtr )
        {
            if( !InModulePtr ) return;

			FBaseModule* baseModulePtr = static_cast<FBaseModule*>( InModulePtr );

			auto iterator = std::find_if( Modules, [InModulePtr]( const FBaseModuleElement& element ) { return element.ModulePtr == InModulePtr; } );
            if( iterator == Modules.end() ) return;

            TRY_DELETE_MODULE( InModulePtr, Initialize );
            TRY_DELETE_MODULE( InModulePtr, Start      );
            TRY_DELETE_MODULE( InModulePtr, PreUpdate  );
            TRY_DELETE_MODULE( InModulePtr, Update     );
            TRY_DELETE_MODULE( InModulePtr, PostUpdate );
            TRY_DELETE_MODULE( InModulePtr, PreRender  );
            TRY_DELETE_MODULE( InModulePtr, Render     );
            TRY_DELETE_MODULE( InModulePtr, End        );
            TRY_DELETE_MODULE( InModulePtr, Destroy    );

			if ( auto deleter = iterator->Deleter )
			{
				deleter();
			}

            Modules.erase( iterator );
        }

        void Clear()
        {
            for( const FBaseModuleElement& element : Modules )
            {
				if ( auto deleter = element.Deleter )
                {
					deleter();
                }
            }

            Modules.clear();

            TRY_CLEAR_MODULE( Initialize );
            TRY_CLEAR_MODULE( Start      );
            TRY_CLEAR_MODULE( PreUpdate  );
            TRY_CLEAR_MODULE( Update     );
            TRY_CLEAR_MODULE( PostUpdate );
            TRY_CLEAR_MODULE( PreRender  );
            TRY_CLEAR_MODULE( Render     );
            TRY_CLEAR_MODULE( End        );
            TRY_CLEAR_MODULE( Destroy    );
        }

        DECLARE_CALL_MODULE_FUNCTION( Initialize );
        DECLARE_CALL_MODULE_FUNCTION( Start      );
        DECLARE_CALL_MODULE_FUNCTION( PreUpdate  );
        DECLARE_CALL_MODULE_FUNCTION( Update     );
        DECLARE_CALL_MODULE_FUNCTION( PostUpdate );
        DECLARE_CALL_MODULE_FUNCTION( PreRender  );
        DECLARE_CALL_MODULE_FUNCTION( Render     );
        DECLARE_CALL_MODULE_FUNCTION( End        );
        DECLARE_CALL_MODULE_FUNCTION( Destroy    );

    };
}
