// ACPI.h
#pragma once


typedef struct acpi_rsd_ptr_t {
    char       signature[8];
    uint8_t    checksum;
    char       oemid[6];
    uint8_t    revision;
    uint32_t   rsdtaddr;
    uint32_t   length;
    uint64_t   xsdtaddr;
    uint8_t    checksum2;
    uint8_t    reserved[3];
} __attribute__((packed)) acpi_rsd_ptr_t;

typedef struct acpi_gas_t {
    uint8_t     address_space_id, bit_width, bit_offset, accesss_size;
    uint64_t    address;
} __attribute__((packed)) acpi_gas_t;

typedef struct acpi_header_t {
    char        signature[4];
    uint32_t    length;
    int8_t      revision;
    uint8_t     checksum;
    char        oemid[6];
    char        oem_table_id[8];
    uint32_t    oem_rev;
    uint32_t    creator_id;
    uint32_t    creator_rev;
} __attribute__((packed)) acpi_header_t;


//  RSDT Root System Description Table
typedef struct acpi_rsdt_t {
    acpi_header_t   Header;
    uint32_t    Entry[];
} acpi_rsdt_t;


//  XSDT Extended System Description Table
typedef struct acpi_xsdt_t {
    acpi_header_t   Header;
    uint64_t    Entry[];
} __attribute__((packed)) acpi_xsdt_t;


//  FADT/FACP Fixed ACPI Descriptor Table
typedef struct acpi_fadt_t {
    acpi_header_t   Header;
    uint32_t    FIRMWARE_CTL;
    uint32_t    DSDT;
    uint8_t     Reserved1;
    uint8_t     Prefered_PM_Profile;
    uint16_t    SCI_INT;
    uint32_t    SMI_CMD;
    uint8_t     ACPI_ENABLE, ACPI_DISABLE;
    uint8_t     S4BIOS_REQ;
    uint8_t     PSTATE_CNT;
    uint32_t    PM1a_EVT_BLK, PM1b_EVT_BLK, PM1a_CNT_BLK, PM1b_CNT_BLK, PM2_CNT_BLK, PM_TMR_BLK, GPE0_BLK, GPE1_BLK;
    uint8_t     PM1_EVT_LEN, PM1_CNT_LEN, PM2_CNT_LEN, PM_TMR_LEN, GPE0_BLK_LEN, GPE1_BLK_LEN, GPE1_BASE, CST_CNT;
    uint16_t    P_LVL2_LAT, P_LVL3_LAT, FLUSH_SIZE, FLUSH_STRIDE;
    uint8_t     DUTY_OFFSET, DUTY_WIDTH, DAY_ALRM, MON_ALRM, CENTURY;
    uint16_t    IAPC_BOOT_ARCH;
    uint8_t     Reserved2;
    uint32_t    Flags;
    acpi_gas_t  RESET_REG;
    uint8_t     RESET_VALUE;
    uint16_t    ARM_BOOT_ARCH;
    uint8_t     FADT_Minor_Version;
    uint64_t    X_FIRMWARE_CTL, X_DSDT;
    acpi_gas_t  X_PM1a_EVT_BLK, X_PM1b_EVT_BLK, X_PM1a_CNT_BLK, X_PM1b_CNT_BLK;
    acpi_gas_t  X_PM2_CNT_BLK, X_PM_TMR_BLK, X_GPE0_BLK, X_GPE1_BLK;
    acpi_gas_t  SLEEP_CONTROL_REG, SLEEP_STATUS_REG;
    uint64_t    HYPERVISOR_VENDOR_IDENTITY;
} __attribute__((packed)) acpi_fadt_t;

#define ACPI_FADT_SIGNATURE         "FACP"
#define ACPI_FADT_TMR_VAL_EXT       0x00000100 /* Timer is 32bit */
#define ACPI_FADT_RESET_REG_SUP     0x00000400 /* RESET_REG supported */
#define ACPI_FADT_HW_REDUCED_ACPI   0x00100000 /* HW reduced ACPI */
#define ACPI_FADT_IAPC_LEGACY       0x0001 /* Legacy Devices */
#define ACPI_FADT_IAPC_8042         0x0002 /* PS2 present */
#define ACPI_FADT_IAPC_NO_VGA       0x0004 /* VGA not present */
#define ACPI_FADT_IAPC_NO_MSI       0x0008 /* MSI not supported */

#define ACPI_PM1_SCI_EN             0x0001
#define ACPI_PM1_SLP_EN             0x2000
#define ACPI_SCR_SLP_EN             0x20

#define ACPI_PM_TIMER_FREQ          3579545


// DSDT Differentiated System Description Table
typedef struct acpi_dsdt_t {
    acpi_header_t   Header;
    uint8_t     Structure[];
} acpi_dsdt_t;

#define ACPI_DSDT_SIGNATURE         "DSDT"


//  MADT/APIC Multiple APIC Description Table
typedef struct acpi_madt_t {
    acpi_header_t   Header;
    uint32_t    lapicaddr;
    uint32_t    Flags;
    uint8_t     Structure[];
} acpi_madt_t;

#define ACPI_MADT_SIGNATURE         "APIC"
#define ACPI_MADT_PCAT_COMPAT       0x0001 /* 8259 PIC Present */


//  BGRT Boot Graphics Resource Table
typedef struct acpi_bgrt_t {
    acpi_header_t   Header;
    uint16_t    Version;
    uint8_t     Status, Image_Type;
    uint64_t    Image_Address;
    uint32_t    Image_Offset_X, Image_Offset_Y;
} __attribute__((packed)) acpi_bgrt_t;

#define ACPI_BGRT_SIGNATURE         "BGRT"
#define ACPI_BGRT_VERSION_CURRENT   0x0001
#define ACPI_BGRT_STATUS_DISPLAYED  0x01
#define ACPI_BGRT_IMAGE_TYPE_BITMAP 0x00


//  HPET High Precision Event Timer
typedef struct {
    acpi_header_t   Header;
    uint32_t event_timer_block_id;
    acpi_gas_t address;
    uint8_t hpet_number;
    uint16_t minimum_tick;
    uint8_t page_protection;
} __attribute__((packed)) acpi_hpet_t;

#define ACPI_HPET_SIGNATURE         "HPET"
