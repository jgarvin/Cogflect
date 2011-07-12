#!/usr/bin/env python

import cog

def hasDupes(collection):
    contents = set()
    for i in collection:
        if i in contents:
            return i
        contents.add(i)

    return False

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

def indent(s, n):
    result = []
    for line in s.split("\n"):
        result.append((' ' * n) + line)

    return "\n".join(result)

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

def verifyName(name):
    "Protects against use of invalid variable names."

    # TODO: Whitespace/empty check
    if name == "":
        cog.error("Empty strings cannot be used for names.")

    if name.isspace():
        cog.error("Names must include non-whitespace characters.")

    prohibited = ["and", "and_eq",
                  "alignas", "alignof", "asm", "auto", "bitand", "bitor", "bool", "break",
                  "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const",
                  "constexpr", "const_cast", "continue", "decltype", "default", "delete", "double", "dynamic_cast",
                  "else", "enum", "explicit", "export", "extern", "false", "float", "for",
                  "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace",
                  "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq",
                  "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed",
                  "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this",
                  "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union",
                  "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor",
                  "xor_eq"]

    if name in prohibited:
        cog.error("Cannot use \"%s\" as a name. It is a C++ keyword. "
                  "Did you accidentally swap the type and name arguments? "
                  "Names cannot be be C++ keywords, they must follow C++ "
                  "variable name rules." % name)

    if name[0].isdigit():
        cog.error("Cannot use \"%s\" as a name. Names cannot start with a digit, "
                  "they must follow C++ variable name rules." % name)

    if name[0] == "_":
        cog.error("Cannot use \"%s\" as a name. Names cannot start with an underscore, "
                  "they must follow C++ variable name rules." % name)

    if not name.isalnum():
        cog.error("Cannot use \"%s\" as a name. Names must be alphanumeric." % name)


