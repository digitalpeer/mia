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

#include "stdafx.h"
//here's my solution to getting unique numbers.  i found that i needed this most when
//using timer's and giving them unique ids.  can't have a bunch of active timers and
//have the chance that they will have the same id
class MiaNumberTrack
{
	public:
		
		//initialize with defaults
		MiaNumberTrack();

		//create a number tracker with a specified min and max
		MiaNumberTrack(int minNumber, int maxNumber);
		
		//return a unigue number that hasn't been used yet
		int getUniqueNumber();

		//remove a unique number from the data
		void releaseUniqueNumber(int num);

	private:

		CList<int,int> numberList;
		
		int min;
		int max;
		
		enum {	DEFAULT_MIN = 0,
				DEFAULT_MAX = 30000};

		//used internaly to determine if a number is in the array
		bool doesNumberExist(int num);
};