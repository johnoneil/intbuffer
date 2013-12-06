//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file FreeGameData.cpp
//@date Dec-05-0506PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "FreeGameData.hpp"

using namespace wbf;

FreeGameData::FreeGameData()
  :m_HeaderId(1)
  ,m_ThemeId(2)
  ,m_FormatId(1)
  ,m_VersionId(3)
  {};

///============================================================================
Int32 FreeGameData::GetHeaderId(void)const{return m_HeaderId;};

///============================================================================
Int32 FreeGameData::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 FreeGameData::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 FreeGameData::GetVersionId(void)const{return m_VersionId;};

///============================================================================
Int32 FreeGameData::GetTotalPrize(void)const{return m_TotalPrize;};
void FreeGameData::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 FreeGameData::FiredUpSpinCount(void)const{return static_cast< Int32 >(m_FiredUpSpins.size());};
FiredUpSpin& FreeGameData::GetFiredUpSpin(const Int32 index){return m_FiredUpSpins.at(index);};
void FreeGameData::AddFiredUpSpin(const FiredUpSpin& value){m_FiredUpSpins.push_back(value);};
void FreeGameData::ClearFiredUpSpins(void){m_FiredUpSpins.clear();};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
FreeGameData FreeGameData::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return FreeGameData::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
FreeGameData FreeGameData::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  FreeGameData returnValue;
  const Int32 size=gameEvent.GetParam(index++);
  if(gameEvent.GetParamCount()-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("FreeGameData cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_HeaderId=gameEvent.GetParam(index++);
  if(returnValue.m_HeaderId!=1)
  {
    throw std::runtime_error("FreeGameData cannot be generated from buffer due to incorrect value of m_HeaderId");
  }
  returnValue.m_ThemeId=gameEvent.GetParam(index++);
  if(returnValue.m_ThemeId!=2)
  {
    throw std::runtime_error("FreeGameData cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=gameEvent.GetParam(index++);
  if(returnValue.m_FormatId!=1)
  {
    throw std::runtime_error("FreeGameData cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_VersionId=gameEvent.GetParam(index++);
  if(returnValue.m_VersionId!=3)
  {
    throw std::runtime_error("FreeGameData cannot be generated from buffer due to incorrect value of m_VersionId");
  }
  returnValue.m_TotalPrize=gameEvent.GetParam(index++);
  {
    returnValue.m_FiredUpSpins.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
      FiredUpSpin value= FiredUpSpin::Parse(gameEvent, index);
      returnValue.m_FiredUpSpins.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGameData::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool FreeGameData::Write(std::vector< Int32 >& array, Int32& index)
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
    const Int32 count = FiredUpSpinCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetFiredUpSpin(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 FreeGameData::Size(void)const
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
    const Int32 count = FiredUpSpinCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_FiredUpSpins.at(i).Size();
    }
  }
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsFreeGameData(const EDC::IGameEvent& gameEvent)
{
  try
  {
    FreeGameData value = FreeGameData::Parse(gameEvent);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::FreeGameData& data)
{
  out<<"HeaderId:"<<data.GetHeaderId()<<std::endl;
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"VersionId:"<<data.GetVersionId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  for(Int32 i=0;i<data.FiredUpSpinCount();++i)
  {
    out<<"FiredUpSpin:"<<i<<":"<<data.GetFiredUpSpin(i)<<std::endl;
  }
  return out;
}


