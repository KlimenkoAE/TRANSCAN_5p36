#!/usr/bin/env python3

import re
import sys
from pathlib import Path


# ============================================================
# Arguments
# ============================================================

if len(sys.argv) != 2:
    print(
        f"Usage: {sys.argv[0]} <StellarisWare>",
        file=sys.stderr
    )
    sys.exit(1)


stellarisware = Path(sys.argv[1]).resolve()

src = stellarisware / "driverlib" / "usb.h"

dst = (
    Path(__file__).resolve().parent.parent.parent
    / "StellarisDefinition.hpp"
)


# ============================================================
# Read source
# ============================================================

if not src.exists():
    print(
        f"Header not found: {src}",
        file=sys.stderr
    )
    sys.exit(1)


text = src.read_text(
    encoding="utf-8",
    errors="ignore"
)


# ============================================================
# Read all numeric #define
#
# Order is preserved exactly as in usb.h.
# ============================================================

defines = []

pattern = re.compile(
    r'^\s*#define\s+'
    r'([A-Za-z0-9_]+)'
    r'\s+'
    r'(0x[0-9A-Fa-f]+|[0-9]+)'
    r'(?:\s|$)',
    re.MULTILINE
)


for name, value in pattern.findall(text):

    defines.append(
        (
            name,
            value
        )
    )


define_map = dict(defines)


# ============================================================
# Helpers
# ============================================================

def group_by_prefix(prefix):
    """
    Return all definitions beginning with prefix,
    preserving the order from usb.h.
    """

    return [
        (name, value)
        for name, value in defines
        if name.startswith(prefix)
    ]


def enum_member(name, prefix, member_prefix=""):
    """
    Remove the group prefix and optionally add another prefix.

    Example:

        USB_FIFO_SZ_2048_DB
        prefix = USB_FIFO_SZ_
        member_prefix = SZ_

        result:
        SZ_2048_DB
    """

    return (
        member_prefix
        + name[len(prefix):]
    )


def write_enum_group(
    f,
    enum_name,
    function_name,
    prefix,
    definitions,
    member_prefix=""
):
    """
    Generate:

        enum class MyUSB_... : uint8_t
        {
            ...
        };

        static constexpr uint32_t FUNC(...)
        {
            constexpr uint32_t mask[] =
            {
                ...
            };

            return mask[...];
        }
    """

    if not definitions:
        return


    f.write(
        f"enum class {enum_name} : uint8_t\n"
    )

    f.write("{\n")


    for name, value in definitions:

        member = enum_member(
            name,
            prefix,
            member_prefix
        )

        f.write(
            f"    {member},\n"
        )


    f.write("};\n\n")


    f.write(
        f"static constexpr uint32_t "
        f"{function_name}({enum_name} flag)\n"
    )

    f.write("{\n")

    f.write(
        "    constexpr uint32_t mask[] =\n"
    )

    f.write("    {\n")


    for name, value in definitions:

        f.write(
            f"        {name},\n"
        )


    f.write("    };\n")

    f.write(
        "    return mask[static_cast<uint8_t>(flag)];\n"
    )

    f.write("}\n\n")


# ============================================================
# Endpoint numbers
#
# USB_EP_0 ... USB_EP_15
# ============================================================

ep_definitions = []

for name, value in defines:

    match = re.fullmatch(
        r"USB_EP_(\d+)",
        name
    )

    if match:

        ep_definitions.append(
            (
                int(match.group(1)),
                name,
                value
            )
        )


ep_definitions.sort(
    key=lambda item: item[0]
)


# ============================================================
# Device IN endpoint interrupt masks
#
# USB_INTEP_0
# USB_INTEP_DEV_IN_1 ... 15
# ============================================================

ep_in = []


if "USB_INTEP_0" in define_map:

    ep_in.append(
        (
            0,
            "USB_INTEP_0"
        )
    )


for name, value in defines:

    match = re.fullmatch(
        r"USB_INTEP_DEV_IN_(\d+)",
        name
    )

    if match:

        ep_in.append(
            (
                int(match.group(1)),
                name
            )
        )


ep_in.sort(
    key=lambda item: item[0]
)


# ============================================================
# Device OUT endpoint interrupt masks
#
# USB_INTEP_0
# USB_INTEP_DEV_OUT_1 ... 15
# ============================================================

ep_out = []


if "USB_INTEP_0" in define_map:

    ep_out.append(
        (
            0,
            "USB_INTEP_0"
        )
    )


for name, value in defines:

    match = re.fullmatch(
        r"USB_INTEP_DEV_OUT_(\d+)",
        name
    )

    if match:

        ep_out.append(
            (
                int(match.group(1)),
                name
            )
        )


ep_out.sort(
    key=lambda item: item[0]
)


# ============================================================
# INTCTRL
# ============================================================

intctrl = group_by_prefix(
    "USB_INTCTRL_"
)


# ============================================================
# EP_CFG
#
# USB_EP_0 ... USB_EP_15 are endpoint numbers,
# therefore they are excluded from EP_CFG.
# ============================================================

ep_cfg = [
    (name, value)
    for name, value in defines
    if name.startswith("USB_EP_")
    and not re.fullmatch(
        r"USB_EP_\d+",
        name
    )
]


# ============================================================
# FIFO sizes
# ============================================================

fifo_size = group_by_prefix(
    "USB_FIFO_SZ_"
)


