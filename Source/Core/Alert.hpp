#pragma once
#include <string>
#include <RUtils/RMacros.hpp>

#ifdef _WIN32
  #include <Windows.h>
#endif

// Alerts a message. If answer is to break from user, do so.
void AlertMessage(const wchar_t* str)
{
  int toEval = 0;
#ifdef _WIN32
  int retVal = MessageBox(
    NULL,
    (LPCWSTR)str,
    (LPCWSTR)L"Engine Error",
    MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON1
  );
  if (retVal != IDYES)
    toEval = retVal;

#else // *nix
  DEBUG_PRINT(str);
  retVal = 0;
#endif
  if (toEval != 0)
    throw str;
}
