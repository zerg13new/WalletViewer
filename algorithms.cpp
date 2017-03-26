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

  description: algorithms for statistic calculation
*/

#include "algorithms.h"



/**
  ROUTINES
*/
static int safe_create_dir(const char *dir);


/**
 return sorted montly inflow/outflow
*/
vector<cashFlow> montlySimple(vector<xmlRow>, date from, date to)
{

}

/**
  return sorted yearly inflow/outflow
*/
vector<cashFlow> yearlySimple(vector<xmlRow>, date from, date to)
{

}

/**
 return number of most expensive items from source
*/
vector<cashFlow> mostExpensiveItems(vector<xmlRow>, unsigned int numberofItemsToReturn)
{

}


/**
*/

int extract_zip(const char *archive, const char *destination)
{
  struct zip      *za;
  struct zip_file *zf;
  struct zip_stat sb;
  char            buf[100];
  int             err;
  int             i, len;
  int             fd;
  long long       sum;

  const int size = 1024;
  char tt [size] = "";
  getcwd(tt, size);
  printf("current dir is %s \n", tt);

  if((za = zip_open(archive, 0, &err)) == NULL)
  {
      zip_error_to_str(buf, sizeof(buf), err, errno);
      fprintf(stderr, "%s: can't open zip archive `%s': %s/n", archive,
          archive, buf);
      return 1;
  }
 
  for(i = 0; i < zip_get_num_entries(za, 0); i++)
  {
    if(zip_stat_index(za, i, 0, &sb) == 0)
    {
      printf("==================\n");
      len = strlen(sb.name);
      printf("Name: [%s], \n", sb.name);
      printf("Size: [%llu], \n", sb.size);
      printf("mtime: [%u]\n", (unsigned int)sb.mtime);

      if(sb.name[len - 1] == '/')
      {
        string tmpDir(destination);
        tmpDir.append(sb.name);

        printf("debug: sb.name = %s, destination = %s, tmpDir = %s",
               sb.name, destination, tmpDir.c_str());

        if( safe_create_dir(tmpDir.c_str()) )
          return 99;
      }
      else
      {
        zf = zip_fopen_index(za, i, 0);
        if(!zf)
        {
          fprintf(stderr, "boese, boese\n");
          return 100;
        }

        fd = open(sb.name, O_RDWR | O_TRUNC | O_CREAT, 0644);
        if(fd < 0)
        {
          fprintf(stderr, "boese, boese\n");
          return 101;
        }

        sum = 0;
        while(sum != sb.size)
        {
          len = zip_fread(zf, buf, 100);
          if(len < 0)
          {
            fprintf(stderr, "boese, boese\n");
            return 102;
          }
          write(fd, buf, len);
          sum += len;
        }
        close(fd);
        zip_fclose(zf);
      } // END if(sb.name

    }
    else
    {
      printf("File[%s] Line[%d]\n", __FILE__, __LINE__);
    } // END if(zip_stat_index

  } // END for(i = 0
 
  if(zip_close(za) == -1)
  {
    fprintf(stderr, "%s: can't close zip archive `%s'\n", archive, archive);
    return 1;
  }

  return 0;
}


static int safe_create_dir(const char *dir)
{
    if(mkdir(dir, 0755) < 0)
    {
      if(errno != EEXIST)
      {
        perror(dir);
        return 1;
      }
    }

    return 0;
}
