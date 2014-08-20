/*
 * AllRaceInstances.cpp
 *
 *  Created on: May 12, 2013
 *      Author: onder
 */

#include "AllRaceInstances.h"



bool AllRaceInstances::isInstructionHasRace(ADDRINT instPtr)
{
	return false;
	if (allRacesInstPointers.count(instPtr) == 0)
		return false;

	return true;
}

bool AllRaceInstances::hasRaceHappenedOnThisLine(string fileNameIn, int lineNumberIn)
{
	return false;

	if (fileNameIn == "" || lineNumberIn == 0) //line bilgisini alamazsan return et
		return false;


	std::map<ADDRINT, RaceInstance*>::iterator it;
	for (it = allRaces.begin(); it != allRaces.end(); ++it)
		if (it->second != NULL)
			try
			{
				if ( (it->second->exactFileName == fileNameIn	&& it->second->exactLineNumber == lineNumberIn)	)
					return true;

			}
			catch(...)
			{
				cout << "except" << endl;
			}

	return false;

}

void AllRaceInstances::removeSameLineRaces()
{
	return;
	std::map<ADDRINT, RaceInstance*>::iterator first_it;
	std::map<ADDRINT, RaceInstance*>::iterator second_it;
	for (first_it = allRaces.begin(); first_it != allRaces.end(); ++first_it)
	{
		for (second_it = allRaces.begin(); second_it != allRaces.end(); ++second_it)
		{
			if ( first_it != second_it 													&&
				first_it->second->print 												&&
				first_it->second->exactFileName == second_it->second->exactFileName     &&
				first_it->second->exactLineNumber == second_it->second->exactLineNumber &&
				first_it->second->exactFileName != ""
			)
				second_it->second->print = false;
		}

	}

}

bool AllRaceInstances::isMemoryAlreadyHasRace(ADDRINT memoryAddr)
{
	if (allRaces.count(memoryAddr) == 0)
		return false;

	return true;
}

void AllRaceInstances::allRaceAddresses()
{

	std::map<ADDRINT, RaceInstance*>::iterator it;
		for (it = allRaces.begin(); it != allRaces.end(); ++it)
			if (it->second != NULL)
				try
				{
					cout << it->second->insPtr << endl;
				}
				catch(...)
				{
					cout << "except" << endl;
				}
}

int AllRaceInstances::getRaceCount()
{
	return allRaces.size();
}


bool AllRaceInstances::isRaceOKOutside(ADDRINT memoryAddr, ADDRINT instPtr,ADDRINT isMallocedAddrToUse)
{

	if ( (allRaces.count(memoryAddr) != 0  ) || allRacedArrayAddresses.count(isMallocedAddrToUse) > 0 || allRacesInstPointers.count(instPtr) > 0)
		return false;

	return true;
}

bool AllRaceInstances::isRaceOK(ADDRINT memoryAddr, ADDRINT instPtr,  ADDRINT isMallocedAddrToUse)
{

/*	if (allRacedArrayAddresses.count(isMalloced.addrToUse ) > 0)
		cout << "address malloced raced:" << memoryAddr << endl;
	else
		cout << "not malloced:" << isMalloced.isMallocArea << endl;

		*/
	//return true;

//	cout << " (allRaces.count(memoryAddr) != 0  )::" <<  (allRaces.count(memoryAddr) != 0  ) << endl;
//	cout << "allRacedArrayAddresses.count(isMalloced.addrToUse):" << allRacedArrayAddresses.count(isMalloced.addrToUse) << endl;

	if ( (allRaces.count(memoryAddr) != 0  ) || allRacedArrayAddresses.count(isMallocedAddrToUse) > 0 || allRacesInstPointers.count(instPtr) > 0)
		return false;

	return true;
}

void AllRaceInstances::addToRaces(RaceInstance* currentRace, ADDRINT isMallocedAddrToUse)
{

	if (!isRaceOK( currentRace->memoryAddr,  currentRace->insPtr, isMallocedAddrToUse))
	{
		if (currentRace != NULL)
			delete currentRace;
		return;
	}
		//cout << hex << "AddToRaces:" <<  currentRace->memoryAddr  << dec << endl;
	allRaces[currentRace->memoryAddr] = currentRace;
	allRacesInstPointers[currentRace->insPtr] = currentRace;
	//cout << "allRaces.size():" << allRaces.size() << endl;

	//if (isMalloced.isMallocArea)
	{

		allRacedArrayAddresses[isMallocedAddrToUse] = currentRace->memoryAddr;
		//cout << "RACE ARE MALLOCED:" << hex<< isMalloced.addrToUse <<  endl;

	}
	//else
	//;//	cout << "RACE ARE NOT MALLOCED" << endl;



	//allRacesInstPointers[currentRace->segmentOneInstPtr] = currentRace;
	//allRacesInstPointers[currentRace->segmentTwoInstPtr] = currentRace;


}


