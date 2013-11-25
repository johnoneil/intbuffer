///----------------------------------------------------------------------------
// vim: set ts=2 expandtab:
///----------------------------------------------------------------------------
///
///@file Spin.hpp
///@date Nov-24-0900PM-2013
///
///----------------------------------------------------------------------------

typedef int Int32;

#pragma once

#ifndef __INTBUFFER_SPIN_HPP__
#define __INTBUFFER_SPIN_HPP__

#include <vector>
#include <iostream>


namespace IntBuffer
{

class Spin
{
public:


	///=====================================
	///Stops
	///=====================================
   Int32  StopCount(void)const;
   Int32  GetStop(const  Int32  index)const;
  void AddStop(const  Int32  value);
  void ClearStops(void);
	///=====================================
	///Prize
	///=====================================
	 Int32  GetPrize(void)const;
	void SetPrize(const  Int32  value);

	///=====================================
	///@brief Fill structure from integer array
	///=====================================
  static Spin Parse(std::vector< Int32 >& array);
	static Spin Parse(std::vector< Int32 >& array,  Int32& index);

	///=====================================
	///@brief write class data to integer array
	///=====================================
  bool Write(std::vector< Int32 >& array);
  bool Write(std::vector< Int32 >& array, Int32& index);

  ///
  ///@brief Get size of class data when dumped to integer array
  ///
  Int32  Size(void)const;

private:
  std::vector< Int32 > m_Stops;
   Int32  m_Prize;
};

}//namespace IntBuffer

//os operator to help dump class to std out
std::ostream& operator<<(std::ostream &out, IntBuffer::Spin& data);

#endif
