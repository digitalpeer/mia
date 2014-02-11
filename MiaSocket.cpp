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
#include "config.h"
#include "MiaSocket.h"
#include "MiaMainWindow.h"
#include "MiaTOC.h"
#include "Mia.h"

IMPLEMENT_DYNAMIC(MiaSocket, CSocket)

MiaSocket::MiaSocket()
{
	ownerProtocol = 0;
		out_sequence=0;
		in_sequence=0;
}

void MiaSocket::OnClose(int nErrorCode)
{
	//AfxMessageBox("disconnected!");
	ownerProtocol->myParentWindow->UpdateDebug("<------Socket Closed Connection----->");
	ownerProtocol->onDisconnect();
}

MiaSocket::MiaSocket(MiaTOC* theOwnerProtocol)
{
	ownerProtocol = theOwnerProtocol;
	out_sequence=0;
	in_sequence=0;

}

void MiaSocket::OnReceive(int nErrorCode)
{
	//let the CSocket do what it needs to do
	CSocket::OnReceive(nErrorCode);

	//ownerProtocol->myParentWindow->UpdateDebug("[Reading new frame]");

	int retval;

	char* framebuffer = new char[6];
	char* framebufferTEMP = new char[6];
	char* buffer = new char[10000];
	int bytes;

	//int datatoread = 0;
	unsigned short datatoread = 0;
	int dataread = 0;

	CString viewbuff;
	CString read;

	bytes = Receive(framebuffer, MiaTOC::SFLAP_HEADERSIZE);

	switch (bytes)
	{
		case 0:
			Close();
		break;

		case SOCKET_ERROR:
			if (GetLastError() != WSAEWOULDBLOCK) 
			{
				AfxMessageBox ("Error occurred");
				Close();
			}
		break;

		case 6:
			//if i am in this stage of signon, there is only
			//4 bytes of other data to read
			if (ownerProtocol->status == MiaTOC::MIA_SIGNON_STEP_0)
			{
				retval = CSocket::Receive(buffer,4);
				if(retval > 0)
				{
					dataread += retval;
				}
			}
			//else this is a payload frame so get all of the data
			else
			{
				//tear apart the frame header

				//bytes 2 and 3 of frame are the incoming sequence number
				memcpy(&in_sequence, framebuffer+2, sizeof(short));
	
				//convert to network byte order
				in_sequence = ntohs(in_sequence);

				//get the length of the data 
				memcpy(&datatoread, framebuffer+4, sizeof(short));

				//convert to network byte order
				datatoread = ntohs(datatoread);
				
				retval = Receive(buffer /*+ dataread*/, datatoread);

				if (retval != datatoread)
					TRACE("did not read same length as needed in socket receieve!");
			}


			//server does not send nullterminated strings, so terminate
			if (retval > 0)
			{
				buffer[retval] = 0;

			//more debug stuff
			viewbuff = buffer;
			//ownerProtocol->myParentWindow->UpdateDebug("Received packet:" + viewbuff);

			//tell the protocol to handle the data
			ownerProtocol->tocServer(viewbuff);
			//it is probably bad to do this, but I am calling
			//a function directly with this data instead of saving
			//it to a buffer and telling a function to get it
			//this could get complicated real fast
			}

			break;

		default:
			break;

	}

	//deleting
	delete [] buffer;
	delete [] framebuffer;
}

void MiaSocket::writeInBuffer(CString data)
{
	inBuffer = data;
}

void MiaSocket::writeSignon(unsigned ver, unsigned short tlv, CString name)
{
	char *frame = new char[200];		//frame data

	unsigned short total_len = 0;		//length of the SIGNON payload
	unsigned long flap_version = 1;		//FLAP version
	unsigned short tlv_tag = 1;			//TLV_TAG
	char *normal_sn = NULL;				//normalized screen name
	int num = 0;						//number of bytes sent

	//normalize the screen name
	normal_sn = name.GetBuffer(name.GetLength());

	//the total length of the frame
	total_len = 8 + strlen(normal_sn);

	//this will save all the needed variables for the frame in
	//network byte order
	unsigned short seq_no = htons(out_sequence);
	unsigned short the_len = htons(total_len);
	unsigned long flap_ver = htonl(1);
	unsigned short ttlv = htons(1);
	unsigned short sn_len = htons(strlen(normal_sn));
  
	//put all the parts of the frame in the right place
	frame[0] = '*';		//this is always the first byte of every frame
	frame[1] = 1;       //this specifies that it is a signon frame
	memcpy(frame+2 , &seq_no, sizeof(short));	//this is the sequence number
	memcpy(frame+4 , &the_len, sizeof(short));  //size of the payload data
	memcpy(frame+6 , &flap_ver, sizeof(long));  //flap version
	memcpy(frame+10, &ttlv, sizeof(short));     //TLV tag
	memcpy(frame+12, &sn_len, sizeof(short));	//the length of the screen name
	strcpy(frame+14, normal_sn);				//the normalized screen name

	//send the frame
	Send(frame, 6+total_len);

	//increase sequence number
	out_sequence++;

	//free memory ??????? causes error
	//delete [] frame;
}


