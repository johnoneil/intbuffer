//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file BaseGame.hpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __WBF_BASEGAME_HPP__
#define __WBF_BASEGAME_HPP__

#include <vector>
#include <iostream>
#include "Overlays.hpp"
namespace wbf
{

class BaseGame
{
public:

  BaseGame();
  ///=====================================
  ///@brief member ThemeId
  ///=====================================
  Int32 GetThemeId(void)const;
  ///=====================================
  ///@brief member FormatId
  ///=====================================
  Int32 GetFormatId(void)const;
  ///=====================================
  ///@brief member TotalPrize
  ///=====================================
  Int32 GetTotalPrize(void)const;
  void SetTotalPrize(const Int32 value);
  ///=====================================
  ///@brief member ReelSetId
  ///=====================================
  Int32 GetReelSetId(void)const;
  void SetReelSetId(const Int32 value);
  ///=====================================
  ///@brief member Overlays
  ///=====================================
  Overlays& GetOverlays(void);
  void SetOverlays(const Overlays& value);

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static BaseGame Parse(const std::vector< Int32 >& array);
  static BaseGame Parse(const std::vector< Int32 >& array, Int32& index);

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
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_ThemeId;
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_FormatId;
  Int32 m_TotalPrize;
  Int32 m_ReelSetId;
  Overlays m_Overlays;
};

///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool IsBaseGame(const std::vector< Int32 >& array);

}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::BaseGame& data);

#endif
