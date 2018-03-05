#include "CShipInfo.h"

namespace SINK_THE_FLEET
{
	CShipInfo::CShipInfo()
	{
	}
	void CShipInfo::print(ostream & sout) const
	{
	}
	void CShipInfo::print() const
	{
	}
	CShip CShipInfo::getName() const
	{
		return CShip();
	}
	CDirection CShipInfo::getOrientation() const
	{
		return CDirection();
	}
	CCell CShipInfo::getBowLocation() const
	{
		return CCell();
	}
	short CShipInfo::getPiecesLeft() const
	{
		return 0;
	}
	bool CShipInfo::isSunk()
	{
		return false;
	}
	void CShipInfo::setName()
	{
	}
	void CShipInfo::setOrientation()
	{
	}
	void CShipInfo::setBowLocation()
	{
	}
	void CShipInfo::setPiecesLeft()
	{
	}
	CShipInfo CShipInfo::operator--()
	{
		return CShipInfo();
	}
	ostream & operator<<(ostream & sout, const CShipInfo & shipInfo)
	{
		
	}
}