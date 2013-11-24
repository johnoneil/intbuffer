#!/usr/bin/python
 # vim: set ts=2 expandtab:
"""
Module: parsergen.py
Desc: generate c++ integer array parsing code
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Thursday, November 21st 2013

  Generate C++ code from a an indent based
	description of integer array structure
  
"""

import argparse
import os
from mako.template import Template

template_string='''
% for typename in typenames:
 
class ${typename._name}
{
public:
% for child in typename._children:

	% if child.__class__.__name__ == 'Integer':
	///=====================================
	///${child._name}
	///=====================================
	Int32 Get${child._name}(void)const{return m_${child._name};};
	void Set${child._name}(const Int32 value)const{m_${child._name}=value;};
  % elif child.__class__.__name__ == 'Repeated':
	///=====================================
	///${child._element._name}s
	///=====================================
  Int32 ${child._element._name}Count(void)const{return static_cast<Int32>(m_${child._element._name}s.size();};
  ${child._element._name}& Get${child._element._name}(const Int32 index)const{return m_${child._element._name}s.at(index);};
  void Clear${child._element._name}s(void){m_${child._element._name}s.clear();};
  void Add${child._element._name}(const ${child._element._name}& value){m_${child._element._name}.push_back(value);};
  % elif child.__class__.__name__ == 'Set':
	///=====================================
	///${child._element._name}s
	///=====================================
  Int32 ${child._element._name}Count(void)const{return ${child._count};};
  ${child._element._name}& Get${child._element._name}(const Int32 index)const{return m_${child._element._name}s.at(index);};
  //void Clear${child._element._name}s(void){m_${child._element._name}s.clear();};
  //void Add${child._element._name}(const ${child._element._name}& value){m_${child._element._name}.push_back(value);};
	% else:
  ///=====================================
  ///${child._name}
  ///=====================================
	${child._name}& Get${child._name}(void)const{return m_${child._name};};
	void Set${child._name}(const ${child._name}& value)const{m_${child._name}=value;};
	% endif
% endfor

	///=====================================
	///Fill structure from integer array
	///=====================================
	static ${typename._name} Parse(std::vector<Int32>& array, Int32& index=0)
	{
    ${typename._name} returnValue;

		const Int32 size=array[index++];
		//TODO: failure on incorrect size?
		% for child in typename._children:
		% if child.__class__.__name__ == 'Integer':
		returnValue.m_${child._name}=array[index++];
		//TODO: test integers that have required default values
		% elif child.__class__.__name__ == 'Repeated':
		{
      returnValue.m_${child._element._name}s.clear();
			const Int32 count=array[index++];
			for(Int32 i=0;i<count;++i)
			{
        ${child._element._name} value= ${child._element._name}::Parse(array, index);
				returnValue.m_${child._element._name}s.push_back(value);
			}
		}
    % elif child.__class__.__name__ == 'Set':
		{
      returnValue.m_${child._element._name}s.clear();
			const Int32 count=${child._count};
			for(Int32 i=0;i<count;++i)
			{
        ${child._element._name} value= ${child._element._name}::Parse(array, index);
				returnValue.m_${child._element._name}s.push_back(value);
			}
		}
		% else:
		returnValue.m_${child._name}= ${child._name}::Parse(array, index);
		% endif
		% endfor

    return returnValue;
		
	};

  //
  // Get the size of this class in 32 bit integers
  //
  Int32 Size(void)const
  {
    Int32 size=0;
    % for child in typename._children:
	  % if child.__class__.__name__ == 'Integer':
    size++;//${child._name}
    % elif child.__class__.__name__ == 'Repeated':
    for(Int32 i=0;i<m_${child._element._name}.size();++i)
    {
      size+=m_${child._element._name}s.at(i).size();
    }
    % elif child.__class__.__name__ == 'Set':
    for(Int32 i=0;i<m_${child._element._name}.size();++i)
    {
      size+=m_${child._element._name}s.at(i).size();
    }
	  % else:
	  size+=m_${child._name}.Size();
	  % endif
    % endfor
    return size;
  }

private:
% for child in typename._children:
	% if child.__class__.__name__ == 'Integer':
  Int32 m_${child._name};
  % elif child.__class__.__name__ == 'Repeated':
  std::vector<${child._element._name}> m_${child._element._name}s;
  % elif child.__class__.__name__ == 'Set':
  std::vector<${child._element._name}> m_${child._element._name}s;
	% else:
	${child._name} m_${child._name};
	% endif
% endfor
};

% endfor
'''

