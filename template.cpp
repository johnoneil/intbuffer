///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file ${output_filename}.cpp
<%
import datetime
mydate = datetime.datetime.now().strftime('%b-%d-%I%M%p-%G')
%>///@date ${mydate}
///
///----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "${output_filename}.hpp"

using namespace ${namespace};
<% contains_const = False
for child in type._children:
  if child.__class__.__name__ == 'Integer' and child._default>=0:
    contains_const = True
first_const = True %>
%if contains_const:
${type._name}::${type._name}()
% for child in type._children:
	% if child.__class__.__name__ == 'Integer' and child._default>=0:
    %if first_const:
<%first_const=False%>
  :m_${child._name}(${child._default})
    %else:
  ,m_${child._name}(${child._default})
    %endif
  % endif
% endfor
  {};
%endif
% for child in type._children:
	% if child.__class__.__name__ == 'Integer':
///=====================================
///${child._name}
///=====================================
Int32 ${type._name}::Get${child._name}(void)const{return m_${child._name};};
    % if child._default<0:
void ${type._name}::Set${child._name}(const Int32 value){m_${child._name}=value;};
    % endif
  % elif child.__class__.__name__ == 'Repeated':
///=====================================
///${child._element._name}s
///=====================================
Int32 ${type._name}::${child._element._name}Count(void)const{return static_cast< Int32 >(m_${child._element._name}s.size());};
  % if child._element.__class__.__name__ == 'Integer':
Int32 ${type._name}::Get${child._element._name}(const Int32 index)const{return m_${child._element._name}s.at(index);};
void ${type._name}::Add${child._element._name}(const Int32 value){m_${child._element._name}s.push_back(value);};
  % else:
  ${child._element._name}& ${type._name}::Get${child._element._name}(const Int32 index){return m_${child._element._name}s.at(index);};
void ${type._name}::Add${child._element._name}(const ${child._element._name}& value){m_${child._element._name}s.push_back(value);};
  % endif
void ${type._name}::Clear${child._element._name}s(void){m_${child._element._name}s.clear();};

  % elif child.__class__.__name__ == 'Set':
///=====================================
///${child._element._name}s
///=====================================
Int32 ${type._name}::${child._element._name}Count(void)const{return ${child._count};};
  % if child._element.__class__.__name__ == 'Integer':
Int32 ${type._name}::Get${child._element._name}(const Int32 index)const{return m_${child._element._name}s.at(index);};
void ${type._name}::Add${child._element._name}(const Int32 value){m_${child._element._name}s.push_back(value);};
  % else:
  ${child._element._name}& ${type._name}::Get${child._element._name}(const Int32 index){return m_${child._element._name}s.at(index);};
void ${type._name}::Add${child._element._name}(const ${child._element._name}& value){m_${child._element._name}s.push_back(value);};
  % endif
void ${type._name}::Clear${child._element._name}s(void){m_${child._element._name}s.clear();};
	% else:
///=====================================
///${child._name}
///=====================================
${child._name}& ${type._name}::Get${child._name}(void){return m_${child._name};};
void ${type._name}::Set${child._name}(const ${child._name}& value){m_${child._name}=value;};
	% endif
% endfor

///=====================================
///Fill structure from integer array
///=====================================
${type._name} ${type._name}::Parse(const std::vector< Int32 >& array)
{
 Int32 index=0;
  return ${type._name}::Parse(array, index);
}

${type._name} ${type._name}::Parse(const std::vector< Int32 >& array, Int32& index)
{
  ${type._name} returnValue;
  %if type.__class__.__name__=='SizedClass':
  	const Int32 size=array[index++];
  if(static_cast<Int32>(array.size())-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("${type._name} cannot be generated from buffer due to incorrect size.");
  }
  % endif
	% for child in type._children:
    % if child.__class__.__name__ == 'Integer':
  returnValue.m_${child._name}=array[index++];
      %if child._default >=0:
  if(returnValue.m_${child._name}!=${child._default})
  {
    throw std::runtime_error("${type._name} cannot be generated from buffer due to incorrect value of m_${child._name}");
  }
      %endif
    % elif child.__class__.__name__ == 'Repeated':
  {
    returnValue.m_${child._element._name}s.clear();
    const Int32 count=array[index++];
    for(Int32 i=0;i<count;++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
     Int32 value= array[index++];
      % else:
      ${child._element._name} value= ${child._element._name}::Parse(array, index);
      % endif
      returnValue.m_${child._element._name}s.push_back(value);
    }
  }
    % elif child.__class__.__name__ == 'Set':
  {
    //This is a set
    returnValue.m_${child._element._name}s.clear();
    const Int32 count=${child._count};
    for(Int32 i=0;i<count;++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
     Int32 value= array[index++];
      % else:
      ${child._element._name} value= ${child._element._name}::Parse(array, index);
      % endif
      returnValue.m_${child._element._name}s.push_back(value);
    }
  }
	  % else:
	returnValue.m_${child._name}= ${child._name}::Parse(array, index);
	  % endif
	% endfor
  return returnValue;
}

