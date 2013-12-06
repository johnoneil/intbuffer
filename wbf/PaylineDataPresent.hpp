//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file PaylineDataPresent.hpp
//@date Dec-05-0715PM-2013
//
//This file generated via intbuffer tool
//Search Confluence online for description.
//-----------------------------------------------------------------------------
#pragma once

#ifndef __WBF_PAYLINEDATAPRESENT_HPP__
#define __WBF_PAYLINEDATAPRESENT_HPP__

#include <vector>
#include <iostream>
#include "Payline.hpp"
namespace wbf
{

class PaylineDataPresent
{
public:

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
  static PaylineDataPresent Parse(const EDC::IGameEvent& gameEvent);
  static PaylineDataPresent Parse(const EDC::IGameEvent& gameEvent, Int32& index);

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
  std::vector<Payline> m_Paylines;
};


}//namespace wbf

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, wbf::PaylineDataPresent& data);

#endif
