//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGamesData.cpp
//@date Dec-07-1215PM-2013
//
//-----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "FreeGamesData.hpp"

using namespace FreeGamesBonus;

FreeGamesData::FreeGamesData()
  :m_ThemeId(3)
  ,m_VersionId(4)
  {};

///============================================================================
Int32 FreeGamesData::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 FreeGamesData::GetVersionId(void)const{return m_VersionId;};

///============================================================================
Int32 FreeGamesData::GetWin(void)const{return m_Win;};
void FreeGamesData::SetWin(const Int32 value){m_Win=value;};

//==============================================================================
FreeGames& FreeGamesData::GetFreeGames(void){return m_FreeGames;};
void FreeGamesData::SetFreeGames(const FreeGames& value){m_FreeGames=value;};

//==============================================================================
//Static method that returns instance of class from buffer
//Reccomend testing buffer before using as this may throw
//==============================================================================
FreeGamesData FreeGamesData::Parse(const std::vector< Int32 >& array)
{
  Int32 index = 0;
  return FreeGamesData::Parse(array, index);
}

//==============================================================================
//Static method that returns instance of class from array starting at index
//==============================================================================
FreeGamesData FreeGamesData::Parse(const std::vector< Int32 >& array, Int32& index)
{
  FreeGamesData returnValue;
  const Int32 size=array[index++];
  if(static_cast<Int32>(array.size())-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("FreeGamesData cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_ThemeId=array[index++];
  if(returnValue.m_ThemeId!=3)
  {
    throw std::runtime_error("FreeGamesData cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_VersionId=array[index++];
  if(returnValue.m_VersionId!=4)
  {
    throw std::runtime_error("FreeGamesData cannot be generated from buffer due to incorrect value of m_VersionId");
  }
  returnValue.m_Win=array[index++];
  returnValue.m_FreeGames = FreeGames::Parse(array, index);
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGamesData::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGamesData::Write(std::vector< Int32 >& array, Int32& index)
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
  m_FreeGames.Write(array, index);
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 FreeGamesData::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//ThemeId
  ++size;//VersionId
  ++size;//Win
  size+=m_FreeGames.Size();
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool FreeGamesBonus::IsFreeGamesData(const std::vector< Int32 >& array)
{
  try
  {
    FreeGamesData value = FreeGamesData::Parse(array);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, FreeGamesBonus::FreeGamesData& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"VersionId:"<<data.GetVersionId()<<std::endl;
  out<<"Win:"<<data.GetWin()<<std::endl;
  out<<"FreeGames:"<<data.GetFreeGames()<<std::endl;
  return out;
}


