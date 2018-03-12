//----------------------------------------------------------------------------
// File:		CShipInfo.cpp
//
// Functions:	void print(ostream &sout) const;
//				void print() const;
//				CShip getName() const;
//				CDirection getOrientation() const;
//				CCell getBowLocation() const;
//				short getPiecesLeft() const;
//				bool isSunk();
//				void setName();
//				void setOrientation();
//				void setBowLocation();
//				void setPiecesLeft();
//				CShipInfo operator--();
//----------------------------------------------------------------------------

#include "CShipInfo.h"

namespace SINK_THE_FLEET
{
	//------------------------------------------------------------------------
	// Class:			CShipInfo
	//
	// Title:			Ship Info Class
	//
	// Description:		Definitions for CShipInfo
	//
	// Programmer:		Aaron Miller
	//					Albert Shymanskyy
	//					Cameron Stevenson
	//					Matthew Jacobson
	//					Paul Jacobson
	//   
	// Date:			03/12/2018
	// 
	// Version:			1.0.0
	//   
	// Environment:		Hardware: PC-compatible
	// 					OS: Microsoft Windows 10
	// 					Compiler: Microsoft Visual Studio 2017
	//
	// Properties:		CShip m_name - ship name
	//					CDirection m_orientation - ship orientation (H/V)
	//					CCell m_bowLocation - bow location
	//					short m_piecesLeft - pieces left in players' fleet
	//
	// History Log:		03/12/2018 Class completed (1.0.0)
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	//	method:        void print(ostream & sout)const;
	//	description:   prints out this object to the stream
	//	Input:         None
	//	Output:        Screen display of CShip
	//	Calls:         None
	//	Called By:     
	//	Parameters:    ostream & sout  -- the stream used for output
	//	Returns:       n/a 
	//	History Log:
	//	               
	//------------------------------------------------------------------------
	void CShipInfo::print(ostream & sout) const
	{
		sout << m_name << ", located ";

		if (this->m_orientation)
			sout << "vertically at ";
		else
			sout << "horizontally at ";

		sout << getBowLocation() << "-- " << this->m_piecesLeft
			<< " pieces left";
	}

	//------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        void setBowLocation(CCell &bowLocation);
	//	description:   mutator for m_bowLocation
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    CCell &bowLocation - bowLocation to set to
	//					m_bowLocation
	//	Returns:       n/a 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//------------------------------------------------------------------------
	void CShipInfo::setBowLocation(CCell &bowLocation)
	{
		
	}

	//------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        CShipInfo operator--();
	//	description:   overloaded -- operator, decrements m_piecesLeft
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:   
	//	Returns:       current object 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//------------------------------------------------------------------------
	CShipInfo CShipInfo::operator--()
	{
		--this->m_piecesLeft;

		return *this;
	}

	// -----------------------------------------------------------------------
	//	method:         ostream& operator<<(ostream& sout, const CShipInfo &
	//					shipInfo)
	//	description:    prints out the shipInfo object to the stream
	//	Input:          None
	//	Output:         Screen display of shipInfo
	//	Calls:          None
	//	Called By:      n/a
	//	Parameters:     ostream & sout  -- the stream used for output
	//	               const CShipInfo & shipInfo -- the object to print
	//	Returns:        a reference to sout 
	//	History Log:
	//	                
	// -----------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const CShipInfo & shipInfo)
	{
		shipInfo.print(sout);

		return sout;
	}
}