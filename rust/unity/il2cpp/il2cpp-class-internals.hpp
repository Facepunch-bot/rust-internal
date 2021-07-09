#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

#include "il2cpp-metadata.hpp"
#include "il2cpp-runtime-metadata.hpp"

#define IL2CPP_CLASS_IS_ARRAY( c )	( ( c )->rank )

struct Il2CppIUnknown;

struct Il2CppGuid;
struct Il2CppImage;
struct Il2CppDomain;
struct Il2CppAssembly;
struct Il2CppAppDomain;
struct Il2CppAppDomainSetup;
struct Il2CppDelegate;
struct Il2CppAppContext;
struct Il2CppClass;
struct Il2CppObject;
struct Il2CppNameToTypeDefinitionIndexHashTable;

struct MethodInfo;
struct FieldInfo;
struct MemberInfo;

struct VirtualInvokeData
{
	Il2CppMethodPointer methodPtr = nullptr;	// 0x0000
	const MethodInfo* method = nullptr;				// 0x0008
};
// sizeof( VirtualInvokeData ) = 0x0010

enum class Il2CppTypeNameFormat
{
	IL2CPP_TYPE_NAME_FORMAT_IL,
	IL2CPP_TYPE_NAME_FORMAT_REFLECTION,
	IL2CPP_TYPE_NAME_FORMAT_FULL_NAME,
	IL2CPP_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED,
};
// sizeof( Il2CppTypeNameFormat ) = 0x0004

struct CustomAttributesCache
{
	std::int32_t count = 0;								// 0x0000
	FIELD_PAD( 0x0004 );									// 0x0004
	Il2CppObject** attributes = nullptr;	// 0x0008
};
// sizeof( CustomAttributesCache ) = 0x0010

using CustomAttributesCacheGenerator = void( * )( CustomAttributesCache* );
// sizeof( CustomAttributesCacheGenerator ) = 0x0008

constexpr std::int32_t THREAD_STATIC_FIELD_OFFSET = -1;

struct FieldInfo
{
	const char* name = nullptr;				// 0x0000
	const Il2CppType* type = nullptr;	// 0x0008
	Il2CppClass* parent = nullptr;		// 0x0010
	std::int32_t offset = -1;					// 0x0018
	std::uint32_t token = 0;					// 0x001C
};
// sizeof( FieldInfo ) = 0x0020

struct PropertyInfo
{
	Il2CppClass* parent = nullptr;		// 0x0000
	const char* name = nullptr;				// 0x0008
	const MethodInfo* get = nullptr;	// 0x0010
	const MethodInfo* set = nullptr;	// 0x0018
	std::uint32_t attrs = 0;					// 0x0020
	std::uint32_t token = 0;					// 0x0024
};
// sizeof( PropertyInfo ) = 0x0028

struct EventInfo
{
	const char* name = nullptr;							// 0x0000
	const Il2CppType* eventType = nullptr;	// 0x0008
	Il2CppClass* parent = nullptr;					// 0x0010
	const MethodInfo* add = nullptr;				// 0x0018
	const MethodInfo* remove = nullptr;			// 0x0020
	const MethodInfo* raise = nullptr;			// 0x0028
	std::uint32_t token = 0;								// 0x0030
	FIELD_PAD( 0x0004 );										// 0x0034
};
// sizeof( EventInfo ) = 0x0038

struct ParameterInfo
{
	const char* name = nullptr;									// 0x0000
	std::int32_t position = 0;									// 0x0008
	std::uint32_t token = 0;										// 0x000C
	const Il2CppType* parameter_type = nullptr;	// 0x0010
};
// sizeof( ParameterInfo ) = 0x0018

using InvokerMethod = void*( * )( Il2CppMethodPointer, const MethodInfo*, void*, void** );
// sizeof( InvokerMethod ) = 0x0008

enum class MethodVariableKind
{
	kMethodVariableKind_This,
	kMethodVariableKind_Parameter,
	kMethodVariableKind_LocalVariable,
};
// sizeof( MethodVariableKind ) = 0x0004

enum class SequencePointKind
{
	kSequencePointKind_Normal,
	kSequencePointKind_StepOut,
};
// sizeof( SequencePointKind ) = 0x0004

