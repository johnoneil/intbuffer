//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file InitialSpin.hpp
//@date Dec-05-0506PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------
#pragma once

#ifndef __WBF_INITIALSPIN_HPP__
#define __WBF_INITIALSPIN_HPP__

#include <vector>
#include <iostream>
#include "TriggeringSpin.hpp"
namespace wbf
{

class InitialSpin
{
public:

  InitialSpin();
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
  ///@brief memberTriggeringSpins
  ///=====================================
  Int32 TriggeringSpinCount(void)const;
  TriggeringSpin& GetTriggeringSpin(const Int32 index);
  void AddTriggeringSpin(const TriggeringSpin& value);
  void ClearTriggeringSpins(void);
  

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static InitialSpin Parse(const EDC::IGameEvent& gameEvent);
  static InitialSpin Parse(const EDC::IGameEvent& gameEvent, Int32& index);

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
  std::vector<TriggeringSpin> m_TriggeringSpins;
};

///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool IsInitialSpin(const EDC::IGameEvent& gameEvent);

}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::InitialSpin& data);

#endif
