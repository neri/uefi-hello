#ifndef INCLUDED_EFISYST_H
#define INCLUDED_EFISYST_H

#include "efidefs.h"

typedef struct _EFI_SYSTEM_TABLE	EFI_SYSTEM_TABLE;
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL	EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef struct _EFI_DEVICE_PATH_PROTOCOL EFI_DEVICE_PATH_PROTOCOL;
typedef struct _EFI_OPEN_PROTOCOL_INFORMATION_ENTRY EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;
typedef struct _EFI_HII_PACKAGE_LIST_HEADER EFI_HII_PACKAGE_LIST_HEADER;


typedef struct _EFI_TABLE_HEADER {
	UINT64 Signature;
	UINT32 Revision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;


typedef struct EFI_CONFIGURATION_TABLE {
	EFI_GUID VendorGuid;
	VOID *VendorTable;
} EFI_CONFIGURATION_TABLE;


#define ACPI_TABLE_GUID \
	{0xeb9d2d30,0x2d88,0x11d3, {0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}
#define SAL_SYSTEM_TABLE_GUID \
	{0xeb9d2d32,0x2d88,0x11d3, {0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}
#define SMBIOS_TABLE_GUID \
	{0xeb9d2d31,0x2d88,0x11d3, {0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}
#define SMBIOS3_TABLE_GUID \
	{0xf2fd1544, 0x9794, 0x4a2c, {0x99,0x2e,0xe5,0xbb,0xcf,0x20,0xe3,0x94})
#define MPS_TABLE_GUID \
	{0xeb9d2d2f,0x2d88,0x11d3, {0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}
#define EFI_ACPI_TABLE_GUID \
	{0x8868e871,0xe4f1,0x11d3, {0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}}
#define EFI_ACPI_20_TABLE_GUID EFI_ACPI_TABLE_GUID
#define ACPI_TABLE_GUID \
	{0xeb9d2d30,0x2d88,0x11d3, {0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}
#define ACPI_10_TABLE_GUID ACPI_TABLE_GUID


//---------------------------------------------------------------------
//
//	Boot Services
//
//---------------------------------------------------------------------

// Event & Timer Services

#define EVT_TIMER 0x80000000
#define EVT_RUNTIME 0x40000000
#define EVT_NOTIFY_WAIT 0x00000100
#define EVT_NOTIFY_SIGNAL 0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
	{0x27abf055, 0xb1b8, 0x4c26, 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf}}
#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
	{0x13fa7698, 0xc831, 0x49c7, 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96}
#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
	{0x78bee926, 0x692f, 0x48fd, 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab}
#define EFI_EVENT_GROUP_READY_TO_BOOT \
	{0x7ce88fb3, 0x4bd7, 0x4679, 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5,0xd, 0x2b}
#define EFI_EVENT_GROUP_RESET_SYSTEM \
	{ 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b } }

typedef
VOID
(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT Event,
	IN VOID *Context
);
 
typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32 Type,
	IN EFI_TPL NotifyTpl,
	IN EFI_EVENT_NOTIFY NotifyFunction, OPTIONAL
	IN VOID *NotifyContext, OPTIONAL
	OUT EFI_EVENT *Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT_EX) (
	IN UINT32 Type,
	IN EFI_TPL NotifyTpl,
	IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
	IN CONST VOID *NotifyContext OPTIONAL,
	IN CONST EFI_GUID *EventGroup OPTIONAL,
	OUT EFI_EVENT *Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_SIGNAL_EVENT) (
	IN EFI_EVENT Event
);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN NumberOfEvents,
	IN EFI_EVENT *Event,
	OUT UINTN *Index
);

typedef
EFI_STATUS
(EFIAPI *EFI_CHECK_EVENT) (
	IN EFI_EVENT Event
);

typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT Event,
	IN EFI_TIMER_DELAY Type,
	IN UINT64 TriggerTime
);

// Task Priority Services

#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

typedef
EFI_TPL
(EFIAPI *EFI_RAISE_TPL) (
	IN EFI_TPL NewTpl
);

typedef
VOID
(EFIAPI *EFI_RESTORE_TPL) (
	IN EFI_TPL OldTpl
);

// Memory Services

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;
#define EFI_MEMORY_DESCRIPTOR_VERSION 1

typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef struct {
	UINT32 Type;
	EFI_PHYSICAL_ADDRESS PhysicalStart;
	EFI_VIRTUAL_ADDRESS VirtualStart;
	UINT64 NumberOfPages;
	UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_NV 0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO 0x0000000000020000
#define EFI_MEMORY_RUNTIME 0x8000000000000000



typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_PAGES) (
	IN EFI_ALLOCATE_TYPE Type,
	IN EFI_MEMORY_TYPE MemoryType,
	IN UINTN Pages,
	IN OUT EFI_PHYSICAL_ADDRESS *Memory
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_PAGES) (
IN EFI_PHYSICAL_ADDRESS Memory,
IN UINTN Pages
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_MEMORY_MAP) (
	IN OUT UINTN *MemoryMapSize,
	IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
	OUT UINTN *MapKey,
	OUT UINTN *DescriptorSize,
	OUT UINT32 *DescriptorVersion
);

typedef
EFI_STATUS
(EFIAPI *EFI_ALLOCATE_POOL) (
	IN EFI_MEMORY_TYPE PoolType,
	IN UINTN Size,
	OUT VOID **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FREE_POOL) (
	IN VOID *Buffer
);

// Protocol Handler Services

typedef VOID *EFI_HANDLE;

typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020


typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_PROTOCOL_INTERFACE) (
	IN OUT EFI_HANDLE *Handle,
	IN EFI_GUID *Protocol,
	IN EFI_INTERFACE_TYPE InterfaceType,
	IN VOID *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN VOID *Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REINSTALL_PROTOCOL_INTERFACE) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN VOID *OldInterface,
	IN VOID *NewInterface
);

typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_PROTOCOL_NOTIFY) (
	IN EFI_GUID *Protocol,
	IN EFI_EVENT Event,
	OUT VOID **Registration
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE) (
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL,
	IN OUT UINTN *BufferSize,
	OUT EFI_HANDLE *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_HANDLE_PROTOCOL) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT VOID **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_DEVICE_PATH) (
	IN EFI_GUID *Protocol,
	IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
	OUT EFI_HANDLE *Device
);

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT VOID **Interface OPTIONAL,
	IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle,
	IN UINT32 Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_PROTOCOL) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	IN EFI_HANDLE AgentHandle,
	IN EFI_HANDLE ControllerHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_OPEN_PROTOCOL_INFORMATION) (
	IN EFI_HANDLE Handle,
	IN EFI_GUID *Protocol,
	OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
	OUT UINTN *EntryCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_CONNECT_CONTROLLER) (
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE *DriverImageHandle OPTIONAL,
	IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
	IN BOOLEAN Recursive
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISCONNECT_CONTROLLER) (
	IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE DriverImageHandle OPTIONAL,
	IN EFI_HANDLE ChildHandle OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_PROTOCOLS_PER_HANDLE) (
	IN EFI_HANDLE Handle,
	OUT EFI_GUID ***ProtocolBuffer,
	OUT UINTN *ProtocolBufferCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_HANDLE_BUFFER) (
	IN EFI_LOCATE_SEARCH_TYPE SearchType,
	IN EFI_GUID *Protocol OPTIONAL,
	IN VOID *SearchKey OPTIONAL,
	IN OUT UINTN *NoHandles,
	OUT EFI_HANDLE **Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_LOCATE_PROTOCOL) (
	IN EFI_GUID *Protocol,
	IN VOID *Registration OPTIONAL,
	OUT VOID **Interface
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN OUT EFI_HANDLE *Handle,
	...
);

typedef
EFI_STATUS
(EFIAPI *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
	IN EFI_HANDLE Handle,
	...
);


// Image Services

#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
	{ 0x6a1ee763, 0xd47a, 0x43b4, { 0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc } }

