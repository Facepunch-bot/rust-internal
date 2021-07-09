#pragma once

#include <horizon/constant/character.hpp>
#include <horizon/constant/hash.hpp>
#include <horizon/constant/secure_string.hpp>
#include <horizon/constant/string.hpp>

#include <horizon/core/map_data.hpp>
#include <horizon/core/mutex.hpp>
#include <horizon/core/no_copy.hpp>
#include <horizon/core/no_move.hpp>
#include <horizon/core/singleton.hpp>
#include <horizon/core/timer.hpp>

#include <horizon/graphics/color.hpp>
#include <horizon/graphics/renderer.hpp>

#include <horizon/hde/hde64.hpp>

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/detour_hook.hpp>
#include <horizon/memory/operation.hpp>
#include <horizon/memory/scan.hpp>
#include <horizon/memory/secure_call.hpp>
#include <horizon/memory/vftable_hook.hpp>

#include <horizon/vcruntime/dll_dllmain.hpp>
#include <horizon/vcruntime/security_cookie.hpp>
#include <horizon/vcruntime/thread_local_storage.hpp>
#include <horizon/vcruntime/thread_safe_statics.hpp>

#include <horizon/win32/sdk/access_mask.hpp>
#include <horizon/win32/sdk/client_id.hpp>
#include <horizon/win32/sdk/constant_page.hpp>
#include <horizon/win32/sdk/constant_region.hpp>
#include <horizon/win32/sdk/constant_section.hpp>
#include <horizon/win32/sdk/event_basic_information.hpp>
#include <horizon/win32/sdk/event_information_class.hpp>
#include <horizon/win32/sdk/event_type.hpp>
#include <horizon/win32/sdk/exception_registration_record.hpp>
#include <horizon/win32/sdk/file_basic_information.hpp>
#include <horizon/win32/sdk/io_apc_routine.hpp>
#include <horizon/win32/sdk/io_status_block.hpp>
#include <horizon/win32/sdk/large_integer.hpp>
#include <horizon/win32/sdk/ldr_data_table_entry.hpp>
#include <horizon/win32/sdk/list_entry.hpp>
#include <horizon/win32/sdk/memory_basic_information.hpp>
#include <horizon/win32/sdk/memory_enclave_image_information.hpp>
#include <horizon/win32/sdk/memory_frame_information.hpp>
#include <horizon/win32/sdk/memory_image_information.hpp>
#include <horizon/win32/sdk/memory_information_class.hpp>
#include <horizon/win32/sdk/memory_region_information.hpp>
#include <horizon/win32/sdk/memory_shared_commit_information.hpp>
#include <horizon/win32/sdk/memory_working_set_block.hpp>
#include <horizon/win32/sdk/memory_working_set_ex_block.hpp>
#include <horizon/win32/sdk/memory_working_set_ex_information.hpp>
#include <horizon/win32/sdk/memory_working_set_ex_location.hpp>
#include <horizon/win32/sdk/memory_working_set_information.hpp>
#include <horizon/win32/sdk/mutant_basic_information.hpp>
#include <horizon/win32/sdk/mutant_information_class.hpp>
#include <horizon/win32/sdk/nt_tib.hpp>
#include <horizon/win32/sdk/object_attributes.hpp>
#include <horizon/win32/sdk/object_basic_information.hpp>
#include <horizon/win32/sdk/object_information_class.hpp>
#include <horizon/win32/sdk/object_name_information.hpp>
#include <horizon/win32/sdk/object_wait_type.hpp>
#include <horizon/win32/sdk/peb.hpp>
#include <horizon/win32/sdk/peb_ldr_data.hpp>
#include <horizon/win32/sdk/rtl_balanced_node.hpp>
#include <horizon/win32/sdk/rtl_condition_variable.hpp>
#include <horizon/win32/sdk/rtl_critical_section.hpp>
#include <horizon/win32/sdk/rtl_critical_section_debug.hpp>
#include <horizon/win32/sdk/rtl_heap_parameters.hpp>
#include <horizon/win32/sdk/section_basic_information.hpp>
#include <horizon/win32/sdk/section_information_class.hpp>
#include <horizon/win32/sdk/section_inherit.hpp>
#include <horizon/win32/sdk/string.hpp>
#include <horizon/win32/sdk/teb.hpp>
#include <horizon/win32/sdk/ularge_integer.hpp>
#include <horizon/win32/sdk/unicode_string.hpp>

#include <horizon/win32/basic.hpp>
#include <horizon/win32/image.hpp>
#include <horizon/win32/input_manager.hpp>
#include <horizon/win32/math.hpp>
#include <horizon/win32/process.hpp>
#include <horizon/win32/string.hpp>
#include <horizon/win32/time.hpp>
#include <horizon/win32/trace.hpp>

