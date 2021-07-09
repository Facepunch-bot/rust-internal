#pragma once

#include <horizon/include/auto.hpp>
#include <horizon/include/base.hpp>
#include <horizon/include/win32.hpp>

#include <horizon/memory/operation.hpp>

#include "il2cpp-config.hpp"
#include "il2cpp-class-internals.hpp"

struct Il2CppType;

struct Il2CppReflectionAssembly;

struct MonitorData;

using Il2CppVTable = Il2CppClass;
// sizeof( Il2CppVTable ) = 0x0128

struct Il2CppObject
{
	union
	{
		Il2CppClass* klass = nullptr;		// 0x0000
		Il2CppVTable* vtable;						// 0x0000
	};
	MonitorData* monitor = nullptr;		// 0x0008
};
// sizeof( Il2CppObject ) = 0x0010

struct Il2CppArrayBounds
{
	std::size_t length = 0;				// 0x0000
	std::int32_t lower_bound = 0;	// 0x0008
	FIELD_PAD( 0x0004 );					// 0x000C
};
// sizeof( Il2CppArrayBounds ) = 0x0010

struct Il2CppArray : Il2CppObject
{
	Il2CppArrayBounds* bounds = nullptr;	// 0x0010
	std::size_t max_length = 0;						// 0x0018
};
// sizeof( Il2CppArray ) = 0x0020

struct Il2CppArraySize : Il2CppArray
{
	ALIGN_TYPE( 8 ) void* vector[ 0 ];	// 0x0020
};
// sizeof( Il2CppArraySize ) = 0x0020

struct Il2CppString
{
	Il2CppObject object = { };									// 0x0000
	std::int32_t length = 0;										// 0x0010
	FIELD_PAD( 0x0004 );												// 0x0014
	Il2CppChar chars[ IL2CPP_ZERO_LEN_ARRAY ];	// 0x0018
};
// sizeof( Il2CppString ) = 0x0018

struct Il2CppReflectionType
{
	Il2CppObject object = { };				// 0x0000
	const Il2CppType* type = nullptr;	// 0x0010
};
// sizeof( Il2CppReflectionType ) = 0x0018

struct Il2CppReflectionRuntimeType
{
	Il2CppReflectionType type = { };						// 0x0000
	Il2CppObject* type_info = nullptr;					// 0x0018
	Il2CppObject* genericCache = nullptr;				// 0x0020
	Il2CppObject* serializationCtor = nullptr;	// 0x0028
};
// sizeof( Il2CppReflectionRuntimeType ) = 0x0030

struct Il2CppReflectionMonoType
{
	const Il2CppType* GetIl2CppType() const
	{
		return type.type.type;
	}

	Il2CppReflectionRuntimeType type = { };	// 0x0000
};
// sizeof( Il2CppReflectionMonoType ) = 0x0030

struct Il2CppReflectionEvent
{
	Il2CppObject object = { };								// 0x0000
	Il2CppObject* cached_add_event = nullptr;	// 0x0010
};
// sizeof( Il2CppReflectionEvent ) = 0x0018

struct Il2CppReflectionMonoEvent
{
	Il2CppReflectionEvent event = { };							// 0x0000
	Il2CppReflectionType* reflectedType = nullptr;	// 0x0018
	const EventInfo* eventInfo = nullptr;						// 0x0020
};
// sizeof( Il2CppReflectionMonoEvent ) = 0x0028

struct Il2CppReflectionMethod;

struct Il2CppReflectionMonoEventInfo
{
	Il2CppReflectionType* declaringType = nullptr;	// 0x0000
	Il2CppReflectionType* reflectedType = nullptr;	// 0x0008
	Il2CppString* name = nullptr;										// 0x0010
	Il2CppReflectionMethod* addMethod = nullptr;		// 0x0018
	Il2CppReflectionMethod* removeMethod = nullptr;	// 0x0020
	Il2CppReflectionMethod* raiseMethod = nullptr;	// 0x0028
	std::uint32_t eventAttributes = 0;							// 0x0030
	FIELD_PAD( 0x0004 );														// 0x0034
	Il2CppArray* otherMethods = nullptr;						// 0x0038
};
// sizeof( Il2CppReflectionMonoEventInfo ) = 0x0040

struct Il2CppReflectionField
{
	Il2CppObject object = { };						// 0x0000
	Il2CppClass* klass = nullptr;					// 0x0010
	FieldInfo* field = nullptr;						// 0x0018
	Il2CppString* name = nullptr;					// 0x0020
	Il2CppReflectionType* type = nullptr;	// 0x0028
	std::uint32_t attrs = 0;							// 0x0030
	FIELD_PAD( 0x0004 );									// 0x0034
};
// sizeof( Il2CppReflectionField ) = 0x0038

