// ------------------------------------------------
//                  LineManagementAssistant
// Copyright 2012-2013, Chengyong Yang & Changhai Gu. 
//               All rights reserved.
// ------------------------------------------------
//	ArxWrapper.h
//	written by Changhai Gu
// ------------------------------------------------
// $File:\\LineManageAssitant\main\header\ArxCustomObject.h $
// $Author: Changhai Gu $
// $DateTime: 2013/1/9 01:35:46 $
// $Revision: #1 $
// ------------------------------------------------

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include <string>

#include <rxobject.h>
#include <rxregsvc.h>
#include <aced.h>
#include <dbsymtb.h>
#include <dbapserv.h>
#include <adslib.h>
#include "tchar.h"
#include <dbobjptr.h>

//3D Object
#include <dbsol3d.h>

#include <LineEntryData.h>

using namespace std;
using namespace com::guch::assistant::data;

namespace com
{

namespace guch
{

namespace assistant
{

namespace arx
{

class LMADbObjectManager
{
public:

	static void RegisterClass();
	static void UnRegisterClass();
};

class LineCutRegion
{
public:

	//切图方向
	static enum CutDirection {CUT_X,CUT_Y,CUT_Z};

	// 切图区域
	AcDbRegion* mCutRegion;

	// 切图中心点
	AcGePoint3d mCenter;
};

class LMALineDbObject : public AcDb3dSolid
{
public:

    ACRX_DECLARE_MEMBERS(LMALineDbObject);

    LMALineDbObject();
    LMALineDbObject(const wstring& layerName,
					const LineCategoryItemData& categoryData,
					const Adesk::Int32& id,
					const Adesk::Int32& seqNO,
					const AcGePoint3d& start,
					const AcGePoint3d& end );

    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*);
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*)
        const;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*);
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*)
        const;

	AcGePoint3d GetCutCenter( const AcGePlane& );

protected:

	// create the line pipe
	Acad::ErrorStatus Init();

	// creat the 3d pipe
	Acad::ErrorStatus CreatePipe();

	// create the dimensions
	Acad::ErrorStatus CreateDimensions();

public:

	//the layer to insert
	wstring mLayerName;

	//line basic info
	LineCategoryItemData* mCategoryData;

	//Identify the index in the line
	Adesk::Int32 mSequenceNO;

	//the outter radius
	double mRadius;

	//the length
	double mLength;

	//the widht
	double mWidth;

	//handler of the dimension
	AcDbHandle mHandleDim;

	//handler of the text
	AcDbHandle mHandleText;

private:

	//Store in database
	Adesk::Int32 mLineID;

	//the bottom
	AcGePoint3d mStartPoint;

	//the top
	AcGePoint3d mEndPoint;
};

} // end of arx

} // end of assistant

} // end of guch

} // end of com
