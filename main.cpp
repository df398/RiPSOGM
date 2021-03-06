/*  ---------------------------------------------------------------------- *
    flocky v1.0 Copyright (C) 2018-2020 David Furman, PhD. 
    df398@cam.ac.uk, University of Cambridge, UK.
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
* ------------------------------------------------------------------------ */

#include <iostream>
#include <math.h>
#include <ctime>
#include <vector>
#include "par.h"

#ifndef WITH_MPI
#include <chrono>
using sec = chrono::seconds;
#endif

using namespace std;
int ierr = 0;
int core = 0;
int numcores = 1;

int main(int argc, char * argv[]) {
  boost::filesystem::ofstream log("log.flocky", ofstream::trunc);
#ifdef WITH_MPI

  ierr = MPI_Init( & argc, & argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, & core);
  ierr = MPI_Comm_size(MPI_COMM_WORLD, & numcores);

  if (core == 0) {
    log << "*********************************************************************\n";
    log << "*                __   _                  _                          *\n";
    log << "*               / _| | |                | |                         *\n";
    log << "*              | |_  | |   ___     ___  | | __  _   _               *\n";
    log << "*              |  _| | |  / _ \\   / __| | |/ / | | | |              *\n";
    log << "*              | |   | | | (_) | | (__  |   <  | |_| |              *\n";
    log << "*              |_|   |_|  \\___/   \\___| |_|\\_\\  \\__, |              *\n";
    log << "*                                                __/ |              *\n";
    log << "*                                               |___/               *\n";
    log << "*                                                                   *\n";
    log << "*                                                                   *\n";
    log << "*            f l o c k y  - training reactive force fields          *\n";
    log << "*                            Version 1.0                            *\n";
    log << "*                                                                   *\n";
    log << "*                David Furman, PhD ; df398@cam.ac.uk                *\n";
    log << "*                       University of Cambridge                     *\n";
    log << "*                  Copyright (C) 2018-2020 GPL-3.0                  *\n";
    log << "*                                                                   *\n";
    log << "*       Users using flocky are requested to cite:                   *\n";
    log << "*       1. Furman, David; Carmeli, Benny; Zeiri, Yehuda;            *\n";
    log << "*       Kosloff, Ronnie, J. Chem. Theory Comput. 2018, 14 (6)       *\n";
    log << "*       2. Furman, David; Wales J. David, J. Phys. Chem. Lett.      *\n";
    log << "*       2019, 10 (22)                                               *\n";
    log << "*                                                                   *\n";
    log << "*                    https://www.furmanlab.com                      *\n";
    log << "*                                                                   *\n";
    log << "*********************************************************************\n";
    log.close();

  };

  for (cycle = 0; cycle < maxcycles; cycle++) {
    string cyclecount = std::to_string(cycle);

    // Start collecting timing info
    // ------------------------------------------------------------------------//
    double starttime, endtime, diff, sumdiff, avgdiff;
    starttime = MPI_Wtime();
    // ------------------------------------------------------------------------//

    // bkup original ffield
    if ( boost::filesystem::exists("ffield") ) {
       boost::filesystem::copy_file("ffield", "ffield.initial." + cyclecount, 
         boost::filesystem::copy_option::overwrite_if_exists);
    };
    
    Swarm MySwarm;
    MySwarm.get_userinp();
    MySwarm.MakeFilesfromPath(MySwarm);
    MySwarm.MakeEnsembleFF(MySwarm);
    MySwarm.Populate(MySwarm, cycle);
    MySwarm.Propagate(MySwarm, cycle);

    // End collecting timing info
    // ------------------------------------------------------------------------//
    endtime = MPI_Wtime();
    diff = endtime - starttime;   
    MPI_Reduce( & diff, & sumdiff, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    avgdiff = sumdiff / numcores;
    if (core == 0) {
      boost::filesystem::ofstream log("log.flocky", ofstream::app);
      log << "Total CPU time: " << boost::format("%6.1f") %avgdiff << " seconds" << endl;
      log.close();
    };
    // ------------------------------------------------------------------------//

    MySwarm = Swarm();

  }; // end cycles

  ierr = MPI_Finalize();
  return 0;
};
#endif

#ifndef WITH_MPI

    log << "*********************************************************************\n";
    log << "*                __   _                  _                          *\n";
    log << "*               / _| | |                | |                         *\n";
    log << "*              | |_  | |   ___     ___  | | __  _   _               *\n";
    log << "*              |  _| | |  / _ \\   / __| | |/ / | | | |              *\n";
    log << "*              | |   | | | (_) | | (__  |   <  | |_| |              *\n";
    log << "*              |_|   |_|  \\___/   \\___| |_|\\_\\  \\__, |              *\n";
    log << "*                                                __/ |              *\n";
    log << "*                                               |___/               *\n";
    log << "*                                                                   *\n";
    log << "*                                                                   *\n";
    log << "*            f l o c k y  - training reactive force fields          *\n";
    log << "*                            Version 1.0                            *\n";
    log << "*                                                                   *\n";
    log << "*                David Furman, PhD ; df398@cam.ac.uk                *\n";
    log << "*                       University of Cambridge                     *\n";
    log << "*                  Copyright (C) 2018-2020 GPL-3.0                  *\n";
    log << "*                                                                   *\n";
    log << "*       Users using flocky are requested to cite:                   *\n";
    log << "*       1. Furman, David; Carmeli, Benny; Zeiri, Yehuda;            *\n";
    log << "*       Kosloff, Ronnie, J. Chem. Theory Comput. 2018, 14 (6)       *\n";
    log << "*       2. Furman, David; Wales J. David, J. Phys. Chem. Lett.      *\n";
    log << "*       2019, 10 (22)                                               *\n";
    log << "*                                                                   *\n";
    log << "*                    https://www.furmanlab.com                      *\n";
    log << "*                                                                   *\n";
    log << "*********************************************************************\n";
    log.close();

  for (cycle = 0; cycle < maxcycles; cycle++) {
    string cyclecount = std::to_string(cycle);

    auto starttime = chrono::steady_clock::now();

    // bkup original ffield before eval_fitness generates one for current particle fitness evaluation
    if ( boost::filesystem::exists("ffield") ) {
       boost::filesystem::copy_file("ffield", "ffield.initial." + cyclecount,
         boost::filesystem::copy_option::overwrite_if_exists);
    };

    Swarm MySwarm;
    MySwarm.get_userinp();
    MySwarm.Populate(MySwarm, cycle);
    MySwarm.Propagate(MySwarm, cycle);
    
    auto endtime = chrono::steady_clock::now();
    auto diff = endtime - starttime;

    boost::filesystem::ofstream log("log.flocky", ofstream::app);
    log << " " << endl;
    log << "Total CPU time: " << chrono::duration_cast<sec>(diff).count() << " seconds" << endl;
    MySwarm = Swarm();
    log.close();
  };
  return 0;
};
#endif
