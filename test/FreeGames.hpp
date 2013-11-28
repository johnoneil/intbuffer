//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGames.hpp
//@date Nov-27-0702PM-2013
//
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __FREEGAMESBONUS_FREEGAMES_HPP__
#define __FREEGAMESBONUS_FREEGAMES_HPP__

#include <vector>
#include <iostream>
#include "Spin.hpp"
namespace FreeGamesBonus
{

class FreeGames
{
public:

  FreeGames();
  ///=====================================
  ///@brief member ThemeId
  ///=====================================
  Int32 GetThemeId(void)const;
  ///=====================================
  ///@brief member VersionId
  ///=====================================
  Int32 GetVersionId(void)const;
  ///=====================================
  ///@brief member Win
  ///=====================================
  Int32 GetWin(void)const;
  void SetWin(const Int32 value);
  ///=====================================
  ///@brief memberSpins
  ///=====================================
  Int32 SpinCount(void)const;
  Spin& GetSpin(const Int32 index);
  void AddSpin(const Spin& value);
  void ClearSpins(void);
  

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static FreeGames Parse(const std::vector< Int32 >& array);
  static FreeGames Parse(const std::vector< Int32 >& array, Int32& index);

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
  Int32 m_VersionId;
  Int32 m_Win;
  std::vector<Spin> m_Spins;
};

///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool IsFreeGames(const std::vector< Int32 >& array);

}//namespace FreeGamesBonus

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, FreeGamesBonus::FreeGames& data);

#endif
