#!/usr/bin/env python3

import re
import sys


# ============================================================
# Configuration
# ============================================================

HEADER_NAME = "stm32f732xx.h"

INSTANCE_BASES = [
    "USB_OTG_FS_PERIPH_BASE",
    "USB_OTG_HS_PERIPH_BASE",
]

GEOMETRY = [
    "USB_OTG_GLOBAL_BASE",
    "USB_OTG_DEVICE_BASE",
    "USB_OTG_IN_ENDPOINT_BASE",
    "USB_OTG_OUT_ENDPOINT_BASE",
    "USB_OTG_EP_REG_SIZE",
    "USB_OTG_HOST_BASE",
    "USB_OTG_HOST_PORT_BASE",
    "USB_OTG_HOST_CHANNEL_BASE",
    "USB_OTG_HOST_CHANNEL_SIZE",
    "USB_OTG_PCGCCTL_BASE",
    "USB_OTG_FIFO_BASE",
    "USB_OTG_FIFO_SIZE",
]


STRUCTS = [
    (
        "USB_OTG_GlobalTypeDef",
        "MyUSB_GLOBAL_REG",
        "USBGlobalReg"
    ),

    (
        "USB_OTG_DeviceTypeDef",
        "MyUSB_DEVICE_REG",
        "USBDeviceReg"
    ),

    (
        "USB_OTG_INEndpointTypeDef",
        "MyUSB_IN_EP_REG",
        "USBInEPReg"
    ),

    (
        "USB_OTG_OUTEndpointTypeDef",
        "MyUSB_OUT_EP_REG",
        "USBOutEPReg"
    ),
]


# ============================================================
# Arguments
# ============================================================

if len(sys.argv) != 2:
    print(
        f"Usage: {sys.argv[0]} <STM32IncludeDirectory>",
        file=sys.stderr
    )
    sys.exit(1)


include_dir = sys.argv[1]


# ============================================================
# Read header
# ============================================================

from pathlib import Path

header = Path(include_dir) / HEADER_NAME

if not header.exists():
    print(
        f"Header not found: {header}",
        file=sys.stderr
    )
    sys.exit(1)


text = header.read_text(
    encoding="utf-8",
    errors="ignore"
)


# ============================================================
# Helpers
# ============================================================

def parse_number(value):
    value = value.strip()

    value = re.sub(
        r"[ULul]+$",
        "",
        value
    )

    try:
        return int(value, 0)
    except ValueError:
        return None


def find_define(name):
    pattern = re.compile(
        rf"^\s*#define\s+"
        rf"{re.escape(name)}\s+"
        rf"(.+?)\s*$",
        re.MULTILINE
    )

    match = pattern.search(text)

    if not match:
        return None

    raw = match.group(1)

    raw = raw.split("//", 1)[0].strip()

    return parse_number(raw)


def find_struct_body(struct_name):
    """
    Find exactly:

        typedef struct
        {
            ...
        } struct_name;

    The body of these STM32 USB structs does not contain nested
    braces, so [^}] is intentional here.
    """

    pattern = re.compile(
        r"typedef\s+struct\s*\{"
        r"(?P<body>[^}]*)"
        r"\}\s*"
        rf"{re.escape(struct_name)}"
        r"\s*;",
        re.DOTALL
    )

    match = pattern.search(text)

    if not match:
        return None

    return match.group("body")


