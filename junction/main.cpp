#include <tchar.h>
#include <iostream>
#include "Directory.h"
#include "JunctionManager.h"
#include "JunctionReparseData.h"
#include "DirectoryEnumerator.h"

#ifdef UNICODE
#define _tcout wcout
#define _tcin wcin
#define _tcerr wcerr
#endif

int _tmain(int argc, TCHAR *argv[])
{
	try
	{
		if (argc < 2 || argc > 3)
			std::_tcerr << _T("Usage: ") << argv[0] << _T(" <junction> [<new-dest>]");
		else
		{
			if (argc == 2)
			{
				for (std::wstring name : DirectoryEnumerator(argv[1]))
				{
					try
					{
						Directory dir(name.c_str());
						JunctionManager manager(dir);
						auto data = manager.GetJunctionData();

						if (!data)
							std::_tcout << name << _T(": Not a junction.") << std::endl;
						else
							std::_tcout << name << _T(" -> ") << data->GetSubstituteName() << std::endl;
					}
					catch (const WinApiException &x)
					{
						std::_tcerr << name << _T(": ") << x.what() << std::endl;
					}
				}
			}
			else
			{
				Directory junction(argv[1], true);
				JunctionManager manager(junction);
				manager.CreateJunction(argv[2]);
				std::_tcout << _T("Created: ") << argv[1] << _T(" -> ") << argv[2] << std::endl;
			}
		}

		return 0;
	}
	catch (const WinApiException &x)
	{
		std::_tcerr << argv[1] << _T(": ") << x.what() << std::endl;
	}

	return -1;
}