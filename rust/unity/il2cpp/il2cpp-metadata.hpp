#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

#include "il2cpp-config.hpp"

enum class Il2CppMetadataUsage
{
	kIl2CppMetadataUsageInvalid,
	kIl2CppMetadataUsageTypeInfo,
	kIl2CppMetadataUsageIl2CppType,
	kIl2CppMetadataUsageMethodDef,
	kIl2CppMetadataUsageFieldInfo,
	kIl2CppMetadataUsageStringLiteral,
	kIl2CppMetadataUsageMethodRef,
};
// sizeof( Il2CppMetadataUsage ) = 0x0004

static inline Il2CppMetadataUsage GetEncodedIndexType( std::uint32_t index )
{
	return static_cast< Il2CppMetadataUsage >( ( index & 0xE0000000 ) >> 29 );
}

static inline std::uint32_t GetDecodedMethodIndex( std::uint32_t index )
{
	return ( index & 0x1FFFFFFF );
}

struct Il2CppImage;
struct Il2CppType;
struct Il2CppTypeDefinitionMetadata;

union Il2CppRGCTXDefinitionData
{
	std::int32_t rgctxDataDummy = -1;	// 0x0000
	std::int32_t methodIndex;					// 0x0000
	std::int32_t typeIndex;						// 0x0000
};
// sizeof( Il2CppRGCTXDefinitionData ) = 0x0004

enum class Il2CppRGCTXDataType
{
	IL2CPP_RGCTX_DATA_INVALID,
	IL2CPP_RGCTX_DATA_TYPE,
	IL2CPP_RGCTX_DATA_CLASS,
	IL2CPP_RGCTX_DATA_METHOD,
	IL2CPP_RGCTX_DATA_ARRAY,
};
// sizeof( Il2CppRGCTXDataType ) = 0x0004

struct Il2CppRGCTXDefinition
{
	Il2CppRGCTXDataType type = Il2CppRGCTXDataType::IL2CPP_RGCTX_DATA_INVALID;	// 0x0000
	Il2CppRGCTXDefinitionData data = { };																				// 0x0004
};
// sizeof( Il2CppRGCTXDefinition ) = 0x0008

struct Il2CppInterfaceOffsetPair
{
	std::int32_t interfaceTypeIndex = -1;	// 0x0000
	std::int32_t offset = 0;							// 0x0004
};
// sizeof( Il2CppInterfaceOffsetPair ) = 0x0008

struct Il2CppTypeDefinition
{
	std::int32_t nameIndex = -1;								// 0x0000
	std::int32_t namespaceIndex = -1;						// 0x0004
	std::int32_t byvalTypeIndex = -1;						// 0x0008
	std::int32_t byrefTypeIndex = -1;						// 0x000C
	std::int32_t declaringTypeIndex = -1;				// 0x0010
	std::int32_t parentIndex = -1;							// 0x0014
	std::int32_t elementTypeIndex = -1;					// 0x0018
	std::int32_t rgctxStartIndex = -1;					// 0x001C
	std::int32_t rgctxCount = 0;								// 0x0020
	std::int32_t genericContainerIndex = -1;		// 0x0024
	std::uint32_t flags = 0;										// 0x0028
	std::int32_t fieldStart = -1;								// 0x002C
	std::int32_t methodStart = -1;							// 0x0030
	std::int32_t eventStart = -1;								// 0x0034
	std::int32_t propertyStart = -1;						// 0x0038
	std::int32_t nestedTypesStart = -1;					// 0x003C
	std::int32_t interfacesStart = -1;					// 0x0040
	std::int32_t vtableStart = -1;							// 0x0044
	std::int32_t interfaceOffsetsStart = -1;		// 0x0048
	std::uint16_t method_count = 0;							// 0x004C
	std::uint16_t property_count = 0;						// 0x004E
	std::uint16_t field_count = 0;							// 0x0050
	std::uint16_t event_count = 0;							// 0x0052
	std::uint16_t nested_type_count = 0;				// 0x0054
	std::uint16_t vtable_count = 0;							// 0x0056
	std::uint16_t interfaces_count = 0;					// 0x0058
	std::uint16_t interface_offsets_count = 0;	// 0x005A
	std::uint32_t bitfield = 0;									// 0x005C
	std::uint32_t token = 0;										// 0x0060
};
// sizeof( Il2CppTypeDefinition ) = 0x0064

