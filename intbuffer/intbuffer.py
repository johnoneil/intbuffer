#!/usr/bin/python
 # vim: set ts=2 expandtab:
"""
Module: intbuffer.py
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

#settings picked up from config file
settings = {'namespace':'IntBuffer',
            'use_radix_gameevents':'false'}

def is_number(s):
  '''
  Determine if input argument can be interpreted as a number (float) or not
  See also http://stackoverflow.com/questions/354038/how-do-i-check-if-a-string-is-a-number-in-python

  :param s: object to determine numerical status on
  :type s: any
  '''
  try:
      float(s)
      return True
  except ValueError:
      return False

class Class(object):
  '''Class to encapsulate standard c++ class to generate.
  '''
  def __init__(self, name):
		self._name=name
		self._children=[]

  def AddChild(self, child):
		self._children.append(child)

class SizedClass(Class):
  '''
  Class to encapsulate sized (preceeded by integer size) c++ class to generate.
  '''
  def __init__(self, name):
    Class.__init__(self, name)

class Integer(object):
  '''
  Class to encapsulate integer class member to generate.
  '''
  def __init__(self, name, default=-1):
    self._name=name
    self._default=default

class Repeated(object):
  '''
  Class wrapper denoting a series of variable N class members within generated c++.
  Repeated classes are preceded by an integer count in the associated integer arrray.
  '''
  def __init__(self, element):
		self._element=element

class Set(object):
  '''
  Class wrapper denoting a predetermined N class members within generated c++.
  Sets need not be tagged with a "count" in the associated integer array.
  '''
  def __init__(self, element, count):
    self._element=element
    self._count=count

def generate_output(input_file):
  #go line by line and build structure based on contents
  classes = []
  for i,line in enumerate(input_file):
    #remove comments
    line=line.split("#")[0]
    
    #pass settings line to settings array
    if "=" in line:
      add_setting(line)
      continue

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

  #TODO: check for duplicate top level classes
  #TODO: check for circular class references
  generate_code(classes)

def add_setting(line):
  '''
  Take a line from input configuration file and extract settings info.
  Store the settings info in this module's dictionary
  '''
  global settings
  setting, value = line.split('=',1)
  setting = setting.strip().lower()
  value = value.strip() #we don't take lowercase values. we can do so later if desired.
  settings[setting]=value

def is_top_level_class(classname, classes):
  for c in classes:
    if classname in c[0]:
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
  #using __file__ to locate templates relative to this module
  global settings
  absolute_path=os.path.abspath(__file__)
  current_directory=os.path.dirname(absolute_path)
  template_hpp_filename = 'template.hpp'
  template_cpp_filename = 'template.cpp'
  if settings['use_radix_gameevents'].lower() == 'true':
    template_hpp_filename = 'ROCKET_template.hpp'
    template_cpp_filename = 'ROCKET_template.cpp'
  hpp_template = Template(filename=os.path.join(current_directory, template_hpp_filename))
  cpp_template = Template(filename=os.path.join(current_directory, template_cpp_filename))
  for top_level_class in code:
    filename=top_level_class._name
    mydata={'type':top_level_class,
            'output_filename':filename,
            'settings': settings}
    with open(filename+'.hpp','w') as hpp:
      hpp.write(hpp_template.render(**mydata))
    with open(filename+'.cpp','w') as cpp:
      cpp.write(cpp_template.render(**mydata))

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


def generate_output_from_filenames(input_filename):
  if not os.path.isfile(input_filename):
    print 'Could not find input file ' + input_filename
    return
  file = open(input_filename)
  return generate_output(file)


def main():
  parser = argparse.ArgumentParser(description='Generate Integer buffer support code from domain specific text description of structure.')
  parser.add_argument('infile', help='Input domain specific text description of C++ structures to generate.')
  parser.add_argument('-v','--verbose', help='Verbose operation. Print status messages during processing', action="store_true")
  args = parser.parse_args()

  infile = args.infile

  if args.verbose:
    print '''******************************************************************************
intbuffer.py
Generates .cpp and .hpp integer read/write support of text file class descriptions
John O'Neil
Sat Nov 23rd, 2013
******************************************************************************
'''
    print 'Generating files via input file '+infile

  generate_output_from_filenames(infile)

if __name__ == '__main__':
  main()


