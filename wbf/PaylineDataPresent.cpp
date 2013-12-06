//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file PaylineDataPresent.cpp
//@date Dec-05-0715PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "PaylineDataPresent.hpp"

using namespace wbf;


///============================================================================
Int32 PaylineDataPresent::PaylineCount(void)const{return static_cast< Int32 >(m_Paylines.size());};
Payline& PaylineDataPresent::GetPayline(const Int32 index){return m_Paylines.at(index);};
void PaylineDataPresent::AddPayline(const Payline& value){m_Paylines.push_back(value);};
void PaylineDataPresent::ClearPaylines(void){m_Paylines.clear();};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
PaylineDataPresent PaylineDataPresent::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return PaylineDataPresent::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
PaylineDataPresent PaylineDataPresent::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  PaylineDataPresent returnValue;
  {
    returnValue.m_Paylines.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
      Payline value= Payline::Parse(gameEvent, index);
      returnValue.m_Paylines.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool PaylineDataPresent::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool PaylineDataPresent::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  {
    const Int32 count = PaylineCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetPayline(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 PaylineDataPresent::Size(void)const
{
 Int32 size = 0;
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = PaylineCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_Paylines.at(i).Size();
    }
  }
  return size;
}


//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::PaylineDataPresent& data)
{
  for(Int32 i=0;i<data.PaylineCount();++i)
  {
    out<<"Payline:"<<i<<":"<<data.GetPayline(i)<<std::endl;
  }
  return out;
}


