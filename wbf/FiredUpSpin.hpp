//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FiredUpSpin.hpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __WBF_FIREDUPSPIN_HPP__
#define __WBF_FIREDUPSPIN_HPP__

#include <vector>
#include <iostream>
#include "Modifier.hpp"
#include "Payline.hpp"
namespace wbf
{

class FiredUpSpin
{
public:

  FiredUpSpin();
  ///=====================================
  ///@brief member HeaderId
  ///=====================================
  Int32 GetHeaderId(void)const;
  ///=====================================
  ///@brief member SpinPrize
  ///=====================================
  Int32 GetSpinPrize(void)const;
  void SetSpinPrize(const Int32 value);
  ///=====================================
  ///@brief member SpinType
  ///=====================================
  Int32 GetSpinType(void)const;
  void SetSpinType(const Int32 value);
  ///=====================================
  ///@brief member FreeGamesAwarded
  ///=====================================
  Int32 GetFreeGamesAwarded(void)const;
  void SetFreeGamesAwarded(const Int32 value);
  ///=====================================
  ///@brief member Multiplier
  ///=====================================
  Int32 GetMultiplier(void)const;
  void SetMultiplier(const Int32 value);
  ///=====================================
  ///@brief member SymbolMapperIndex
  ///=====================================
  Int32 GetSymbolMapperIndex(void)const;
  void SetSymbolMapperIndex(const Int32 value);
  ///=====================================
  ///@brief member ReelStops
  ///=====================================
  Int32 ReelStopCount(void)const;
  Int32 GetReelStop(const Int32 index)const;
  void SetReelStop(const Int32 index, const Int32 value);
  ///=====================================
  ///@brief memberModifiers
  ///=====================================
  Int32 ModifierCount(void)const;
  Modifier& GetModifier(const Int32 index);
  void AddModifier(const Modifier& value);
  void ClearModifiers(void);
  
  ///=====================================
  ///@brief member PaylineDataPresent
  ///=====================================
  Int32 GetPaylineDataPresent(void)const;
  void SetPaylineDataPresent(const Int32 value);
  ///=====================================
  ///@brief memberPaylines
  ///=====================================
  Int32 PaylineCount(void)const;
  Payline& GetPayline(const Int32 index);
  void AddPayline(const Payline& value);
  void ClearPaylines(void);
  

  ///=====================================
  ///@brief Fill structure from integer array
  ///=====================================
  static FiredUpSpin Parse(const std::vector< Int32 >& array);
  static FiredUpSpin Parse(const std::vector< Int32 >& array, Int32& index);

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
  Int32 m_SpinPrize;
  Int32 m_SpinType;
  Int32 m_FreeGamesAwarded;
  Int32 m_Multiplier;
  Int32 m_SymbolMapperIndex;
  Int32 m_ReelStops[5];
  std::vector<Modifier> m_Modifiers;
  Int32 m_PaylineDataPresent;
  std::vector<Payline> m_Paylines;
};

///
///@brief Helper to see if a given buffer satisfies the
///'requirements' for being a certain type.
///
bool IsFiredUpSpin(const std::vector< Int32 >& array);

}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::FiredUpSpin& data);

#endif
