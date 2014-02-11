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


#ifndef MIASOCKET_H
#define MIASOCKET_H

#include "StdAfx.h"

class MiaTOC;

/*
struct sflap_frame
{
	unsigned char asterisk;
	unsigned char type;
	unsigned short sequence;
	unsigned short data_length;
	char data[MiaTOC::SFLAP_DATA_SIZE];
};
*/

//this is a struct that holds the signon data in a special format
struct signon
{
	unsigned int ver;
	unsigned short tag;
	unsigned short namelen;
	char username[80];
};


class MiaSocket : public CSocket
{
	DECLARE_DYNAMIC(MiaSocket);
	
	public:
		//do not use this
		MiaSocket();
		
		//create socket with parent protocol
		MiaSocket(MiaTOC* theOwnerProtocol);
		
		//this is the pointer to the owning protocol of this socket
		MiaTOC* ownerProtocol;
		
		//this is the one and only in buffer
		CString inBuffer;

		/////////socket IO//////////
		virtual void OnReceive(int nErrorCode);
		void writeData(CString data, int typeOfFrame);
		void writeSignon(unsigned ver, unsigned short tlv, CString name);

		/////////buffer IO//////////
		CString readInBuffer();
		void writeInBuffer(CString data);
		
		//on close the socket connection
		void OnClose( int nErrorCode );
	
	private:
		
		//frame in and out sequence numbers
		unsigned short out_sequence;
		//int in_sequence;

		unsigned short in_sequence;

		//TSFBuffer outBuffer, inBuffer;
};


#endif