#!/usr/bin/env python

from cogflect.util import typedef, const

# First list entry defines the schema
# typedef/const use the same order of arguments as C++

fields = [
    ["name",        "value",     "type",    "tags",            "metadata"],
    ["SHOE_PRICE",   15,          "double",  ["key", "price"],  typedef("float", "serial_type")],
    ["GUM_PRICE",    23,          "double",  ["key", "price"]],
    ["CAR_PRICE",    42,          "int",     ["key", "price"],  const("unsigned", "foo", 3)]
    ]
