#if !defined(AFX_MIAPROPERTYAWAYIDLE_H__19066817_07FC_469A_97A3_AA676F7292DC__INCLUDED_)
#define AFX_MIAPROPERTYAWAYIDLE_H__19066817_07FC_469A_97A3_AA676F7292DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MiaPropertyAwayIdle.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// MiaPropertyAwayIdle dialog

class MiaPropertyAwayIdle : public CPropertyPage
{
	DECLARE_DYNCREATE(MiaPropertyAwayIdle)

// Construction
public:
	MiaPropertyAwayIdle();
	~MiaPropertyAwayIdle();

// Dialog Data
	//{{AFX_DATA(MiaPropertyAwayIdle)
	enum { IDD = PROPERTIES_AWAYANDIDLE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(MiaPropertyAwayIdle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(MiaPropertyAwayIdle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIAPROPERTYAWAYIDLE_H__19066817_07FC_469A_97A3_AA676F7292DC__INCLUDED_)
