// =================================================================================================
//  @file CommonDefine.ixx
// 
//  @brief 상세 설명을 입력하시오
//  
//  @date 2022/12/25
// =================================================================================================
module;

#include "Common/Define/GlobalMacro.h"

export module KG.Common.Define.Vector;

import KG.Platform.Core.PlatformCore;


namespace KG
{
    //----------------------------------------------------------------------
    //! @brief FVector2D
    //! @tparam Ty 각 원소에서 사용할 타입
    //----------------------------------------------------------------------
    export template < typename Ty >
    struct FVector2D : public IKGType
    {
        DECLARE_KG_TYPE( FVector2D )

        Ty X;
        Ty Y;


        FVector2D()
            : X( 0 ),
              Y( 0 )
        {
        }

        FVector2D( Ty X, Ty Y )
            : X( X ),
              Y( Y )
        {
        }

        FVector2D( const FVector2D& InVector2D )
            : FVector2D( InVector2D.X, InVector2D.Y )
        {
        }

        FVector2D( FVector2D&& InVector2D ) noexcept
            : FVector2D( InVector2D.X, InVector2D.Y )
        {
            InVector2D.SetX( 0 );
            InVector2D.SetY( 0 );
        }


        void SetX( Ty X )
        {
            this->X = X;
        }


        void SetY( Ty Y )
        {
            this->Y = Y;
        }


        ThisType operator+( const ThisType& InOther ) const
        {
            return ThisType( X + InOther.X, Y + InOther.Y );
        }

        ThisType& operator+=( const ThisType& InOther )
        {
            return *this = this->operator+( InOther );
        }

        template < typename Ty2 > requires Concept::IsArithmetic<Ty2>
        ThisType operator*( const Ty2& InValue )
        {
            return ThisType( this->X * InValue, this->Y * InValue );
        }

        template < typename Ty2 > requires Concept::IsArithmetic<Ty2>
        ThisType& operator*=( const Ty2& InValue )
        {
            return *this = this->operator*( InValue );
        }

        template < typename Ty2 > requires Concept::IsArithmetic<Ty2>
        ThisType operator/( const Ty2& InValue )
        {
            return ThisType( this->X / InValue, this->Y / InValue );
        }

        template < typename Ty2 > requires Concept::IsArithmetic<Ty2>
        ThisType& operator/=( const Ty2& InValue )
        {
            return *this = this->operator/( InValue );
        }
    };

    //----------------------------------------------------------------------
    //! @brief 
    //! @tparam Ty 
    //----------------------------------------------------------------------
    export template < typename Ty >
    struct FVector3D
    {
        union
        {
            FVector2D< Ty > Vector2D;

            struct
            {
                Ty X;
                Ty Y;
            };
        };

        Ty Z;
    };

    //
    export using FVector2DI = FVector2D< int32 >;
    //
    export using FVector2DU = FVector2D< uint32 >;
    //
    export using FVector3DI = FVector3D< int32 >;
    //
    export using FVector3DU = FVector3D< uint32 >;
    //
    export using FVector2DS = FVector2D< single >;
    //
    export using FVector3DS = FVector3D< single >;
    //
    export using FVector2DD = FVector2D< double >;
    //
    export using FVector3DD = FVector3D< double >;
}
