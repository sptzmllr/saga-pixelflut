#include <saga_api/saga_api.h>

CSG_String Get_Info(int i)
{
	switch( i )
	{
	case TLB_INFO_Name:	default:
		return( _TL("SAGA Pixelflut"));

	case TLB_INFO_Category:
		return( _TL("SAGA Pixelflut") );

	case TLB_INFO_Author:
		return( SG_T("Justus Spitzmüller" ));

	case TLB_INFO_Description:
		return( _TL("" ));

	case TLB_INFO_Version:
		return( SG_T("1.0") );

	case TLB_INFO_Menu_Path:
		return( _TL("Pixelflut" ));
	}
}

#include "saga_pixelflut.h"

CSG_Tool *		Create_Tool(int i)
{
	switch( i )
	{
		case    0:	return( new CPixelflut );
		default:	return(	NULL );
	}
}

	TLB_INTERFACE