//convert the data to a frame and send it
void MiaSocket::writeData(CString data, int typeOfFrame)
{

	const int TOC_CLIENT_TO_SERVER_BUFFER_MAX = 1024;

	if (ownerProtocol != 0)
	{
		//ownerProtocol->myParentWindow->UpdateDebug("Sending:" + data);
	}
	else
	{
		return;
	}

	CString dataToSend = data;
	char* payload;
	int size;
	char *frame;
	unsigned short seq_no;
	unsigned short pay_len;

	//temp place to store the payload data
	payload = new char[dataToSend.GetLength()+1];

	//copy from the CString to the buffer
	strcpy(payload,dataToSend.GetBuffer(dataToSend.GetLength()));


	//the data size + 6 frame header bytes + null
	size = strlen(payload) + 6 + 1;

	frame = new char[size];				//frame

	//convert the sequence number and payload to short
	seq_no = htons(out_sequence);
	pay_len = htons(strlen(payload)+1);

	//the FLAP frame to send
	frame[0] = '*';								//always a * for first byte
	frame[1] = typeOfFrame;						//set the frame type
	memcpy(frame+2, &seq_no, sizeof(short));	//frame seq number
	memcpy(frame+4, &pay_len, sizeof(short));	//data size
	strcpy(frame+6, payload);					//data

	//increase outgoing seq number
	out_sequence++;

	int sendSize = 0;

	while (sendSize < size)
	{
		/*
		if (data.GetLength() > TOC_CLIENT_TO_SERVER_BUFFER_MAX)
		{
			dataToSend = data.Left(TOC_CLIENT_TO_SERVER_BUFFER_MAX);
			data.Delete(0,TOC_CLIENT_TO_SERVER_BUFFER_MAX);
			TRACE("length was too big for buffer, so sending first portion");
			//ownerProtocol->myParentWindow->UpdateDebug("Sending:" + dataToSend);
		}
		else
		{
			TRACE("length was NOT too big for buffer, so sending all data now");
			dataToSend = data;
			data.Empty();
			//ownerProtocol->myParentWindow->UpdateDebug("Sending:" + dataToSend);
		}
		*/

		//send the FLAP
		sendSize += CSocket::Send(frame + sendSize, size);


		//

		//????? Errors!
		//delete [] frame;
		//delete [] payload;
	}

}

/*
//convert the data to a frame and send it
void MiaSocket::writeData(CString data, int typeOfFrame)
{

	const int TOC_CLIENT_TO_SERVER_BUFFER_MAX = 900;

	if (ownerProtocol != 0)
	{
		//ownerProtocol->myParentWindow->UpdateDebug("Sending:" + data);
	}
	else
	{
		return;
	}

	CString dataToSend;
	char* payload;
	int size;
	char *frame;
	unsigned short seq_no;
	unsigned short pay_len;

	while (!data.IsEmpty())
	{
		if (data.GetLength() > TOC_CLIENT_TO_SERVER_BUFFER_MAX)
		{
			dataToSend = data.Left(TOC_CLIENT_TO_SERVER_BUFFER_MAX);
			data.Delete(0,TOC_CLIENT_TO_SERVER_BUFFER_MAX);
			TRACE("length was too big for buffer, so sending first portion");
			//ownerProtocol->myParentWindow->UpdateDebug("Sending:" + dataToSend);
		}
		else
		{
			TRACE("length was NOT too big for buffer, so sending all data now");
			dataToSend = data;
			data.Empty();
			//ownerProtocol->myParentWindow->UpdateDebug("Sending:" + dataToSend);
		}


		//temp place to store the payload data
		payload = new char[dataToSend.GetLength()+1];

		//copy from the CString to the buffer
		strncpy(payload,dataToSend.GetBuffer(dataToSend.GetLength()),dataToSend.GetLength()+1);

		CString dump = payload;
		
		ownerProtocol->myParentWindow->UpdateDebug("\r\nSENDING:" + dump + "\r\n");

		//the size of the frame total
		//size = 0;

		//the data size + 6 frame header bytes + null
		size = strlen(payload) + 6 + 1;

		frame = new char[size];				//frame

		//convert the sequence number and payload to short
		seq_no = htons(out_sequence);
		pay_len = htons(strlen(payload)+1);

		//the FLAP frame to send
		frame[0] = '*';								//always a * for first byte
		frame[1] = typeOfFrame;						//set the frame type
		memcpy(frame+2, &seq_no, sizeof(short));	//frame seq number
		memcpy(frame+4, &pay_len, sizeof(short));	//data size
		strcpy(frame+6, payload);					//data

		//send the FLAP
		CSocket::Send(frame, size);

		//increase outgoing seq number
		out_sequence++;


		//

		//?????
		//delete [] frame;
		//delete [] payload;
	}

}
*/

//this just gets the current in buffer
CString MiaSocket::readInBuffer()
{
	return inBuffer;
}
