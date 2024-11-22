#ifndef __PIPE__
#define __PIPE__

#include <stdio.h>
#include <omp.h>
#include "WallTime.h"
#undef DEBUG

static inline void Estagio(const int esta, const int prod, const double tIni){
  const double tIniEste=WallTime();
  double tFimEste;
  do 
    tFimEste=WallTime()-tIniEste;
  while (tFimEste < 1.0);
#ifdef DEBUG
  printf("thread %d passou produto %d no estagio %d no tempo %2.0lf\n",
	 omp_get_thread_num(), prod, esta, WallTime()-tIni);
#endif
}

#endif
