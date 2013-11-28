//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file InitialSpin.cpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "InitialSpin.hpp"

using namespace wbf;

InitialSpin::InitialSpin()
  :m_HeaderId(0)
  ,m_ThemeId(2)
  ,m_FormatId(1)
  ,m_VersionId(3)
  {};

///============================================================================
Int32 InitialSpin::GetHeaderId(void)const{return m_HeaderId;};

///============================================================================
Int32 InitialSpin::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 InitialSpin::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 InitialSpin::GetVersionId(void)const{return m_VersionId;};

///============================================================================
Int32 InitialSpin::GetTotalPrize(void)const{return m_TotalPrize;};
void InitialSpin::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 InitialSpin::TriggeringSpinCount(void)const{return static_cast< Int32 >(m_TriggeringSpins.size());};
TriggeringSpin& InitialSpin::GetTriggeringSpin(const Int32 index){return m_TriggeringSpins.at(index);};
void InitialSpin::AddTriggeringSpin(const TriggeringSpin& value){m_TriggeringSpins.push_back(value);};
void InitialSpin::ClearTriggeringSpins(void){m_TriggeringSpins.clear();};

//==============================================================================
//Static method that returns instance of class from buffer
//Reccomend testing buffer before using as this may throw
//==============================================================================
InitialSpin InitialSpin::Parse(const std::vector< Int32 >& array)
{
  Int32 index = 0;
  return InitialSpin::Parse(array, index);
}

//==============================================================================
//Static method that returns instance of class from array starting at index
//==============================================================================
InitialSpin InitialSpin::Parse(const std::vector< Int32 >& array, Int32& index)
{
  InitialSpin returnValue;
  const Int32 size=array[index++];
  if(static_cast<Int32>(array.size())-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("InitialSpin cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_HeaderId=array[index++];
  if(returnValue.m_HeaderId!=0)
  {
    throw std::runtime_error("InitialSpin cannot be generated from buffer due to incorrect value of m_HeaderId");
  }
  returnValue.m_ThemeId=array[index++];
  if(returnValue.m_ThemeId!=2)
  {
    throw std::runtime_error("InitialSpin cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=array[index++];
  if(returnValue.m_FormatId!=1)
  {
    throw std::runtime_error("InitialSpin cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_VersionId=array[index++];
  if(returnValue.m_VersionId!=3)
  {
    throw std::runtime_error("InitialSpin cannot be generated from buffer due to incorrect value of m_VersionId");
  }
  returnValue.m_TotalPrize=array[index++];
  {
    returnValue.m_TriggeringSpins.clear();
    const Int32 count = array[index++];
    for(Int32 i=0;i<count;++i)
    {
      TriggeringSpin value= TriggeringSpin::Parse(array, index);
      returnValue.m_TriggeringSpins.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool InitialSpin::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool InitialSpin::Write(std::vector< Int32 >& array, Int32& index)
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
    const Int32 count = TriggeringSpinCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetTriggeringSpin(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 InitialSpin::Size(void)const
{
 Int32 size = 0;
  ++size;//sized class header
  ++size;//HeaderId
  ++size;//ThemeId
  ++size;//FormatId
  ++size;//VersionId
  ++size;//TotalPrize
  ++size;//increment once for the number of elements 'header'
  const Int32 count = TriggeringSpinCount();
  for(Int32 i=0;i<count;++i)
  {
    size+=m_TriggeringSpins.at(i).Size();
  }
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsInitialSpin(const std::vector< Int32 >& array)
{
  try
  {
    InitialSpin value = InitialSpin::Parse(array);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::InitialSpin& data)
{
  out<<"HeaderId:"<<data.GetHeaderId()<<std::endl;
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"VersionId:"<<data.GetVersionId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  for(Int32 i=0;i<data.TriggeringSpinCount();++i)
  {
    out<<"TriggeringSpin:"<<i<<":"<<data.GetTriggeringSpin(i)<<std::endl;
  }
  return out;
}


