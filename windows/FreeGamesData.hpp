///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file FreeGamesData.hpp
///@date Nov-26-1221AM-2013
///
///----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __INTBUFFER_FREEGAMESDATA_HPP__
#define __INTBUFFER_FREEGAMESDATA_HPP__

#include <vector>
#include <iostream>

#include "FreeGames.hpp"

namespace IntBuffer
{

class FreeGamesData
{
public:

  FreeGamesData();

  ///=====================================
  ///ThemeId
  ///=====================================
  Int32  GetThemeId(void)const;
  ///=====================================
  ///VersionId
  ///=====================================
  Int32  GetVersionId(void)const;
  ///=====================================
  ///Win
  ///=====================================
  Int32  GetWin(void)const;
	void SetWin(const  Int32  value);
  ///=====================================
  ///FreeGames
  ///=====================================
  FreeGames& GetFreeGames(void);
  void SetFreeGames(const FreeGames& value);

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static FreeGamesData Parse(std::vector< Int32 >& array);
  static FreeGamesData Parse(std::vector< Int32 >& array,  Int32& index);

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
  Int32  m_ThemeId;
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32  m_VersionId;
  Int32  m_Win;
  FreeGames m_FreeGames;
};

}//namespace IntBuffer

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, IntBuffer::FreeGamesData& data);

#endif