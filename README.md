IntBuffer
=========

Mako based C++ code generation for integer buffer read/write support.

Installation
============
I recommend pointing pip to this github as follows:
```
pip install git+https://github.com/johnoneil/intbuffer
```
That doesn't quite agree with the documentation I see online, but it appears to be the simplest, most effective method to me.
You can also clone the git repository and run setup.py as usual:
```
git clone https://github.com/johnoneil/intbuffer
cd intbuffer
python setup.py install
```

Using the Tool
==============
Once installed the tool can be invoked via that 'intbuffer-generate' command.
Simple command line help for tool is available:
```
joneil@joneilDesktop ~/code $ intbuffer-generate --help
usage: intbuffer-generate [-h] [-v] infile

Generate Integer buffer support code from domain specific text description of
structure.

positional arguments:
  infile         Input domain specific text description of C++ structures to
                 generate.

optional arguments:
  -h, --help     show this help message and exit
  -v, --verbose  Verbose operation. Print status messages during processing
```

Generating C++ code requires an input file. The demo.txt file input is probably the best documentation I'm going to provide for the input file format. Its contents follow:
```
#------------------------------------------------------------------------------
#Integer Buffer Parsing Support
#Domain specific language description in comments.
#John O'Neil
#Thursday, Nove 21st 2013
#------------------------------------------------------------------------------

#First, comments are anything following an octothorpe(hash).
#comments can follow non comments on the same line, but there's no 'in line'.

#we can also specify tool settings by using X = Y notation on non-commented lines
#spacing for settings ought not matter, neither does case.
#You can define any settings you want but only the following are picked up at present

namespace = FreeGamesBonus
use_radix_gameevents = true

#Second, in this file we can define Parents and children
#Parents correspond to generated C++ classes, and children to class members.

#Parents and children are differentiated by TAB indentation.
#zero indentation = Parent, so C++ class will be generated
#one indentaiton = child so a member of parent class will be generated.

#Classes are generated for ALL zero tabbed parents.

#Now, the SECTION reserved keyword indicates an integer "size"
#will be included in data written to integer buffer as zeroth element.
#Class children will be a single integer value, ULESS they share a name
#with a zero tabbed element (wich may or may not be a sized SECTION)
#------------------------------------------------------------------------------
SECTION FreeGamesData
        #Putting a Single numer after an integer (non-class) member
        #makes the member a const member, initialized to that value.
        #The member gets an accessor, but no mutator (getter, but no setter).
        #The value read from int buffers will also be tested, causing an
        #invalid read if the correct value is not found.
        #----------------------------------------------------------------------
        ThemeId 3
        VersionId 4
        #Children that don't share a name with a top level (zero tabbed) class
        #will be a simple, single integer value
        #----------------------------------------------------------------------
        Win
        #This child shares the name of a top-level (zero tabbed) class.
        #We will be able to access a ref of this single instance which
        #breaks encapsulation, but makes this whole thing easier to deal with.
        #----------------------------------------------------------------------
        FreeGames

#------------------------------------------------------------------------------
SECTION FreeGames
        ThemeId 2
        VersionId 3
        Win
        #using the REPEATED reserved keyword indicates we can have N of what
        #follows. REPEATED can be followed by either a top level class or just
        #an integer.
        #When written to an integer buffer a "count" value will proceed the
        #repeated elements. Also an accessor for the count is available as
        #well as a method to get value N.
        #----------------------------------------------------------------------
        REPEATED Spin

#------------------------------------------------------------------------------
Spin
        #preceeding an integer value before a child indicates N of that type
        #(no more or less) must be specificed before data is written to int
        #buffer.
        #----------------------------------------------------------------------
        5 Stop
        Prize``

```

Example
=======
A couple of examples exist in the git repository. For example, the 'test' folder contains a simple .txt configuraiton file and a supporting Makefile to generate C++ code and buid an executable with the output. Test folder contents are configured for non-windows building.
Contents of the windows folder have been built and used on Windows, but I haven't checked their state recently.