def parse_struct_registers(body):
    if body is None:
        return []

    result = []

    for line in body.splitlines():

        # Remove comments before parsing member declaration.
        code = line.split("/*", 1)[0]

        # Remove trailing // comments only after saving original line.
        code = code.split("//", 1)[0]

        # ----------------------------------------------------
        # Register member
        #
        # Example:
        #
        # __IO uint32_t GOTGCTL;
        # ----------------------------------------------------

        match = re.search(
            r"\b([A-Za-z_][A-Za-z0-9_]*)\s*;",
            code
        )

        if not match:
            continue

        name = match.group(1)

        if name.lower().startswith("reserved"):
            continue

        # ----------------------------------------------------
        # Find offset in original line comment.
        #
        # Examples:
        #
        # 000h
        # 900h + (ep_num * 20h) + 08h
        # ----------------------------------------------------

        offset_match = re.search(
            r"\b([0-9A-Fa-f]+)h"
            r"(?:\s*\+\s*\(ep_num\s*\*\s*20h\))?"
            r"(?:\s*\+\s*([0-9A-Fa-f]+)h)?",
            line
        )

        if offset_match is None:
            continue

        first = int(
            offset_match.group(1),
            16
        )

        second = offset_match.group(2)

        if second is not None:
            offset = int(second, 16)
        else:
            offset = first

        # For endpoint structures the first number is the base
        # (900h / B00h), while the second is the register offset.
        if "ep_num" in line:
            offset = (
                second
                and int(second, 16)
                or 0
            )

        result.append(
            (name, offset)
        )

    return result


def emit_register_group(
    f,
    enum_name,
    table_name,
    accessor_name,
    registers
):
    if not registers:
        return

    f.write(
        f"enum class {enum_name} : uint8_t\n"
    )
    f.write("{\n")

    for name, offset in registers:
        f.write(
            f"    {name},\n"
        )

    f.write("};\n\n")

    f.write(
        f"static constexpr uint32_t "
        f"{table_name}[] =\n"
    )
    f.write("{\n")

    for name, offset in registers:
        f.write(
            f"    0x{offset:04X}, // {name}\n"
        )

    f.write("};\n\n")

    f.write(
        f"static constexpr uint32_t "
        f"{accessor_name}({enum_name} reg)\n"
    )
    f.write("{\n")

    f.write(
        f"    return {table_name}["
        f"static_cast<uint8_t>(reg)"
        f"];\n"
    )

    f.write("}\n\n")


# ============================================================
# Parse instances
# ============================================================

instances = []

for name in INSTANCE_BASES:

    value = find_define(name)

    if value is None:
        continue

    if name.endswith("_FS_PERIPH_BASE"):
        member = "FS"
    elif name.endswith("_HS_PERIPH_BASE"):
        member = "HS"
    else:
        member = name

    instances.append(
        (member, value)
    )


# ============================================================
# Parse geometry
# ============================================================

geometry = []

for name in GEOMETRY:

    value = find_define(name)

    if value is None:
        continue

    short = name[len("USB_OTG_"):]

    geometry.append(
        (short, value)
    )


# ============================================================
# Parse structures
# ============================================================

parsed = {}

for struct_name, enum_name, accessor_name in STRUCTS:

    body = find_struct_body(
        struct_name
    )

    registers = parse_struct_registers(
        body
    )

    parsed[struct_name] = registers

    print(
        f"{struct_name:32s}: "
        f"{len(registers)} registers",
        file=sys.stderr
    )


# ============================================================
# Diagnostics
# ============================================================

print(
    f"STM32 USB header : {header}",
    file=sys.stderr
)

print(
    f"USB instances    : {len(instances)}",
    file=sys.stderr
)

print(
    f"USB geometry     : {len(geometry)}",
    file=sys.stderr
)

print(
    f"USB instance FS/HS bases:",
    file=sys.stderr
)

for name, value in instances:
    print(
        f"    {name}: 0x{value:08X}",
        file=sys.stderr
    )


# ============================================================
# Generate
# ============================================================

print(
    "// ============================================================"
)
print(
    "// STM32 USB definitions generated from stm32f732xx.h"
)
print(
    "// ============================================================"
)
print()


# ============================================================
# USB instances
# ============================================================

print(
    "// ============================================================"
)
print("// USB instances")
print(
    "// ============================================================"
)
print()

print(
    "enum class MyUSB_INSTANCE : uint8_t"
)
print("{")

for name, value in instances:
    print(
        f"    {name},"
    )

print("};")
print()

print(
    "static constexpr uint32_t USB_INSTANCE_BASES[] ="
)
print("{")

