#!/usr/bin/env python

# 'object' is a C class so python doesn't let us set arbitrary
# attributes on it. We subclass it so we can just smack whatever
# we want on there.
class _object(object): pass

class GeneratorBase(object):
    def __init__(self, name, fields):
        self.name = name
        self.fields = []
        self.possible_tags = set()

        self.schema = fields[0]
        assert type(fields[0]) == list

        for column in self.schema:
            assert type(column) == str

        for row in fields[1:]:
            field = _object()
            for field_name, value in zip(self.schema, row):
                setattr(field, field_name, value)
            self.fields.append(field)

        for f in self.fields:
            if hasattr(f, "tags") and f.tags != None:
                if type(f.tags) == list:
                    self.possible_tags.update(f.tags)
                else:
                    self.possible_tags.add(f.tags)
                    f.tags = [f.tags]
            else:
                f.tags = []

            if (hasattr(f, "metadata") and f.metadata != None
                and type(f.metadata) != list):
                f.metadata = [f.metadata]
            else:
                f.metadata = []

            if not hasattr(f, "value"):
                f.value = None

            if not hasattr(f, "type"):
                f.type = None

        self.generate()

    def generate(self):
        pass

