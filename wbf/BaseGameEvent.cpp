//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file BaseGameEvent.cpp
//@date Dec-05-0715PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "BaseGameEvent.hpp"

using namespace wbf;

BaseGameEvent::BaseGameEvent()
  :m_ThemeId(4)
  ,m_FormatId(1)
  {};

///============================================================================
Int32 BaseGameEvent::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 BaseGameEvent::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 BaseGameEvent::GetTotalPrize(void)const{return m_TotalPrize;};
void BaseGameEvent::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 BaseGameEvent::GetReelSetId(void)const{return m_ReelSetId;};
void BaseGameEvent::SetReelSetId(const Int32 value){m_ReelSetId=value;};

//==============================================================================
Overlays& BaseGameEvent::GetOverlays(void){return m_Overlays;};
void BaseGameEvent::SetOverlays(const Overlays& value){m_Overlays=value;};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
BaseGameEvent BaseGameEvent::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return BaseGameEvent::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
BaseGameEvent BaseGameEvent::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  BaseGameEvent returnValue;
  const Int32 size=gameEvent.GetParam(index++);
  if(gameEvent.GetParamCount()-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("BaseGameEvent cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_ThemeId=gameEvent.GetParam(index++);
  if(returnValue.m_ThemeId!=4)
  {
    throw std::runtime_error("BaseGameEvent cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=gameEvent.GetParam(index++);
  if(returnValue.m_FormatId!=1)
  {
    throw std::runtime_error("BaseGameEvent cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_TotalPrize=gameEvent.GetParam(index++);
  returnValue.m_ReelSetId=gameEvent.GetParam(index++);
  returnValue.m_Overlays = Overlays::Parse(gameEvent, index);
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool BaseGameEvent::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool BaseGameEvent::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = size;
  array[index++] = m_ThemeId;
  array[index++] = m_FormatId;
  array[index++] = m_TotalPrize;
  array[index++] = m_ReelSetId;
  m_Overlays.Write(array, index);
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 BaseGameEvent::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//ThemeId
  ++size;//FormatId
  ++size;//TotalPrize
  ++size;//ReelSetId
  size+=m_Overlays.Size();
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsBaseGameEvent(const EDC::IGameEvent& gameEvent)
{
  try
  {
    BaseGameEvent value = BaseGameEvent::Parse(gameEvent);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::BaseGameEvent& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  out<<"ReelSetId:"<<data.GetReelSetId()<<std::endl;
  out<<"Overlays:"<<data.GetOverlays()<<std::endl;
  return out;
}


