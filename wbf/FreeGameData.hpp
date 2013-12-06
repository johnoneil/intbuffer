//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGameData.hpp
//@date Dec-05-0506PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------
#pragma once

#ifndef __WBF_FREEGAMEDATA_HPP__
#define __WBF_FREEGAMEDATA_HPP__

#include <vector>
#include <iostream>
#include "FiredUpSpin.hpp"
namespace wbf
{

class FreeGameData
{
public:

  FreeGameData();
  ///=====================================
  ///@brief member HeaderId
  ///=====================================
  Int32 GetHeaderId(void)const;
  ///=====================================
  ///@brief member ThemeId
  ///=====================================
  Int32 GetThemeId(void)const;
  ///=====================================
  ///@brief member FormatId
  ///=====================================
  Int32 GetFormatId(void)const;
  ///=====================================
  ///@brief member VersionId
  ///=====================================
  Int32 GetVersionId(void)const;
  ///=====================================
  ///@brief member TotalPrize
  ///=====================================
  Int32 GetTotalPrize(void)const;
  void SetTotalPrize(const Int32 value);
  ///=====================================
  ///@brief memberFiredUpSpins
  ///=====================================
  Int32 FiredUpSpinCount(void)const;
  FiredUpSpin& GetFiredUpSpin(const Int32 index);
  void AddFiredUpSpin(const FiredUpSpin& value);
  void ClearFiredUpSpins(void);
  

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static FreeGameData Parse(const EDC::IGameEvent& gameEvent);
  static FreeGameData Parse(const EDC::IGameEvent& gameEvent, Int32& index);

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
  Int32 m_HeaderId;
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_ThemeId;
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_FormatId;
  //can't make member const as it disabled compiler generated assignment operator
  //We'll have to settle for disabling the Setter and initializing it 
  Int32 m_VersionId;
  Int32 m_TotalPrize;
  std::vector<FiredUpSpin> m_FiredUpSpins;
};

///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool IsFreeGameData(const EDC::IGameEvent& gameEvent);

}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::FreeGameData& data);

#endif
