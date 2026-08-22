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

src = stellarisware / "driverlib" / "timer.h"

dst = (
    Path(__file__).resolve().parent.parent.parent
    / "StellarisDefinition.hpp"
)
def fix_enum_name(name: str) -> str:
    # если имя начинается с цифры — добавляем префикс T
    if name[0].isdigit():
        return "T" + name
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

timer = [
    (name, value)
    for name, value in defines
    if name.startswith("TIMER_")
]


wtimer = [
    (name, value)
    for name, value in defines
    if name.startswith("WTIMER_")
]

# ============================================================
# Diagnostics
# ============================================================

print(
    f"TIMER definitions : {len(timer)}",
    file=sys.stderr
)

print(
    f"WTIMER definitions   : {len(wtimer)}",
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
        "// Timer definitions generated from timer.h\n"
    )
    f.write(
        "// ============================================================\n\n"
    )


    # ========================================================
    # Timer
    # ========================================================

    if timer:

        f.write(
            "enum class MyTIMER : uint8_t\n"
        )

        f.write("{\n")

        for name, value in timer:

            member = name[len("TIMER_"):]
            if member == "DEBUG":
                member = "DBG"
            f.write(
                f"    {fix_enum_name(member)},\n"
            )

        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "TIMER(MyTIMER flag)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")

        for name, value in timer:

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

    if wtimer:

        f.write(
            "enum class MyWTIMER : uint8_t\n"
        )

        f.write("{\n")

        for name, value in wtimer:

            member = name[len("WTIMER_"):]

            f.write(
                f"    {fix_enum_name(member)},\n"
            )

        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "WTIMER(MyWTIMER flag)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")

        for name, value in wtimer:

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