struct Il2CppReflectionProperty
{
	Il2CppObject object = { };							// 0x0000
	Il2CppClass* klass = nullptr;						// 0x0010
	const PropertyInfo* property = nullptr;	// 0x0018
};
// sizeof( Il2CppReflectionProperty ) = 0x0020

struct Il2CppReflectionMethod
{
	Il2CppObject object = { };								// 0x0000
	const MethodInfo* method = nullptr;				// 0x0010
	Il2CppString* name = nullptr;							// 0x0018
	Il2CppReflectionType* reftype = nullptr;	// 0x0020
};
// sizeof( Il2CppReflectionMethod ) = 0x0028

struct Il2CppReflectionGenericMethod : Il2CppReflectionMethod
{ };
// sizeof( Il2CppReflectionGenericMethod ) = 0x0028

struct Il2CppMethodInfo
{
	Il2CppReflectionType* parent = nullptr;	// 0x0000
	Il2CppReflectionType* ret = nullptr;		// 0x0008
	std::uint32_t attrs = 0;								// 0x0010
	std::uint32_t implattrs = 0;						// 0x0014
	std::uint32_t callconv = 0;							// 0x0018
	FIELD_PAD( 0x0004 );										// 0x001C
};
// sizeof( Il2CppMethodInfo ) = 0x0020

struct Il2CppPropertyInfo
{
	Il2CppReflectionType* parent = nullptr;					// 0x0000
	Il2CppReflectionType* delcaringType = nullptr;	// 0x0008
	Il2CppString* name = nullptr;										// 0x0010
	Il2CppReflectionMethod* get = nullptr;					// 0x0018
	Il2CppReflectionMethod* set = nullptr;					// 0x0020
	std::uint32_t attrs = 0;												// 0x0028
	FIELD_PAD( 0x0004 );														// 0x002C
};
// sizeof( Il2CppPropertyInfo ) = 0x0030

struct Il2CppReflectionParameter
{
	Il2CppObject object = { };									// 0x0000
	Il2CppReflectionType* ClassImpl = nullptr;	// 0x0010
	Il2CppObject* DefaultValueImpl = nullptr;		// 0x0018
	Il2CppObject* MemberImpl = nullptr;					// 0x0020
	Il2CppString* NameImpl = nullptr;						// 0x0028
	std::int32_t PositionImpl = 0;							// 0x0030
	std::uint32_t AttrsImpl = 0;								// 0x0034
	Il2CppObject* MarshalAsImpl = nullptr;			// 0x0038
};
// sizeof( Il2CppReflectionParameter ) = 0x0040

struct Il2CppReflectionModule
{
	Il2CppObject object = { };										// 0x0000
	const Il2CppImage* image = nullptr;						// 0x0010
	Il2CppReflectionAssembly* assembly = nullptr;	// 0x0018
	Il2CppString* fqname = nullptr;								// 0x0020
	Il2CppString* name = nullptr;									// 0x0028
	Il2CppString* scopename = nullptr;						// 0x0030
	bool is_resource = false;											// 0x0038
	FIELD_PAD( 0x0003 );													// 0x0039
	std::uint32_t token = 0;											// 0x003C
};
// sizeof( Il2CppReflectionModule ) = 0x0040

struct Il2CppReflectionAssemblyName
{
	Il2CppObject object = { };								// 0x0000
	Il2CppString* name = nullptr;							// 0x0010
	Il2CppString* codebase = nullptr;					// 0x0018
	std::int32_t major = 0;										// 0x0020
	std::int32_t minor = 0;										// 0x0024
	std::int32_t build = 0;										// 0x0028
	std::int32_t revision = 0;								// 0x002C
	Il2CppObject* cultureInfo = nullptr;			// 0x0030
	std::uint32_t flags = 0;									// 0x0038
	std::uint32_t hashalg = 0;								// 0x003C
	Il2CppObject* keypair = nullptr;					// 0x0040
	Il2CppArray* publicKey = nullptr;					// 0x0048
	Il2CppArray* keyToken = nullptr;					// 0x0050
	std::uint32_t versioncompat = 0;					// 0x0058
	FIELD_PAD( 0x0004 );											// 0x005C
	Il2CppObject* version = nullptr;					// 0x0060
	std::uint32_t processor_architecture = 0;	// 0x0068
	std::uint32_t contentType = 0;						// 0x006C
};
// sizeof( Il2CppReflectionAssemblyName ) = 0x0070

