///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file FreeGames.hpp
///@date Nov-26-0848PM-2013
///
///----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __INTBUFFER_FREEGAMES_HPP__
#define __INTBUFFER_FREEGAMES_HPP__

#include <vector>
#include <iostream>
#include "Spin.hpp"
namespace IntBuffer
{

class FreeGames
{
public:

  FreeGames();
  ///=====================================
  ///@ThemeId
  ///=====================================
  Int32 GetThemeId(void)const;
  ///=====================================
  ///@VersionId
  ///=====================================
  Int32 GetVersionId(void)const;
  ///=====================================
  ///@Win
  ///=====================================
  Int32 GetWin(void)const;
  void SetWin(const Int32 value);
  ///=====================================
  ///@Spins
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

}//namespace IntBuffer

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, IntBuffer::FreeGames& data);

#endif
