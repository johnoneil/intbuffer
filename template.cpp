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
#include "${output_filename}.hpp"

using namespace IntBuffer;
% for typename in typenames:

<% contains_const = False
for child in typename._children:
  if child.__class__.__name__ == 'Integer' and child._default>=0:
    contains_const = True
first_const = True %>
%if contains_const:
${typename._name}::${typename._name}()
% for child in typename._children:
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

% for child in typename._children:
	% if child.__class__.__name__ == 'Integer':
///=====================================
///${child._name}
///=====================================
 Int32  ${typename._name}::Get${child._name}(void)const{return m_${child._name};};
    % if child._default<0:
void ${typename._name}::Set${child._name}(const  Int32  value){m_${child._name}=value;};
    % endif
  % elif child.__class__.__name__ == 'Repeated':
///=====================================
///${child._element._name}s
///=====================================
 Int32  ${typename._name}::${child._element._name}Count(void)const{return static_cast< Int32 >(m_${child._element._name}s.size());};
  % if child._element.__class__.__name__ == 'Integer':
 Int32  ${typename._name}::Get${child._element._name}(const  Int32  index)const{return m_${child._element._name}s.at(index);};
void ${typename._name}::Add${child._element._name}(const  Int32  value){m_${child._element._name}s.push_back(value);};
  % else:
  ${child._element._name}& ${typename._name}::Get${child._element._name}(const  Int32  index){return m_${child._element._name}s.at(index);};
void ${typename._name}::Add${child._element._name}(const ${child._element._name}& value){m_${child._element._name}s.push_back(value);};
  % endif
void ${typename._name}::Clear${child._element._name}s(void){m_${child._element._name}s.clear();};

  % elif child.__class__.__name__ == 'Set':
///=====================================
///${child._element._name}s
///=====================================
 Int32  ${typename._name}::${child._element._name}Count(void)const{return static_cast< Int32 >(m_${child._element._name}s.size());};
  % if child._element.__class__.__name__ == 'Integer':
 Int32  ${typename._name}::Get${child._element._name}(const  Int32  index)const{return m_${child._element._name}s.at(index);};
void ${typename._name}::Add${child._element._name}(const  Int32  value){m_${child._element._name}s.push_back(value);};
  % else:
  ${child._element._name}& ${typename._name}::Get${child._element._name}(const  Int32  index){return m_${child._element._name}s.at(index);};
void ${typename._name}::Add${child._element._name}(const ${child._element._name}& value){m_${child._element._name}s.push_back(value);};
  % endif
void ${typename._name}::Clear${child._element._name}s(void){m_${child._element._name}s.clear();};
	% else:
///=====================================
///${child._name}
///=====================================
${child._name}& ${typename._name}::Get${child._name}(void){return m_${child._name};};
void ${typename._name}::Set${child._name}(const ${child._name}& value){m_${child._name}=value;};
	% endif
% endfor

///=====================================
///Fill structure from integer array
///=====================================
${typename._name} ${typename._name}::Parse(std::vector< Int32 >& array,  Int32 & index)
{
  ${typename._name} returnValue;
	const  Int32  size=array[index++];
	//TODO: failure on incorrect size?
	% for child in typename._children:
    % if child.__class__.__name__ == 'Integer':
  returnValue.m_${child._name}=array[index++];
	//TODO: test integers that have required default values
	  % elif child.__class__.__name__ == 'Repeated':
	{
    returnValue.m_${child._element._name}s.clear();
		const  Int32  count=array[index++];
		for( Int32  i=0;i<count;++i)
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
    returnValue.m_${child._element._name}s.clear();
		const  Int32  count=${child._count};
		for( Int32  i=0;i<count;++i)
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

//
// Get the size of this class in 32 bit integers
//
 Int32  ${typename._name}::Size(void)const
{
   Int32  size=0;
  % for child in typename._children:
  % if child.__class__.__name__ == 'Integer':
  ++size;//${child._name}
  % elif child.__class__.__name__ == 'Repeated':
  for( Int32  i=0;i<m_${child._element._name}s.size();++i)
  {
    % if child._element.__class__.__name__ == 'Integer':
    ++size;
    % else:
    size+=m_${child._element._name}s.at(i).Size();
    %endif
  }
  % elif child.__class__.__name__ == 'Set':
  for( Int32  i=0;i<m_${child._element._name}s.size();++i)
  {
    % if child._element.__class__.__name__ == 'Integer':
    ++size;
    % else:
    size+=m_${child._element._name}s.at(i).Size();
    %endif
  }
  % else:
  size+=m_${child._name}.Size();
  % endif
  % endfor
  return size;
}

% endfor

