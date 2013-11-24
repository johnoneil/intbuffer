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

def generate_output(input_file, output_filename):
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
  generate_code(classes, output_filename)

def is_top_level_class(classname, classes):
  for c in classes:
    if classname in c[0]:
      return True
  return False

def generate_code(classes, output_filename):
  code=[]
  for c in classes:
    current_class=code_from_line(c[0], classes)
    for child in c[1]:
      current_class.AddChild(code_from_line(child, classes))
    code.append(current_class)

  render_from_templates(code, output_filename)

def render_from_templates(code, output_filename):
  global template_string
  #mytemplate = Template(template_string)
  hpp_template = Template(filename='template.hpp')
  cpp_template = Template(filename='template.cpp')
  mydata={'typenames':code,'output_filename':output_filename}

  with open(output_filename+'.hpp','w') as hpp:
    hpp.write(hpp_template.render(**mydata))
  
  with open(output_filename+'.cpp','w') as cpp:
    cpp.write(cpp_template.render(**mydata))
  #print mytemplate.render(typenames=code)

def code_from_line(line, classes):
  words = line.split(' ')
  #simplest cases first
  if len(words)==1:
    word=words[0]
    if is_top_level_class(word, classes):
      print 'Top level class ' + word
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


def generate_output_from_filenames(input_filename, output_filename):
  if not os.path.isfile(input_filename):
    print 'Could not find input file ' + input_filename
    return
  file = open(input_filename)
  return generate_output(file, output_filename)


def main():
  parser = argparse.ArgumentParser(description='Generate Integer buffer support code from domain specific text description of structure.')
  parser.add_argument('infile', help='Input domain specific text description of C++ structures to generate.')
  parser.add_argument('-v','--verbose', help='Verbose operation. Print status messages during processing', action="store_true")
  parser.add_argument('-o', '--outfile', help='Threshold for nonzero pixels to separete vert/horiz text lines.',default='Parser')
  parser.add_argument('--namespace', help='Namespace to wrap generated code', default='IntBuffer')
  args = parser.parse_args()

  infile = args.infile
  outfile = args.outfile

  if args.verbose:
    print '''******************************************************************************
intbuffer.py
Generates .cpp and .hpp integer read/write support of text file class descriptions
John O'Neil
Sat Nov 23rd, 2013
******************************************************************************
'''
    print 'Generating files '+outfile+'.hpp and '+outfile+'.cpp via input file '+infile

  generate_output_from_filenames(infile, outfile)

if __name__ == '__main__':
  main()


