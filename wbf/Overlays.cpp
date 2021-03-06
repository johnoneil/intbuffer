//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file Overlays.cpp
//@date Dec-05-0715PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "Overlays.hpp"

using namespace wbf;

Overlays::Overlays()
  :m_ThemeId(2)
  ,m_FormatId(5)
  ,m_VersionId(1)
  {};

///============================================================================
Int32 Overlays::GetHeaderId(void)const{return m_HeaderId;};
void Overlays::SetHeaderId(const Int32 value){m_HeaderId=value;};

///============================================================================
Int32 Overlays::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 Overlays::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 Overlays::GetVersionId(void)const{return m_VersionId;};

///============================================================================
Int32 Overlays::GetTotalPrize(void)const{return m_TotalPrize;};
void Overlays::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 Overlays::OverlaySymbolCount(void)const{return static_cast< Int32 >(m_OverlaySymbols.size());};
OverlaySymbol& Overlays::GetOverlaySymbol(const Int32 index){return m_OverlaySymbols.at(index);};
void Overlays::AddOverlaySymbol(const OverlaySymbol& value){m_OverlaySymbols.push_back(value);};
void Overlays::ClearOverlaySymbols(void){m_OverlaySymbols.clear();};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
Overlays Overlays::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return Overlays::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
Overlays Overlays::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  Overlays returnValue;
  const Int32 size=gameEvent.GetParam(index++);
  if(gameEvent.GetParamCount()-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("Overlays cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_HeaderId=gameEvent.GetParam(index++);
  returnValue.m_ThemeId=gameEvent.GetParam(index++);
  if(returnValue.m_ThemeId!=2)
  {
    throw std::runtime_error("Overlays cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=gameEvent.GetParam(index++);
  if(returnValue.m_FormatId!=5)
  {
    throw std::runtime_error("Overlays cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_VersionId=gameEvent.GetParam(index++);
  if(returnValue.m_VersionId!=1)
  {
    throw std::runtime_error("Overlays cannot be generated from buffer due to incorrect value of m_VersionId");
  }
  returnValue.m_TotalPrize=gameEvent.GetParam(index++);
  {
    returnValue.m_OverlaySymbols.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
      OverlaySymbol value= OverlaySymbol::Parse(gameEvent, index);
      returnValue.m_OverlaySymbols.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Overlays::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool Overlays::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = size;
  array[index++] = m_HeaderId;
  array[index++] = m_ThemeId;
  array[index++] = m_FormatId;
  array[index++] = m_VersionId;
  array[index++] = m_TotalPrize;
  {
    const Int32 count = OverlaySymbolCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetOverlaySymbol(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 Overlays::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//HeaderId
  ++size;//ThemeId
  ++size;//FormatId
  ++size;//VersionId
  ++size;//TotalPrize
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = OverlaySymbolCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_OverlaySymbols.at(i).Size();
    }
  }
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsOverlays(const EDC::IGameEvent& gameEvent)
{
  try
  {
    Overlays value = Overlays::Parse(gameEvent);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::Overlays& data)
{
  out<<"HeaderId:"<<data.GetHeaderId()<<std::endl;
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"VersionId:"<<data.GetVersionId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  for(Int32 i=0;i<data.OverlaySymbolCount();++i)
  {
    out<<"OverlaySymbol:"<<i<<":"<<data.GetOverlaySymbol(i)<<std::endl;
  }
  return out;
}


