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

#include "MiaFileFunc.h"

CString MiaLoadFile(CString fileName)
{
	CString buddyListData;
	CString buffer;
	
	if (!fileName.IsEmpty())
	{

		CStdioFile loadFile(fileName, CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate );

		while(loadFile.ReadString(buffer))
			buddyListData += buffer + "\n";
		

		loadFile.Close();
	}
	return buddyListData;
}

void MiaSaveFile(CString fileName, CString data)
{
	CStdioFile saveFile(fileName, CFile::modeWrite | CFile::modeCreate);
		
	saveFile.WriteString(data);

	//close the file (don't have to but just makes me feel better)
	saveFile.Close();
}

void MiaLogToFile(CString fileName, CString data)
{
	CStdioFile saveFile(fileName, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate);
		
	saveFile.Seek(0L, CFile::end );
	saveFile.WriteString(data + "\r\n");

	//close the file (don't have to but just makes me feel better)
	saveFile.Close();
}