//-----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
//-----------------------------------------------------------------------------
//
//@file TriggeringSpin.cpp
//@date Dec-05-0506PM-2013
//
//-----------------------------------------------------------------------------

#include "Pch.hpp"
#include <stdexcept>
#include "TriggeringSpin.hpp"

using namespace wbf;

TriggeringSpin::TriggeringSpin()
  :m_HeaderId(0)
  {};

///============================================================================
Int32 TriggeringSpin::GetHeaderId(void)const{return m_HeaderId;};

///============================================================================
Int32 TriggeringSpin::GetSpinPrize(void)const{return m_SpinPrize;};
void TriggeringSpin::SetSpinPrize(const Int32 value){m_SpinPrize=value;};

///============================================================================
Int32 TriggeringSpin::GetSpinType(void)const{return m_SpinType;};
void TriggeringSpin::SetSpinType(const Int32 value){m_SpinType=value;};

///============================================================================
Int32 TriggeringSpin::GetFreeGamesAwarded(void)const{return m_FreeGamesAwarded;};
void TriggeringSpin::SetFreeGamesAwarded(const Int32 value){m_FreeGamesAwarded=value;};

///============================================================================
Int32 TriggeringSpin::GetMultiplier(void)const{return m_Multiplier;};
void TriggeringSpin::SetMultiplier(const Int32 value){m_Multiplier=value;};

///============================================================================
Int32 TriggeringSpin::GetSymbolMapperIndex(void)const{return m_SymbolMapperIndex;};
void TriggeringSpin::SetSymbolMapperIndex(const Int32 value){m_SymbolMapperIndex=value;};

//==============================================================================
Int32 TriggeringSpin::ReelStopCount(void)const{return 5;};
Int32 TriggeringSpin::GetReelStop(const Int32 index)const
{
  if(index<0||index>=ReelStopCount())
  {
    return -1;//there's a chance -1 is not adequate. but I don't want to throw.
  }
  return m_ReelStops[index];
}
void TriggeringSpin::SetReelStop(const Int32 index, const Int32 value)
{
  if(index<0||index>=ReelStopCount())
  {
    return;//I don't want to throw.
  }
  m_ReelStops[index] = value;
}

///============================================================================
Int32 TriggeringSpin::ModifierCount(void)const{return static_cast< Int32 >(m_Modifiers.size());};
Modifier& TriggeringSpin::GetModifier(const Int32 index){return m_Modifiers.at(index);};
void TriggeringSpin::AddModifier(const Modifier& value){m_Modifiers.push_back(value);};
void TriggeringSpin::ClearModifiers(void){m_Modifiers.clear();};

///============================================================================
Int32 TriggeringSpin::GetPaylineDataPresent(void)const{return m_PaylineDataPresent;};
void TriggeringSpin::SetPaylineDataPresent(const Int32 value){m_PaylineDataPresent=value;};

///============================================================================
Int32 TriggeringSpin::PaylineCount(void)const{return static_cast< Int32 >(m_Paylines.size());};
Payline& TriggeringSpin::GetPayline(const Int32 index){return m_Paylines.at(index);};
void TriggeringSpin::AddPayline(const Payline& value){m_Paylines.push_back(value);};
void TriggeringSpin::ClearPaylines(void){m_Paylines.clear();};

//==============================================================================
//Static method that returns instance of class from game event
//Reccomend testing game event before using as this may throw
//==============================================================================
TriggeringSpin TriggeringSpin::Parse(const EDC::IGameEvent& gameEvent)
{
  Int32 index = 0;
  return TriggeringSpin::Parse(gameEvent, index);
}

//==============================================================================
//Static method that returns instance of class from game event starting at index
//==============================================================================
TriggeringSpin TriggeringSpin::Parse(const EDC::IGameEvent& gameEvent, Int32& index)
{
  TriggeringSpin returnValue;
  returnValue.m_HeaderId=gameEvent.GetParam(index++);
  if(returnValue.m_HeaderId!=0)
  {
    throw std::runtime_error("TriggeringSpin cannot be generated from buffer due to incorrect value of m_HeaderId");
  }
  returnValue.m_SpinPrize=gameEvent.GetParam(index++);
  returnValue.m_SpinType=gameEvent.GetParam(index++);
  returnValue.m_FreeGamesAwarded=gameEvent.GetParam(index++);
  returnValue.m_Multiplier=gameEvent.GetParam(index++);
  returnValue.m_SymbolMapperIndex=gameEvent.GetParam(index++);
  {
    const Int32 count = 5;
    for(Int32 i=0;i<count;++i)
    {
      Int32 value = gameEvent.GetParam(index++);
      returnValue.SetReelStop(i, value);
    }
  }
  {
    returnValue.m_Modifiers.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
      Modifier value= Modifier::Parse(gameEvent, index);
      returnValue.m_Modifiers.push_back(value);
    }
  }
  returnValue.m_PaylineDataPresent=gameEvent.GetParam(index++);
  {
    returnValue.m_Paylines.clear();
    const Int32 count = gameEvent.GetParam(index++);
    for(Int32 i=0;i<count;++i)
    {
      Payline value= Payline::Parse(gameEvent, index);
      returnValue.m_Paylines.push_back(value);
    }
  }
  return returnValue;
}