for name, value in instances:
    print(
        f"    0x{value:08X}, // {name}"
    )

print("};")
print()

print(
    "static constexpr uint32_t "
    "USB_INSTANCE_BASE(MyUSB_INSTANCE instance)"
)
print("{")

print(
    "    return USB_INSTANCE_BASES["
    "static_cast<uint8_t>(instance)"
    "];"
)

print("}")
print()


# ============================================================
# USB geometry
# ============================================================

print(
    "// ============================================================"
)
print("// USB geometry")
print(
    "// ============================================================"
)
print()

for name, value in geometry:
    print(
        f"static constexpr uint32_t "
        f"{name} = 0x{value:04X};"
    )

print()


# ============================================================
# Global registers
# ============================================================

emit_register_group(
    sys.stdout,
    "MyUSB_GLOBAL_REG",
    "USBGlobalRegOffsets",
    "USBGlobalReg",
    parsed["USB_OTG_GlobalTypeDef"]
)


# ============================================================
# Device registers
# ============================================================

emit_register_group(
    sys.stdout,
    "MyUSB_DEVICE_REG",
    "USBDeviceRegOffsets",
    "USBDeviceReg",
    parsed["USB_OTG_DeviceTypeDef"]
)


# ============================================================
# IN endpoint registers
# ============================================================

in_regs = parsed[
    "USB_OTG_INEndpointTypeDef"
]

if in_regs:

    print(
        "// ============================================================"
    )
    print("// USB IN endpoint registers")
    print(
        "// ============================================================"
    )
    print()

    print(
        "enum class MyUSB_IN_EP_REG : uint8_t"
    )
    print("{")

    for name, offset in in_regs:
        print(
            f"    {name},"
        )

    print("};")
    print()

    print(
        "static constexpr uint32_t "
        "USBInEPRegOffsets[] ="
    )
    print("{")

    for name, offset in in_regs:
        print(
            f"    0x{offset:04X}, // {name}"
        )

    print("};")
    print()

    print(
        "static constexpr uint32_t "
        "USBInEPReg("
        "uint8_t ep, "
        "MyUSB_IN_EP_REG reg)"
    )
    print("{")

    print(
        "    return "
        "IN_ENDPOINT_BASE + "
        "static_cast<uint32_t>(ep) * "
        "EP_REG_SIZE + "
        "USBInEPRegOffsets["
        "static_cast<uint8_t>(reg)"
        "];"
    )

    print("}")
    print()


# ============================================================
# OUT endpoint registers
# ============================================================

out_regs = parsed[
    "USB_OTG_OUTEndpointTypeDef"
]

if out_regs:

    print(
        "// ============================================================"
    )
    print("// USB OUT endpoint registers")
    print(
        "// ============================================================"
    )
    print()

    print(
        "enum class MyUSB_OUT_EP_REG : uint8_t"
    )
    print("{")

    for name, offset in out_regs:
        print(
            f"    {name},"
        )

    print("};")
    print()

    print(
        "static constexpr uint32_t "
        "USBOutEPRegOffsets[] ="
    )
    print("{")

    for name, offset in out_regs:
        print(
            f"    0x{offset:04X}, // {name}"
        )

    print("};")
    print()

    print(
        "static constexpr uint32_t "
        "USBOutEPReg("
        "uint8_t ep, "
        "MyUSB_OUT_EP_REG reg)"
    )
    print("{")

    print(
        "    return "
        "OUT_ENDPOINT_BASE + "
        "static_cast<uint32_t>(ep) * "
        "EP_REG_SIZE + "
        "USBOutEPRegOffsets["
        "static_cast<uint8_t>(reg)"
        "];"
    )

    print("}")
    print()


# ============================================================
# FIFO
# ============================================================

print(
    "// ============================================================"
)
print("// USB FIFO")
print(
    "// ============================================================"
)
print()

print(
    "static constexpr uint32_t "
    "USBFIFO(uint32_t offset)"
)
print("{")

print(
    "    return FIFO_BASE + offset;"
)

print("}")
print()