#mytemplate = Template(template_string)

#http://stackoverflow.com/questions/354038/how-do-i-check-if-a-string-is-a-number-in-python
def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

class Class(object):
	def __init__(self, name):
		self._name=name
		self._children=[]
	def AddChild(self, child):
		self._children.append(child)

class SizedClass(Class):
  def __init__(self, name):
    Class.__init__(self, name)

class Integer(object):
  def __init__(self, name, default=-1):
    self._name=name
    self._default=default

class Repeated:
	def __init__(self, element):
		self._element=element

class Set:
  def __init__(self, element, count):
    self._element=element
    self._count=count

def parse_input(input_file):
  #go line by line and build structure based on contents
  classes = []
  for i,line in enumerate(input_file):
    #remove comments
    line=line.split("#")[0]
    #count the indents at the head of line
    indent = len(line) - len(line.lstrip())
    line=line.lstrip()
    line=line.strip()
    if(len(line)<1):
      continue
    
    #print str(indent)+':'+line
    if indent==0:
      classes.append([line,[]])
    elif len(classes)>0:
      classes[-1][-1].append(line)

  #print str(classes)

  #TODO: check for duplicate top level classes
  #TODO: check for circular class references
  generate_code(classes)

def is_top_level_class(classname, classes):
  for c in classes:
    if c[0] == classname:
      return True
  return False

def generate_code(classes):
  code=[]
  for c in classes:
    current_class=code_from_line(c[0], classes)
    for child in c[1]:
      current_class.AddChild(code_from_line(child, classes))
    code.append(current_class)

  render_from_templates(code)

def render_from_templates(code):
  global template_string
  mytemplate = Template(template_string)
  print mytemplate.render(typenames=code)

def code_from_line(line, classes):
  words = line.split(' ')
  #simplest cases first
  if len(words)==1:
    word=words[0]
    if is_top_level_class(word, classes):
      return Class(word)
    else:
      return Integer(word)
  first_word, remaining_words=line.split(' ',1)
  if first_word=='SECTION':
    #TODO: check for second word
    return SizedClass(remaining_words)
  if is_number(first_word):
    return Set(code_from_line(remaining_words, classes),int(first_word))
  if first_word=='REPEATED':
    return Repeated(code_from_line(remaining_words, classes))

  #the only other supported case would be an integer value with default
  if len(words)==2 and is_number(words[1]):
    return Integer(first_word,default=int(remaining_words))


def old_generate_code(classes):
  primary=SizedClass("FreeSpinBonus")
  free_spins=SizedClass("FreeSpins")

  primary.AddChild(Integer("ThemeId", default=4))
  primary.AddChild(Integer("VersionId", default=1))
  primary.AddChild(Integer("Win"))
  primary.AddChild(free_spins)

  free_spins.AddChild(Integer("ThemeId"))
  free_spins.AddChild(Integer("VersionId"))
  free_spins.AddChild(Integer("Win"))
  free_spins.AddChild(Set(Integer("Stop"),5))

  #print mytemplate.render(typenames=[primary,free_spins])

def parse_input_file(input_filename):
  if not os.path.isfile(input_filename):
    print 'Could not find input file ' + input_filename
    return
  file = open(input_filename)
  return parse_input(file)


def main():
  parser = argparse.ArgumentParser(description='Generate Integer buffer support code from domain specific text description of structure.')
  parser.add_argument('infile', help='Input domain specific text description of C++ structures to generate.')
  parser.add_argument('-v','--verbose', help='Verbose operation. Print status messages during processing', action="store_true")
  #parser.add_argument('--segment_threshold', help='Threshold for nonzero pixels to separete vert/horiz text lines.',type=int,default=1)
  args = parser.parse_args()

  infile = args.infile

  parse_input_file(infile)

if __name__ == '__main__':
  main()


