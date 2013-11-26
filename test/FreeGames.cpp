///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file FreeGames.cpp
///@date Nov-26-1221AM-2013
///
///----------------------------------------------------------------------------

//#include "Pch.hpp"
#include "FreeGames.hpp"

using namespace IntBuffer;


FreeGames::FreeGames()

  :m_ThemeId(2)
  ,m_VersionId(3)
  {};

///=====================================
///ThemeId
///=====================================
Int32  FreeGames::GetThemeId(void)const{return m_ThemeId;};
///=====================================
///VersionId
///=====================================
Int32  FreeGames::GetVersionId(void)const{return m_VersionId;};
///=====================================
///Win
///=====================================
Int32  FreeGames::GetWin(void)const{return m_Win;};
void FreeGames::SetWin(const  Int32  value){m_Win=value;};
///=====================================
///Spins
///=====================================
Int32  FreeGames::SpinCount(void)const{return static_cast< Int32 >(m_Spins.size());};
  Spin& FreeGames::GetSpin(const  Int32  index){return m_Spins.at(index);};
void FreeGames::AddSpin(const Spin& value){m_Spins.push_back(value);};
void FreeGames::ClearSpins(void){m_Spins.clear();};


///=====================================
///Fill structure from integer array
///=====================================
FreeGames FreeGames::Parse(std::vector< Int32 >& array)
{
  Int32 index=0;
  return FreeGames::Parse(array, index);
}

FreeGames FreeGames::Parse(std::vector< Int32 >& array,  Int32 & index)
{
  FreeGames returnValue;
  	const  Int32  size=array[index++];
	//TODO: failure on incorrect size?
  returnValue.m_ThemeId=array[index++];
  //TODO: test integers that have required default values
  returnValue.m_VersionId=array[index++];
  //TODO: test integers that have required default values
  returnValue.m_Win=array[index++];
  //TODO: test integers that have required default values
  {
    returnValue.m_Spins.clear();
    const  Int32  count=array[index++];
    for( Int32  i=0;i<count;++i)
    {
      Spin value= Spin::Parse(array, index);
      returnValue.m_Spins.push_back(value);
    }
  }
  return returnValue;
}

bool FreeGames::Write(std::vector< Int32 >& array)
{
  Int32 index=0;
  return Write(array, index);
}

bool FreeGames::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  //if(static_cast<Int32>(array.size())-index<size)
  {
  //  return false;//failed to write for lack of room
  }
  array[index++]=size;
  array[index++] = m_ThemeId;
  array[index++] = m_VersionId;
  array[index++] = m_Win;
	{
		const  Int32  count = SpinCount();
    array[index++] = count;
		for( Int32  i=0;i<count;++i)
		{
      GetSpin(i).Write(array, index);
		}
	}
  return true;
}

//
// Get the size of this class in 32 bit integers
//
Int32  FreeGames::Size(void)const
{
  Int32  size=0;
  ++size;//ThemeId
  ++size;//VersionId
  ++size;//Win
  ++size;//increment once for the number of elements 'header'
  for( Int32  i=0;i<m_Spins.size();++i)
  {
    size+=m_Spins.at(i).Size();
  }
  return size;
}

std::ostream& operator<<(std::ostream &out, IntBuffer::FreeGames& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"VersionId:"<<data.GetVersionId()<<std::endl;
  out<<"Win:"<<data.GetWin()<<std::endl;
  for( Int32  i=0;i<data.SpinCount();++i)
  {
    out<<"Spin:"<<i<<":"<<data.GetSpin(i)<<std::endl;
  }
}