struct Il2CppMethodExecutionContextInfo
{
	std::int32_t typeIndex = -1;	// 0x0000
	std::int32_t nameIndex = -1;	// 0x0004
	std::int32_t scopeIndex = -1;	// 0x0008
};
// sizeof( Il2CppMethodExecutionContextInfo ) = 0x000C

struct Il2CppMethodExecutionContextInfoIndex
{
	std::int8_t tableIndex = 0;		// 0x0000
	FIELD_PAD( 0x0003 );					// 0x0001
	std::int32_t startIndex = 0;	// 0x0004
	std::int32_t count = 0;				// 0x0008
};
// sizeof( Il2CppMethodExecutionContextInfoIndex ) = 0x000C

struct Il2CppMethodScope
{
	std::int32_t startOffset = 0;	// 0x0000
	std::int32_t endOffset = 0;		// 0x0004
};
// sizeof( Il2CppMethodScope ) = 0x0008

union Il2CppRGCTXData
{
	void* rgctxDataDummy = nullptr;	// 0x0000
	const MethodInfo* method;				// 0x0000
	const Il2CppType* type;					// 0x0000
	Il2CppClass* klass;							// 0x0000
};
// sizeof( Il2CppRGCTXData ) = 0x0008

struct MethodInfo
{
	Il2CppMethodPointer methodPointer = nullptr;					// 0x0000
	InvokerMethod invoker_method = nullptr;								// 0x0008
	const char* name = nullptr;														// 0x0010
	Il2CppClass* klass = nullptr;													// 0x0018
	const Il2CppType* return_type = nullptr;							// 0x0020
	const ParameterInfo* parameters = nullptr;						// 0x0028
	union
	{
		const Il2CppRGCTXData* rgctx_data = nullptr;				// 0x0030
		const Il2CppMethodDefinition* methodDefinition;			// 0x0030
	};
	union
	{
		const Il2CppGenericMethod* genericMethod = nullptr;	// 0x0038
		const Il2CppGenericContainer* genericContainer;			// 0x0038
	};
	std::uint32_t token = 0;															// 0x0040
	std::uint16_t flags = 0;															// 0x0044
	std::uint16_t iflags = 0;															// 0x0046
	std::uint16_t slot = 0;																// 0x0048
	std::uint8_t parameters_count = 0;										// 0x004A
	std::uint8_t is_generic : 1;													// 0x004B
	std::uint8_t is_inflated : 1;													// 0x004B
	std::uint8_t wrapper_type : 1;												// 0x004B
	std::uint8_t is_marshaled_from_native : 1;						// 0x004B
	FIELD_PAD( 0x0004 );																	// 0x004C
};
// sizeof( MethodInfo ) = 0x0050

struct Il2CppRuntimeInterfaceOffsetPair
{
	Il2CppClass* interfaceType = nullptr;	// 0x0000
	std::int32_t offset = -1;							// 0x0008
	FIELD_PAD( 0x0004 );									// 0x000C
};
// sizeof( Il2CppRuntimeInterfaceOffsetPair ) = 0x0010

using PInvokeMarshalToNativeFunc = void( * )( void* managedStructure, void* marshaledStructure );
// sizeof( PInvokeMarshalToNativeFunc ) = 0x0008

using PInvokeMarshalFromNativeFunc = void( * )( void* marshaledStructure, void* managedStructure );
// sizeof( PInvokeMarshalFromNativeFunc ) = 0x0008

using PInvokeMarshalCleanupFunc = void( * )( void* marshaledStructure );
// sizeof( PInvokeMarshalCleanupFunc ) = 0x0008

using CreateCCWFunc = Il2CppIUnknown*( * )( Il2CppObject* obj );
// sizeof( CreateCCWFunc ) = 0x0008

struct Il2CppInteropData
{
	Il2CppMethodPointer delegatePInvokeWrapperFunction = nullptr;							// 0x0000
	PInvokeMarshalToNativeFunc pinvokeMarshalToNativeFunction = nullptr;			// 0x0008
	PInvokeMarshalFromNativeFunc  pinvokeMarshalFromNativeFunction = nullptr;	// 0x0010
	PInvokeMarshalCleanupFunc pinvokeMarshalCleanupFunction = nullptr;				// 0x0018
	CreateCCWFunc createCCWFunction = nullptr;																// 0x0020
	const Il2CppGuid* guid = nullptr;																					// 0x0028
	const Il2CppType* type = nullptr;																					// 0x0030
};
// sizeof( Il2CppInteropData ) = 0x0038

