// =================================================================================================
//  @file GlobalMacro.h
// 
//  @brief 전역 매크로
//  
//  @date 2022/12/26
// =================================================================================================

#pragma once
#include <type_traits>
#include <string_view>

namespace KG
{
	class IKGType;
	using FClassID = void*;
	using FClassName = std::string_view;

	namespace Concept
	{
		template <typename Ty>
		concept HasClassID = std::is_same_v< decltype( std::declval<Ty>().GetID() ), FClassID >;
	}

	template <typename Ty>
	class TClassID
	{
	private:
		using ThisType = TClassID< Ty >;
		inline static const Ty* _classAddress = nullptr;

	public:
		static FClassID GetID()
		{
			return &_classAddress;
		}

		template< typename Ty2 > requires Concept::HasClassID<Ty>
		bool operator==( Ty2 InOtherID )
		{
			return ThisType::GetID() == Ty2::GetID();
		}
	};

	template <typename Ty>
	class TClassName
	{
	private:
		using ThisType = TClassName< Ty >;
		static FClassName _className;
	public:
		static FClassName GetName()
		{
			return _className;
		}
	};

	class IKGType
	{
	public:
		IKGType() = default;
		virtual ~IKGType() = default;
	};

	class IKGObject : public IKGType
	{
	public:
		IKGObject() = default;
		virtual ~IKGObject() = default;
		virtual FClassID GetClassID() const = 0;
		virtual FClassName GetName() const = 0;
	};

	namespace Concept
	{
		template <typename Ty>
		concept IsKGType = std::is_base_of_v<IKGType, Ty> == true;

		template <typename Ty>
		concept IsKGObject = std::is_base_of_v<IKGObject, Ty> == true;
	}

}

#define DECLARE_KG_TYPE( TYPE ) \
	private:\
		using ThisType = TYPE;\
		static const TClassID< TYPE > _classID;\
	public:\
		static FClassID StaticClassID() { return TClassID<TYPE>::GetID(); };

#define DECLARE_KG_OBJECT( TYPE ) \
	private:\
		using ThisType = TYPE;\
		static const TClassID< TYPE > _classID;\
		static const TClassName< TYPE > _className;\
	public:\
		virtual FClassID GetClassID() const override { return _classID.GetID(); }\
		virtual FClassName GetName() const override { return _className.GetName(); }

#define IMPLEMENT_KG_OBJECT( TYPE ) \
	FClassName KG::TClassName< TYPE >::_className = #TYPE;


namespace KG::Concept
{
	template <typename Ty>
	concept IsArithmetic = std::is_arithmetic_v<Ty> == true;

	template<typename... CheckTy>
	concept IsNotVoid = std::is_void_v<CheckTy...> != true;

	template<typename ... CheckTys>
	concept IsNotVoids = ( IsNotVoid<CheckTys> && ... );

	template<typename... CheckTy>
	concept IsVoid = std::is_void_v<CheckTy...> == true;

	template<typename ... CheckTys>
	concept IsVoids = ( IsVoid<CheckTys> && ... );

	template<typename Ty1, typename Ty2>
	concept IsSame = std::is_same_v<Ty1, Ty2>;

	template<typename Ty>
	concept IsPointer = std::is_pointer_v<Ty>;
}