typedef EFI_HII_PACKAGE_LIST_HEADER *EFI_HII_PACKAGE_LIST_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_ENTRY_POINT) (
	IN EFI_HANDLE ImageHandle,
	IN EFI_SYSTEM_TABLE *SystemTable
);


typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_LOAD) (
	IN BOOLEAN BootPolicy,
	IN EFI_HANDLE ParentImageHandle,
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
	IN VOID *SourceBuffer OPTIONAL,
	IN UINTN SourceSize,
	OUT EFI_HANDLE *ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_START) (
	IN EFI_HANDLE ImageHandle,
	OUT UINTN *ExitDataSize,
	OUT CHAR16 **ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_IMAGE_UNLOAD) (
	IN EFI_HANDLE ImageHandle
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT) (
	IN EFI_HANDLE ImageHandle,
	IN EFI_STATUS ExitStatus,
	IN UINTN ExitDataSize,
	IN CHAR16 *ExitData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_EXIT_BOOT_SERVICES) (
	IN EFI_HANDLE ImageHandle,
	IN UINTN MapKey
);


// Miscellaneous Boot Services


typedef
EFI_STATUS
(EFIAPI *EFI_SET_WATCHDOG_TIMER) (
	IN UINTN Timeout,
	IN UINT64 WatchdogCode,
	IN UINTN DataSize,
	IN CHAR16 *WatchdogData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_STALL) (
	IN UINTN Microseconds
);

typedef
VOID
(EFIAPI *EFI_COPY_MEM) (
	IN VOID *Destination,
	IN VOID *Source,
	IN UINTN Length
);

typedef
VOID
(EFIAPI *EFI_SET_MEM) (
	IN VOID *Buffer,
	IN UINTN Size,
	IN UINT8 Value
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_MONOTONIC_COUNT) (
	OUT UINT64 *Count
);

typedef
EFI_STATUS
(EFIAPI *EFI_INSTALL_CONFIGURATION_TABLE) (
	IN EFI_GUID *Guid,
	IN VOID *Table
);

typedef
EFI_STATUS
(EFIAPI *EFI_CALCULATE_CRC32) (
	IN VOID *Data,
	IN UINTN DataSize,
	OUT UINT32 *Crc32
);


#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef struct {
	EFI_TABLE_HEADER Hdr;

	EFI_RAISE_TPL RaiseTPL;
	EFI_RESTORE_TPL RestoreTPL;

	EFI_ALLOCATE_PAGES AllocatePages;
	EFI_FREE_PAGES FreePages;
	EFI_GET_MEMORY_MAP GetMemoryMap;
	EFI_ALLOCATE_POOL AllocatePool;
	EFI_FREE_POOL FreePool;

	EFI_CREATE_EVENT CreateEvent;
	EFI_SET_TIMER SetTimer;
	EFI_WAIT_FOR_EVENT WaitForEvent;
	EFI_SIGNAL_EVENT SignalEvent;
	EFI_CLOSE_EVENT CloseEvent;
	EFI_CHECK_EVENT CheckEvent;

	EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL HandleProtocol;
	VOID *Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
	EFI_LOCATE_HANDLE LocateHandle;
	EFI_LOCATE_DEVICE_PATH LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

	EFI_IMAGE_LOAD LoadImage;
	EFI_IMAGE_START StartImage;
	EFI_EXIT Exit;
	EFI_IMAGE_UNLOAD UnloadImage;
	EFI_EXIT_BOOT_SERVICES ExitBootServices;

	EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
	EFI_STALL Stall;
	EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

	EFI_CONNECT_CONTROLLER ConnectController;
	EFI_DISCONNECT_CONTROLLER DisconnectController;

	EFI_OPEN_PROTOCOL OpenProtocol;
	EFI_CLOSE_PROTOCOL CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

	EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

	EFI_CALCULATE_CRC32 CalculateCrc32;

	EFI_COPY_MEM CopyMem;
	EFI_SET_MEM SetMem;
	EFI_CREATE_EVENT_EX CreateEventEx;
} EFI_BOOT_SERVICES;


