#!/usr/bin/env python3

import re
import sys
from pathlib import Path


if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <StellarisWare>")
    sys.exit(1)


stellarisware = Path(sys.argv[1]).resolve()

src = stellarisware / "inc" / "lm3s5p36.h"

dst = (
    Path(__file__).resolve().parent.parent.parent
    / "StellarisDefinition.hpp"
)


with open(src, encoding="utf-8") as f:
    text = f.read()


# ------------------------------------------------------------
# USB0 registers
#
# USB0_FADDR_R is the first register and defines offset 0.
# The FADDR register itself is not placed into the table.
# ------------------------------------------------------------

pattern = re.compile(
    r'#define\s+'
    r'(USB0_\w+_R)\s+'
    r'.*?'
    r'(0x[0-9A-Fa-f]+)',
    re.MULTILINE
)


regs = pattern.findall(text)


print(f"USB registers   : {len(regs)}")


if not regs:
    print("No USB0 registers found")
    sys.exit(1)


# First register = base address.
# We deliberately do not use USB0_BASE.

base = int(regs[0][1], 16)

print(f"USB register base: 0x{base:08X}")


# ------------------------------------------------------------
# Generate
# ------------------------------------------------------------

with open(dst, "a", encoding="utf-8") as f:

    f.write("\n")
    f.write("// ============================================================\n")
    f.write("// USB registers generated from lm3s5p36.h\n")
    f.write("// ============================================================\n\n")

    # --------------------------------------------------------
    # enum
    # --------------------------------------------------------

    f.write("enum class USB_REGS : uint8_t\n")
    f.write("{\n")

    for name, address in regs[1:]:
        short = name[5:-2]       # USB0_FADDR_R -> FADDR
        f.write(f"    {short},\n")

    f.write("};\n\n")

    # --------------------------------------------------------
    # USB_REG()
    # --------------------------------------------------------

    f.write("static constexpr uint32_t USB_REG(USB_REGS ur)\n")
    f.write("{\n")

    f.write("    constexpr uint32_t mask[] =\n")
    f.write("    {\n")

    for name, address in regs[1:]:
        offset = int(address, 16) - base
        f.write(f"        0x{offset:08X},\n")

    f.write("    };\n\n")

    f.write("    return mask[static_cast<uint8_t>(ur)];\n")

    f.write("}\n")


print(f"Generated: {dst}")