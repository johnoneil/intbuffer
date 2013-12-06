//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Modifier.hpp
//@date Dec-05-0715PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------
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
  static Modifier Parse(const EDC::IGameEvent& gameEvent);
  static Modifier Parse(const EDC::IGameEvent& gameEvent, Int32& index);

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
