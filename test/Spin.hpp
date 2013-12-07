//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Spin.hpp
//@date Dec-07-1213PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __FREEGAMESBONUS_SPIN_HPP__
#define __FREEGAMESBONUS_SPIN_HPP__

#include <vector>
#include <iostream>
namespace FreeGamesBonus
{

class Spin
{
public:

  ///=====================================
  ///@brief member Stops
  ///=====================================
  Int32 StopCount(void)const;
  Int32 GetStop(const Int32 index)const;
  void SetStop(const Int32 index, const Int32 value);
  ///=====================================
  ///@brief member Prize
  ///=====================================
  Int32 GetPrize(void)const;
  void SetPrize(const Int32 value);

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static Spin Parse(const std::vector< Int32 >& array);
  static Spin Parse(const std::vector< Int32 >& array, Int32& index);

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
  Int32 m_Stops[5];
  Int32 m_Prize;
};


}//namespace FreeGamesBonus

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, FreeGamesBonus::Spin& data);

#endif