struct Il2CppFieldDefinition
{
	std::int32_t nameIndex = -1;	// 0x0000
	std::int32_t typeIndex = -1;	// 0x0004
	std::uint32_t token = 0;			// 0x0008
};
// sizeof( Il2CppFieldDefinition ) = 0x000C

struct Il2CppFieldDefaultValue
{
	std::int32_t fieldIndex = -1;	// 0x0000
	std::int32_t typeIndex = -1;	// 0x0004
	std::int32_t dataIndex = -1;	// 0x0008
};
// sizeof( Il2CppFieldDefaultValue ) = 0x000C

struct Il2CppFieldMarshaledSize
{
	std::int32_t fieldIndex = -1;	// 0x0000
	std::int32_t typeIndex = -1;	// 0x0004
	std::int32_t size = 0;				// 0x0008
};
// sizeof( Il2CppFieldMarshaledSize ) = 0x000C

struct Il2CppFieldRef
{
	std::int32_t typeIndex = -1;	// 0x0000
	std::int32_t fieldIndex = -1;	// 0x0004
};
// sizeof( Il2CppFieldRef ) = 0x0008

struct Il2CppParameterDefinition
{
	std::int32_t nameIndex = -1;	// 0x0000
	std::uint32_t token = 0;			// 0x0004
	std::int32_t typeIndex = -1;	// 0x0008
};
// sizeof( Il2CppParameterDefinition ) = 0x000C

struct Il2CppParameterDefaultValue
{
	std::int32_t parameterIndex = -1;	// 0x0000
	std::int32_t typeIndex = -1;			// 0x0004
	std::int32_t dataIndex = -1;			// 0x0008
};
// sizeof( Il2CppParameterDefaultValue ) = 0x000C

struct Il2CppMethodDefinition
{
	std::int32_t nameIndex = -1;									// 0x0000
	std::int32_t declaringType = -1;							// 0x0004
	std::int32_t returnType = -1;									// 0x0008
	std::int32_t parameterStart = -1;							// 0x000C
	std::int32_t genericContainerIndex = -1;			// 0x0010
	std::int32_t methodIndex = -1;								// 0x0014
	std::int32_t invokerIndex = -1;								// 0x0018
	std::int32_t reversePInvokeWrapperIndex = -1;	// 0x001C
	std::int32_t rgctxStartIndex = -1;						// 0x0020
	std::int32_t rgctxCount = 0;									// 0x0024
	std::uint32_t token = 0;											// 0x0028
	std::uint16_t flags = 0;											// 0x002C
	std::uint16_t iflags = 0;											// 0x002E
	std::uint16_t slot = 0;												// 0x0030
	std::uint16_t parameterCount = 0;							// 0x0032
};
// sizeof( Il2CppMethodDefinition ) = 0x0034

struct Il2CppEventDefinition
{
	std::int32_t nameIndex = -1;	// 0x0000
	std::int32_t typeIndex = -1;	// 0x0004
	std::int32_t add = -1;				// 0x0008
	std::int32_t remove = -1;			// 0x000C
	std::int32_t raise = -1;			// 0x0010
	std::uint32_t token = 0;			// 0x0014
};
// sizeof( Il2CppEventDefinition ) = 0x0018

struct Il2CppPropertyDefinition
{
	std::int32_t nameIndex = -1;	// 0x0000
	std::int32_t get = -1;				// 0x0004
	std::int32_t set = -1;				// 0x0008
	std::uint32_t attrs = 0;			// 0x000C
	std::uint32_t token = 0;			// 0x0010
};
// sizeof( Il2CppPropertyDefinition ) = 0x0014

struct Il2CppMethodSpec
{
	std::int32_t methodDefinitionIndex = -1;	// 0x0000
	std::int32_t classIndexIndex = -1;				// 0x0004
	std::int32_t methodIndexIndex = -1;				// 0x0008
};
// sizeof( Il2CppMethodSpec ) = 0x000C

