//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file BaseGame.cpp
//@date Nov-27-0804PM-2013
//
//-----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "BaseGame.hpp"

using namespace wbf;

BaseGame::BaseGame()
  :m_ThemeId(4)
  ,m_FormatId(1)
  {};

///============================================================================
Int32 BaseGame::GetThemeId(void)const{return m_ThemeId;};

///============================================================================
Int32 BaseGame::GetFormatId(void)const{return m_FormatId;};

///============================================================================
Int32 BaseGame::GetTotalPrize(void)const{return m_TotalPrize;};
void BaseGame::SetTotalPrize(const Int32 value){m_TotalPrize=value;};

///============================================================================
Int32 BaseGame::GetReelSetId(void)const{return m_ReelSetId;};
void BaseGame::SetReelSetId(const Int32 value){m_ReelSetId=value;};

//==============================================================================
Overlays& BaseGame::GetOverlays(void){return m_Overlays;};
void BaseGame::SetOverlays(const Overlays& value){m_Overlays=value;};

//==============================================================================
//Static method that returns instance of class from buffer
//Reccomend testing buffer before using as this may throw
//==============================================================================
BaseGame BaseGame::Parse(const std::vector< Int32 >& array)
{
  Int32 index = 0;
  return BaseGame::Parse(array, index);
}

//==============================================================================
//Static method that returns instance of class from array starting at index
//==============================================================================
BaseGame BaseGame::Parse(const std::vector< Int32 >& array, Int32& index)
{
  BaseGame returnValue;
  const Int32 size=array[index++];
  if(static_cast<Int32>(array.size())-index+1<size)
  {
    //not enough array for whole class. throw.
    throw std::runtime_error("BaseGame cannot be generated from buffer due to incorrect size.");
  }
  returnValue.m_ThemeId=array[index++];
  if(returnValue.m_ThemeId!=4)
  {
    throw std::runtime_error("BaseGame cannot be generated from buffer due to incorrect value of m_ThemeId");
  }
  returnValue.m_FormatId=array[index++];
  if(returnValue.m_FormatId!=1)
  {
    throw std::runtime_error("BaseGame cannot be generated from buffer due to incorrect value of m_FormatId");
  }
  returnValue.m_TotalPrize=array[index++];
  returnValue.m_ReelSetId=array[index++];
  returnValue.m_Overlays = Overlays::Parse(array, index);
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool BaseGame::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool BaseGame::Write(std::vector< Int32 >& array, Int32& index)
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
Int32 BaseGame::Size(void)const
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
bool wbf::IsBaseGame(const std::vector< Int32 >& array)
{
  try
  {
    BaseGame value = BaseGame::Parse(array);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::BaseGame& data)
{
  out<<"ThemeId:"<<data.GetThemeId()<<std::endl;
  out<<"FormatId:"<<data.GetFormatId()<<std::endl;
  out<<"TotalPrize:"<<data.GetTotalPrize()<<std::endl;
  out<<"ReelSetId:"<<data.GetReelSetId()<<std::endl;
  out<<"Overlays:"<<data.GetOverlays()<<std::endl;
  return out;
}


