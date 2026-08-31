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

src = stellarisware / "driverlib" / "can.h"

dst = (
    Path(__file__).resolve().parent.parent.parent
    / "StellarisDefinition.hpp"
)


def fix_enum_name(name: str) -> str:
    # если имя начинается с цифры — добавляем префикс C
    if name[0].isdigit():
        return "C" + name

    return name


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
# Remove deprecated section
#
# Everything after:
#
# #ifndef DEPRECATED
#
# is ignored.
# ============================================================

match = re.search(
    r'^\s*#ifndef\s+DEPRECATED\b',
    text,
    re.MULTILINE
)

if match:
    text = text[:match.start()]


# ============================================================
# Read #define
#
# Order is preserved exactly as in can.h
# ============================================================

defines = []

pattern = re.compile(
    r'^\s*#define\s+'
    r'([A-Za-z0-9_]+)'
    r'\s+'
    r'(\(?)'
    r'(0?x?)'
    r'([0-9A-Za-z|\s_]+\)?)'
    r'(?:\s|$)',
    re.MULTILINE
)

for name, pref1, pref2, value in pattern.findall(text):
    defines.append((name, pref1, pref2, value))


# ============================================================
# Define map
#
# Used for expanding references such as:
#
# MSG_OBJ_STATUS_MASK
#     -> (MSG_OBJ_NEW_DATA | MSG_OBJ_DATA_LOST)
#     -> (0x00000080 | 0x00000100)
#
# ============================================================

define_map = {
    name: f"{pref1}{pref2}{value}".strip()
    for name, pref1, pref2, value in defines
}


def expand_macros(value: str, seen=None) -> str:
    """
    Recursively expand #define references.

    Example:

        (MSG_OBJ_NEW_DATA | MSG_OBJ_DATA_LOST)

    becomes:

        (0x00000080 | 0x00000100)
    """

    if seen is None:
        seen = set()

    def replace(match):
        name = match.group(0)

        # Это не наш #define — оставляем как есть.
        if name not in define_map:
            return name

        # Защита от циклических define.
        if name in seen:
            return name

        return expand_macros(
            define_map[name],
            seen | {name}
        )

    return re.sub(
        r'\b[A-Za-z_][A-Za-z0-9_]*\b',
        replace,
        value
    )


# ============================================================
# Groups
# ============================================================

msg = [
    (name, pref1, pref2, value)
    for name, pref1, pref2, value in defines
    if name.startswith("MSG_")
]


can = [
    (name, pref1, pref2, value)
    for name, pref1, pref2, value in defines
    if name.startswith("CAN_")
]


# ============================================================
# Diagnostics
# ============================================================

print(
    f"CAN_MSG definitions : {len(msg)}",
    file=sys.stderr
)

print(
    f"CAN definitions     : {len(can)}",
    file=sys.stderr
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
        "// CAN definitions generated from can.h\n"
    )
    f.write(
        "// ============================================================\n\n"
    )


    # ========================================================
    # MSG
    # ========================================================

    if msg:

        f.write(
            "enum class MyCAN_MSG : uint8_t\n"
        )

        f.write("{\n")

        for name, pref1, pref2, value in msg:

            member = name[len("MSG_"):]

            f.write(
                f"    {fix_enum_name(member)},\n"
            )

        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "CAN_MSG(MyCAN_MSG flag)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")

        for name, pref1, pref2, value in msg:

            original_value = f"{pref1}{pref2}{value}".strip()

            expanded = expand_macros(
                original_value
            )

            f.write(
                f"        {expanded},//{name}\n"
            )

        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(flag)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # CAN
    #
    # We do not split CAN_* by peripheral here.
    # The generated layer only mirrors can.h.
    # ========================================================

    if can:

        f.write(
            "enum class MyCAN : uint8_t\n"
        )

        f.write("{\n")

        for name, pref1, pref2, value in can:

            member = name[len("CAN_"):]

            f.write(
                f"    {fix_enum_name(member)},\n"
            )

        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "CAN(MyCAN flag)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")

        for name, pref1, pref2, value in can:

            original_value = f"{pref1}{pref2}{value}".strip()

            expanded = expand_macros(
                original_value
            )

            f.write(
                f"        {expanded},//{name}\n"
            )

        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(flag)"
            "];\n"
        )

        f.write("}\n\n")