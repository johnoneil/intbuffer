//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Spin.cpp
//@date Dec-07-1213PM-2013
//
//-----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "Spin.hpp"

using namespace FreeGamesBonus;


//==============================================================================
Int32 Spin::StopCount(void)const{return 5;};
Int32 Spin::GetStop(const Int32 index)const
{
  if(index<0||index>=StopCount())
  {
    return -1;//there's a chance -1 is not adequate. but I don't want to throw.
  }
  return m_Stops[index];
}
void Spin::SetStop(const Int32 index, const Int32 value)
{
  if(index<0||index>=StopCount())
  {
    return;//I don't want to throw.
  }
  m_Stops[index] = value;
}

///============================================================================
Int32 Spin::GetPrize(void)const{return m_Prize;};
void Spin::SetPrize(const Int32 value){m_Prize=value;};

//==============================================================================
//Static method that returns instance of class from buffer
//Reccomend testing buffer before using as this may throw
//==============================================================================
Spin Spin::Parse(const std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Spin::Parse(array, index);
}

//==============================================================================
//Static method that returns instance of class from array starting at index
//==============================================================================
Spin Spin::Parse(const std::vector< Int32 >& array, Int32& index)
{
  Spin returnValue;
  {
    const Int32 count = 5;
    for(Int32 i=0;i<count;++i)
    {
      Int32 value = array[index++];
      returnValue.SetStop(i, value);
    }
  }
  returnValue.m_Prize=array[index++];
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Spin::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Spin::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  {
    const Int32 count = StopCount();
    for(Int32 i=0;i<count;++i)
    {
      array[index++] = GetStop(i);
    }
  }
  array[index++] = m_Prize;
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 Spin::Size(void)const
{
 Int32 size = 0;
  {
    const Int32 count = StopCount();
    for(Int32 i=0;i<count;++i)
    {
      ++size;
    }
  }
  ++size;//Prize
  return size;
}


//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, FreeGamesBonus::Spin& data)
{
  for(Int32 i=0;i<data.StopCount();++i)
  {
    out<<"Stop:"<<i<<":"<<data.GetStop(i)<<std::endl;
  }
  out<<"Prize:"<<data.GetPrize()<<std::endl;
  return out;
}


