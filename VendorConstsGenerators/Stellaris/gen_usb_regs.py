import sys
import re
from pathlib import Path


HEADER_NAME = "lm3s5p36.h"


if len(sys.argv) != 2:
    print(
        "Usage: gen_usb_regs.py <StellarisWare>",
        file=sys.stderr
    )
    sys.exit(1)


stellaris_root = Path(sys.argv[1])
header = stellaris_root / "inc" / HEADER_NAME


if not header.exists():
    print(f"Header not found: {header}", file=sys.stderr)
    sys.exit(1)


text = header.read_text(
    encoding="utf-8",
    errors="ignore"
)


# ============================================================
# Find all USB0 registers
#
# Example:
#
# #define USB0_FADDR_R (*((volatile unsigned char *)0x40050000))
# #define USB0_POWER_R (*((volatile unsigned char *)0x40050001))
# #define USB0_TXMAXP1_R (*((volatile unsigned short *)0x40050110))
#
# We deliberately do NOT assume USB0_BASE exists.
# ============================================================

all_registers = {}

for line in text.splitlines():

    match = re.search(
        r"#define\s+USB0_"
        r"([A-Za-z0-9_]+)_R\b"
        r".*?"
        r"(0x[0-9A-Fa-f]+)",
        line
    )

    if not match:
        continue

    name = match.group(1)
    address = int(match.group(2), 16)

    all_registers[name] = address


if not all_registers:
    print("No USB0 registers found", file=sys.stderr)
    sys.exit(1)


# ============================================================
# Determine USB base
#
# The base is the lowest address occupied by USB0 registers.
# It is used ONLY internally to calculate offsets.
#
# The base itself is NOT generated.
# ============================================================

usb_base = min(all_registers.values())


print(
    f"USB0 base               : 0x{usb_base:08X}",
    file=sys.stderr
)

print(
    f"USB0 registers found    : {len(all_registers)}",
    file=sys.stderr
)


# ============================================================
# Split registers into:
#
#   normal USB registers
#   endpoint registers
#
# Endpoint register form:
#
#   USB0_TXMAXP1_R
#   USB0_TXCSRL1_R
#   USB0_RXCOUNT1_R
#
# Endpoint number is the final decimal number.
# ============================================================

endpoint_registers = {}

normal_registers = {}


for name, address in all_registers.items():

    match = re.fullmatch(
        r"(.+?)(\d+)",
        name
    )

    if match:
        reg_name = match.group(1)
        ep = int(match.group(2))

        # Only treat it as endpoint register if the
        # endpoint number is in the valid USB range.
        if 0 <= ep <= 15:
            endpoint_registers[(ep, reg_name)] = address
            continue

    normal_registers[name] = address


# ============================================================
# Normal USB registers
#
# We do NOT generate FADDR.
#
# FADDR is used only indirectly as part of determining
# the USB base.
# ============================================================

normal_registers.pop("FADDR", None)


# ============================================================
# Generate normal USB register enum
# ============================================================

if normal_registers:

    print()
    print("// ============================================================")
    print("// USB registers")
    print("// ============================================================")
    print()

    print("enum class MyUSB_REG : uint8_t")
    print("{")

    for name in normal_registers:
        print(f"    {name},")

    print("};")
    print()

    print("static constexpr uint32_t USB_REGS[] =")
    print("{")

    for name, address in normal_registers.items():

        offset = address - usb_base

        print(
            f"    0x{offset:04X}, // {name}"
        )

    print("};")
    print()

    print(
        "static constexpr uint32_t USB_REG(MyUSB_REG reg)"
    )
    print("{")

    print(
        "    return USB_REGS[static_cast<uint8_t>(reg)];"
    )

    print("}")
    print()


# ============================================================
# Endpoint registers
#
# Endpoint 0 is allowed here.
#
# We collect all register names automatically from the header.
# ============================================================

endpoint_names = sorted(
    set(
        name
        for ep, name in endpoint_registers.keys()
    )
)


endpoints = sorted(
    set(
        ep
        for ep, name in endpoint_registers.keys()
    )
)


if endpoint_registers:

    print()
    print("// ============================================================")
    print("// USB endpoint registers")
    print("// ============================================================")
    print()

    print("enum class MyUSB_EP_REG : uint8_t")
    print("{")

    for name in endpoint_names:
        print(f"    {name},")

    print("};")
    print()


    # ------------------------------------------------------------
    # Address table
    # ------------------------------------------------------------

    print(
        "static constexpr uint32_t USB_EP_REGS[]["
        f"{len(endpoint_names)}] ="
    )

    print("{")

    for ep in endpoints:

        values = []

        for name in endpoint_names:

            address = endpoint_registers.get(
                (ep, name)
            )

            if address is None:

                values.append("0")

            else:

                offset = address - usb_base

                values.append(
                    f"0x{offset:04X}"
                )

        print(
            "    { "
            + ", ".join(values)
            + f" }}, // EP{ep}"
        )

    print("};")
    print()


    # ------------------------------------------------------------
    # Endpoint accessor
    #
    # MyUSB_EP already comes from gen_usb_defs.py.
    # ------------------------------------------------------------

    print(
        "static constexpr uint32_t EP_REG("
        "MyUSB_EP ep, MyUSB_EP_REG reg)"
    )

    print("{")

    print(
        "    return USB_EP_REGS["
        "static_cast<uint8_t>(ep)"
        "]["
        "static_cast<uint8_t>(reg)"
        "];"
    )

    print("}")
    print()


    # ------------------------------------------------------------
    # Individual register helpers
    # ------------------------------------------------------------

    for name in endpoint_names:

        print(
            f"static constexpr uint32_t {name}(MyUSB_EP ep)"
        )

        print("{")

        print(
            f"    return EP_REG(ep, MyUSB_EP_REG::{name});"
        )

        print("}")
        print()