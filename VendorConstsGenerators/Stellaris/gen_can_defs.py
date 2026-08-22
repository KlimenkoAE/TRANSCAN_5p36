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
    # если имя начинается с цифры — добавляем префикс T
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
# Read numeric #define
#
# Order is preserved exactly as in timer.h
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
    defines.append((name, value))




# ============================================================
# Groups
# ============================================================

msg = [
    (name, value)
    for name, value in defines
    if name.startswith("MSG_")
]


can = [
    (name, value)
    for name, value in defines
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
    f"CAN definitions   : {len(can)}",
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
    # Timer
    # ========================================================

    if msg:

        f.write(
            "enum class MyCAN_MSG : uint8_t\n"
        )

        f.write("{\n")

        for name, value in msg:

            member = name[len("MSG_"):]
        #    if member == "DEBUG":
        #        member = "DBG"
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

        for name, value in msg:

            f.write(
                f"        {value},\n"
            )

        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(flag)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # Interrupts
    #
    # IMPORTANT:
    # We do not split INT_* by peripheral here.
    # The generated layer only mirrors hw_ints.h.
    # Semantic mapping is done manually in
    # StellarisDefinitionView.hpp.
    # ========================================================

    if can:

        f.write(
            "enum class MyCAN : uint8_t\n"
        )

        f.write("{\n")

        for name, value in can:

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

        for name, value in can:

            f.write(
                f"        {value},\n"
            )

        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(flag)"
            "];\n"
        )

        f.write("}\n\n")

