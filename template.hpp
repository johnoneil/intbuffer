///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file ${output_filename}.hpp
<%
import datetime
mydate = datetime.datetime.now().strftime('%b-%d-%I%M%p-%G')
%>///@date ${mydate}
///
///----------------------------------------------------------------------------

typedef int Int32;

#pragma once
<% ifdef_filename = output_filename.upper() %>
#ifndef __INTBUFFER_${ifdef_filename}_HPP__
#define __INTBUFFER_${ifdef_filename}_HPP__

#include <vector>
#include <iostream>
%for child in type._children:
  % if child.__class__.__name__ == 'Class' or child.__class__.__name__ == 'SizedClass':
#include "${child._name}.hpp"
  % elif child.__class__.__name__ == 'Set' or child.__class__.__name__=='Repeated':
    %if child._element.__class__.__name__ != 'Integer':
#include "${child._element._name}.hpp"
    %endif
  % endif
% endfor
namespace IntBuffer
{

class ${type._name}
{
public:
<% contains_const = False
for child in type._children:
  if child.__class__.__name__ == 'Integer' and child._default>=0:
    contains_const = True
first_const = True %>
    %if contains_const:
  ${type._name}();
    %endif
% for child in type._children:
	% if child.__class__.__name__ == 'Integer':
  ///=====================================
  ///@${child._name}
  ///=====================================
  Int32 Get${child._name}(void)const;
    % if child._default<0:
	void Set${child._name}(const Int32 value);
    % endif
  % elif child.__class__.__name__ == 'Repeated':
  ///=====================================
  ///@${child._element._name}s
  ///=====================================
  Int32 ${child._element._name}Count(void)const;
    % if child._element.__class__.__name__ == 'Integer':
  Int32 Get${child._element._name}(const Int32 index)const;
  void Add${child._element._name}(const Int32 value);
    % else:
  ${child._element._name}& Get${child._element._name}(const Int32 index);
  void Add${child._element._name}(const ${child._element._name}& value);
    % endif
  void Clear${child._element._name}s(void);
  
  % elif child.__class__.__name__ == 'Set':
  ///=====================================
  ///${child._element._name}s
  ///=====================================
  Int32 ${child._element._name}Count(void)const;
    % if child._element.__class__.__name__ == 'Integer':
  Int32 Get${child._element._name}(const Int32 index)const;
  void Add${child._element._name}(const Int32 value);
    % else:
  ${child._element._name}& Get${child._element._name}(const Int32 index);
  void Add${child._element._name}(const ${child._element._name}& value);
    % endif
  void Clear${child._element._name}s(void);
	% else:
  ///=====================================
  ///${child._name}
  ///=====================================
  ${child._name}& Get${child._name}(void);
  void Set${child._name}(const ${child._name}& value);
	% endif
% endfor

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static ${type._name} Parse(const std::vector< Int32 >& array);
  static ${type._name} Parse(const std::vector< Int32 >& array, Int32& index);

  ///=====================================
  ///@brief write class data to integer array
  ///=====================================
  bool Write(std::vector< Int32 >& array);
  bool Write(std::vector< Int32 >& array, Int32& index);

  ///
  ///@brief Get size of class data when dumped to integer array
  ///
  Int32  Size(void)const;

private:
% for child in type._children:
	% if child.__class__.__name__ == 'Integer':
    %if child._default<0:
  Int32 m_${child._name};
    %else:
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_${child._name};
    %endif
  % elif child.__class__.__name__ == 'Repeated':
     % if child._element.__class__.__name__ == 'Integer':
  std::vector< Int32 > m_${child._element._name}s;
     % else:
  std::vector<${child._element._name}> m_${child._element._name}s;
     % endif
  % elif child.__class__.__name__ == 'Set':
     % if child._element.__class__.__name__ == 'Integer':
  std::vector< Int32 > m_${child._element._name}s;
     % else:
  std::vector<${child._element._name}> m_${child._element._name}s;
     % endif
	% else:
  ${child._name} m_${child._name};
	% endif
% endfor
};

%if contains_const:
///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool Is${type._name}(const std::vector< Int32 >& array);
%endif

}//namespace IntBuffer

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, IntBuffer::${type._name}& data);

#endif
