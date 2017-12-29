#include "Utils/UtilsString.hpp"
#include <algorithm>
#include <string.h>



// Makes the provided reference string lowercase, and returns it.
std::string U_Lowercase(std::string &str)
{
  std::transform(str.begin(), str.end(), str.begin(), tolower);
  return str;
}
