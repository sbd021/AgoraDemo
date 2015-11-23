#pragma once

class CAGResourceVisitor
{
public:
	CAGResourceVisitor(void);
	~CAGResourceVisitor(void);

	static BOOL PASCAL SaveResourceToFile(LPCTSTR lpResourceType, WORD wResourceID, LPCTSTR lpFilePath);
};
