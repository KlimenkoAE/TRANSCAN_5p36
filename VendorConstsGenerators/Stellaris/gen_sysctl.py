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

src = stellarisware / "driverlib" / "sysctl.h"

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
    preserving the order from sysctl.h.
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

        static constexpr uint32_t FUNC_TABLE[] =
        {
            ...
        };

        static constexpr uint32_t FUNC(MyUSB_... flag)
        {
            return FUNC_TABLE[static_cast<uint8_t>(flag)];
        }
    """

    if not definitions:
        return




    # --------------------------------------------------------
    # enum
    # --------------------------------------------------------

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


    # --------------------------------------------------------
    # Public constexpr table
    # --------------------------------------------------------

    f.write(
        f"static constexpr uint32_t "
        f"{function_name}_TABLE[] =\n"
    )

    f.write("{\n")


    for name, value in definitions:

        f.write(
            f"    {value},//{name}\n"
        )


    f.write("};\n\n")


    # --------------------------------------------------------
    # Accessor
    # --------------------------------------------------------

    f.write(
        f"static constexpr uint32_t "
        f"{function_name}({enum_name} flag)\n"
    )

    f.write("{\n")

    f.write(
        f"    return {function_name}_TABLE["
        f"static_cast<uint8_t>(flag)"
        f"];\n"
    )

    f.write("}\n\n")

#*****************************************************************************
#
# The following are values that can be passed to the
# SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
# SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
# ulPeripheral parameter.  The peripherals in the fourth group (upper nibble
# is 3) can only be used with the SysCtlPeripheralPresent() API.
#
#*****************************************************************************

import re

def get_enum_group(enum_group, prefix, definitions, cut_prefix=""):
    for name, value in definitions:
        # регулярка с f-string
        match = re.fullmatch(fr"{prefix}[A-Za-z0-9_]+", name)
        if match:
            # убираем префикс cut_prefix
            member = name[len(cut_prefix):]
            enum_group.append((member, value))

    # сортировка по имени
    enum_group.sort(key=lambda item: item[0])

def write_enum_group(f, in_arr, enum_name, getter_name):
    """
    f          — файловый объект для записи
    enum_name  — имя enum (например "MyPERIPH")
    getter_name — имя функции (например "PERIPH")
    peripheral — список [(member, value), ...]
    """

    if not in_arr:
        return

    # enum
    f.write(f"enum class {enum_name} : uint8_t\n")
    f.write("{\n")
    for member, _ in in_arr:
        f.write(f"    {member},\n")
    f.write("};\n\n")

    # таблица
    f.write(f"static constexpr uint32_t {getter_name}_TABLE[] =\n")
    f.write("{\n")
    for member, value in in_arr:
        f.write(f"    {value}, // {member}\n")
    f.write("};\n\n")

    # accessor
    f.write(f"static constexpr uint32_t {getter_name}({enum_name} flag)\n")
    f.write("{\n")
    f.write(f"    return {getter_name}_TABLE[static_cast<uint8_t>(flag)];\n")
    f.write("}\n\n")

peripheral = []

get_enum_group(peripheral,"SYSCTL_PERIPH",defines,"SYSCTL_")

pin = []
get_enum_group(pin,"SYSCTL_PIN",defines,"SYSCTL_")

ldocfg = []
get_enum_group(ldocfg,"SYSCTL_LDOCFG",defines,"SYSCTL_")

ldo = []
get_enum_group(ldo,"SYSCTL_LDO",defines,"SYSCTL_")

int = []
get_enum_group(int,"SYSCTL_INT",defines,"SYSCTL_")

cause = []
get_enum_group(cause,"SYSCTL_CAUSE",defines,"SYSCTL_")

bor = []
get_enum_group(bor,"SYSCTL_BOR",defines,"SYSCTL_")

pwm_div = []
get_enum_group(pwm_div,"SYSCTL_PWM_DIV",defines,"SYSCTL_")

adc_speed = []
get_enum_group(adc_speed,"SYSCTL_ADC_SPEED",defines,"SYSCTL_")

xtal = []
get_enum_group(xtal,"SYSCTL_XTAL",defines,"SYSCTL_")

osc = []
get_enum_group(osc,"SYSCTL_OSC",defines,"SYSCTL_")

dslp = []
get_enum_group(dslp,"SYSCTL_DSLP",defines,"SYSCTL_")

int_osc = []
get_enum_group(int_osc,"SYSCTL_INT_OSC",defines,"SYSCTL_")

main_osc = []
get_enum_group(main_osc,"SYSCTL_MAIN_OSC",defines,"SYSCTL_")

use = []
get_enum_group(use,"SYSCTL_USE",defines,"SYSCTL_")


    # ========================================================
    # writer
    # ========================================================

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
        "// SYSCTL definitions generated from sysctl.h\n"
    )

    f.write(
        "// ============================================================\n\n"
    )


    write_enum_group(f,peripheral,"MyPERIPH","PERIPH")

    write_enum_group(f,pin,"MyPIN","PIN")

    write_enum_group(f,ldocfg,"MyLDOCFG","LDOCFG")

    write_enum_group(f,ldo,"MyLDO","LDO")

    write_enum_group(f,int,"MySYSCTL_INT","SYSCTL_INT")

    write_enum_group(f,cause,"MyCAUSE","CAUSE")

    write_enum_group(f,bor,"MyBOR","MyBOR")

    write_enum_group(f,pwm_div,"MyPWM_DIV","PWM_DIV")

    write_enum_group(f,adc_speed,"MyADC_SPEED","ADC_SPEED")

    write_enum_group(f,xtal,"MyXTAL","XTAL")

    write_enum_group(f,osc,"MyOSC","OSC")

    write_enum_group(f,dslp,"MyDSLP","DSLP")

    write_enum_group(f,int_osc,"MyINT_OSC","INT_OSC")

    write_enum_group(f,main_osc,"MyMAIN_OSC","MAIN_OSC")

    write_enum_group(f,use,"MyUSE","USE")


