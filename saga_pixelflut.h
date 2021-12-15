#pragma once
#include <saga_api/saga_api.h>

class CPixelflut : public CSG_Tool_Grid
{
public:
	
	CPixelflut(void);
	virtual ~CPixelflut(void);
	
protected:
	
	virtual int		On_Parameter_Changed	(CSG_Parameters *pParameters, CSG_Parameter *pParameter);

	virtual int 	On_Parameters_Enable	(CSG_Parameters *pParameters, CSG_Parameter *pParameter);

	virtual bool	On_Execute(void);

	
private:
};
