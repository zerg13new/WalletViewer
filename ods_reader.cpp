/**
  This file is part of CashFlow software. CashFlow it is a software
  for getting statistic of cashflow in your pocket.
  Copyright (C) 2017  Anufriev Sergey

  CashFlow is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  CashFlow is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with CashFlow.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ods_reader.h"
/*
#if defined LINUX
  #define DELIM \\\\
#elif defined WINDOWS
  #define DELIM  ////
#endif
*/
ODSReader::ODSReader(const string _odsFileName)
 :odsFileName(_odsFileName) // should be full absolute path
{
  string FUNC_  = "ODSReader::ODSReader(const string _odsFileName)";
  path tmpDir   = temp_directory_path();
  path uniqPath = unique_path();

  // make uniq path for temp directory
  tmpDir /= uniqPath;

  // check file exists
  if( !exists(_odsFileName) )
  {
    string errorMessage = FUNC_.append(": file doesn't exist ").append(_odsFileName);
    throw runtime_error(errorMessage);
  }

  // check temporary folder doesn't exist
  if( exists(tmpDir) )
  {
    string errorMessage = FUNC_.append(": temp doesn't' already exist ").append(tmpDir.string());
    throw runtime_error(errorMessage);
  }

  // create temporary directory
  if(!create_directories(tmpDir))
  {
    string errorMessage = FUNC_.append(": can't create directory ").append(tmpDir.string());
    throw runtime_error(errorMessage);
  }

  // extract ods file to temp directory
  if( extract_zip(_odsFileName.c_str(), tmpDir.string().c_str()) )
  {
    string errorMessage = FUNC_.append(": can't extract file ").append(_odsFileName)
                               .append(" to temp directory ").append(tmpDir.string());
    throw runtime_error(errorMessage);
  }
}


void ODSReader::extractFile()
{
}


string ODSReader::getODSFileName() const
{
    return odsFileName;
}


string ODSReader::getTmpDir() const
{
    return tmpDir;
}


ODSReader::~ODSReader()
{
  remove_all(tmpDir);
}

#undef DELIM
