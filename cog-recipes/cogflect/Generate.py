import cogflect.common
from cogflect.Enum import Enum
from cogflect.CppClass import CppClass

class Generate(object):
    def __init__(self, name, fields):
        self.name = name
        self.fields = fields

        self.generated_common = False

    def _common(self):
        if self.generated_common:
            return

        cogflect.common.generate()
        self.generated_common = True

    def enum():
        Enum(self.name, self.fields)

    def class():
        CppClass(self.name, self.fields)
