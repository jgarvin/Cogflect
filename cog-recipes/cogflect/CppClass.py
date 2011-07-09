#!/usr/bin/env python

from cogflect.GeneratorBase import GeneratorBase
from cogflect.common import generate_cppclass_common
from cogflect.util import sanitizeTypename, indent
import cog

_body = """
    typedef %(name)s::type enum_type;

    // TODO: iterate public/protected/private independently?
    // TODO: iterate over members with a tag? <-- public/protected/private tags
    // TODO: tag to indicate reflection is available

    template<typename T>
    typename T::type& get_member();

    template<typename T>
    typename T::type const& get_member() const;

    template<unsigned index>
    typename %(name)s::info_index<index>::type& get_indexed_member()
    {
        return get_member< info_index<index> >();
    }

    template<unsigned index>
    typename %(name)s::info_index<index>::type const& get_indexed_member() const
    {
        return get_member< info_index<index> >();
    }

    template<typename Processor>
    inline void get_runtime_member(Processor& p, type value)
    {
        cogflect::pass_member_action<Processor, data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor const& p, type value)
    {
        cogflect::pass_member_action<const Processor, data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor& p, type value) const
    {
        cogflect::pass_member_action<Processor, const data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_member(Processor const& p, type value) const
    {
        cogflect::pass_member_action<const Processor, const data> tmp(p, *this);
        value.switcher(tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor& p, unsigned index)
    {
        cogflect::pass_member_action<Processor, data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor& p, unsigned index) const
    {
        cogflect::pass_member_action<Processor, const data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor const& p, unsigned index)
    {
        cogflect::pass_member_action<const Processor, data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<typename Processor>
    inline void get_runtime_indexed_member(Processor const& p, unsigned index) const
    {
        cogflect::pass_member_action<const Processor, const data> tmp(p, *this);
        type::index_switcher(index, tmp);
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT& visitor)
    {
%(forAllMembersBody)s
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT& visitor) const
    {
%(forAllMembersBody)s
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT const& visitor)
    {
%(forAllMembersBody)s
    }

    template<class VisitorT>
    inline void for_all_members(VisitorT const& visitor) const
    {
%(forAllMembersBody)s
    }

    template<class TargetType>
    inline void shape_assign(TargetType const& other)
    {
        cogflect::shape_assign<data, TargetType> visitor;
        for_all_members(visitor);
    }


"""

class CppClass(GeneratorBase):
    def __init__(self, name, fields, config={}):
        GeneratorBase.__init__(self, name, fields, config)

    def __gen_for_all_members(self):
        calls = []

        call_template = ("visitor.\n"
                         "   template process_member<%s_INFO>(%s_);")

        for f in self.fields:
            calls.append(indent(call_template % (f.name, f.name.lower()), 8))

        return "\n".join(calls)

    def generate(self):
        generate_cppclass_common()

        cog.out("namespace %s {\n"
                "\n" % self.name)

        cog.out("class data\n"
                "{\n"
                "public:")

        cog.out(_body % { "name" : self.name,
                          "forAllMembersBody" : self.__gen_for_all_members() })

        cog.out("private:\n")

        for f in self.fields:
            if f.type:
                cog.out("    %s %s_;\n" % (sanitizeTypename(f.type), f.name.lower()))

        cog.out("}; // class data\n\n")

        for f in self.fields:
            if f.type:
                cog.out("template<>\n"
                        "inline %(name)s_INFO::type& data::get_member<%(name)s_INFO>()\n"
                        "{\n"
                        "    return %(lower_name)s_;\n"
                        "}\n\n" % { "name" : f.name, "lower_name" : f.name.lower() })

        for f in self.fields:
            if f.type:
                cog.out("template<>\n"
                        "inline %(name)s_INFO::type const& data::get_member<%(name)s_INFO>() const\n"
                        "{\n"
                        "    return %(lower_name)s_;\n"
                        "}\n\n" % { "name" : f.name, "lower_name" : f.name.lower() })

        cog.out("} // namespace %s\n" % self.name)
