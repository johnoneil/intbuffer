///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file FreeGamesData.cpp
///@date Nov-24-0731PM-2013
///
///----------------------------------------------------------------------------

//#include "Pch.hpp"
#include "FreeGamesData.hpp"

using namespace IntBuffer;


FreeGamesData::FreeGamesData()

  :m_ThemeId(3)
  ,m_VersionId(4)
  {};

///=====================================
///ThemeId
///=====================================
 Int32  FreeGamesData::GetThemeId(void)const{return m_ThemeId;};
///=====================================
///VersionId
///=====================================
 Int32  FreeGamesData::GetVersionId(void)const{return m_VersionId;};
///=====================================
///Win
///=====================================
 Int32  FreeGamesData::GetWin(void)const{return m_Win;};
void FreeGamesData::SetWin(const  Int32  value){m_Win=value;};
///=====================================
///FreeGames
///=====================================
FreeGames& FreeGamesData::GetFreeGames(void){return m_FreeGames;};
void FreeGamesData::SetFreeGames(const FreeGames& value){m_FreeGames=value;};

///=====================================
///Fill structure from integer array
///=====================================
FreeGamesData FreeGamesData::Parse(std::vector< Int32 >& array)
{
  Int32 index=0;
  return FreeGamesData::Parse(array, index);
}

FreeGamesData FreeGamesData::Parse(std::vector< Int32 >& array,  Int32 & index)
{
  FreeGamesData returnValue;
	const  Int32  size=array[index++];
	//TODO: failure on incorrect size?
  returnValue.m_ThemeId=array[index++];
	//TODO: test integers that have required default values
  returnValue.m_VersionId=array[index++];
	//TODO: test integers that have required default values
  returnValue.m_Win=array[index++];
	//TODO: test integers that have required default values
	returnValue.m_FreeGames= FreeGames::Parse(array, index);
  return returnValue;
}

bool FreeGamesData::Write(std::vector< Int32 >& array)
{
  Int32 index=0;
  return Write(array, index);
}

bool FreeGamesData::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++]=size;
  array[index++] = m_ThemeId;
  array[index++] = m_VersionId;
  array[index++] = m_Win;
	m_FreeGames.Write(array, index);
  return true;
}

//
// Get the size of this class in 32 bit integers
//
 Int32  FreeGamesData::Size(void)const
{
   Int32  size=0;
  ++size;//ThemeId
  ++size;//VersionId
  ++size;//Win
  size+=m_FreeGames.Size();
  return size;
}


