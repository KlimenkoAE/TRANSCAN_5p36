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


# ============================================================
# Regular expressions
# ============================================================

ENUM_RE = re.compile(
    r"""
    typedef\s+enum
    \s*\{
        (?P<body>.*?)
    \}
    \s*(?P<name>[A-Za-z_]\w*)
    \s*;
    """,
    re.S | re.X,
)


ENUM_ITEM_RE = re.compile(
    r"""
    (?P<name>[A-Za-z_]\w*)
    \s*
    (?:
        =
        \s*
        (?P<value>
            [^,\n]+
        )
    )?
    \s*
    (?=,|$)
    """,
    re.X,
)


# ============================================================
# Parsing
# ============================================================

def parse_enums(text: str):

    result = []

    for match in ENUM_RE.finditer(text):

        body = match.group("body")
        name = match.group("name")

        items = []

        # Убираем C/C++ комментарии.
        body = re.sub(
            r"/\*.*?\*/",
            "",
            body,
            flags=re.S
        )

        body = re.sub(
            r"//.*",
            "",
            body
        )

        for item in body.split(","):

            item = item.strip()

            if not item:
                continue

            if "=" in item:

                item_name, value = item.split(
                    "=",
                    1
                )

                item_name = item_name.strip()
                value = value.strip()

                if not re.match(
                    r"^[A-Za-z_]\w*$",
                    item_name
                ):
                    continue

                items.append(
                    (item_name, value)
                )

            else:

                if not re.match(
                    r"^[A-Za-z_]\w*$",
                    item
                ):
                    continue

                items.append(
                    (item, None)
                )

        if items:
            result.append(
                (name, items)
            )

    return result


# ============================================================
# Code generation
# ============================================================

def generate(enums):

    out = []

    out.append("")
    out.append("// ============================================================")
    out.append("// CAN enums")
    out.append("// ============================================================")
    out.append("")

    for name, items in enums:

        out.append(f"enum class {name}")
        out.append("{")

        for item_name, value in items:

            if value is None:
                out.append(
                    f"    {item_name},"
                )
            else:
                out.append(
                    f"    {item_name} = {value},"
                )

        out.append("};")
        out.append("")

    return "\n".join(out)


# ============================================================
# Main
# ============================================================

def main():

    if not src.exists():
        print(
            f"CAN header not found: {src}",
            file=sys.stderr
        )
        return 2

    text = src.read_text(
        encoding="utf-8"
    )

    enums = parse_enums(text)

    if not enums:
        print(
            f"No CAN enums found in {src}",
            file=sys.stderr
        )
        return 3

    if not dst.exists():
        print(
            f"Output file not found: {dst}",
            file=sys.stderr
        )
        return 4

    generated = generate(enums)

    with dst.open(
        "a",
        encoding="utf-8"
    ) as f:
        f.write(generated)

    return 0


# ============================================================
# Entry point
# ============================================================

if __name__ == "__main__":
    raise SystemExit(main())