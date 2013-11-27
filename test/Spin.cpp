///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file Spin.cpp
///@date Nov-26-0528PM-2013
///
///----------------------------------------------------------------------------

//#include "Pch.hpp"
#include <stdexcept>
#include "Spin.hpp"

using namespace IntBuffer;

///=====================================
///Stops
///=====================================
Int32 Spin::StopCount(void)const{return 5;};
Int32 Spin::GetStop(const Int32 index)const{return m_Stops.at(index);};
void Spin::AddStop(const Int32 value){m_Stops.push_back(value);};
void Spin::ClearStops(void){m_Stops.clear();};
///=====================================
///Prize
///=====================================
Int32 Spin::GetPrize(void)const{return m_Prize;};
void Spin::SetPrize(const Int32 value){m_Prize=value;};

///=====================================
///Fill structure from integer array
///=====================================
Spin Spin::Parse(const std::vector< Int32 >& array)
{
 Int32 index=0;
  return Spin::Parse(array, index);
}

Spin Spin::Parse(const std::vector< Int32 >& array, Int32& index)
{
  Spin returnValue;
  {
    //This is a set
    returnValue.m_Stops.clear();
    const Int32 count=5;
    for(Int32 i=0;i<count;++i)
    {
     Int32 value= array[index++];
      returnValue.m_Stops.push_back(value);
    }
  }
  returnValue.m_Prize=array[index++];
  return returnValue;
}

bool Spin::Write(std::vector< Int32 >& array)
{
  Int32 index=0;
  return Write(array, index);
}

bool Spin::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  //if(static_cast<Int32>(array.size())-index<size)
  {
    //return false;//failed to write for lack of room
  }
  {
    const Int32 count = StopCount();
    //As "set" is defined as a STATIC list with known number of elements
    //therefore we don't have to head it with the element count    
    //array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      array[index++]=GetStop(i);
    }
  }
  array[index++] = m_Prize;
  return true;
}

//
// Get the size of this class in 32 bit integers
//
Int32 Spin::Size(void)const
{
 Int32 size=0;
  {
    const Int32 count = StopCount();
    for(Int32 i=0;i<count;++i)
    {
      ++size;
    }
  }
  ++size;//Prize
  return size;
}


std::ostream& operator<<(std::ostream &out, IntBuffer::Spin& data)
{
  for(Int32 i=0;i<data.StopCount();++i)
  {
    out<<"Stop:"<<i<<":"<<data.GetStop(i)<<std::endl;
  }
  out<<"Prize:"<<data.GetPrize()<<std::endl;
  return out;
}


