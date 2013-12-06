//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file OverlaySymbol.cpp
//@date Dec-05-0715PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "OverlaySymbol.hpp"

using namespace wbf;


///============================================================================
Int32 OverlaySymbol::GetHeaderId(void)const{return m_HeaderId;};
void OverlaySymbol::SetHeaderId(const Int32 value){m_HeaderId=value;};

///============================================================================
Int32 OverlaySymbol::GetOverlaySymbolId(void)const{return m_OverlaySymbolId;};
void OverlaySymbol::SetOverlaySymbolId(const Int32 value){m_OverlaySymbolId=value;};

//==============================================================================
Int32 OverlaySymbol::OverlayPositionCount(void)const{return 5;};
OverlayPosition& OverlaySymbol::GetOverlayPosition(const Int32 index)
{
  if(index<0||index>=OverlayPositionCount())
  {
    return m_OverlayPositions[0];//don't want to throw.
  }
  return m_OverlayPositions[index];
}
void OverlaySymbol::SetOverlayPosition(const Int32 index, const OverlayPosition& value)
{
  if(index<0||index>=OverlayPositionCount())
  {
    return;//I don't want to throw.
  }
  m_OverlayPositions[index] = value;
}

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
OverlaySymbol OverlaySymbol::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return OverlaySymbol::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
OverlaySymbol OverlaySymbol::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  OverlaySymbol returnValue;
  returnValue.m_HeaderId=gameEvent.GetParam(index++);
  returnValue.m_OverlaySymbolId=gameEvent.GetParam(index++);
  {
    const Int32 count = 5;
    for(Int32 i=0;i<count;++i)
    {
      OverlayPosition value= OverlayPosition::Parse(gameEvent, index);
      returnValue.SetOverlayPosition(i, value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool OverlaySymbol::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool OverlaySymbol::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = m_HeaderId;
  array[index++] = m_OverlaySymbolId;
  {
    const Int32 count = OverlayPositionCount();
    for(Int32 i=0;i<count;++i)
    {
      GetOverlayPosition(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 OverlaySymbol::Size(void)const
{
 Int32 size = 0;
  ++size;//HeaderId
  ++size;//OverlaySymbolId
  {
    const Int32 count = OverlayPositionCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_OverlayPositions[i].Size();
    }
  }
  return size;
}


//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::OverlaySymbol& data)
{
  out<<"HeaderId:"<<data.GetHeaderId()<<std::endl;
  out<<"OverlaySymbolId:"<<data.GetOverlaySymbolId()<<std::endl;
  for(Int32 i=0;i<data.OverlayPositionCount();++i)
  {
    out<<"OverlayPosition:"<<i<<":"<<data.GetOverlayPosition(i)<<std::endl;
  }
  return out;
}


