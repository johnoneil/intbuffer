//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGames.cpp
//@date Dec-07-1215PM-2013
//
//-----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "FreeGames.hpp"

using namespace FreeGamesBonus;

FreeGames::FreeGames()
  :m_ThemeId(2)
  ,m_VersionId(3)
  {};

///============================================================================
Int32 FreeGames::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 FreeGames::GetVersionId(void)const{return m_VersionId;};

///============================================================================
Int32 FreeGames::GetWin(void)const{return m_Win;};
void FreeGames::SetWin(const Int32 value){m_Win=value;};

///============================================================================
Int32 FreeGames::SpinCount(void)const{return static_cast< Int32 >(m_Spins.size());};
Spin& FreeGames::GetSpin(const Int32 index){return m_Spins.at(index);};
void FreeGames::AddSpin(const Spin& value){m_Spins.push_back(value);};
void FreeGames::ClearSpins(void){m_Spins.clear();};

//==============================================================================
//Static method that returns instance of class from buffer
//Reccomend testing buffer before using as this may throw
//==============================================================================
FreeGames FreeGames::Parse(const std::vector< Int32 >& array)
{
  Int32 index = 0;
  return FreeGames::Parse(array, index);
}

//==============================================================================
//Static method that returns instance of class from array starting at index
//==============================================================================
FreeGames FreeGames::Parse(const std::vector< Int32 >& array, Int32& index)
{
  FreeGames returnValue;
  const Int32 size=array[index++];
  if(static_cast<Int32>(array.size())-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("FreeGames cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_ThemeId=array[index++];
  if(returnValue.m_ThemeId!=2)
  {
    throw std::runtime_error("FreeGames cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_VersionId=array[index++];
  if(returnValue.m_VersionId!=3)
  {
    throw std::runtime_error("FreeGames cannot be generated from buffer due to incorrect value of m_VersionId");
  }
  returnValue.m_Win=array[index++];
  {
    returnValue.m_Spins.clear();
    const Int32 count = array[index++];
    for(Int32 i=0;i<count;++i)
    {
      Spin value= Spin::Parse(array, index);
      returnValue.m_Spins.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGames::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGames::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = size;
  array[index++] = m_ThemeId;
  array[index++] = m_VersionId;
  array[index++] = m_Win;
  {
    const Int32 count = SpinCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetSpin(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 FreeGames::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//ThemeId
  ++size;//VersionId
  ++size;//Win
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = SpinCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_Spins.at(i).Size();
    }
  }
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool FreeGamesBonus::IsFreeGames(const std::vector< Int32 >& array)
{
  try
  {
    FreeGames value = FreeGames::Parse(array);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, FreeGamesBonus::FreeGames& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"VersionId:"<<data.GetVersionId()<<std::endl;
  out<<"Win:"<<data.GetWin()<<std::endl;
  for(Int32 i=0;i<data.SpinCount();++i)
  {
    out<<"Spin:"<<i<<":"<<data.GetSpin(i)<<std::endl;
  }
  return out;
}


