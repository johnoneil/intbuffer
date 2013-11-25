//main.cpp
//John O'Neil
//Sunday, Nov 24th 2013
//
//Example of how to use intbuffer support classes
//

typedef int Int32;

#include "FreeGamesData.hpp"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	//Imagine we have some game data
	const Int32 win=3000;
	const Int32 numFreeSpins=10;
	
	IntBuffer::FreeGamesData data;
	data.SetWin(win);
	IntBuffer::FreeGames& freegames = data.GetFreeGames();
	freegames.SetWin(win);
	for(Int32 s=0;s<numFreeSpins;++s)
	{
		IntBuffer::Spin spin;
		const Int32 reelCount=spin.StopCount();
		for(Int32 stop=0;stop<reelCount;++stop)
		{
			spin.AddStop(stop);
		}
		spin.SetPrize(300);
		freegames.AddSpin(spin);
		//cout<<"Current spin count is "<<freegames.SpinCount()<<endl;
		//cout<<"Spin number "<<s<<" is "<<spin;
	}

	cout<<"total spins in freegames is "<<data.GetFreeGames().SpinCount()<<endl;

	//Dump current class data to screen
	//cout<<data;

	//write class data to integer buffer
	const Int32 size=data.Size();
	cout<<"Size of the free spins data is now "<<size<<endl;
	std::vector<Int32> buffer(2*size);
	data.Write(buffer);

	//Read buffer data into another instance of class
	IntBuffer::FreeGamesData readData=IntBuffer::FreeGamesData::Parse(buffer);

	//Dump contents of class to screen.
	cout<<"--------------------------------------"<<endl;
	const Int32 readSize=readData.Size();
	cout<<"Size of the read back free spins data is now "<<readSize<<endl;
	cout<<"Data read back from buffer is now:"<<endl;
	//cout<<readData;


	return 0;
}

