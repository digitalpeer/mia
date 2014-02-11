
class MiaChatDialogView : public CEditView
{
	DECLARE_DYNCREATE(MiaChatDialogView)
	protected:
		MiaChatDialogView();
		

// Attributes
//public:
	//MiaMainWindow* GetDocument();

// Operations
public:
	void Message(LPCTSTR lpszMessage);


	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~MiaChatDialogView();


protected:

	DECLARE_MESSAGE_MAP()
};




