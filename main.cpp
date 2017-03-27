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

#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include "ods_reader.h"
//#include "content_reader.h"
//#include "algorithms.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::exception;
using std::string;
using std::vector;




//int main(int argc, char **argv)
int main()
{

  cout << "Start main" << endl;

  ODSReader("/home/xxx/Work/payment_cli/test.ods");

  return 0;
}

