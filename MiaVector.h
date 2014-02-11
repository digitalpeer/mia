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

////////////////////////////////////////////////////////
//JHPong by Joshua Henderson
//March 2002
//CS493 Project #2
////////////////////////////////////////////////////////
// A simple MiaVector template class
// Randy Ribler and the cs142 class
// March, 2001
// Modified April 2001 by Josh Henderson 
////////////////////////////////////////////////////////

//disable the dang float to int warning
//I found MS doing this to a bool warning on msdn.microsoft.com
//and figured that the number represented was the number
//displayed when you get that warning during compile time
#pragma warning( disable : 4244)

#ifndef JOSHH_MiaVector_H
#define JOSHH_MiaVector_H

template <typename Type>
class MiaVector
{
   public:
      // Default constructor (MiaVector of size 1)
      MiaVector();
      
      // Constructor with specified size.
      MiaVector(int size);

      // Copy constructor
      MiaVector(const MiaVector<Type>& orig);

      // Destructor
      virtual ~MiaVector();
      
      // Assignment operator
      MiaVector<Type>& operator=(const MiaVector<Type>& rhs);

      // Element selection
      Type& operator[](int index);

      // Find the size of the MiaVector
      int getSize() const;

	  // sort
	  void insertionSort(int sortSize);

   protected:
      // Store the actual MiaVector data
      Type* MiaVectorData_;

      // The number of elements in the MiaVector
      int size_;

};

// Default Constructor (create MiaVector with one element)
template <typename Type>
MiaVector<Type>::MiaVector() :
   size_(1), MiaVectorData_(new Type[1])
{
}

// Constructor with size definition
template <typename Type>
MiaVector<Type>::MiaVector(int size) :
   size_(size), MiaVectorData_(new Type[size])
{
}

// Copy Constructor
template <typename Type>
MiaVector<Type>::MiaVector(const MiaVector<Type>& orig) :
   size_(orig.size_), MiaVectorData_(new Type[size])
{
   // Copy original MiaVector to new MiaVector.
   for(int i=0;i<size_;i++)
   {
      MiaVectorData_[i] = orig.MiaVectorData_[i];
   }
}

// Destructor
template <typename Type>
MiaVector<Type>::~MiaVector()
{
   delete [] MiaVectorData_;
}


// Access an element in the MiaVector
// This operator needs to work on both the left and
// right sides of an assignment.
template <typename Type>
Type& MiaVector<Type>::operator[](int index)
{
	// Check array bounds during debug.
	//assert ((index >= 0) && (index < size_));
	const float DEFAULT_INCREASE_BY_VALUE = 1.25;
	if (index >= size_)	//if the index is greater than the size
	{
		int newSize = size_ * DEFAULT_INCREASE_BY_VALUE;	//get new size
		
		while (newSize <= index)	//increase until ok
		{
			newSize++;
		}

		//create a pointer to our new data
		Type* tempData= new Type[newSize];	//allocate new data
			for (int x=0; x < size_;x++)	//copy all data over
			{
				tempData[x] = MiaVectorData_[x];
			}

		delete [] MiaVectorData_;	//delete the old
		size_ = newSize;		//reset size
		MiaVectorData_ = tempData;	//reassign pointer to new data
	}

	// Return the requested value.
	return MiaVectorData_[index];
}

template <typename Type>
int MiaVector<Type>::getSize() const
{
   return size_;
}

template <typename Type>
MiaVector<Type>& MiaVector<Type>::operator=(const MiaVector<Type>& rhs)
{
   // Check for self assignment
   if (this != &rhs)
   {
      if (size_ != rhs.size_)
      {
	 // Delete the memory currently stored in the lhs object
	 delete [] MiaVectorData_;

	 // Reallocate the correct size MiaVector.
	 MiaVectorData_ = new Type[size_];
      }
      
      // Copy the rhs data to the lhs
      for(int i=0;i<size_;i++)
      {
	 MiaVectorData_[i] = rhs.MiaVectorData_[i];
      }
   }
   return *this;
}

template <typename Type>
void MiaVector<Type>::insertionSort(int sortSize)
{
  // From the second element to the end of the array.
  for(int i=1; i<sortSize; i++)
  {
    // The "mover" is the next element to be placed in its correct
    // location in the array.
    Type mover = MiaVectorData_[i];

    // Start at the mover's location and work back towards
    // the first element in the array.
    int j = i;

    // Keep looking until we find an element that is 
    // larger than the mover.
    while((j > 0) && (MiaVectorData_[j-1] < mover))
    {
      // This element is smaller than the mover.
      // move it back one place in the array.
      MiaVectorData_[j] = MiaVectorData_[j-1];
      j--;
    }
    // We have found the correct location for the moveer
    MiaVectorData_[j] = mover;
  }
}


#endif

