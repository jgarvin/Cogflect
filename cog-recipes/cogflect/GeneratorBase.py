#!/usr/bin/env python

from util import verifyName, hasDupes

import cog

# 'object' is a C class so python doesn't let us set arbitrary
# attributes on it. We subclass it so we can just smack whatever
# we want on there.
class _object(object): pass

class GeneratorBase(object):
    def __init__(self, name, fields, config={}):
        self.config = config

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
                verifyName(field_name)
                setattr(field, field_name, value)
            self.fields.append(field)

        fieldNames = [f.name for f in self.fields]
        maybeDupe = hasDupes(fieldNames)
        if maybeDupe:
            cog.error("You can't specify the same field name twice. "
                      "Name specified twice: " + maybeDupe)

        for f in self.fields:
            if hasattr(f, "tags") and f.tags != None:
                if type(f.tags) == list:
                    maybeDupe = hasDupes(f.tags)
                    if maybeDupe:
                        cog.error("You can't specify the same tag twice "
                                  " on the same field. "
                                  "Tag specified twice: " + maybeDupe +
                                  " on field: " + f.name)
                    self.possible_tags.update(f.tags)
                elif type(f.tags) == set:
                    self.possible_tags.update(f.tags)
                else:
                    self.possible_tags.add(f.tags)
                    f.tags = [f.tags]
            else:
                f.tags = []

            for t in f.tags:
                verifyName(t)

            if not hasattr(f, "metadata") or f.metadata == None:
                f.metadata = []
            elif type(f.metadata) == list:
                metaNames = [m.name for m in f.metadata]
                maybeDupe = hasDupes(metaNames)
                if maybeDupe:
                    cog.error("You can't specify metadata with the same "
                              "name twice. Name specified twice: " +
                              maybeDupe + " on field: " + f.name)
            else:
                f.metadata = [f.metadata]

            if not hasattr(f, "value"):
                f.value = None

            if not hasattr(f, "type"):
                f.type = None

        self.generate()

    def generate(self):
        pass