using namespace horizon;

using graphics::TextLeft;
using graphics::TextRight;
using graphics::TextCenterH;
using graphics::TextCenterV;
using graphics::TextCenter;

using graphics::Color;

#include "il2cpp/il2cpp-api.hpp"
#include "il2cpp/il2cpp-api-types.hpp"
#include "il2cpp/il2cpp-blob.hpp"
#include "il2cpp/il2cpp-class-internals.hpp"
#include "il2cpp/il2cpp-config.hpp"
#include "il2cpp/il2cpp-config-api.hpp"
#include "il2cpp/il2cpp-metadata.hpp"
#include "il2cpp/il2cpp-object-internals.hpp"
#include "il2cpp/il2cpp-runtime-metadata.hpp"

// 
// [ procedure ] il2cpp declarations
// 
namespace rust
{

DO_API( Il2CppDomain*, il2cpp_domain_get, ( ) );
DO_API( const Il2CppAssembly**, il2cpp_domain_get_assemblies, ( const Il2CppDomain* domain, std::size_t* size ) );

DO_API( void, il2cpp_set_memory_callbacks, ( Il2CppMemoryCallbacks* callbacks ) );
DO_API( const Il2CppImage*, il2cpp_get_corlib, ( ) );
DO_API( void, il2cpp_add_internal_call, ( const char* name, Il2CppMethodPointer method ) );
DO_API( Il2CppMethodPointer, il2cpp_resolve_icall, ( const char* name ) );

DO_API( void*, il2cpp_alloc, ( std::size_t size ) );
DO_API( void, il2cpp_free, ( void* ptr ) );

DO_API( const Il2CppImage*, il2cpp_assembly_get_image, ( const Il2CppAssembly* assembly ) );

DO_API( bool, il2cpp_class_has_parent, ( Il2CppClass* klass, Il2CppClass* klassc ) );
DO_API( Il2CppClass*, il2cpp_class_from_name, ( const Il2CppImage* image, const char* namespaze, const char* name ) );
DO_API( const EventInfo*, il2cpp_class_get_events, ( const Il2CppClass* klass, void** iter ) );
DO_API( FieldInfo*, il2cpp_class_get_fields, ( const Il2CppClass* klass, void** iter ) );
DO_API( FieldInfo*, il2cpp_class_get_field_from_name, ( const Il2CppClass* klass, const char* name ) );
DO_API( const PropertyInfo*, il2cpp_class_get_properties, ( const Il2CppClass* klass, void** iter ) );
DO_API( const PropertyInfo*, il2cpp_class_get_property_from_name, ( const Il2CppClass* klass, const char* name ) );
DO_API( const MethodInfo*, il2cpp_class_get_methods, ( Il2CppClass* klass, void** iter ) );
DO_API( const MethodInfo*, il2cpp_class_get_method_from_name, ( Il2CppClass* klass, const char* name, int argsCount ) );
DO_API( const char*, il2cpp_class_get_name, ( Il2CppClass* klass ) );
DO_API( const char*, il2cpp_class_get_namespace, ( Il2CppClass* klass ) );
DO_API( Il2CppClass*, il2cpp_class_get_parent, ( Il2CppClass* klass ) );

DO_API( const char*, il2cpp_field_get_name, ( const FieldInfo* field ) );
DO_API( std::size_t, il2cpp_field_get_offset, ( const FieldInfo* field ) );

DO_API( const MethodInfo*, il2cpp_property_get_get_method, ( const PropertyInfo* prop ) );
DO_API( const MethodInfo*, il2cpp_property_get_set_method, ( const PropertyInfo* prop ) );
DO_API( const char*, il2cpp_property_get_name, ( const PropertyInfo* prop ) );

DO_API( const Il2CppAssembly*, il2cpp_image_get_assembly, ( const Il2CppImage* image ) );
DO_API( const char*, il2cpp_image_get_name, ( const Il2CppImage* image ) );
DO_API( const char*, il2cpp_image_get_filename, ( const Il2CppImage* image ) );
DO_API( const MethodInfo*, il2cpp_image_get_entry_point, ( const Il2CppImage* image ) );

const Il2CppClass* FindClass( const Il2CppImage* image, const char* name_space, const char* name );
const Il2CppClass* FindClass( const char* name_space, const char* name );
const FieldInfo* FindField( const Il2CppClass* object, std::uint64_t name_hash );
const PropertyInfo* FindProperty( const Il2CppClass* object, std::uint64_t name_hash );

} // namespace rust

// 
// [ macro ] il2cpp definitions
// 
#pragma region region_macro_il2cpp
#define IL2CPP_NAME_SPACE( name )																															\
	static constexpr const char* cx_name_space = name