struct Il2CppReflectionAssembly
{
	Il2CppObject object = { };										// 0x0000
	const Il2CppAssembly* assembly = nullptr;			// 0x0010
	Il2CppObject* resolve_event_holder = nullptr;	// 0x0018
	Il2CppObject* evidence = nullptr;							// 0x0020
	Il2CppObject* minimum = nullptr;							// 0x0028
	Il2CppObject* optional = nullptr;							// 0x0030
	Il2CppObject* refuse = nullptr;								// 0x0038
	Il2CppObject* granted = nullptr;							// 0x0040
	Il2CppObject* denied = nullptr;								// 0x0048
	bool from_byte_array = false;									// 0x0050
	FIELD_PAD( 0x0007 );													// 0x0051
	Il2CppString* name = nullptr;									// 0x0058
};
// sizeof( Il2CppReflectionAssembly ) = 0x0060

struct Il2CppReflectionMarshal
{
	Il2CppObject object = { };							// 0x0000
	std::int32_t count = 0;									// 0x0010
	std::int32_t type = 0;									// 0x0014
	std::int32_t eltype = 0;								// 0x0018
	FIELD_PAD( 0x0004 );										// 0x001C
	Il2CppString* guid = nullptr;						// 0x0020
	Il2CppString* mcookie = nullptr;				// 0x0028
	Il2CppString* marshaltype = nullptr;		// 0x0030
	Il2CppString* marshaltyperef = nullptr;	// 0x0038
	std::int32_t param_num = 0;							// 0x0040
	bool has_size = false;									// 0x0044
	FIELD_PAD( 0x0003 );										// 0x0045
};
// sizeof( Il2CppReflectionMarshal ) = 0x0048

struct Il2CppReflectionPointer
{
	Il2CppObject object = { };						// 0x0000
	void* data = nullptr;									// 0x0010
	Il2CppReflectionType* type = nullptr;	// 0x0018
};
// sizeof( Il2CppReflectionPointer ) = 0x0020

struct Il2CppInternalThread
{
	Il2CppObject object = { };											// 0x0000
	std::int32_t lock_thread_id = 0;								// 0x0010
	FIELD_PAD( 0x0004 );														// 0x0014
	void* handle = nullptr;													// 0x0018
	void* native_handle = nullptr;									// 0x0020
	Il2CppArray* cached_culture_info = nullptr;			// 0x0028
	Il2CppChar* name = nullptr;											// 0x0030
	std::int32_t name_len = 0;											// 0x0038
	std::uint32_t state = 0;												// 0x003C
	Il2CppObject* abort_exc = nullptr;							// 0x0040
	std::int32_t abort_state_handle = 0;						// 0x0048
	FIELD_PAD( 0x0004 );														// 0x004C
	std::uint64_t tid = 0;													// 0x0050
	std::intptr_t debugger_thread = 0;							// 0x0058
	void** static_data = nullptr;										// 0x0060
	void* runtime_thread_info = nullptr;						// 0x0068
	Il2CppObject* current_appcontext = nullptr;			// 0x0070
	Il2CppObject* root_domain_thread = nullptr;			// 0x0078
	Il2CppArray* _serialized_principal = nullptr;		// 0x0080
	std::int32_t _serialized_principal_version = 0;	// 0x0088
	FIELD_PAD( 0x0004 );														// 0x008C
	void* appdomain_refs = nullptr;									// 0x0090
	std::int32_t interruption_requested = 0;				// 0x0098
	FIELD_PAD( 0x0004 );														// 0x009C
	void* synch_cs = nullptr;												// 0x00A0
	bool threadpool_thread = false;									// 0x00A8
	bool thread_interrupt_requested = false;				// 0x00A9
	FIELD_PAD( 0x0002 );														// 0x00AA
	std::int32_t stack_size = 0;										// 0x00AC
	std::uint8_t apartment_state = 0;								// 0x00B0
	FIELD_PAD( 0x0003 );														// 0x00B1
	std::int32_t critical_region_level = 0;					// 0x00B4
	std::int32_t managed_id = 0;										// 0x00B8
	std::uint32_t small_id = 0;											// 0x00BC
	void* manage_callback = nullptr;								// 0x00C0
	void* interrupt_on_stop = nullptr;							// 0x00C8
	std::intptr_t flags = 0;												// 0x00D0
	void* thread_pinning_ref = nullptr;							// 0x00D8
	void* abort_protected_block_count = nullptr;		// 0x00E0
	std::int32_t priority = 0;											// 0x00E8
	FIELD_PAD( 0x0004 );														// 0x00EC
	void* owned_mutexes = nullptr;									// 0x00F0
	void* suspended = nullptr;											// 0x00F8
	std::int32_t self_suspended = 0;								// 0x0100
	FIELD_PAD( 0x0004 );														// 0x0104
	std::size_t thread_state = 0;										// 0x0108
	FIELD_PAD( 0x0008 );														// 0x0110
	void* last = nullptr;														// 0x0118
};
// sizeof( Il2CppInternalThread ) = 0x0120

// constexpr auto disp_of_chars = FIELD_OFFSET( Il2CppString, chars );
// constexpr auto size_of_Il2CppString = sizeof( Il2CppString );