//---------------------------------------------------------------------
//
//	Runtime Services
//
//---------------------------------------------------------------------

// Variable Services

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x00000008
//This attribute is identified by the mnemonic 'HR' elsewhere
//in this specification.
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS 0x00000010
//NOTE: EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS is deprecated
//and should be considered reserved.
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE 0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS 0x00000080

// #define EFI_VARIABLE_AUTHENTICATION_3_CERT_ID_SHA256 1
// typedef struct {
// 	UINT8 Type;
// 	UINT32 IdSize;
// 	// UINT8 Id[IdSize];
// } EFI_VARIABLE_AUTHENTICATION_3_CERT_ID; 

// typedef struct _WIN_CERTIFICATE_UEFI_GUID WIN_CERTIFICATE_UEFI_GUID;

// typedef struct {
// 	UINT64 MonotonicCount;
// 	WIN_CERTIFICATE_UEFI_GUID AuthInfo;
// } EFI_VARIABLE_AUTHENTICATION;

// typedef struct {
// 	EFI_TIME TimeStamp;
// 	WIN_CERTIFICATE_UEFI_GUID AuthInfo;
// } EFI_VARIABLE_AUTHENTICATION_2;

// #define EFI_VARIABLE_AUTHENTICATION_3_TIMESTAMP_TYPE 1
// #define EFI_VARIABLE_AUTHENTICATION_3_NONCE_TYPE 2
// typedef struct {
// 	UINT8 Version;
// 	UINT8 Type;
// 	UINT32 MetadataSize;
// 	UINT32 Flags;
// } EFI_VARIABLE_AUTHENTICATION_3;

// typedef struct {
// 	UINT32 NonceSize;
// 	// UINT8 Nonce[NonceSize];
// } EFI_VARIABLE_AUTHENTICATION_3_NONCE; 


typedef
EFI_STATUS
(EFIAPI *EFI_GET_VARIABLE) (
	IN CHAR16 *VariableName,
	IN EFI_GUID *VendorGuid,
	OUT UINT32 *Attributes OPTIONAL,
	IN OUT UINTN *DataSize,
	OUT VOID *Data OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_VARIABLE_NAME) (
	IN OUT UINTN *VariableNameSize,
	IN OUT CHAR16 *VariableName,
	IN OUT EFI_GUID *VendorGuid
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_VARIABLE) (
	IN CHAR16 *VariableName,
	IN EFI_GUID *VendorGuid,
	IN UINT32 Attributes,
	IN UINTN DataSize,
	IN VOID *Data
);

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_VARIABLE_INFO) (
	IN UINT32 Attributes,
	OUT UINT64 *MaximumVariableStorageSize,
	OUT UINT64 *RemainingVariableStorageSize,
	OUT UINT64 *MaximumVariableSize
);


// Time Services

typedef struct _EFI_TIME {
	UINT16 Year; // 1900 – 9999
	UINT8 Month; // 1 – 12
	UINT8 Day; // 1 – 31
	UINT8 Hour; // 0 – 23
	UINT8 Minute; // 0 – 59
	UINT8 Second; // 0 – 59
	UINT8 Pad1;
	UINT32 Nanosecond; // 0 – 999,999,999
	INT16 TimeZone; // -1440 to 1440 or 2047
	UINT8 Daylight;
	UINT8 Pad2;
} EFI_TIME;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02

#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef struct {
	UINT32 Resolution;
	UINT32 Accuracy;
	BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;


typedef
EFI_STATUS
(EFIAPI *EFI_GET_TIME) (
	OUT EFI_TIME *Time,
	OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIME) (
	IN EFI_TIME *Time
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_WAKEUP_TIME) (
	OUT BOOLEAN *Enabled,
	OUT BOOLEAN *Pending,
	OUT EFI_TIME *Time
);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_WAKEUP_TIME) (
	IN BOOLEAN Enable,
	IN EFI_TIME *Time OPTIONAL
);


// Virtual Memory Services

#define EFI_OPTIONAL_PTR 0x00000001

