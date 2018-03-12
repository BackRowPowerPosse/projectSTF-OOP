
//-----------------------------------------------------------------------------
//	File:		CShipInfo.cpp
//
//	functions:	
//		void print(ostream &sout) const;
//		void print() const;
//		CShip getName() const;
//		CDirection getOrientation() const;
//		CCell getBowLocation() const;
//		short getPiecesLeft() const;
//		bool isSunk();
//		void setName();
//		void setOrientation();
//		void setBowLocation();
//		void setPiecesLeft();
//		CShipInfo operator--();
//			
//-----------------------------------------------------------------------------

#include "FleetLibrary.h"

namespace SINK_THE_FLEET
{
	//-----------------------------------------------------------------------------
	//	Class:          CShipInfo
	//
	//	Title:          Ship Info Class
	//
	//	Description:    Definitions for CShipInfo
	//
	//	Programmer:     Aaron Miller
	//   
	//	Date:           3/4/2018
	// 
	//	Version:        1.0
	//   
	//		Software:   MS Windows 10 for execution;  
	//                  Compiles under Microsoft Visual C++.Net 2017
	// 
	//	class: CShipInfo
	//
	//	Properties:
	//		CShip m_name - ship name
	//		CDirection m_orientation - ship orientation (H/V)
	//		CCell m_bowLocation - bow location
	//		short m_piecesLeft - pieces left in players' fleet
	//
	//	History Log:
	//                	3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
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
	//-----------------------------------------------------------------------------
	void CShipInfo::print(ostream & sout) const
	{
		sout << m_name << ", located ";
		if (this->m_orientation)
		{
			sout << "vertically at ";
		}
		else
		{
			sout << "horizontally at ";
		}
		sout << getBowLocation() << "-- " << this->m_piecesLeft << " pieces left";

	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        void print()const;
	//	description:   prints out this object to the stream
	//	Input:         None
	//	Output:        Screen display of complex number
	//	Calls:         void CShipInfo::print(ostream & sout) const
	//	Called By:     
	//	Parameters:    n/a
	//	Returns:       n/a 
	//	History Log:
	//-----------------------------------------------------------------------------
	void CShipInfo::print() const
	{
		print(cout);
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        CShip getName() const;
	//	description:   accessor for m_name
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    None
	//	Returns:       m_name 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	CShip CShipInfo::getName() const
	{
		return this->m_name;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        CDirection getOrientation() const;
	//	description:   accessor for m_orientation
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    None
	//	Returns:       m_orientation 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	CDirection CShipInfo::getOrientation() const
	{
		return this->m_orientation;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        CCell getBowLocation() const
	//	description:   accessor for m_bowLocation
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    None
	//	Returns:       m_bowLocation 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	CCell CShipInfo::getBowLocation() const
	{
		return this->m_bowLocation;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        short getPiecesLeft() const;
	//	description:   accessor for m_piecesLeft
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    None
	//	Returns:       m_piecesLeft 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	short CShipInfo::getPiecesLeft() const
	{
		return this->m_piecesLeft;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        bool isSunk();
	//	description:    returns true if pieces = 0, otherwise false
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    
	//	Returns:       returns true if pieces = 0, otherwise false 
	//	History Log:
	//	               
	//-----------------------------------------------------------------------------
	bool CShipInfo::isSunk()
	{
		if (this->m_piecesLeft == 0)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        void setName(CShip &name);
	//	description:   mutator for m_name
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    CShip &name - name to set to m_name
	//	Returns:       n/a 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	void CShipInfo::setName(CShip &name)
	{
		this->m_name = name;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        void setOrientation(CDirection &orientation);
	//	description:   mutator for m_orientation
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    CDirection &orientation - orientation to set to m_orientation
	//	Returns:       n/a 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	void CShipInfo::setOrientation(CDirection &orientation)
	{
		this->m_orientation = orientation;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        void setBowLocation(CCell &bowLocation);
	//	description:   mutator for m_bowLocation
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:    CCell &bowLocation - bowLocation to set to m_bowLocation
	//	Returns:       n/a 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	void CShipInfo::setBowLocation(CCell &bowLocation)
	{
		this->m_bowLocation = bowLocation;
	}
	//-----------------------------------------------------------------------------
	//	Class:         CShipInfo
	//	method:        void setPiecesLeft();
	//	description:   mutator for m_piecesLeft
	//	Input:         None
	//	Output:        None
	//	Calls:         None
	//	Called By:     
	//	Parameters:   
	//	Returns:       n/a 
	//	History Log:
	//	               3/5/18  AM  completed version 1.0
	//-----------------------------------------------------------------------------
	void CShipInfo::setPiecesLeft(short pieces)
	{
		this->m_piecesLeft = pieces;
	}
	//-----------------------------------------------------------------------------
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
	//-----------------------------------------------------------------------------
	CShipInfo CShipInfo::operator--()
	{
		--this->m_piecesLeft;
		return *this;
	}
	// ----------------------------------------------------------------------------
	//	method:         ostream& operator<<(ostream& sout, const CShipInfo & shipInfo)
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
	// ----------------------------------------------------------------------------
	ostream & operator<<(ostream & sout, const CShipInfo & shipInfo)
	{
		shipInfo.print(sout);
		return sout;
	}
}