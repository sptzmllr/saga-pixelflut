#include "saga_pixelflut.h"
#include <boost/asio.hpp>
#include <iomanip>
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
	
	Set_Version		(_TL("1.1"));

	//-----------------------------------------------------
	Parameters.Add_Grid(
		"" , "R", _TL("Red"),
		_TL("Input Image"),
		PARAMETER_INPUT
	);

	Parameters.Add_Grid(
		"" , "G", _TL("Green"),
		_TL("Input Image"),
		PARAMETER_INPUT
	);

	Parameters.Add_Grid(
		"" , "B", _TL("Blue"),
		_TL("Input Image"),
		PARAMETER_INPUT
	);

	Parameters.Add_Int(
		"", "X_OFF", _TL("X Offset"),
		_TL(""), 0 
	);

	Parameters.Add_Int(
		"", "Y_OFF", _TL("Y Offset"),
		_TL(""), 0 
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
	CSG_Grid 	*R = Parameters("R")->asGrid();
	CSG_Grid 	*G = Parameters("G")->asGrid();
	CSG_Grid 	*B = Parameters("B")->asGrid();

	int y_size = Get_NY();

	int x_offset = Parameters("X_OFF")->asInt();
	int y_offset = Parameters("Y_OFF")->asInt();

	boost::asio::io_context io_context;

	//boost::asio::io_service &io;

	CSG_String Endpoint = Parameters("HOST")->asString();

	tcp::resolver	resolver(io_context);
	//tcp::resolver::results_type endpoints = resolver.resolve( Endpoint.b_str(), "1337" );
	tcp::resolver::results_type endpoints = resolver.resolve( "10.23.42.150", "2342" );

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

	if( socket.is_open() )
	{
		for( ; ; )
		{
			for( int x=0; x<Get_NX(); x++ )
			{
				for( int y=0; y<Get_NY(); y++ )
				{
					//CSG_String 	msg = CSG_String::Format("PX %d %d %x%x%xf", x, y, pR->asChar(x,y), pG->asChar(x,y), pB->asChar(x,y));

					std::stringstream stream;
					stream  << std::setfill('0') << std::setw(2) << std::hex << R->asInt(x,y)
							<< std::setfill('0') << std::setw(2) << std::hex << G->asInt(x,y)
							<< std::setfill('0') << std::setw(2) << std::hex << B->asInt(x,y);

					std::string	msg = "PX " + std::to_string(x + x_offset) + " " + std::to_string((y_size-y)+ y_offset ) + " " + stream.str() + "\n";
					socket.send(boost::asio::buffer(msg.data(), msg.size()) );
			
				}
			}
		}
	}
	else
	{
		Error_Set("No Connection");
	}

	return true;

}