struct Il2CppClass
{
	const Il2CppImage* image = nullptr;														// 0x0000
	void* gc_desc = nullptr;																			// 0x0008
	const char* name = nullptr;																		// 0x0010
	const char* namespaze = nullptr;															// 0x0018
	Il2CppType byval_arg = { };																		// 0x0020
	Il2CppType this_arg = { };																		// 0x0030
	Il2CppClass* element_class = nullptr;													// 0x0040
	Il2CppClass* castClass = nullptr;															// 0x0048
	Il2CppClass* declaringType = nullptr;													// 0x0050
	Il2CppClass* parent = nullptr;																// 0x0058
	Il2CppGenericClass* generic_class = nullptr;									// 0x0060
	const Il2CppTypeDefinition* typeDefinition = nullptr;					// 0x0068
	const Il2CppInteropData* interopData = nullptr;								// 0x0070
	Il2CppClass* klass = nullptr;																	// 0x0078
	FieldInfo* fields = nullptr;																	// 0x0080
	const EventInfo* events = nullptr;														// 0x0088
	const PropertyInfo* properties = nullptr;											// 0x0090
	const MethodInfo** methods = nullptr;													// 0x0098
	Il2CppClass** nestedTypes = nullptr;													// 0x00A0
	Il2CppClass** implementedInterfaces = nullptr;								// 0x00A8
	Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets = nullptr;	// 0x00B0
	void* static_fields = nullptr;																// 0x00B8
	const Il2CppRGCTXData* rgctx_data = nullptr;									// 0x00C0
	Il2CppClass** typeHierarchy = nullptr;												// 0x00C8
	std::uint32_t initializationExceptionGCHandle = 0;						// 0x00D0
	std::uint32_t cctor_started = 0;															// 0x00D4
	std::uint32_t cctor_finished = 0;															// 0x00D8
	FIELD_PAD( 0x0004 );																					// 0x00DC
	ALIGN_TYPE( 8 ) std::uint64_t cctor_thread = 0;								// 0x00E0
	std::int32_t genericContainerIndex = -1;											// 0x00E8
	std::uint32_t instance_size = 0;															// 0x00EC
	std::uint32_t actualSize = 0;																	// 0x00F0
	std::uint32_t element_size = 0;																// 0x00F4
	std::int32_t native_size = 0;																	// 0x00F8
	std::uint32_t static_fields_size = 0;													// 0x00FC
	std::uint32_t thread_static_fields_size = 0;									// 0x0100
	std::int32_t thread_static_fields_offset = -1;								// 0x0104
	std::uint32_t flags = 0;																			// 0x0108
	std::uint32_t token = 0;																			// 0x010C
	std::uint16_t method_count = 0;																// 0x0110
	std::uint16_t property_count = 0;															// 0x0112
	std::uint16_t field_count = 0;																// 0x0114
	std::uint16_t event_count = 0;																// 0x0116
	std::uint16_t nested_type_count = 0;													// 0x0118
	std::uint16_t vtable_count = 0;																// 0x011A
	std::uint16_t interfaces_count = 0;														// 0x011C
	std::uint16_t interface_offsets_count = 0;										// 0x011E
	std::uint8_t typeHierarchyDepth = 0;													// 0x0120
	std::uint8_t genericRecursionDepth = 0;												// 0x0121
	std::uint8_t rank = 0;																				// 0x0122
	std::uint8_t minimumAlignment = 0;														// 0x0123
	std::uint8_t naturalAligment = 0;															// 0x0124
	std::uint8_t packingSize = 0;																	// 0x0125
	std::uint8_t initialized_and_no_error : 1;										// 0x0126
	std::uint8_t valuetype : 1;																		// 0x0126
	std::uint8_t initialized : 1;																	// 0x0126
	std::uint8_t enumtype : 1;																		// 0x0126
	std::uint8_t is_generic : 1;																	// 0x0126
	std::uint8_t has_references : 1;															// 0x0126
	std::uint8_t init_pending : 1;																// 0x0126
	std::uint8_t size_inited : 1;																	// 0x0126
	std::uint8_t has_finalize : 1;																// 0x0127
	std::uint8_t has_cctor : 1;																		// 0x0127
	std::uint8_t is_blittable : 1;																// 0x0127
	std::uint8_t is_import_or_windows_runtime : 1;								// 0x0127
	std::uint8_t is_vtable_initialized : 1;												// 0x0127
	std::uint8_t has_initialization_error : 1;										// 0x0127
	VirtualInvokeData vtable[ IL2CPP_ZERO_LEN_ARRAY ];						// 0x0128
};
// sizeof( Il2CppClass ) = 0x0128

