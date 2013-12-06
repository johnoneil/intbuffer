//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file OverlayPosition.cpp
//@date Dec-05-0506PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "OverlayPosition.hpp"

using namespace wbf;


///============================================================================
Int32 OverlayPosition::ReelIndexCount(void)const{return static_cast< Int32 >(m_ReelIndexs.size());};
Int32 OverlayPosition::GetReelIndex(const Int32 index)const{return m_ReelIndexs.at(index);};
void OverlayPosition::AddReelIndex(const Int32 value){m_ReelIndexs.push_back(value);};
void OverlayPosition::ClearReelIndexs(void){m_ReelIndexs.clear();};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
OverlayPosition OverlayPosition::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return OverlayPosition::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
OverlayPosition OverlayPosition::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  OverlayPosition returnValue;
  {
    returnValue.m_ReelIndexs.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
     Int32 value = gameEvent.GetParam(index++);
      returnValue.m_ReelIndexs.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool OverlayPosition::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool OverlayPosition::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  {
    const Int32 count = ReelIndexCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      array[index++] = GetReelIndex(i);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 OverlayPosition::Size(void)const
{
 Int32 size = 0;
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = ReelIndexCount();
    for(Int32 i=0;i<count;++i)
    {
      ++size;
    }
  }
  return size;
}


//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::OverlayPosition& data)
{
  for(Int32 i=0;i<data.ReelIndexCount();++i)
  {
    out<<"ReelIndex:"<<i<<":"<<data.GetReelIndex(i)<<std::endl;
  }
  return out;
}


