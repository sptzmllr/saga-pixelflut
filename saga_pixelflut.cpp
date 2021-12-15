#include "saga_pixelflut.h"
#include <boost/asio.hpp>
//#include "wx/socket.h"
//#include "wx/wxprec.h"
//#include "wx/wx.h"


using boost::asio::ip::tcp;

CPixelflut::CPixelflut(void)
{
	Set_Name 		(_TL("SAGA Pixelflut"));

	Set_Author		(_TL("Justus Spitzmüller"));

	Set_Description	(_TW(
		"Pixelflut for SAGA GIS"
		)
							
	);
	
	Set_Version		(_TL("1.0"));

	//-----------------------------------------------------
	Parameters.Add_Grid(
		"" , "IMG", _TL("Input Image"),
		_TL("Input Image"),
		PARAMETER_INPUT
	);

	Parameters.Add_String(
		"", "HOST", _TL("Host"),
		_TL("Set the Host"), "localhost"
	);

	Parameters.Add_Int(
		"", "PORT", _TL("Port"),
		_TL("Set the Server Port"), 1337
	);

}

CPixelflut::~CPixelflut(void)
{}

int CPixelflut::On_Parameter_Changed(CSG_Parameters *pParameters, CSG_Parameter *pParameter)
{
	return( CSG_Tool::On_Parameter_Changed( pParameters, pParameter));
}

int CPixelflut::On_Parameters_Enable( CSG_Parameters *pParameters, CSG_Parameter *pParameter)
{
	return( CSG_Tool::On_Parameters_Enable(pParameters, pParameter) );
}

bool CPixelflut::On_Execute(void)
{
	CSG_Grid 	*Image = Parameters("IMG")->asGrid();

	boost::asio::io_context io_context;

	CSG_String Endpoint = Parameters("HOST")->asString();

	tcp::resolver	resolver(io_context);
	//tcp::resolver::results_type endpoints = resolver.resolve( Endpoint.b_str(), "1337" );
	tcp::resolver::results_type endpoints = resolver.resolve( "localhost", "1337" );

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

	if( socket.is_open() )
	{
		for( int x=0; x<Image->Get_NX(); x++ )
		{
			for( int y=0; y<Image->Get_NY(); y++ )
			{
				//CSG_String 	msg = CSG_String::Format("PX %d %d ffffff", x, y);
				std::string	msg = "PX " + std::to_string(x) + " " + std::to_string(y) + " ff8000";
				socket.write_some(boost::asio::buffer(msg.data(), msg.size()) );
		
			}
		}
	}
	else
	{
		Error_Set("No Connection");
	}

	return true;

}
