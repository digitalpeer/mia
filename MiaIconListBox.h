//http://codeguru.earthweb.com/listbox/IconLB.html


#ifndef MIAICONLISTBOX_H
#define MIAICONLISTBOX_H

#include "MiaVector.h"
class MiaListItem;

class MiaIconListBox : public CListBox
{

	public:
		MiaIconListBox();

	protected:
		//this is the image list with all the images from the resource
		CImageList* m_pImageList;

	public:
		int AddString(LPCTSTR lpszItem);
		int AddString(LPCTSTR lpszItem, int iImg);
		int InsertString(int iIndex, LPCTSTR lpszItem);
		int InsertString(int iIndex, LPCTSTR lpszItem, int iImg);
		void SetItemImage(int iIndex, int iImg);
		inline void SetImageList(CImageList* pImgList = NULL)
			{ m_pImageList = pImgList; }

		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
		virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

		MiaVector<int> listItemData;
		virtual ~MiaIconListBox();
};

#endif
