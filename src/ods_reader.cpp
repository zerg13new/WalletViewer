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

ODSReader::ODSReader(const std::string _odsFileName)
 :odsFileName(_odsFileName) // should be full absolute path
{
  const std::string FUNC_  = "ODSReader::ODSReader(const std::string _odsFileName)";
  std::string       tmpDir = "/tmp";
  std::string       currentUserUID = std::to_string(getuid()); // get current user UID

  // make uniq path for user directory
  tmpDir.append("/").append(currentUserUID);

  // object initialization
  pathToExtractedODS = tmpDir;

  // cleanup from previous data
  remove_all(pathToExtractedODS);

  // check file exists
  if( !exists(_odsFileName) )
  {
    std::string errorMessage = std::string(FUNC_).append(": file doesn't exist ")
                          .append(_odsFileName);
    throw std::runtime_error(errorMessage);
  }

  // check temporary folder doesn't exist
  if( exists(path(tmpDir)) )
  {
    std::string errorMessage = std::string(FUNC_).append(": temp directory already exist ")
                          .append(tmpDir);
    throw std::runtime_error(errorMessage);
  }

  // create temporary directory
  if(!create_directories(tmpDir))
  {
    std::string errorMessage = std::string(FUNC_).append(": can't create directory ")
                          .append(tmpDir);
    throw std::runtime_error(errorMessage);
  }

  // extract ods file to temp directory
  extractFile();

}


void ODSReader::extractFile() const
{
  const std::string FUNC_  = "ODSReader::extractFile() const";

  // extract ods file to temp directory
  if( extract_zip(odsFileName.c_str(), pathToExtractedODS.c_str()) )
  {
    // cleanup extracted files
    remove_all(pathToExtractedODS);

    std::string errorMessage = std::string(FUNC_).append(": can't extract file ")
                          .append(odsFileName).append(" to temp directory ")
                          .append(pathToExtractedODS);
    throw std::runtime_error(errorMessage);
  }
}


std::string ODSReader::getODSFileName() const
{
    return odsFileName;
}


std::string ODSReader::getPathToODS() const
{
    return pathToExtractedODS;
}


ODSReader::~ODSReader()
{
  remove_all(pathToExtractedODS);
}

#undef DELIM
