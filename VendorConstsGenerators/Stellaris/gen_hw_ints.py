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

src = stellarisware / "inc" / "hw_ints.h"

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
# Order is preserved exactly as in hw_ints.h.
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

faults = [
    (name, value)
    for name, value in defines
    if name.startswith("FAULT_")
]


interrupts = [
    (name, value)
    for name, value in defines
    if name.startswith("INT_")
]


special_names = {
    "NUM_INTERRUPTS",
    "NUM_PRIORITY",
    "NUM_PRIORITY_BITS",
}


special = [
    (name, value)
    for name, value in defines
    if name in special_names
]


# ============================================================
# Diagnostics
# ============================================================

print(
    f"FAULT definitions : {len(faults)}",
    file=sys.stderr
)

print(
    f"INT definitions   : {len(interrupts)}",
    file=sys.stderr
)

print(
    f"Special constants : {len(special)}",
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
        "// Interrupt definitions generated from hw_ints.h\n"
    )
    f.write(
        "// ============================================================\n\n"
    )


    # ========================================================
    # Faults
    # ========================================================

    if faults:

        f.write(
            "enum class MyFAULT : uint8_t\n"
        )

        f.write("{\n")

        for name, value in faults:

            member = name[len("FAULT_"):]

            f.write(
                f"    {member},\n"
            )

        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "FAULT(MyFAULT flag)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")

        for name, value in faults:

            f.write(
                f"        {name},\n"
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

    if interrupts:

        f.write(
            "enum class MyINT : uint8_t\n"
        )

        f.write("{\n")

        for name, value in interrupts:

            member = name[len("INT_"):]

            f.write(
                f"    {member},\n"
            )

        f.write("};\n\n")


        f.write(
            "static constexpr uint32_t "
            "INT(MyINT flag)\n"
        )

        f.write("{\n")

        f.write(
            "    constexpr uint32_t mask[] =\n"
        )

        f.write("    {\n")

        for name, value in interrupts:

            f.write(
                f"        {name},\n"
            )

        f.write("    };\n")

        f.write(
            "    return mask["
            "static_cast<uint8_t>(flag)"
            "];\n"
        )

        f.write("}\n\n")


    # ========================================================
    # Special constants
    # ========================================================

    special_names_map = {
      "NUM_INTERRUPTS": "NumInterrupts",
      "NUM_PRIORITY": "NumPriority",
      "NUM_PRIORITY_BITS": "NumPriorityBits",
    }



    for name, value in special:
      cpp_name = special_names_map[name]
      f.write(
          f"static constexpr uint32_t "
          f"{cpp_name} = {value};\n"
      )
          

    if special:
        f.write("\n")


