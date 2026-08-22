import re
import sys
from pathlib import Path
dst = (
    Path(__file__).resolve().parent.parent.parent
    / "StellarisDefinition.hpp"
)


if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <StellarisWare>", file=sys.stderr)
    sys.exit(1)

stellarisware = Path(sys.argv[1]).resolve()
src = stellarisware / "inc" / "hw_memmap.h"

if not src.exists():
    print(f"Header not found: {src}", file=sys.stderr)
    sys.exit(1)

text = src.read_text(encoding="utf-8", errors="ignore")

pattern = re.compile(
    r'^\s*#define\s+([A-Za-z0-9_]+)_BASE\s+(0x[0-9A-Fa-f]+)',
    re.MULTILINE
)

defines = pattern.findall(text)

def fix_name(name: str) -> str:
    # убираем _BASE
    name = name.replace("_BASE", "")
    # GPIO_PORTA -> GPIOA
    name = name.replace("GPIO_PORT", "GPIO")
    return name

with open(dst, "a", encoding="utf-8") as f:
    f.write("// Auto-generated from hw_memmap.h\n\n")
    f.write("enum class MyBASE_ADDR : uint8_t\n{\n")
    for name, addr in defines:
        f.write(f"    {fix_name(name)},\n")
    f.write("};\n\n")

    f.write("static constexpr uint32_t BASE_ADDR(MyBASE_ADDR p)\n{\n")
    f.write("    constexpr uint32_t base[] = {\n")
    for name, addr in defines:
        f.write(f"        {addr}, // {name}\n")
    f.write("    };\n")
    f.write("    return base[static_cast<uint8_t>(p)];\n")
    f.write("}\n")