//==============================================================================
//Fill a buffer with data from an instance of this class.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool TriggeringSpin::Write(std::vector< Int32 >& array)
{
  Int32 index = 0;
  return Write(array, index);
}

//==============================================================================
//Fill a buffer with data from an instance of this class from index N.
//Returns: false if there is not enough room to write data.
//==============================================================================
bool TriggeringSpin::Write(std::vector< Int32 >& array, Int32& index)
{
  const Int32 size = Size();
  if(static_cast<Int32>(array.size())-index<size)
  {
    return false;//failed to write for lack of room
  }
  array[index++] = m_HeaderId;
  array[index++] = m_SpinPrize;
  array[index++] = m_SpinType;
  array[index++] = m_FreeGamesAwarded;
  array[index++] = m_Multiplier;
  array[index++] = m_SymbolMapperIndex;
  {
    const Int32 count = ReelStopCount();
    for(Int32 i=0;i<count;++i)
    {
      array[index++] = GetReelStop(i);
    }
  }
  {
    const Int32 count = ModifierCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetModifier(i).Write(array, index);
    }
  }
  array[index++] = m_PaylineDataPresent;
  {
    const Int32 count = PaylineCount();
    array[index++] = count;
    for(Int32 i=0;i<count;++i)
    {
      GetPayline(i).Write(array, index);
    }
  }
  return true;
}

//==============================================================================
// Get the size of this class in 32 bit integers
//==============================================================================
Int32 TriggeringSpin::Size(void)const
{
 Int32 size = 0;
  ++size;//HeaderId
  ++size;//SpinPrize
  ++size;//SpinType
  ++size;//FreeGamesAwarded
  ++size;//Multiplier
  ++size;//SymbolMapperIndex
  {
    const Int32 count = ReelStopCount();
    for(Int32 i=0;i<count;++i)
    {
      ++size;
    }
  }
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = ModifierCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_Modifiers.at(i).Size();
    }
  }
  ++size;//PaylineDataPresent
  ++size;//increment once for the number of elements 'header'
  {
    const Int32 count = PaylineCount();
    for(Int32 i=0;i<count;++i)
    {
      size+=m_Paylines.at(i).Size();
    }
  }
  return size;
}

//==============================================================================
//Helper to test if the contents of a buffer match the pattern for this class
//==============================================================================
bool wbf::IsTriggeringSpin(const EDC::IGameEvent& gameEvent)
{
  try
  {
    TriggeringSpin value = TriggeringSpin::Parse(gameEvent);
  }catch(...)
  {
    return false;
  }
  return true;
};

//==============================================================================
//Helper to dump class to std::stream for debugging etc.
//==============================================================================
std::ostream& operator<<(std::ostream &out, wbf::TriggeringSpin& data)
{
  out<<"HeaderId:"<<data.GetHeaderId()<<std::endl;
  out<<"SpinPrize:"<<data.GetSpinPrize()<<std::endl;
  out<<"SpinType:"<<data.GetSpinType()<<std::endl;
  out<<"FreeGamesAwarded:"<<data.GetFreeGamesAwarded()<<std::endl;
  out<<"Multiplier:"<<data.GetMultiplier()<<std::endl;
  out<<"SymbolMapperIndex:"<<data.GetSymbolMapperIndex()<<std::endl;
  for(Int32 i=0;i<data.ReelStopCount();++i)
  {
    out<<"ReelStop:"<<i<<":"<<data.GetReelStop(i)<<std::endl;
  }
  for(Int32 i=0;i<data.ModifierCount();++i)
  {
    out<<"Modifier:"<<i<<":"<<data.GetModifier(i)<<std::endl;
  }
  out<<"PaylineDataPresent:"<<data.GetPaylineDataPresent()<<std::endl;
  for(Int32 i=0;i<data.PaylineCount();++i)
  {
    out<<"Payline:"<<i<<":"<<data.GetPayline(i)<<std::endl;
  }
  return out;
}


