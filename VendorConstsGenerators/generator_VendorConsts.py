import sys
import subprocess
from pathlib import Path


if len(sys.argv) != 3:
    print("Usage: generator_VendorConsts.py <vendor> <library_path>")
    print("Targets: stellaris, stm32, atmega")
    sys.exit(1)


vendor = sys.argv[1].lower()
library_path = Path(sys.argv[2]).resolve()



generators = {
    "stellaris": [
        "gen_usb_defs.py",
        "gen_usb_regs.py",
        "gen_hw_ints.py",
        "gen_timer_dfs.py",
        "gen_hw_memmap.py",
        "gen_sysctl.py",
	"gen_can_defs.py",
        "gen_can_struct.py",
        "gen_can_enum.py",

    ],

    "stm32": [
        # "gen_usb_defs.py",
         "gen_stm32.py",
    ],

    "atmega": [
        # "gen_atmega_defs.py",
    ],
}


if vendor not in generators:
    print(f"Unknown vendor: {vendor}")
    print("Targets:", ", ".join(generators))
    sys.exit(1)


generator_root = Path(__file__).resolve().parent
project_root = generator_root.parent

vendor_dirs = {
    "stellaris": "Stellaris",
    "stm32": "STM32",
    "atmega": "ATMega",
}

generator_dir = generator_root / vendor_dirs[vendor]


#generator_dir = generator_root / vendor.capitalize()

output = project_root / f"{vendor.capitalize()}Definition.hpp"


# ------------------------------------------------------------
# Create output
# ------------------------------------------------------------

with open(output, "w", encoding="utf-8") as f:

    f.write("#pragma once\n")
    f.write("#include <cstdint>\n\n")



# ------------------------------------------------------------
# Run generators
# ------------------------------------------------------------

for generator in generators[vendor]:

    generator_path = generator_dir / generator

    print(
        f"RUN: {generator_path} {library_path}",
        file=sys.stderr
    )

    with output.open("a", encoding="utf-8") as f:

        subprocess.run(
            [
                "python3",
                str(generator_path),
                str(library_path),
            ],
            stdout=f,
            stderr=sys.stderr,
            check=True,
        )


print(f"Generated: {output}")