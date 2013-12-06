//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGamesBonus.hpp
//@date Dec-05-0506PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------
#pragma once

#ifndef __WBF_FREEGAMESBONUS_HPP__
#define __WBF_FREEGAMESBONUS_HPP__

#include <vector>
#include <iostream>
#include "InitialSpin.hpp"
#include "Overlays.hpp"
#include "FreeGameData.hpp"
namespace wbf
{

class FreeGamesBonus
{
public:

  FreeGamesBonus();
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
  ///@brief member NumberOfObjects
  ///=====================================
  Int32 GetNumberOfObjects(void)const;
  ///=====================================
  ///@brief member InitialSpin
  ///=====================================
  InitialSpin& GetInitialSpin(void);
  void SetInitialSpin(const InitialSpin& value);
  ///=====================================
  ///@brief member Overlays
  ///=====================================
  Overlays& GetOverlays(void);
  void SetOverlays(const Overlays& value);
  ///=====================================
  ///@brief member FreeGameData
  ///=====================================
  FreeGameData& GetFreeGameData(void);
  void SetFreeGameData(const FreeGameData& value);

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static FreeGamesBonus Parse(const EDC::IGameEvent& gameEvent);
  static FreeGamesBonus Parse(const EDC::IGameEvent& gameEvent, Int32& index);

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
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_NumberOfObjects;
  InitialSpin m_InitialSpin;
  Overlays m_Overlays;
  FreeGameData m_FreeGameData;
};

///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool IsFreeGamesBonus(const EDC::IGameEvent& gameEvent);

}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::FreeGamesBonus& data);

#endif
