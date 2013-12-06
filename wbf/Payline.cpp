//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Payline.cpp
//@date Dec-05-0715PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "Payline.hpp"

using namespace wbf;


///============================================================================
Int32 Payline::GetIndex(void)const{return m_Index;};
void Payline::SetIndex(const Int32 value){m_Index=value;};

///============================================================================
Int32 Payline::GetMask(void)const{return m_Mask;};
void Payline::SetMask(const Int32 value){m_Mask=value;};

///============================================================================
Int32 Payline::GetWinAmount(void)const{return m_WinAmount;};
void Payline::SetWinAmount(const Int32 value){m_WinAmount=value;};

///============================================================================
Int32 Payline::GetWinId(void)const{return m_WinId;};
void Payline::SetWinId(const Int32 value){m_WinId=value;};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
Payline Payline::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return Payline::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
Payline Payline::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  Payline returnValue;
  returnValue.m_Index=gameEvent.GetParam(index++);
  returnValue.m_Mask=gameEvent.GetParam(index++);
  returnValue.m_WinAmount=gameEvent.GetParam(index++);
  returnValue.m_WinId=gameEvent.GetParam(index++);
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Payline::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Payline::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = m_Index;
  array[index++] = m_Mask;
  array[index++] = m_WinAmount;
  array[index++] = m_WinId;
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 Payline::Size(void)const
{
 Int32 size = 0;
  ++size;//Index
  ++size;//Mask
  ++size;//WinAmount
  ++size;//WinId
  return size;
}


//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::Payline& data)
{
  out<<"Index:"<<data.GetIndex()<<std::endl;
  out<<"Mask:"<<data.GetMask()<<std::endl;
  out<<"WinAmount:"<<data.GetWinAmount()<<std::endl;
  out<<"WinId:"<<data.GetWinId()<<std::endl;
  return out;
}


