#ifndef _IRESOURCE_H_
#define _IRESOURCE_H_

#include <string>

struct IResource
{
public:
	virtual ~IResource() {}
	virtual bool Load(const std::wstring& path) = 0;
};

#endif // !_IRESOURCE_H_
