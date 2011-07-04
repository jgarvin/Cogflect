# cogflect - A set of cog recipes for C++ reflection
### Original Author: Joseph H. Garvin (2011)
### License: MIT

## What is Cogflect for?

Cogflect is intended to do the smallest amount of C++ code generation possible to bootstrap proper C++ metaprogramming. Code generation makes builds more complicated and generated code can be a pain debug, so rather than try to generate every possible thing for you, Cogflect's philosophy is to do just enough work to get reflection information accessible at the type level, so that you can use C++ templates to do most of your metaprogramming. Cogflect does go over this bound occasionally, when it will significantly help usability.

## Design Philosophy

 * Generated code should have no dependencies other than those brought in by the user.
 * Optimizing compilers should result in the generated code having the same performance as hand written C++.
 * No attempting to parse C++. Besides standards compliant C++ being [infamously difficult to parse](http://cacm.acm.org/magazines/2010/2/69354-a-few-billion-lines-of-code-later/fulltext "A Few Billion Lines of Code Later"), vendors have their own extensions and the standard itself changes over time (as seen by the recent release of C++0x). A robust parser is a multi man year project, and not my main goal.

## What can Cogflect do for me?

 * Generate switch statements, string conversion functions, etc. that have the exact same performance as code you would normally write by hand. As much work is done at compile time as possible.
 * Generate classes where you can iterate over all members at compile time or run time and perform an action. You can use this to implement serialization with less boilerplate for example.
 * Generate enums where you can iterate over all of the elements at compile time or runtime and perform an action.

## What are examples of things that are a pain without Cogflect?

 * Serialization (there are alternatives, but they generally involve listing all your members a second time).
 * Writing classes that track whether each member has changed since some earlier time.
 * Writing classes for objects that can be assigned to objects of other classes that contain a subset of the same members.
 * GUIs that let you navigate an object graph.

## I want to see some code!

In a header, call it missile.hpp.cog, you place this:

    /*[[[cog

      import cogflect as cf

      fields = [
      ["name",              "type"       ],
      ["MISSILE_TYPE",      "std::string"],
      ["X_LOCATION",        "double"     ],
      ["X_VELOCITY",        "double"     ],
      ["X_ACCELERATION",    "double"     ],
      ["Y_LOCATION",        "double"     ],
      ["Y_VELOCITY",        "double"     ],
      ["Y_ACCELERATION",    "double"     ],
      ["Z_LOCATION",        "double"     ],
      ["Z_VELOCITY",        "double"     ],
      ["Z_ACCELERATION",    "double"     ],
      ]

      cf.Enum("missile", fields)
      cf.CppClass("missile", fields)

      ]]]*/
    //[[[end]]]

And then it will generate code that will make it easy to do things like print all members to stdout:

    #include "missile.hpp"

    struct visitor {
        template<class MemberType>
        void process_member(typename MemberType::type const& v) const
        {
            std::cout << MemberType::string() << "\t\t" << v << std::endl;
        }

        void unknown_member() const
        {}
    };

    int main() {
        missile::data mymissile;

        mymissile.get_member<missile::MISSILE_TYPE_INFO>()   = "ICBM";
        mymissile.get_member<missile::X_LOCATION_INFO>()     = 50;
        mymissile.get_member<missile::X_VELOCITY_INFO>()     = 10;
        mymissile.get_member<missile::X_ACCELERATION_INFO>() = 30;
        mymissile.get_member<missile::Y_LOCATION_INFO>()     = 25;
        mymissile.get_member<missile::Y_VELOCITY_INFO>()     = 5;
        mymissile.get_member<missile::Y_ACCELERATION_INFO>() = 15;
        mymissile.get_member<missile::Z_LOCATION_INFO>()     = 3;
        mymissile.get_member<missile::Z_VELOCITY_INFO>()     = 9;
        mymissile.get_member<missile::Z_ACCELERATION_INFO>() = 300;

        for(unsigned i = 0; i < missile::size; ++i) {
            mymissile.get_runtime_indexed_member(visitor(), i);
        }

        return 0;
    }

Producing output like this:

    MISSILE_TYPE   ICBM
    X_LOCATION     50
    X_VELOCITY     10
    X_ACCELERATION 30
    Y_LOCATION     25
    Y_VELOCITY     5
    Y_ACCELERATION 15
    Z_LOCATION     3
    Z_VELOCITY     9
    Z_ACCELERATION 300

If you want to see what the generated code looks like, [here's a sample](http://github.com/jgarvin/Cogflect/blob/master/generated_sample/missile.hpp "Generated sample").

## How far along is it?

Cogflect should be considered pre-alpha. There are no guarantees about maintaining backwards compatibility yet. Names and interfaces may change at will.

## Building / Installation

You will need:

1. To install [Python](http://www.python.org "Python") if you don't already have it.
2. To get [cog](http://nedbatchelder.com/code/cog/ "cog"), a code generation tool written in Python by Ned Batchelder. Cogflect is just a set of modules that you can import when using cog, it doesn't handle generating output files itself.
3. A C++98 compliant compiler. Otherwise you won't be able to compile the generated code.
4. To copy the .py files from the 'cog-recipes' folder to somewhere where cog can see them.

That's it! See cog's documentation for how to have cog generate code. In essence, you put comments into your code that contain python snippets. To use Cogflect, you'll make sure its .py files are somewhere in your PYTHONPATH when invoking cog, and then within your snippets doing an import of one or more of Cogflect's modules. Getting the right entry in your PYTHONPATH and invoking cog are something that you'll need to integrate into your build, which is specific to the build system you are using and outside the scope of this FAQ, but it's not too hard to setup.

If you are interested in building the tests, you will also need an implementation of redo, a promising make alternative. The tests rely on features specific to [redo](https://github.com/apenwarr/redo "Avery Pennarun's implementation"), and my reusable redo template for C++ projects, [redo-lab](https://github.com/jgarvin/redo-lab "redo-lab").

## Enum features

 * Strongly typed. They intentionally do not implicitly convert to int in order to avoid programming errors. You can still explicitly convert them to int via the value() and index() methods.
 * Index is distinct from their value. You can give each element a random number for its value, but still refer to the Nth enum element, meaning the Nth declared element. If no value is provided the index is the default, just like a C++ enum.
 * You can associate multiple values with a single enum element, rather than just one.
 * You can associate types with each enum element. You can use this to, for example, allocate memory based on an enum value. It's actually possible to use this feature with recursive templates to mostly generate the classes that Cogflect normally generates for you (it's pretty hairy though, so I recommend using Cogflect's generation instead; I just mention it to give an indication of this feature's power).
 * Builtin string conversion and construction from string is provided.
 * A switch function covering all enum elements is provided out of the box.

## Class features

 * Automatic generation of members.
 * Compile time and runtime accessors are provided.
 * Iteration over all members at compile time or runtime with a typesafe visitor.
 * Tags can be associated with individual members, letting you perform actions on particular subsets of members.

## Why not use the preprocessor?

I attempted to use the preprocessor for enum and class reflection a few times before deciding to write Cogflect. I tried using both [Boost's preprocessor library](http://www.boost.org/doc/libs/1_46_1/libs/preprocessor/doc/index.html "Boost Preprocessor Library") and [X macros](http://en.wikipedia.org/wiki/C_preprocessor#X-Macros "X macros"). There were a few issues:

 * The preprocessor in many compilers, even fairly recent compilers (e.g. GCC 4.2), is slow. For an enum of 100 elements I saw my compilation time bloat by 20 minutes! GCC 4.5 brought this down to 18 minutes.
 * You pay the cost of expanding the preprocessor list in every object file that includes the header containing the list, bloating compilation time further.
 * The preprocessor is also a memory hog under many compilers. Boost Enum with the GCC 4.2 preprocessor on a 100 element enum consumed over 1.5GB of memory. On a 4 core 32-bit box with 4GB memory max, this means I can't use make's -j flag to parallelize my build without hitting swap!
 * Boost preprocessor is limited to 256 items in lists. An enum representing the various message types in a network protocol can easily have over 256 entries.
 * Code generated by the preprocessor often looks nothing like what a human would actually write, making it harder to debug. Because the preprocessor can only concatenate strings and not do any more complicated operations on them, you can't do seemingly simple things like give a class a camel case name and give a generated instantiation of that class the same name in lowercase.

## Why not use templates?

Cogflect's job is to make it *easier* to use templates safely for more types of metaprogramming. It is intended to be used with templates.

Templates can theoretically be used for the enum and class generation, in particular in C++0x where variadic templates are supported (you could hack it in C++98 using boost::tuple's as type lists or boost::mpl type lists), but:

 * Your compiler may lack C++0x support.
 * Many compilers have a hard limit on the number of template parameters lower than the number of members needed by your classes.
 * Supporting some features, like tags, will have to be implemented with slow linear searches.
 * It will be significantly more verbose to specify new elements/members.
 * The compile time will be worse because the template instantiations won't be cached between compilations.
 * It will be impossible to make the classes outwardly appear to have hand written interfaces (e.g. you can have templatized getters/setter for set<FOO\_FIELD>(x), get<FOO\_FIELD>(), but set\_foo and get\_foo won't be generatable)
 * No doxygen comment generation (not implemented yet in Cogflect either, but planned).
 * The error messages, even with [Clang](http://clang.llvm.org "Clang"), are probably going to be harder to debug than problems in Cogflect's generated code.

## Why not use Boost Enum?

See: Why not use the preprocessor? Also, Boost Enum will not help with generating other types of reflective code.

## Why not use Protocol Buffers or Thrift or ... ?

Apples and oranges. Cogflect isn't trying to provide a serialization format, or cross language code generation. It's specifically aimed at making introspectable C++ code. It is quite possible to write code that generates input files intended for cog+Cogflect. In fact, it should be possible to implement Protocol Buffers serialization by generating input files for cog+cogflect, rather than relying on Google's provided C++ code generator.

Note that because cog just operates on raw text, there's no reason you couldn't separate your element lists into their own python files, write enum/class generators with cog for other languages, and then feed the same element lists into your own generators and Cogflect's.

## Why not operate on a declarative file format, like XML or JSON?

I am sympathetic to keeping things as declarative as possible, but I decided I wasn't smart enough to come up with a schema/format that would anticipate all use cases. See following question.

## Why not write a generator from scratch and avoid the python dependency?

My original plan was to implement a code generator myself in standard C++ with no dependencies that given a declarative input file would create a directory and populate it with headers (one for the enum, one for the class, etc.). But I kept thinking of more things that would need to be supported in order for Cogflect to be useful, and eventually concluded that I was never going be able to anticipate all the use cases and support them well, so I may as well use a Turing complete language. And as long as I was going to provide a Turing complete language, I ought to stick to one people already have some chance of knowing rather than reinventing the wheel. That cog was written in Python sealed the deal.

Some examples of cases that should be supported:

 * Generating standalone headers is insufficient because it's common to have enum values that are the result of a macro or a static constant within a class or template class. Users need to be able to include headers above where the generated enum will appear.
 * Similarly generated classes may contain non-builtin types as members and need to include the appropriate header.
 * Some projects may use header guards and others may use "#pragma once".
 * Users may need to control the namespace(s) where the generated code is placed.
 * Some projects may prefer to bundle generated enums/classes/whatever together in a single header and others may prefer multiple headers.
 * Different users will have different preferred styles for the generated code, e.g. camelCase vs. under_scores.
 * In most instances it would be substantially simpler to write python code that loads a CSV/XML/JSON file and generates elements from that than it would be to add another script to the build process for translating the file to another input file format and invoking Cogflect on it.

## Why use cog rather than [Cheetah](http://www.cheetahtemplate.org/ "Cheetah Template Engine")?

 * Cog specifically has support for indenting the generated code according to how the cog tags are indented, helping keep the generated code human readable. Cheetah may support something similar but I didn't find it in a quick scan of its documentation.
 * Cheetah doesn't generate output files directly. It generates a python script that when run finally generates the output file. I assume this is an optimization for web servers where Cheetah is meant to be used, but I haven't investigated. Generated code is already harder to debug, another layer is simply too much. Cheetah can be passed a flag so that it doesn't appear to make an intermediate file, but I assume it still generates the intermediate code in memory, just without writing it to disk, so the added complexity is still there (Cheetah users feel free to correct me ;).

## Could C++0x's strongly typed enums be used in the future?

C++0x's strongly typed enums still lack reflection, so no. In order to add reflective functions like size() we would still have to define a class.

## Future directions

 * Customization of generated code
     * camelCase versus under_scores
     * access specifiers for generated functions
        * for\_all\_members\_with\_tag
     * omitting generated functions
 * Iterator interface for iterating members
 * Generating doxygen documentation
 * for\_all\_members
 * Shape based construction/assignment