#!/usr/bin/env python

import cog

class typedef(object):
    def __init__(self, cpp_type, name):
        self.cpp_type = cpp_type
        self.name = name

    def out(self):
        cog.out("typedef %s %s;" % (self.cpp_type, self.name))

class const(object):
    def __init__(self, cpp_type, name, value):
        self.cpp_type = cpp_type
        self.name = name
        self.value = value

    def out(self):
        cog.out("static const %s %s = %s;" % (self.cpp_type, self.name, self.value))

def sanitizeTypename(typename):
    # Instead of sanitizing typenames we could try to sanitize variable declarations
    # by moving the array extents over to the variable name, but to do that reliably
    # we'd have to consider hairy cases like when typename is:
    #
    #    foo<double[3]>::bar[4]
    #
    # In which case we only want to move the [4], and not the [3]. we can pull only
    # array extents at the end of the type, but we'll still have to handle
    # multidimensional extents, extents with complex expressions inside them, etc.
    # I can think of an algorithm that can cover the cases I can think of, but I'm
    # not confident I can think of all the cases ;)

    # Use only for arrays, is unnecessary otherwise and makes the generated
    # code harder to read.
    if "[" in typename or "]" in typename:
        # Spaces around the %s to avoid nested templates being interpreted
        # as '>>' operator. This is fixed in C++0x.
        return "cogflect::type_passthrough< %s >::type" % typename
    return typename
