//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file OverlaySymbol.hpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __WBF_OVERLAYSYMBOL_HPP__
#define __WBF_OVERLAYSYMBOL_HPP__

#include <vector>
#include <iostream>
#include "OverlayPosition.hpp"
namespace wbf
{

class OverlaySymbol
{
public:

  ///=====================================
  ///@brief member HeaderId
  ///=====================================
  Int32 GetHeaderId(void)const;
  void SetHeaderId(const Int32 value);
  ///=====================================
  ///@brief member OverlaySymbolId
  ///=====================================
  Int32 GetOverlaySymbolId(void)const;
  void SetOverlaySymbolId(const Int32 value);
  ///=====================================
  ///@brief member OverlayPositions
  ///=====================================
  Int32 OverlayPositionCount(void)const;
  OverlayPosition& GetOverlayPosition(const Int32 index);
  void SetOverlayPosition(const Int32 index, const OverlayPosition& value);

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static OverlaySymbol Parse(const std::vector< Int32 >& array);
  static OverlaySymbol Parse(const std::vector< Int32 >& array, Int32& index);

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
  Int32 m_HeaderId;
  Int32 m_OverlaySymbolId;
  Int32 m_OverlayPositions[5];
};


}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::OverlaySymbol& data);

#endif