#define IL2CPP_CLASS( name )																																	\
	static const Il2CppClass* StaticClass()																											\
	{																																														\
		static const Il2CppClass* instance = nullptr;																							\
		if( !memory::IsAddressValid( instance ) )																									\
		{																																													\
			instance = rust::FindClass( cx_name_space, name );																			\
		}																																													\
		return instance;																																					\
	}

#define IL2CPP_FIELD( return_type, name )																											\
	return_type& name()																																					\
	{																																														\
		static std::size_t offset = 0;																														\
		if( !offset )																																							\
		{																																													\
			const auto field = rust::FindField( klass, HASH( #name ) );															\
			if( memory::IsAddressValid( field ) )																										\
			{																																												\
				offset = rust::il2cpp_field_get_offset( field );																			\
			}																																												\
		}																																													\
		return *reinterpret_cast< return_type* >( memory::ToAddress( this ) + offset );						\
	}

#define IL2CPP_STATIC_FIELD( return_type, name )																							\
	static return_type& name()																																	\
	{																																														\
		static auto offset = std::numeric_limits< std::size_t >::max();														\
		if( offset == std::numeric_limits< std::size_t >::max() )																	\
		{																																													\
			const auto field = rust::FindField( StaticClass(), HASH( #name ) );											\
			if( memory::IsAddressValid( field ) )																										\
			{																																												\
				offset = rust::il2cpp_field_get_offset( field );																			\
			}																																												\
		}																																													\
		const auto static_fields = StaticClass()->static_fields;																	\
		return *reinterpret_cast< return_type* >( memory::ToAddress( static_fields ) + offset );	\
	}

#define IL2CPP_PROPERTY( return_type, name )																																		\
	return_type JOIN( get_, name )()																																							\
	{																																																							\
		static std::uintptr_t procedure = 0;																																				\
		if( !memory::IsAddressValid( procedure ) )																																	\
		{																																																						\
			const auto prop = rust::FindProperty( klass, HASH( #name ) );																							\
			if( memory::IsAddressValid( prop ) )																																			\
			{																																																					\
				const auto method = rust::il2cpp_property_get_get_method( prop );																				\
				if( memory::IsAddressValid( method ) )																																	\
				{																																																				\
					procedure = memory::ToAddress( method->methodPointer );																								\
				}																																																				\
			}																																																					\
		}																																																						\
		if constexpr( sizeof( return_type ) > sizeof( std::uintptr_t ) )																						\
		{																																																						\
			return_type data = { };																																										\
			const auto method = reinterpret_cast< return_type*( __fastcall* )( return_type*, void* ) >( procedure );	\
			method( &data, this );																																										\
			return std::move( data );																																									\
		}																																																						\
		else																																																				\
		{																																																						\
			const auto method = reinterpret_cast< return_type( __fastcall* )( void* ) >( procedure );									\
			return method( this );																																										\
		}																																																						\
	}

#define IL2CPP_STATIC_PROPERTY( return_type, name )																															\
	static return_type JOIN( get_, name )()																																				\
	{																																																							\
		static std::uintptr_t procedure = 0;																																				\
		if( !memory::IsAddressValid( procedure ) )																																	\
		{																																																						\
			const auto prop = rust::FindProperty( StaticClass(), HASH( #name ) );																			\
			if( memory::IsAddressValid( prop ) )																																			\
			{																																																					\
				const auto method = rust::il2cpp_property_get_get_method( prop );																				\
				if( memory::IsAddressValid( method ) )																																	\
				{																																																				\
					procedure = memory::ToAddress( method->methodPointer );																								\
				}																																																				\
			}																																																					\
		}																																																						\
		if constexpr( sizeof( return_type ) > sizeof( std::uintptr_t ) )																						\
		{																																																						\
			return_type data = { };																																										\
			const auto method = reinterpret_cast< return_type*( __fastcall* )( return_type* ) >( procedure );					\
			method( &data );																																													\
			return std::move( data );																																									\
		}																																																						\
		else																																																				\
		{																																																						\
			const auto method = reinterpret_cast< return_type( __fastcall* )() >( procedure );												\
			return method();																																													\
		}																																																						\
	}
#pragma endregion

IL2CPP_NAME_SPACE( "" );

// 
// [ struct ] declarations
// 


//
// [ class ] declarations
// 
class D3D11SwapChain;

// 
// [ class ] definitions
// 
class D3D11SwapChain
{
public:
	IDXGISwapChain* GetSwapChain() const;

protected:
	FIELD_PAD( 0x03A0 );										// 0x0000
	IDXGISwapChain* m_SwapChain = nullptr;	// 0x03A0
};
// sizeof( D3D11SwapChain ) = 0x03A8