typedef
EFI_STATUS
(EFIAPI *EFI_SET_VIRTUAL_ADDRESS_MAP) (
	IN UINTN MemoryMapSize,
	IN UINTN DescriptorSize,
	IN UINT32 DescriptorVersion,
	IN EFI_MEMORY_DESCRIPTOR *VirtualMap
);


typedef
EFI_STATUS
(EFIAPI *EFI_CONVERT_POINTER) (
	IN UINTN DebugDisposition,
	IN VOID **Address
);


// Miscellaneous Runtime Services

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef struct {
	UINT64 Length;
	union {
		EFI_PHYSICAL_ADDRESS DataBlock;
		EFI_PHYSICAL_ADDRESS ContinuationPointer;
	}Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
	EFI_GUID CapsuleGuid;
	UINT32 HeaderSize;
	UINT32 Flags;
	UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

#define CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define CAPSULE_FLAGS_INITIATE_RESET 0x00040000

#define EFI_CAPSULE_REPORT_GUID \
 { 0x39b68c46, 0xf7fb, 0x441b, {0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3 }} 

typedef struct {
	UINT32 VariableTotalSize;
	UINT32 Reserved;	//for alignment
	EFI_GUID CapsuleGuid;
	EFI_TIME CapsuleProcessed;
	EFI_STATUS CapsuleStatus;
} EFI_CAPSULE_RESULT_VARIABLE_HEADER;

typedef struct {
	UINT16 Version;
	UINT8 PayloadIndex;
	UINT8 UpdateImageIndex;

	EFI_GUID UpdateImageTypeId;
	// CHAR16 CapsuleFileName[];
	// CHAR16 CapsuleTarget[];
} EFI_CAPSULE_RESULT_VARIABLE_FMP;


typedef
VOID
(EFIAPI *EFI_RESET_SYSTEM) (
	IN EFI_RESET_TYPE ResetType,
	IN EFI_STATUS ResetStatus,
	IN UINTN DataSize,
	IN VOID *ResetData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_GET_NEXT_HIGH_MONO_COUNT) (
	OUT UINT32 *HighCount
);

typedef
EFI_STATUS
(EFIAPI *EFI_UPDATE_CAPSULE) (
	IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
	IN UINTN CapsuleCount,
	IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_QUERY_CAPSULE_CAPABILITIES) (
	IN EFI_CAPSULE_HEADER **CapsuleHeaderArray,
	IN UINTN CapsuleCount,
	OUT UINT64 *MaximumCapsuleSize,
	OUT EFI_RESET_TYPE *ResetType
);


#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef struct {
	EFI_TABLE_HEADER Hdr;

	EFI_GET_TIME GetTime;
	EFI_SET_TIME SetTime;
	EFI_GET_WAKEUP_TIME GetWakeupTime;
	EFI_SET_WAKEUP_TIME SetWakeupTime;

	EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
	EFI_CONVERT_POINTER ConvertPointer;

	EFI_GET_VARIABLE GetVariable;
	EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
	EFI_SET_VARIABLE SetVariable;

	EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM ResetSystem;

	EFI_UPDATE_CAPSULE UpdateCapsule;
	EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

	EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;


//---------------------------------------------------------------------
//
//	System Table
//
//---------------------------------------------------------------------

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_70_SYSTEM_TABLE_REVISION ((2 << 16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2 << 16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2 << 16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2 << 16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2 << 16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2 << 16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2 << 16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2 << 16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2 << 16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1 << 16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1 << 16) | (02))
#define EFI_SPECIFICATION_VERSION EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION EFI_2_70_SYSTEM_TABLE_REVISION

typedef struct _EFI_SYSTEM_TABLE {
	EFI_TABLE_HEADER Hdr;
	CHAR16 *FirmwareVendor;
	UINT32 FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
	EFI_HANDLE ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
	EFI_HANDLE StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
	EFI_RUNTIME_SERVICES *RuntimeServices;
	EFI_BOOT_SERVICES *BootServices;
	UINTN NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;


#endif
