/*
 *
 * Copyright (C) 2002, Josh Henderson <digitalpeer@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#include "MiaNumberTrack.h"

MiaNumberTrack::MiaNumberTrack()
{
	min = DEFAULT_MIN;
	max = DEFAULT_MAX;
}


MiaNumberTrack::MiaNumberTrack(int minNumber, int maxNumber)
{
	min = minNumber;
	max = maxNumber;
}

int MiaNumberTrack::getUniqueNumber()
{
	int thisNumber = 0;
	//a do so it will pass through atleast once
	do
	{
		thisNumber = min + (rand() % max);
	}
	while (doesNumberExist(thisNumber));
	
	numberList.AddHead(thisNumber);
	return thisNumber;
}

void MiaNumberTrack::releaseUniqueNumber(int num)
{
	POSITION pos = numberList.Find(num);
	numberList.RemoveAt(pos);
}

bool MiaNumberTrack::doesNumberExist(int num)
{
	bool answer = false;
	POSITION pos = numberList.GetHeadPosition();
	for (int i=0;i < numberList.GetCount() && !answer;i++)
	{
		if (numberList.GetNext(pos) == num)
			answer = true;
	}
	return answer;

}