//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Payline.hpp
//@date Dec-05-0506PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------
#pragma once

#ifndef __WBF_PAYLINE_HPP__
#define __WBF_PAYLINE_HPP__

#include <vector>
#include <iostream>
namespace wbf
{

class Payline
{
public:

  ///=====================================
  ///@brief member Index
  ///=====================================
  Int32 GetIndex(void)const;
  void SetIndex(const Int32 value);
  ///=====================================
  ///@brief member Mask
  ///=====================================
  Int32 GetMask(void)const;
  void SetMask(const Int32 value);
  ///=====================================
  ///@brief member WinAmount
  ///=====================================
  Int32 GetWinAmount(void)const;
  void SetWinAmount(const Int32 value);
  ///=====================================
  ///@brief member WinId
  ///=====================================
  Int32 GetWinId(void)const;
  void SetWinId(const Int32 value);

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static Payline Parse(const EDC::IGameEvent& gameEvent);
  static Payline Parse(const EDC::IGameEvent& gameEvent, Int32& index);

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
  Int32 m_Index;
  Int32 m_Mask;
  Int32 m_WinAmount;
  Int32 m_WinId;
};


}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::Payline& data);

#endif