# ============================================================
# Transfer types
# ============================================================

trans = group_by_prefix(
    "USB_TRANS_"
)


# ============================================================
# Speed
#
# The source names are:
#
# USB_UNDEF_SPEED
# USB_FULL_SPEED
# USB_LOW_SPEED
# ============================================================

speed = []

for name, value in defines:

    if name in (
        "USB_UNDEF_SPEED",
        "USB_FULL_SPEED",
        "USB_LOW_SPEED",
    ):

        speed.append(
            (name, value)
        )


# ============================================================
# Endpoint status
# ============================================================

ep_status = group_by_prefix(
    "USB_DEV_"
)


# ============================================================
# USB interrupt masks
# ============================================================

usb_int = group_by_prefix(
    "USB_INT_"
)


# ============================================================
# Generate
# ============================================================

with open(
    dst,
    "a",
    encoding="utf-8"
) as f:

    f.write("\n")

    f.write(
        "// ============================================================\n"
    )

    f.write(
        "// USB definitions generated from usb.h\n"
    )

    f.write(
        "// ============================================================\n\n"
    )


    # ========================================================
    # MyUSB_EP
    # ========================================================

    if ep_definitions:

        f.write(
            "enum class MyUSB_EP : uint8_t\n"
        )

        f.write("{\n")


        for number, name, value in ep_definitions:

            f.write(
                f"    EP{number},\n"
            )


        f.write("};\n\n")


        # ----------------------------------------------------
        # Endpoint()
        # ----------------------------------------------------

        f.write(
            "static constexpr uint32_t "
            "Endpoint(MyUSB_EP ep)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")


        for number, name, value in ep_definitions:

            f.write(
                f"        {name},\n"
            )


        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(ep)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # INTEP_IN
    # ========================================================

    if ep_in:

        f.write(
            "static constexpr uint32_t "
            "INTEP_IN(MyUSB_EP ep)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")


        for number, name in ep_in:

            f.write(
                f"        {name},\n"
            )


        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(ep)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # INTEP_OUT
    # ========================================================

    if ep_out:

        f.write(
            "static constexpr uint32_t "
            "INTEP_OUT(MyUSB_EP ep)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")


        for number, name in ep_out:

            f.write(
                f"        {name},\n"
            )


        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(ep)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # INTCTRL
    # ========================================================

    write_enum_group(
        f,
        "MyUSB_INTCTRL",
        "INTCTRL",
        "USB_INTCTRL_",
        intctrl
    )


    # ========================================================
    # EP_CFG
    # ========================================================

    write_enum_group(
        f,
        "MyUSB_EP_CFG",
        "EP_CFG",
        "USB_EP_",
        ep_cfg
    )


    # ========================================================
    # FIFO_SIZE
    #
    # USB_FIFO_SZ_8
    #       ->
    # MyUSB_FIFO_SIZE::SZ_8
    # ========================================================

    write_enum_group(
        f,
        "MyUSB_FIFO_SIZE",
        "FIFO_SIZE",
        "USB_FIFO_SZ_",
        fifo_size,
        member_prefix="SZ_"
    )


    # ========================================================
    # TRANS
    # ========================================================

    write_enum_group(
        f,
        "MyUSB_TRANS",
        "TRANS",
        "USB_TRANS_",
        trans
    )


    # ========================================================
    # SPEED
    # ========================================================

    if speed:

        f.write(
            "enum class MyUSB_SPEED : uint8_t\n"
        )

        f.write("{\n")


        for name, value in speed:

            if name == "USB_UNDEF_SPEED":
                member = "UNDEF"

            elif name == "USB_FULL_SPEED":
                member = "FULL"

            elif name == "USB_LOW_SPEED":
                member = "LOW"

            else:
                continue


            f.write(
                f"    {member},\n"
            )


        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "SPEED(MyUSB_SPEED speed)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")


        for name, value in speed:

            f.write(
                f"        {name},\n"
            )


        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(speed)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # EP_STATUS
    # ========================================================

    write_enum_group(
        f,
        "MyUSB_EP_STATUS",
        "EP_STATUS",
        "USB_DEV_",
        ep_status
    )


    # ========================================================
    # INT
    # ========================================================

    write_enum_group(
        f,
        "MyUSB_INT",
        "INT",
        "USB_INT_",
        usb_int
    )


# ============================================================
# Diagnostics
# ============================================================

print(
    f"USB definitions : {len(defines)}",
    file=sys.stderr
)

print(
    f"Endpoints       : {len(ep_definitions)}",
    file=sys.stderr
)

print(
    f"Device IN       : {len(ep_in)}",
    file=sys.stderr
)

print(
    f"Device OUT      : {len(ep_out)}",
    file=sys.stderr
)

print(
    f"INTCTRL         : {len(intctrl)}",
    file=sys.stderr
)

print(
    f"EP_CFG          : {len(ep_cfg)}",
    file=sys.stderr
)

print(
    f"FIFO_SIZE       : {len(fifo_size)}",
    file=sys.stderr
)

print(
    f"TRANS           : {len(trans)}",
    file=sys.stderr
)

print(
    f"SPEED           : {len(speed)}",
    file=sys.stderr
)

print(
    f"EP_STATUS       : {len(ep_status)}",
    file=sys.stderr
)

print(
    f"INT             : {len(usb_int)}",
    file=sys.stderr
)