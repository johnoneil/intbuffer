//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FastFireBonus.cpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "FastFireBonus.hpp"

using namespace wbf;

FastFireBonus::FastFireBonus()
  :m_ThemeId(2)
  ,m_FormatId(1)
  ,m_NumberOfObjects(1)
  {};

///============================================================================
Int32 FastFireBonus::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 FastFireBonus::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 FastFireBonus::GetTotalPrize(void)const{return m_TotalPrize;};
void FastFireBonus::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 FastFireBonus::GetNumberOfObjects(void)const{return m_NumberOfObjects;};

//==============================================================================
InitialSpin& FastFireBonus::GetInitialSpin(void){return m_InitialSpin;};
void FastFireBonus::SetInitialSpin(const InitialSpin& value){m_InitialSpin=value;};

//==============================================================================
Overlays& FastFireBonus::GetOverlays(void){return m_Overlays;};
void FastFireBonus::SetOverlays(const Overlays& value){m_Overlays=value;};

//==============================================================================
FreeGames& FastFireBonus::GetFreeGames(void){return m_FreeGames;};
void FastFireBonus::SetFreeGames(const FreeGames& value){m_FreeGames=value;};

//==============================================================================
//Static method that returns instance of class from buffer
//Reccomend testing buffer before using as this may throw
//==============================================================================
FastFireBonus FastFireBonus::Parse(const std::vector< Int32 >& array)
{
  Int32 index = 0;
  return FastFireBonus::Parse(array, index);
}

//==============================================================================
//Static method that returns instance of class from array starting at index
//==============================================================================
FastFireBonus FastFireBonus::Parse(const std::vector< Int32 >& array, Int32& index)
{
  FastFireBonus returnValue;
  const Int32 size=array[index++];
  if(static_cast<Int32>(array.size())-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("FastFireBonus cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_ThemeId=array[index++];
  if(returnValue.m_ThemeId!=2)
  {
    throw std::runtime_error("FastFireBonus cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=array[index++];
  if(returnValue.m_FormatId!=1)
  {
    throw std::runtime_error("FastFireBonus cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_TotalPrize=array[index++];
  returnValue.m_NumberOfObjects=array[index++];
  if(returnValue.m_NumberOfObjects!=1)
  {
    throw std::runtime_error("FastFireBonus cannot be generated from buffer due to incorrect value of m_NumberOfObjects");
  }
  returnValue.m_InitialSpin = InitialSpin::Parse(array, index);
  returnValue.m_Overlays = Overlays::Parse(array, index);
  returnValue.m_FreeGames = FreeGames::Parse(array, index);
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FastFireBonus::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FastFireBonus::Write(std::vector< Int32 >& array, Int32& index)
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
  m_FreeGames.Write(array, index);
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 FastFireBonus::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//ThemeId
  ++size;//FormatId
  ++size;//TotalPrize
  ++size;//NumberOfObjects
  size+=m_InitialSpin.Size();
  size+=m_Overlays.Size();
  size+=m_FreeGames.Size();
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsFastFireBonus(const std::vector< Int32 >& array)
{
  try
  {
    FastFireBonus value = FastFireBonus::Parse(array);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::FastFireBonus& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  out<<"NumberOfObjects:"<<data.GetNumberOfObjects()<<std::endl;
  out<<"InitialSpin:"<<data.GetInitialSpin()<<std::endl;
  out<<"Overlays:"<<data.GetOverlays()<<std::endl;
  out<<"FreeGames:"<<data.GetFreeGames()<<std::endl;
  return out;
}


