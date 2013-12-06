//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGamesBonus.cpp
//@date Dec-05-0506PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "FreeGamesBonus.hpp"

using namespace wbf;

FreeGamesBonus::FreeGamesBonus()
  :m_ThemeId(2)
  ,m_FormatId(1)
  ,m_NumberOfObjects(1)
  {};

///============================================================================
Int32 FreeGamesBonus::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 FreeGamesBonus::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 FreeGamesBonus::GetTotalPrize(void)const{return m_TotalPrize;};
void FreeGamesBonus::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 FreeGamesBonus::GetNumberOfObjects(void)const{return m_NumberOfObjects;};

//==============================================================================
InitialSpin& FreeGamesBonus::GetInitialSpin(void){return m_InitialSpin;};
void FreeGamesBonus::SetInitialSpin(const InitialSpin& value){m_InitialSpin=value;};

//==============================================================================
Overlays& FreeGamesBonus::GetOverlays(void){return m_Overlays;};
void FreeGamesBonus::SetOverlays(const Overlays& value){m_Overlays=value;};

//==============================================================================
FreeGameData& FreeGamesBonus::GetFreeGameData(void){return m_FreeGameData;};
void FreeGamesBonus::SetFreeGameData(const FreeGameData& value){m_FreeGameData=value;};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
FreeGamesBonus FreeGamesBonus::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return FreeGamesBonus::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
FreeGamesBonus FreeGamesBonus::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  FreeGamesBonus returnValue;
  const Int32 size=gameEvent.GetParam(index++);
  if(gameEvent.GetParamCount()-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("FreeGamesBonus cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_ThemeId=gameEvent.GetParam(index++);
  if(returnValue.m_ThemeId!=2)
  {
    throw std::runtime_error("FreeGamesBonus cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=gameEvent.GetParam(index++);
  if(returnValue.m_FormatId!=1)
  {
    throw std::runtime_error("FreeGamesBonus cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_TotalPrize=gameEvent.GetParam(index++);
  returnValue.m_NumberOfObjects=gameEvent.GetParam(index++);
  if(returnValue.m_NumberOfObjects!=1)
  {
    throw std::runtime_error("FreeGamesBonus cannot be generated from buffer due to incorrect value of m_NumberOfObjects");
  }
  returnValue.m_InitialSpin = InitialSpin::Parse(gameEvent, index);
  returnValue.m_Overlays = Overlays::Parse(gameEvent, index);
  returnValue.m_FreeGameData = FreeGameData::Parse(gameEvent, index);
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGamesBonus::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGamesBonus::Write(std::vector< Int32 >& array, Int32& index)
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
  array[index++] = m_NumberOfObjects;
  m_InitialSpin.Write(array, index);
  m_Overlays.Write(array, index);
  m_FreeGameData.Write(array, index);
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 FreeGamesBonus::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//ThemeId
  ++size;//FormatId
  ++size;//TotalPrize
  ++size;//NumberOfObjects
  size+=m_InitialSpin.Size();
  size+=m_Overlays.Size();
  size+=m_FreeGameData.Size();
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsFreeGamesBonus(const EDC::IGameEvent& gameEvent)
{
  try
  {
    FreeGamesBonus value = FreeGamesBonus::Parse(gameEvent);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::FreeGamesBonus& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  out<<"NumberOfObjects:"<<data.GetNumberOfObjects()<<std::endl;
  out<<"InitialSpin:"<<data.GetInitialSpin()<<std::endl;
  out<<"Overlays:"<<data.GetOverlays()<<std::endl;
  out<<"FreeGameData:"<<data.GetFreeGameData()<<std::endl;
  return out;
}


