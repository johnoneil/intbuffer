//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file OverlayPosition.hpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __WBF_OVERLAYPOSITION_HPP__
#define __WBF_OVERLAYPOSITION_HPP__

#include <vector>
#include <iostream>
namespace wbf
{

class OverlayPosition
{
public:

  ///=====================================
  ///@brief memberReelIndexs
  ///=====================================
  Int32 ReelIndexCount(void)const;
  Int32 GetReelIndex(const Int32 index)const;
  void AddReelIndex(const Int32 value);
  void ClearReelIndexs(void);
  

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static OverlayPosition Parse(const std::vector< Int32 >& array);
  static OverlayPosition Parse(const std::vector< Int32 >& array, Int32& index);

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
  std::vector< Int32 > m_ReelIndexs;
};


}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::OverlayPosition& data);

#endif