bool ${type._name}::Write(std::vector< Int32 >& array)
{
  Int32 index=0;
  return Write(array, index);
}

bool ${type._name}::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  //if(static_cast<Int32>(array.size())-index<size)
  {
    //return false;//failed to write for lack of room
  }
  %if type.__class__.__name__ == 'SizedClass':
  array[index++]=size;
  %endif
  % for child in type._children:
    % if child.__class__.__name__ == 'Integer':
  array[index++] = m_${child._name};
	  % elif child.__class__.__name__ == 'Repeated':
  {
    const Int32 count = ${child._element._name}Count();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
      array[index++]=Get${child._element._name}(i);
      % else:
      Get${child._element._name}(i).Write(array, index);
      % endif
    }
  }
    % elif child.__class__.__name__ == 'Set':
  {
    const Int32 count = ${child._element._name}Count();
    //As "set" is defined as a STATIC list with known number of elements
    //therefore we don't have to head it with the element count    
    //array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
      array[index++]=Get${child._element._name}(i);
      % else:
      Get${child._element._name}(i).Write(array, index);
      % endif
    }
  }
	  % else:
  m_${child._name}.Write(array, index);
	  % endif
	% endfor
  return true;
}

//
// Get the size of this class in 32 bit integers
//
Int32 ${type._name}::Size(void)const
{
 Int32 size=0;
  %if type.__class__.__name__ == 'SizedClass':
  size++;//sized class header
  %endif
  % for child in type._children:
  % if child.__class__.__name__ == 'Integer':
  ++size;//${child._name}
  % elif child.__class__.__name__ == 'Repeated':
  ++size;//increment once for the number of elements 'header'
  for(Int32 i=0;i<m_${child._element._name}s.size();++i)
  {
    % if child._element.__class__.__name__ == 'Integer':
    ++size;
    % else:
    size+=m_${child._element._name}s.at(i).Size();
    %endif
  }
  % elif child.__class__.__name__ == 'Set':
  {
    const Int32 count = ${child._element._name}Count();
    for(Int32 i=0;i<count;++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
      ++size;
      % else:
      size+=m_${child._element._name}s.at(i).Size();
      %endif
    }
  }
  % else:
  size+=m_${child._name}.Size();
  % endif
  % endfor
  return size;
}

%if contains_const:
bool ${namespace}::Is${type._name}(const std::vector< Int32 >& array)
{
  try
  {
    ${type._name} value = ${type._name}::Parse(array);
  }catch(...)
  {
    return false;
  }
  return true;
};
%endif

std::ostream& operator<<(std::ostream &out, IntBuffer::${type._name}& data)
{
% for child in type._children:
  % if child.__class__.__name__ == 'Integer':
  out<<"${child._name}:"<<data.Get${child._name}()<<std::endl;
  % elif child.__class__.__name__ == 'Repeated':
  for(Int32 i=0;i<data.${child._element._name}Count();++i)
  {
    % if child._element.__class__.__name__ == 'Integer':
    out<<"${child._element._name}:"<<i<<":"<<data.Get${child._element._name}(i)<<std::endl;
    % else:
    out<<"${child._element._name}:"<<i<<":"<<data.Get${child._element._name}(i)<<std::endl;
    %endif
  }
  % elif child.__class__.__name__ == 'Set':
  for(Int32 i=0;i<data.${child._element._name}Count();++i)
  {
    % if child._element.__class__.__name__ == 'Integer':
    out<<"${child._element._name}:"<<i<<":"<<data.Get${child._element._name}(i)<<std::endl;
    % else:
    out<<"${child._element._name}:"<<i<<":"<<data.Get${child._element._name}(i)<<std::endl;
    %endif
  }
  % else:
  out<<"${child._name}:"<<data.Get${child._name}()<<std::endl;
  % endif
% endfor
  return out;
}


