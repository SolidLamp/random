#!/usr/bin/env python3

import sys
from ctypes import *

emulator = CDLL("./lmc.so")

KEYWORDS: dict[str, str] = {
    "ADD": "1",
    "SUB": "2",
    "STA": "3",
    "LDA": "5",
    "BRA": "6",
    "BRZ": "7",
    "BRP": "8",
    "INP": "901",
    "OUT": "902",
    "HLT": "000",
    "DAT": "000",
}

identifiers: dict[str, int] = {}


def main() -> int:
    text: str = ""
    with open("program.asm") as f:
        text: str = f.read()
    lines: list[str] = text.split("\n")
    for i in range(len(lines)):
        handleidenifiers(lines[i].upper(), i)
    assembled: list[int] = []
    errors: list[str] = []
    for i in range(len(lines)):
        line: str = lines[i]
        asm = assembleline(line.upper())
        if isinstance(asm, int):
            assembled.append(asm)
        elif isinstance(asm, str):
            errors.append(f"Error on line {i}: {asm}")
    if errors:
        print(errors)
        return 1
    else:
        print(assembled)
        arr = (c_uint16 * len(assembled))(*assembled)
        emulator.run_cpu(arr, len(assembled))
        return 0


def handleidenifiers(line: str, index: int):
    words: list[str] = line.split(" ")
    if words:
        identifier: str = words[0]
    else:
        return False
    if identifier in KEYWORDS.keys():
        return False
    else:
        identifiers.update({identifier: index})
        return True


def assembleline(line: str) -> None | int | str:
    """Assembles LMC assembly to code.

    Args:
        line (str): The line of assembly to assemble.

    Returns:
        None | int | str:
            If None, the input was a blank line; nothing to compile.
            If int, the assembly has been successfully assembled, as an int.
            If str, an error was encountered - this is the error encountered.
    """
    words: list[str] = line.split(" ")
    if not words or words[0] == "" or words[0] == " ":
        return None
    if words[0] in identifiers:
        words.pop(0)
    if not words:
        return "No instruction but identifier specified."
    if words[0].upper() not in KEYWORDS:
        return f"Keyword {words[0]} is invalid."
    instruction: str = ""
    instruction += KEYWORDS[words[0].upper()]
    words.pop(0)
    if len(instruction) == 3:
        return int(instruction)
    if not words:
        return f"Keyword {words[0]} takes operand - none given."
    if words[0] in identifiers:
        operand = identifiers[words[0]]
    else:
        try:
            operand = int(words[0])
        except:
            return "Non-integer operand."
    operand = str(operand % 99)
    return int(instruction + operand)


if __name__ == "__main__":
    exit_code: int = main()
    sys.exit(exit_code)
