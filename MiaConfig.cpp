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

#include "MiaConfig.h"

IMPLEMENT_SERIAL(MiaConfig,CObject,1)

const CString MiaConfig::LOCAL_INFO_FILE_PATH = "info.html";
const CString MiaConfig::LOCAL_ABOUTDATA_FILE_PATH = "aboutmia.txt";
const CString MiaConfig::CONFIG_FILENAME = "config.dat";
const CString MiaConfig::LOGDIR = "logs";

//const int MiaConfig::SERIALIZE_VERSION = 1;


MiaConfig::MiaConfig()
{}

void MiaConfig::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_tocUsername;
		ar << m_tocPassword;

		ar << m_tocHost;
		ar << m_tocPort;
	}
	else
	{
		ar >> m_tocUsername;
		ar >> m_tocPassword;

		ar >> m_tocHost;
		ar >> m_tocPort;
	}
}


void MiaConfig::InitializeConfig()
{
	CFile theFile;
	CFileException e;
	//try
	//{
	if (!theFile.Open(CONFIG_FILENAME, CFile::modeRead,&e))
	{
		AfxMessageBox("There was no config.dat file, a default will be created for you.");
		//e->Delete();
		return;
	}
	
	//}
	//catch (CFileException* e)
	//{
	
	//}

	CArchive ar(&theFile,CArchive::load);
	Serialize(ar);
	ar.Close();

	theFile.Close();
}

void MiaConfig::SaveConfig()
{

	CFile theFile;
	theFile.Open(CONFIG_FILENAME, CFile::modeWrite | CFile::modeCreate);

	CArchive ar(&theFile,CArchive::store);
	Serialize(ar);
	ar.Close();

	theFile.Close();

}