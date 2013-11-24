///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file ${output_filename}.hpp
<%
import datetime
mydate = datetime.datetime.now().strftime('%b-%d-%I%M%p-%G')
%>
/// ${mydate}
///
///----------------------------------------------------------------------------

#pragma once
<% ifdef_filename = output_filename.upper() %>
#ifndef __${ifdef_filename}_HPP__
#define __${ifdef_filename}_HPP__

namespace IntBuffer
{
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
    ++size;//${child._name}
    % elif child.__class__.__name__ == 'Repeated':
    for(Int32 i=0;i<m_${child._element._name}s.size();++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
      ++size;
      % else:
      size+=m_${child._element._name}s.at(i).size();
      %endif
    }
    % elif child.__class__.__name__ == 'Set':
    for(Int32 i=0;i<m_${child._element._name}s.size();++i)
    {
      % if child._element.__class__.__name__ == 'Integer':
      ++size;
      % else:
      size+=m_${child._element._name}s.at(i).size();
      %endif
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
     % if child._element.__class__.__name__ == 'Integer':
  std::vector<Int32> m_${child._element._name}s;
     % else:
  std::vector<${child._element._name}> m_${child._element._name}s;
     % endif
  % elif child.__class__.__name__ == 'Set':
     % if child._element.__class__.__name__ == 'Integer':
  std::vector<Int32> m_${child._element._name}s;
     % else:
  std::vector<${child._element._name}> m_${child._element._name}s;
     % endif
	% else:
	${child._name} m_${child._name};
	% endif
% endfor
};

% endfor

}//namespace IntBuffer

#endif
