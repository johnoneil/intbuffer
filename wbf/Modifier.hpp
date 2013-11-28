//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Modifier.hpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __WBF_MODIFIER_HPP__
#define __WBF_MODIFIER_HPP__

#include <vector>
#include <iostream>
namespace wbf
{

class Modifier
{
public:

  ///=====================================
  ///@brief member SymbolIndex
  ///=====================================
  Int32 GetSymbolIndex(void)const;
  void SetSymbolIndex(const Int32 value);
  ///=====================================
  ///@brief memberLocations
  ///=====================================
  Int32 LocationCount(void)const;
  Int32 GetLocation(const Int32 index)const;
  void AddLocation(const Int32 value);
  void ClearLocations(void);
  

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static Modifier Parse(const std::vector< Int32 >& array);
  static Modifier Parse(const std::vector< Int32 >& array, Int32& index);

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
  Int32 m_SymbolIndex;
  std::vector< Int32 > m_Locations;
};


}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::Modifier& data);

#endif