struct Il2CppStringLiteral
{
	std::uint32_t length = 0;			// 0x0000
	std::int32_t dataIndex = -1;	// 0x0004
};
// sizeof( Il2CppStringLiteral ) = 0x0008

struct Il2CppGenericMethodIndices
{
	std::int32_t methodIndex = -1;	// 0x0000
	std::int32_t invokerIndex = -1;	// 0x0004
};
// sizeof( Il2CppGenericMethodIndices ) = 0x0008

struct Il2CppGenericMethodFunctionsDefinitions
{
	std::int32_t genericMethodIndex = -1;			// 0x0000
	Il2CppGenericMethodIndices indices = { };	// 0x0004
};
// sizeof( Il2CppGenericMethodFunctionsDefinitions ) = 0x000C

constexpr std::int32_t kPublicKeyByteLength = 8;
// sizeof( kPublicKeyByteLength ) = 0x0004

struct Il2CppAssemblyNameDefinition
{
	std::int32_t nameIndex = -1;																	// 0x0000
	std::int32_t cultureIndex = -1;																// 0x0004
	std::int32_t hashValueIndex = -1;															// 0x0008
	std::int32_t publicKeyIndex = -1;															// 0x000C
	std::uint32_t hash_alg = 0;																		// 0x0010
	std::int32_t hash_len = 0;																		// 0x0014
	std::uint32_t flags = 0;																			// 0x0018
	std::int32_t major = 0;																				// 0x001C
	std::int32_t minor = 0;																				// 0x0020
	std::int32_t build = 0;																				// 0x0024
	std::int32_t revision = 0;																		// 0x0028
	std::uint8_t public_key_token[ kPublicKeyByteLength ] = { };	// 0x002C
};
// sizeof( Il2CppAssemblyNameDefinition ) = 0x0034

struct Il2CppImageDefinition
{
	std::int32_t nameIndex = -1;						// 0x0000
	std::int32_t assemblyIndex = -1;				// 0x0004
	std::int32_t typeStart = -1;						// 0x0008
	std::uint32_t typeCount = 0;						// 0x000C
	std::int32_t exportedTypeStart = -1;		// 0x0010
	std::uint32_t exportedTypeCount = 0;		// 0x0014
	std::int32_t entryPointIndex = -1;			// 0x0018
	std::uint32_t token = 0;								// 0x001C
	std::int32_t customAttributeStart = -1;	// 0x0020
	std::uint32_t customAttributeCount = 0;	// 0x0024
};
// sizeof( Il2CppImageDefinition ) = 0x0028

struct Il2CppAssemblyDefinition
{
	std::int32_t imageIndex = -1;								// 0x0000
	std::uint32_t token = 0;										// 0x0004
	std::int32_t referencedAssemblyStart = -1;	// 0x0008
	std::int32_t referencedAssemblyCount = 0;		// 0x000C
	Il2CppAssemblyNameDefinition aname = { };		// 0x0010
};
// sizeof( Il2CppAssemblyDefinition ) = 0x0044

struct Il2CppMetadataUsageList
{
	std::uint32_t start = 0;	// 0x0000
	std::uint32_t count = 0;	// 0x0004
};
// sizeof( Il2CppMetadataUsageList ) = 0x0008

struct Il2CppMetadataUsagePair
{
	std::uint32_t destinationIndex = 0;		// 0x0000
	std::uint32_t encodedSourceIndex = 0;	// 0x0004
};
// sizeof( Il2CppMetadataUsagePair ) = 0x0008

struct Il2CppCustomAttributeTypeRange
{
	std::uint32_t token = 0;	// 0x0000
	std::int32_t start = 0;		// 0x0004
	std::int32_t count = 0;		// 0x0008
};
// sizeof( Il2CppCustomAttributeTypeRange ) = 0x000C

struct Il2CppRange
{
	std::int32_t start = 0;		// 0x0000
	std::int32_t length = 0;	// 0x0004
};
// sizeof( Il2CppRange ) = 0x0008

struct Il2CppWindowsRuntimeTypeNamePair
{
	std::int32_t nameIndex = -1;	// 0x0000
	std::int32_t typeIndex = -1;	// 0x0004
};
// sizeof( Il2CppWindowsRuntimeTypeNamePair ) = 0x0008