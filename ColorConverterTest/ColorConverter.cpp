//**************************************************************************/
// Copyright (c) 1998-2022 Autodesk, Inc.
// All rights reserved.
// 
// Use of this software is subject to the terms of the Autodesk license 
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// DESCRIPTION: Color converter built on top of ColorManagement APIs
// AUTHOR: 
//***************************************************************************/

#include "ColorConverter.h"

#include "ui_plugin_form.h"
#include "qmessagebox.h"
#include "qobject.h"

#include "QColorConverterWidget.h"

#define ColorConverter_CLASS_ID Class_ID(0x695170a2, 0x68130104) // 테스트용 클래스 아이디로 새로 만듬.

class ColorConverterTest : public UtilityObj, public QObject{
public:
	// Constructor/Destructor
	ColorConverterTest();
	virtual ~ColorConverterTest();

	void DeleteThis() override {}

	void BeginEditParams(Interface* ip, IUtil* iu) override;
	void EndEditParams(Interface* ip, IUtil* iu) override;

	virtual void Init(HWND hWnd);
	virtual void Destroy(HWND hWnd);

	// Singleton access
	static ColorConverterTest* GetInstance()
	{
		static ColorConverterTest theColorConverter;
		return &theColorConverter;
	}

private:
	void ShowColorConveter();
	QWidget* widget;
	Ui::PluginRollup ui;

	IUtil* iu;
};


class ColorConverterClassDesc : public ClassDesc2 
{
public:
	int           IsPublic() override                               { return TRUE; }
	void*         Create(BOOL /*loading = FALSE*/) override         { return ColorConverterTest::GetInstance(); }
	const TCHAR*  ClassName() override                              { return GetString(IDS_CLASS_NAME); }
	const TCHAR*  NonLocalizedClassName() override                  { return _T("ColorConverterTest"); }
	SClass_ID     SuperClassID() override                           { return UTILITY_CLASS_ID; }
	Class_ID      ClassID() override                                { return ColorConverter_CLASS_ID; }
	const TCHAR*  Category() override                               { return GetString(IDS_CATEGORY); }

	const TCHAR*  InternalName() override                           { return _T("ColorConverterTest"); } // Returns fixed parsable name (scripter-visible name)
	HINSTANCE     HInstance() override                              { return hInstance; } // Returns owning module handle


};

ClassDesc2* GetColorConverterDesc()
{
	static ColorConverterClassDesc ColorConverterDesc;
	return &ColorConverterDesc; 
}




//--- ColorConverter -------------------------------------------------------
ColorConverterTest::ColorConverterTest()
	: iu(nullptr)
{

}

ColorConverterTest::~ColorConverterTest()
{

}

void ColorConverterTest::BeginEditParams(Interface* ip,IUtil* iu)
{
	this->iu = iu;
	widget = new QWidget;
	ui.setupUi(widget);

	// We can connect UI signals here using Qt Functor syntax
	QObject::connect(ui.pushButton, &QPushButton::clicked, this, &ColorConverterTest::ShowColorConveter);
	ip->AddRollupPage(*widget, GetString(IDS_CATEGORY));
}

void ColorConverterTest::EndEditParams(Interface* ip, IUtil*)
{
	this->iu = nullptr;
	ip -> DeleteRollupPage(*widget);
}

void ColorConverterTest::Init(HWND /*handle*/)
{

}

void ColorConverterTest::Destroy(HWND /*handle*/)
{

}

void ColorConverterTest::ShowColorConveter()
{
	// Show or Hide the converter widget
	if (!s_theConverterDockWidget)
	{
		s_theConverterDockWidget = new MaxSDK::QmaxDockWidget("QColorConverterWidget", QApplication::translate("ColorConverter", "Color Converter"), GetCOREInterface()->GetQmaxMainWindow());
		s_theConverterDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
		auto childWidget = new QColorConverterWidget(GetCOREInterface()->GetQmaxMainWindow());
		s_theConverterDockWidget->setWidget(childWidget);
		childWidget->UpdateTitle();

		if (!GetCOREInterface()->GetQmaxMainWindow()->restoreDockWidget(s_theConverterDockWidget))
		{
			s_theConverterDockWidget->setFloating(true);
		}

		s_theConverterDockWidget->show();
	}
	else
	{
		if (s_theConverterDockWidget->isVisible())
		{
			s_theConverterDockWidget->hide();
		}
		else
		{
			s_theConverterDockWidget->show();
			s_theConverterDockWidget->raise();
		}
	}
}
