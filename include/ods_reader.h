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


#ifndef _ODS_READER_H_
#define _ODS_READER_H_

#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <filesystem>

#include "algorithms.h"

//using std::string;
//using std::to_string;
//using std::runtime_error;
using namespace std::filesystem;

/**
 * @brief The ODSReader class for extracting content of *.ods file in
 *        temp directory for further processing
 */
class ODSReader
{
  public:
    /**
      * @brief ODSReader main constructor to initialize class instance.
      *        Can raise exception of runtime_error class
      * @param _odsFileName full path to *.ods file name
      *        e.g. /tmp/test.ods
      */
    ODSReader(const std::string _odsFileName);

    /**
      * @brief ~ODSReader remove tmpDir
      */
    virtual ~ODSReader();

    /**
     * @brief getODSFileName return odsFileName
     * @return odsFileName
     */
    std::string getODSFileName() const;
    /**
     * @brief getPathToODS
     * @return path to extracted odsFileName file
     */
    std::string getPathToODS() const;

  private:
    /**
     * @brief ODSReader default constructor isn't used somehow
     */
    explicit ODSReader();

    /**
     * @brief ODSReader copy constructor isn't used somehow
     * @param obj
     */
    explicit ODSReader(const ODSReader &obj);

    /**
     * @brief extractFile Service function to extract ods file.
     *                    Can raise exception of runtime_error class
     */
    void extractFile() const;

  protected:
    /**
     * @brief odsFileName filename of processd file
     */
    std::string odsFileName;

    /**
     * @brief full path (without trailed /) to temp dir where *.ods file
     *        was extracted. Currently it is /tmp/uid/filename.ods/
     */
    std::string pathToExtractedODS;
};

#endif