struct Il2CppTypeDefinitionSizes
{
	std::uint32_t instance_size = 0;							// 0x0000
	std::int32_t native_size = 0;									// 0x0004
	std::uint32_t static_fields_size = 0;					// 0x0008
	std::uint32_t thread_static_fields_size = 0;	// 0x000C
};
// sizeof( Il2CppTypeDefinitionSizes ) = 0x0010

struct Il2CppDomain
{
	Il2CppAppDomain* domain = nullptr;						// 0x0000
	Il2CppAppDomainSetup* setup = nullptr;				// 0x0008
	Il2CppAppContext* default_context = nullptr;	// 0x0010
	const char* friendly_name = nullptr;					// 0x0018
	std::uint32_t domain_id = 0;									// 0x0020
	FIELD_PAD( 0x0004 );													// 0x0024
	void* agent_info = nullptr;										// 0x0028
};
// sizeof( Il2CppDomain ) = 0x0030

struct Il2CppAssemblyName
{
	const char* name = nullptr;																		// 0x0000
	const char* culture = nullptr;																// 0x0008
	const char* hash_value = nullptr;															// 0x0010
	const char* public_key = nullptr;															// 0x0018
	std::uint32_t hash_alg = 0;																		// 0x0020
	std::int32_t hash_len = 0;																		// 0x0024
	std::uint32_t flags = 0;																			// 0x0028
	std::int32_t major = 0;																				// 0x002C
	std::int32_t minor = 0;																				// 0x0030
	std::int32_t build = 0;																				// 0x0034
	std::int32_t revision = 0;																		// 0x0038
	FIELD_PAD( 0x0004 );																					// 0x003C
	std::uint8_t public_key_token[ kPublicKeyByteLength ] = { };	// 0x0040
};
// sizeof( Il2CppAssemblyName ) = 0x0048

struct Il2CppImage
{
	const char* name = nullptr;																								// 0x0000
	const char* nameNoExt = nullptr;																					// 0x0008
	Il2CppAssembly* assembly = nullptr;																				// 0x0010
	std::int32_t typeStart = -1;																							// 0x0018
	std::uint32_t typeCount = 0;																							// 0x001C
	std::int32_t exportedTypeStart = -1;																			// 0x0020
	std::uint32_t exportedTypeCount = 0;																			// 0x0024
	std::int32_t CustomAttributeStart = -1;																		// 0x0028
	std::uint32_t CustomAttributeCount = 0;																		// 0x002C
	std::int32_t entryPointIndex = -1;																				// 0x0030
	FIELD_PAD( 0x0004 );																											// 0x0034
	Il2CppNameToTypeDefinitionIndexHashTable* nameToClassHashTable = nullptr;	// 0x0038
	std::uint32_t token = 0;																									// 0x0040
	std::uint8_t dynamic = 0;																									// 0x0044
	FIELD_PAD( 0x0003 );																											// 0x0045
};
// sizeof( Il2CppImage ) = 0x0048

struct Il2CppAssembly
{
	Il2CppImage* image = nullptr;								// 0x0000
	std::uint32_t token = 0;										// 0x0008
	std::int32_t referencedAssemblyStart = -1;	// 0x000C
	std::int32_t referencedAssemblyCount = 0;		// 0x0010
	FIELD_PAD( 0x0004 );												// 0x0014
	Il2CppAssemblyName aname = { };							// 0x0018
};
// sizeof( Il2CppAssembly ) = 0x0060

struct Il2CppCodeGenOptions
{
	bool enablePrimitiveValueTypeGenericSharing = false;	// 0x0000
};
// sizeof( Il2CppCodeGenOptions ) = 0x0001