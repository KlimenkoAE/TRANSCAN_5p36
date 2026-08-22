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
# Type conversion
# ============================================================

TYPE_MAP = {
    "unsigned long": "uint32_t",
    "unsigned int": "uint32_t",
    "unsigned short": "uint16_t",
    "unsigned char": "uint8_t",
    "unsigned char *": "uint8_t*",
    "char *": "char*",
    "void *": "void*",
}


def normalize_type(type_name: str) -> str:
    type_name = re.sub(r"\s+", " ", type_name.strip())

    if type_name in TYPE_MAP:
        return TYPE_MAP[type_name]

    raise ValueError(f"Unknown type: {type_name}")


# ============================================================
# Regular expressions
# ============================================================

STRUCT_RE = re.compile(
    r"""
    typedef\s+struct
    \s*\{
        (?P<body>.*?)
    \}
    \s*(?P<name>[A-Za-z_]\w*)
    \s*;
    """,
    re.S | re.X,
)


FIELD_RE = re.compile(
    r"""
    ^\s*
    (?P<type>
        unsigned\s+char\s*\* |
        unsigned\s+long |
        unsigned\s+int |
        unsigned\s+short |
        unsigned\s+char |
        char\s*\* |
        void\s*\*
    )
    \s+
    (?P<name>[A-Za-z_]\w*)
    \s*;
    """,
    re.M | re.X,
)


# ============================================================
# Parsing
# ============================================================

def parse_structs(text: str):
    result = []

    for match in STRUCT_RE.finditer(text):

        body = match.group("body")
        name = match.group("name")

        fields = []

        for field in FIELD_RE.finditer(body):

            field_type = normalize_type(
                field.group("type")
            )

            field_name = field.group("name")

            fields.append(
                (field_type, field_name)
            )

        if fields:
            result.append(
                (name, fields)
            )

    return result


# ============================================================
# Code generation
# ============================================================

def generate(structs):

    out = []

    out.append("")
    out.append("// ============================================================")
    out.append("// CAN structures")
    out.append("// ============================================================")
    out.append("")

    for name, fields in structs:

        out.append(f"struct {name}")
        out.append("{")

        for field_type, field_name in fields:
            out.append(
                f"    {field_type} {field_name};"
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

    structs = parse_structs(text)

    if not structs:
        print(
            f"No CAN structs found in {src}",
            file=sys.stderr
        )
        return 3

    if not dst.exists():
        print(
            f"Output file not found: {dst}",
            file=sys.stderr
        )
        return 4

    generated = generate(structs)

    with dst.open(
        "a",
        encoding="utf-8"
    ) as f:
        f.write(generated)

 #   print(
 #       f"Appended CAN structs to {dst}"
 #   )

 #   for name, fields in structs:
 #       print(
 #           f"  {name}: {len(fields)} fields"
  #      )

    return 0


# ============================================================
# Entry point
# ============================================================

if __name__ == "__main__":
    raise SystemExit(main())