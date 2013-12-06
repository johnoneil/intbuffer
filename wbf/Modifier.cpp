//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Modifier.cpp
//@date Dec-05-0715PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "Modifier.hpp"

using namespace wbf;


///============================================================================
Int32 Modifier::GetSymbolIndex(void)const{return m_SymbolIndex;};
void Modifier::SetSymbolIndex(const Int32 value){m_SymbolIndex=value;};

///============================================================================
Int32 Modifier::LocationCount(void)const{return static_cast< Int32 >(m_Locations.size());};
Int32 Modifier::GetLocation(const Int32 index)const{return m_Locations.at(index);};
void Modifier::AddLocation(const Int32 value){m_Locations.push_back(value);};
void Modifier::ClearLocations(void){m_Locations.clear();};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
Modifier Modifier::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return Modifier::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
Modifier Modifier::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  Modifier returnValue;
  returnValue.m_SymbolIndex=gameEvent.GetParam(index++);
  {
    returnValue.m_Locations.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
     Int32 value = gameEvent.GetParam(index++);
      returnValue.m_Locations.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Modifier::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Modifier::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = m_SymbolIndex;
  {
    const Int32 count = LocationCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      array[index++] = GetLocation(i);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 Modifier::Size(void)const
{
 Int32 size = 0;
  ++size;//SymbolIndex
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = LocationCount();
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
std::ostream& operator<<(std::ostream &out, wbf::Modifier& data)
{
  out<<"SymbolIndex:"<<data.GetSymbolIndex()<<std::endl;
  for(Int32 i=0;i<data.LocationCount();++i)
  {
    out<<"Location:"<<i<<":"<<data.GetLocation(i)<<std::endl;
  }
  return out;
}


