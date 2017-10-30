// This file was extracted from the 'decay0' program by V.I. Tretyak
// Copyright 1995-2011 V.I. Tretyak
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at
// your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//

// Ourselves:
#include <bxdecay0/genbbsub.h>

// Standard library:
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <limits>

// This project:
#include <bxdecay0/utils.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/positron.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/pairext1.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/PbAtShell.h>
#include <bxdecay0/bb.h>
#include <bxdecay0/Ac228.h>
#include <bxdecay0/Am241.h>
#include <bxdecay0/Ar39.h>
#include <bxdecay0/Ar42.h>
#include <bxdecay0/As79.h>
#include <bxdecay0/At214.h>
#include <bxdecay0/At214low.h>
#include <bxdecay0/Ba136low.h>
#include <bxdecay0/Ba138low.h>
#include <bxdecay0/Bi207.h>
#include <bxdecay0/Bi208.h>
#include <bxdecay0/Bi210.h>
#include <bxdecay0/Bi212.h>
#include <bxdecay0/Bi214.h>
#include <bxdecay0/C14.h>
#include <bxdecay0/Ca48.h>
#include <bxdecay0/Cd112low.h>
#include <bxdecay0/Cd113.h>
#include <bxdecay0/Co60.h>
#include <bxdecay0/Cs136.h>
#include <bxdecay0/Cs137.h>
#include <bxdecay0/Eu147.h>
#include <bxdecay0/Eu152.h>
#include <bxdecay0/Eu154.h>
#include <bxdecay0/Fe58low.h>
#include <bxdecay0/Gd146.h>
#include <bxdecay0/Gd156low.h>
#include <bxdecay0/Gd158low.h>
#include <bxdecay0/Ge70low.h>
#include <bxdecay0/Ge74low.h>
#include <bxdecay0/Hf180low.h>
#include <bxdecay0/Hf182.h>
#include <bxdecay0/Hg198low.h>
#include <bxdecay0/I126.h>
#include <bxdecay0/I133.h>
#include <bxdecay0/I134.h>
#include <bxdecay0/I135.h>
#include <bxdecay0/K40.h>
#include <bxdecay0/K42.h>
#include <bxdecay0/Kr81.h>
#include <bxdecay0/Kr82low.h>
#include <bxdecay0/Kr84low.h>
#include <bxdecay0/Kr85.h>
#include <bxdecay0/Mn54.h>
#include <bxdecay0/Mo94low.h>
#include <bxdecay0/Mo96low.h>
#include <bxdecay0/Na22.h>
#include <bxdecay0/Nb96.h>
#include <bxdecay0/Nd142low.h>
#include <bxdecay0/Ni64low.h>
#include <bxdecay0/Os186low.h>
#include <bxdecay0/Os190low.h>
#include <bxdecay0/P32.h>
#include <bxdecay0/Pa231.h>
#include <bxdecay0/Pa234m.h>
#include <bxdecay0/Pb210.h>
#include <bxdecay0/Pb211.h>
#include <bxdecay0/Pb212.h>
#include <bxdecay0/Pb214.h>
#include <bxdecay0/Pd104low.h>
#include <bxdecay0/Pd106low.h>
#include <bxdecay0/Pd108low.h>
#include <bxdecay0/Po212.h>
#include <bxdecay0/Po214.h>
#include <bxdecay0/Po214low.h>
#include <bxdecay0/Ra222.h>
#include <bxdecay0/Ra222low.h>
#include <bxdecay0/Ra226.h>
#include <bxdecay0/Ra228.h>
#include <bxdecay0/Rb87.h>
#include <bxdecay0/Rh106.h>
#include <bxdecay0/Rn218.h>
#include <bxdecay0/Rn218low.h>
#include <bxdecay0/Ru100low.h>
#include <bxdecay0/Sb125.h>
#include <bxdecay0/Sb126.h>
#include <bxdecay0/Sb133.h>
#include <bxdecay0/Sc48.h>
#include <bxdecay0/Se76low.h>
#include <bxdecay0/Sm148low.h>
#include <bxdecay0/Sm150low.h>
#include <bxdecay0/Sn114low.h>
#include <bxdecay0/Sn116low.h>
#include <bxdecay0/Sn120low.h>
#include <bxdecay0/Sr90.h>
#include <bxdecay0/Ta182.h>
#include <bxdecay0/Te122low.h>
#include <bxdecay0/Te124low.h>
#include <bxdecay0/Te133.h>
#include <bxdecay0/Te133m.h>
#include <bxdecay0/Te134.h>
#include <bxdecay0/Th234.h>
#include <bxdecay0/Ti48low.h>
#include <bxdecay0/Tl207.h>
#include <bxdecay0/Tl208.h>
#include <bxdecay0/Xe128low.h>
#include <bxdecay0/Xe129m.h>
#include <bxdecay0/Xe130low.h>
#include <bxdecay0/Xe131m.h>
#include <bxdecay0/Xe133.h>
#include <bxdecay0/Xe135.h>
#include <bxdecay0/Y88.h>
#include <bxdecay0/Y90.h>
#include <bxdecay0/Zn65.h>
#include <bxdecay0/Zr92low.h>
#include <bxdecay0/Zr96.h>

namespace bxdecay0 {

  void genbbsub(i_random & prng_,
                event & event_,
                const int i2bbs_,
                const std::string & chnuclide_,
                const int ilevel_,
                const int modebb_,
                const int istart_,
                int & ier_,
                bbpars & bb_params_)
  {
    // Subroutine GENBBsub generates the events of decay of natural
    // radioactive nuclides and various modes of double beta decay.
    // GENBB units: energy and moment - MeV and MeV/c
    // Energy release in double beta decay - in accordance with
    // G.Audi and A.H.Wapstra, Nucl. Phys. A 595(1995)409.
    // Call : character chnuclide*16, chfile*256, chart*4, chdspin*4
    // common/genbbpar/nevents, ievstart, irndmst, iwrfile, chfile
    // common/currentev/icurrent
    // common/enrange/ebb1, ebb2, toallevents, levelE, chdspin
    // common/artificial/nartparts, chart(10),
    // + artemin(10), artemax(10),
    // + arttmin(10), arttmax(10),
    // + artfmin(10), artfmax(10),
    // + artQb(10), artZd(10),
    // + arttdelay(10), artthalf(10)
    // + nartnpg(10)
    // // common/genevent/tevst, npfull, npgeant(100), pmoment(3, 100), // ptime(100)
    // call GENBBsub(i2bbs, chnuclide, ilevel, modebb, istart, ier)
    // Input : i2bbs - i2bbs=1 - to generate 2b-decay,
    // i2bbs=2 - to generate decay of background nuclide
    // or calibration source
    // chnuclide - character*16 name of nuclide:
    // =======> for i2bbs=1
    // Ca48,
    // Ni58,
    // Zn64, Zn70,
    // Ge76,
    // Se74, Se82,
    // Sr84,
    // Zr94, Zr96,
    // Mo92, Mo100,
    // Ru96, Ru104,
    // Cd106, Cd108, Cd114, Cd116,
    // Sn112, Sn122, Sn124,
    // Te120, Te128, Te130,
    // Xe136,
    // Ce136, Ce138, Ce142,
    // Nd148, Nd150,
    // Dy156, Dy158,
    // W180, W186,
    // Pt190, Pt198,
    // Bi214 (for Bi214+At214),
    // Pb214 (for Pb214+Po214),
    // Po218 (for Po218+Rn218+Po214),
    // Rn222 (for Rn222+Ra222+Rn218+Po214)
    // Rn226 (for Rn226)
    // =======> for i2bbs=2
    // Ac228,
    // Am241,
    // Ar39,
    // Ar42,
    // As79 (for As79+Se79m),
    // Bi207 (for Bi207+Pb207m),
    // Bi208,
    // Bi210,
    // Bi212 (for Bi212+Po212),
    // Bi214 (for Bi214+Po214),
    // Ca48 (for Ca48+Sc48),
    // C14,
    // Cd113,
    // Co60,
    // Cs136,
    // Cs137 (for Cs137+Ba137m),
    // Eu147,
    // Eu152,
    // Eu154,
    // Gd146,
    // Hf182,
    // I126,
    // I133,
    // I134,
    // I135,
    // K40,
    // K42,
    // Kr81,
    // Kr85,
    // Mn54,
    // Na22,
    // P32,
    // Pa231, // Added 2013-09-06
    // Pa234m,
    // Pb210,
    // Pb211,
    // Pb212,
    // Pb214,
    // Ra226, // Added 2013-07-11
    // Ra228,
    // Rb87,
    // Rh106,
    // Sb125,
    // Sb126,
    // Sb133,
    // Sr90,
    // Ta182,
    // Te133,
    // Te133m,
    // Te134,
    // Th234,
    // Tl207,
    // Tl208,
    // Xe129m,
    // Xe131m,
    // Xe133,
    // Xe135,
    // Y88,
    // Y90,
    // Zn95,
    // Zr96 (for Zr96+Nb96),
    // Art (for artificial event),
    // Com (for Compton effect),
    // Mol (for Moller scattering),
    // Pai (for e+e- pair creation from
    // external gammas)
    // =======> ilevel - (for i2bbs=1 only) level of daughter nucleus occupied
    // in 2b decay (0 - ground state, 1 - first excited 0+ or
    // 2+ level, 2 - second excited 0+ or 2+ level etc.
    // excited levels with other spin than 0+ and 2+ should be
    // omitted):
    // for Ca48-Ti48 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.984 MeV},
    // 2. 2+ (2) {2.421 MeV},
    // for Ni58-Fe58 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.811 MeV},
    // 2. 2+ (2) {1.675 MeV},
    // for Zn64-Ni64 - 0. 0+ (gs) {0 MeV},
    // for Zn70-Ge70 - 0. 0+ (gs) {0 MeV},
    // for Ge76-Se76 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.559 MeV},
    // 2. 0+ (1) {1.122 MeV},
    // 3. 2+ (2) {1.216 MeV},
    // for Se74-Ge74 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.596 MeV},
    // 2. 2+ (2) {1.204 MeV},
    // for Se82-Kr82 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.776 MeV},
    // 2. 2+ (2) {1.475 MeV},
    // for Sr84-Kr84 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.882 MeV},
    // for Zr94-Mo94 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.871 MeV},
    // for Zr96-Mo96 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.778 MeV},
    // 2. 0+ (1) {1.148 MeV},
    // 3. 2+ (2) {1.498 MeV},
    // 4. 2+ (3) {1.626 MeV},
    // 5. 2+ (4) {2.096 MeV},
    // 6. 2+ (5) {2.426 MeV},
    // 7. 0+ (2) {2.623 MeV},
    // 8. 2+ (6) {2.700 MeV},
    // 9. 2+?(7) {2.713 MeV},
    // for Mo92-Zr92 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.934 MeV},
    // 2. 0+ (1) {1.383 MeV},
    // for Mo100-Ru100 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.540 MeV},
    // 2. 0+ (1) {1.130 MeV},
    // 3. 2+ (2) {1.362 MeV},
    // 4. 0+ (2) {1.741 MeV},
    // for Ru96-Mo96 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.778 MeV},
    // 2. 0+ (1) {1.148 MeV},
    // 3. 2+ (2) {1.498 MeV},
    // 4. 2+ (3) {1.626 MeV},
    // 5. 2+ (4) {2.096 MeV},
    // 6. 2+ (5) {2.426 MeV},
    // 7. 0+ (2) {2.623 MeV},
    // 8. 2+ (6) {2.700 MeV},
    // 9. 2+?(7) {2.713 MeV},
    // for Ru104-Pd104 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.556 MeV},
    // for Cd106-Pd106 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.512 MeV},
    // 2. 2+ (2) {1.128 MeV},
    // 3. 0+ (1) {1.134 MeV},
    // 4. 2+ (3) {1.562 MeV},
    // 5. 0+ (2) {1.706 MeV},
    // for Cd108-Pd108 - 0. 0+ (gs) {0 MeV},
    // for Cd114-Sn114 - 0. 0+ (gs) {0 MeV},
    // for Cd116-Sn116 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {1.294 MeV},
    // 2. 0+ (1) {1.757 MeV},
    // 3. 0+ (2) {2.027 MeV},
    // 4. 2+ (2) {2.112 MeV},
    // 5. 2+ (3) {2.225 MeV},
    // for Sn112-Cd112 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.618 MeV},
    // 2. 0+ (1) {1.224 MeV},
    // 3. 2+ (2) {1.312 MeV},
    // 4. 0+ (2) {1.433 MeV},
    // 5. 2+ (3) {1.469 MeV},
    // 6. 0+ (3) {1.871 MeV},
    // for Sn122-Te122 - 0. 0+ (gs) {0 MeV},
    // for Sn124-Te124 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.603 MeV},
    // 2. 2+ (2) {1.326 MeV},
    // 3. 0+ (1) {1.657 MeV},
    // 4. 0+ (2) {1.883 MeV},
    // 5. 2+ (3) {2.039 MeV},
    // 6. 2+ (4) {2.092 MeV},
    // 7. 0+ (3) {2.153 MeV},
    // 8. 2+ (5) {2.182 MeV},
    // for Te120-Sn120 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {1.171 MeV},
    // for Te128-Xe128 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.443 MeV},
    // for Te130-Xe130 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.536 MeV},
    // 2. 2+ (2) {1.122 MeV},
    // 3. 0+ (1) {1.794 MeV},
    // for Xe136-Ba136 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.819 MeV},
    // 2. 2+ (2) {1.551 MeV},
    // 3. 0+ (1) {1.579 MeV},
    // 4. 2+ (3) (2.080 MeV},
    // 5. 2+ (4) {2.129 MeV},
    // 6. 0+ (2) {2.141 MeV},
    // 7. 2+ (5) {2.223 MeV},
    // 8. 0+ (3) {2.315 MeV},
    // 9. 2+ (6) {2.400 MeV},
    // for Ce136-Ba136 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.819 MeV},
    // 2. 2+ (2) {1.551 MeV},
    // 3. 0+ (1) {1.579 MeV},
    // 4. 2+ (3) (2.080 MeV},
    // 5. 2+ (4) {2.129 MeV},
    // 6. 0+ (2) {2.141 MeV},
    // 7. 2+ (5) {2.223 MeV},
    // 8. 0+ (3) {2.315 MeV},
    // 9. 2+ (6) {2.400 MeV},
    // for Ce138-Ba138 - 0. 0+ (gs) {0 MeV},
    // for Ce142-Nd142 - 0. 0+ (gs) {0 MeV},
    // for Nd148-Sm148 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.550 MeV},
    // 2. 2+ (2) {1.455 MeV},
    // for Nd150-Sm150 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.334 MeV},
    // 2. 0+ (1) {0.740 MeV},
    // 3. 2+ (2) {1.046 MeV},
    // 4. 2+ (3) {1.194 MeV},
    // 5. 0+ (2) {1.256 MeV}
    // for Dy156-Gd156 - 0. 0+ (gs) {0 MeV}'
    // 1. 2+ (1) {0.089 MeV}'
    // 2. 0+ (1) {1.050 MeV}'
    // 3. 2+ (2) {1.129 MeV}'
    // 4. 2+ (3) {1.154 MeV}'
    // 5. 0+ (2) {1.168 MeV}'
    // 6. 2+ (4) {1.258 MeV}'
    // 7. 0+ (3) {1.715 MeV}'
    // 8. 2+ (5) {1.771 MeV}'
    // 9. 2+ (6) {1.828 MeV}'
    // 10. 0+ (4) {1.851 MeV}'
    // 11. 2+ (7) {1.915 MeV}'
    // 12. 1- {1.946 MeV}'
    // 13. 0- {1.952 MeV}'
    // 14. 0+ (5) {1.989 MeV}'
    // 15. 2+ (8) {2.004 MeV}'
    // for Dy158-Gd158 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.080 MeV},
    // 2. 4+ (1) {0.261 MeV}
    // for W180-Hf180 - 0. 0+ (gs) {0 MeV}
    // for W186-Os186 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.137 MeV}
    // for Pt190-Os190 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.187 MeV},
    // 2. 2+ (2) {0.558 MeV},
    // 3. 0+ (1) {0.912 MeV},
    // 4. 2+ (3) {1.115 MeV},
    // 5. 0+ (2) {1.382 MeV}
    // for Pt198-Hg198 - 0. 0+ (gs) {0 MeV},
    // 1. 2+ (1) {0.412 MeV}
    // for Bi214-At214 - 0. 1- (gs) {0 MeV}
    // for Pb214-Po214 - 0. 0+ (gs) {0 MeV}
    // for Po218-Rn218 - 0. 0+ (gs) {0 MeV}
    // for Rn222-Ra222 - 0. 0+ (gs) {0 MeV}
    // modebb - (for i2bbs=1 only) mode of 2b decay:
    // 1. 0nubb(mn) 0+ -> 0+ {2n},
    // 2. 0nubb(rhc-lambda) 0+ -> 0+ {2n},
    // 3. 0nubb(rhc-lambda) 0+ -> 0+, 2+ {N*},
    // 4. 2nubb 0+ -> 0+ {2n},
    // 5. 0nubbM1 0+ -> 0+ {2n}
    // Majoron with spectral index SI=1
    // (old M of Gelmini-Roncadelli),
    // 6. 0nubbM3 0+ -> 0+ {2n}
    // Majoron with SI=3 (vector M, double M, charged M),
    // 7. 0nubb(rhc-lambda) 0+ -> 2+ {2n},
    // 8. 2nubb 0+ -> 2+ {2n}, {N*},
    // 9. 0nuKb+ 0+ -> 0+, 2+,
    // 10. 2nuKb+ 0+ -> 0+, 2+,
    // 11. 0nu2K 0+ -> 0+, 2+,
    // 12. 2nu2K 0+ -> 0+, 2+,
    // 13. 0nubbM7 0+ -> 0+ {2n}
    // Majoron with SI=7,
    // 14. 0nubbM2 0+ -> 0+ {2n}
    // Majoron with SI=2 (bulk M of Mohapatra)
    // 15. 2nubb 0+ -> 0+ with bosonic neutrinos,
    // 16. 2nubb 0+ -> 2+ with bosonic neutrinos,
    // 17. 0nubb(rhc-eta) 0+ -> 0+ simplified expression,
    // 18. 0nubb(rhc-eta) 0+ -> 0+ with specified NMEs
    // istart - -1 - to check consistency of input data and fill
    // working arrays without generation of events
    // 0 - the same but one event will be generated
    // 1 - to generate all subsequent events. So, for
    // the first call to GENBBsub istart must be
    // =0 or -1
    // nevents - number of events to generate
    // for information in GENBB.report file and in output
    // file with generated events (if asked) - so, one
    // has to call GENBBsub one time for one decay event
    // ievstart - number of first event
    // irndmst - (only for ievstart > 1) initial random integer
    // for RDMIN
    // iwrfile - iwrfile=0 - do { // not write generated events in file,
    // iwrfile=1 - to write generated events in file
    // chfile - (only for iwrfile=1) character*40 name of file
    // icurrent - current number of event
    // GENBB.report is created
    // ebb1, ebb2 - (only for i2bbs=1) left and right energy limits for
    // sum of energies of emitted e-/e+
    // be thrown away (for modebb = 4, 5, 6, 8, 10 and 13)
    // For artificial event (i2bbs=2 and chnuclide='Art')
    // (emission of up to 10 beta, e+e- pairs and all
    // GEANT particles in region of energies and angles
    // with time delay and halflife):
    // nartparts - number of parts of artificial event (up to 10)
    // chart - character*4 array of identifiers:
    // GP - emission of GEANT particle,
    // Pi - emission of internal conversion e+/e- pair,
    // Be - beta decay
    // artemin, - arrays of min and max values for particles kinetic
    // artemax energies (MeV)
    // arttmin, - arrays of min and max values for particles teta
    // arttmax angles (degree)
    // artfmin, - arrays of min and max values for particles phi
    // artfmax angles (degree)
    // artQb - (for chart='Be') array of Qbeta values (MeV),
    // (for chart='Pi') array of pair kinetic energy (MeV)
    // artZd - (for chart='Be') array of atomic numbers of daughter
    // nucleus (artZd>0 for beta- and artZd<0 for beta+ decay)
    // arttdelay - array of time delays: minimum time between current
    // part of event and previous one (sec)
    // artthalf - array of half-lives of current part of events (sec)
    // nartnpg - array of GEANT number particles:
    // 1 - gamma 2 - positron 3 - electron
    // 4 - neutrino 5 - muon+ 6 - muon-
    // 7 - pion0 8 - pion+ 9 - pion-
    // 10 - kaon0 long 11 - kaon+ 12 - kaon-
    // 13 - neutron 14 - proton 15 - antiproton
    // 16 - kaon0 short 17 - eta 18 - lambda
    // 19 - sigma+ 20 - sigma0 21 - sigma-
    // 22 - xi0 23 - xi- 24 - omega
    // 25 - antineutron 26 - antilambda 27 - antisigma-
    // 28 - antisigma0 29 - antisigma+ 30 - antixi0
    // 31 - antixi+ 32 - antiomega+ 45 - deuteron
    // 46 - tritium 47 - alpha 48 - geantino
    // 49 - He3 50 - Cerenkov.
    // For chart = 'GP' particle's energy will be uniformly
    // distributed in the range [artemin, artemax]
    // will be emitted isotropically in the region of space
    // determined by [arttmin, arttmax], [artfmin, artfmax].
    // For chart = 'Be', energy will be sampled in [0, artQb] in
    // accordance with beta decay energy spectrum
    // will be emitted isotropically in full space.
    // For chart = 'Pi', energy of pair is fixed to artQb and
    // divided half to half for e- and e+
    // emitted in the same direction
    // distributed isotropically in full space.
    // For generation of events of Compton effect (i2bbs=2 and
    // chnuclide='Com'):
    // artemin(1), - min and max values for kinetic energy of initial
    // artemax(1) gamma quantum (MeV)
    // arttmin(1), - min and max values for teta angle of initial particle
    // arttmax(1) (degree)
    // artfmin(1), - min and max values for phi angle of initial particle
    // artfmax(1) (degree)
    // For generation of events of Moller scattering (i2bbs=2
    // and chnuclide='Mol'):
    // artemin(1), - min and max values for kinetic energy of initial
    // artemax(1) electron (MeV)
    // arttmin(1), - min and max values for teta angle of initial particle
    // arttmax(1) (degree)
    // artfmin(1), - min and max values for phi angle of initial particle
    // artfmax(1) (degree)
    // artQb(1) - lower energy threshold for emitted delta rays (MeV)
    // For generation of events of e+e- pair creation from
    // external gamma quanta: (i2bbs=2 and chnuclide='Pai'):
    // artemin(1), - min and max values for kinetic energy of initial
    // artemax(1) gamma quantum (MeV)
    // arttmin(1), - min and max values for teta angle of initial particle
    // arttmax(1) (degree)
    // artfmin(1), - min and max values for phi angle of initial particle
    // artfmax(1) (degree)
    // artZd(1) - atomic number Z of target
    // Output: ier - ier=0/1 - everything is correct/incorrect in
    // input parameters
    // tevst - time of event's start (sec)
    // npfull - full number of emitted particles in event
    // npgeant(1-npfull) - array of GEANT numbers for particle identi-
    // fication (1 for gamma, 2 for e+, 3 for e-,
    // 5 for muon+, 6 for muon-, 47 for alpha)
    // pmoment(1-3, 1-npfull) - array of x, y, z components of particle momentum
    // (MeV/c)
    // ptime(1-npfull) - array of time shift from previous time to
    // calculate when particle was emitted (sec)
    // toallevents - (only for i2bbs=1 and restricted range for sum
    // of energies of emitted e-/e+) coefficient to
    // recalculate number of bb events in full range
    // of energies:
    // full_number=generated_number*toallevents
    // (for modebb = 4, 5, 6, 8, 10 and 13)
    // levelE - (only for i2bbs=1) energy (in keV) of level of
    // daughter 2b nuclide
    // chdspin - (only for i2bbs=1) character*4 spin and parity of
    // the level of daughter nuclide in 2b decay.
    // V.I.Tretyak, 04.12.1995.

    /*
      common/genbbpar/nevents, ievstart, irndmst, iwrfile, chfile;
      common/const/pi, emass, datamass(50);
      common/enrange/ebb1, ebb2, toallevents, levelE, chdspin;
      common/currentev/icurrent;
      common/slate/isl(40);
      common/artificial/nartparts, chart(10),
      artemin(10), artemax(10),
      arttmin(10), arttmax(10),
      artfmin(10), artfmax(10),
      artQb(10), artZd(10),
      arttdelay(10), artthalf(10),
      nartnpg(10);
      save Qbb, EK, Zdbb, Adbb, istartbb;
      common/eta_nme/chi_GTw, chi_Fw, chip_GT, chip_F, chip_T,
      chip_P, chip_R;
      //std::string chart;
      //int nartparts;
      //int np;
      */

    double tdnuc;
    double tdnuc1;
    int    npfull0;

    static const double emass = decay0_emass();
    if (modebb_ != bb_params_.modebb) {
      bb_params_.modebb = modebb_;
    }

    // Error code :
    ier_ = 0;

    if (istart_ != GENBBSUB_ISTART_GENERATE) {

      if (i2bbs_ == GENBBSUB_I2BBS_DBD) {
        if (name_starts_with(chnuclide_,"Ca48")) {
          bb_params_.Qbb=4.272;
          bb_params_.Zdbb=22.;
          bb_params_.Adbb=48.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=984;
          if (ilevel_ == 2) bb_params_.levelE=2421;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Ni58")) {
          bb_params_.Qbb=1.926;
          bb_params_.Zdbb=-26.;
          bb_params_.Adbb=58.;
          bb_params_.EK=0.007;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=811;
          if (ilevel_ == 2) bb_params_.levelE=1675;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Zn64")) {
          bb_params_.Qbb=1.096;
          bb_params_.Zdbb=-28.;
          bb_params_.Adbb=64.;
          bb_params_.EK=0.008;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Zn70")) {
          bb_params_.Qbb=1.001;
          bb_params_.Zdbb=32.;
          bb_params_.Adbb=70.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Ge76")) {
          bb_params_.Qbb=2.039;
          bb_params_.Zdbb=34.;
          bb_params_.Adbb=76.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 3) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=559;
          if (ilevel_ == 2) bb_params_.levelE=1122;
          if (ilevel_ == 3) bb_params_.levelE=1216;
          if (ilevel_ == 0 || ilevel_ == 2) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 3) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Se74")) {
          bb_params_.Qbb=1.209;
          bb_params_.Zdbb=-32.;
          bb_params_.Adbb=74.;
          bb_params_.EK=0.011;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=596;
          if (ilevel_ == 2) bb_params_.levelE=1204;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Se82")) {
          bb_params_.Qbb=2.995;
          bb_params_.Zdbb=36.;
          bb_params_.Adbb=82.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=776;
          if (ilevel_ == 2) bb_params_.levelE=1475;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Sr84")) {
          bb_params_.Qbb=1.787;
          bb_params_.Zdbb=-36.;
          bb_params_.Adbb=84.;
          bb_params_.EK=0.014;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=882;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Zr94")) {
          bb_params_.Qbb=1.144;
          bb_params_.Zdbb=42.;
          bb_params_.Adbb=94.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=871;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Zr96")) {
          bb_params_.Qbb=3.350;
          bb_params_.Zdbb=42.;
          bb_params_.Adbb=96.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=778;
          if (ilevel_ == 2) bb_params_.levelE=1148;
          if (ilevel_ == 3) bb_params_.levelE=1498;
          if (ilevel_ == 4) bb_params_.levelE=1626;
          if (ilevel_ == 5) bb_params_.levelE=2096;
          if (ilevel_ == 6) bb_params_.levelE=2426;
          if (ilevel_ == 7) bb_params_.levelE=2623;
          if (ilevel_ == 8) bb_params_.levelE=2700;
          if (ilevel_ == 9) bb_params_.levelE=2713;
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 7) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4 ||
              ilevel_ == 5 || ilevel_ == 6 || ilevel_ == 8 ||
              // we suppose here that 2713 keV level is 2+
              ilevel_ == 9) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Mo92")) {
          bb_params_.Qbb=1.649;
          bb_params_.Zdbb=-40.;
          bb_params_.Adbb=92.;
          bb_params_.EK=0.018;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=934;
          if (ilevel_ == 2) bb_params_.levelE=1383;
          if (ilevel_ == 0 || ilevel_ == 2) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Mo100")) {
          bb_params_.Qbb=3.034;
          bb_params_.Zdbb=44.;
          bb_params_.Adbb=100.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 4) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=540;
          if (ilevel_ == 2) bb_params_.levelE=1130;
          if (ilevel_ == 3) bb_params_.levelE=1362;
          if (ilevel_ == 4) bb_params_.levelE=1741;
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 4) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 3) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Ru96")) {
          bb_params_.Qbb=2.718;
          bb_params_.Zdbb=-42.;
          bb_params_.Adbb=96.;
          bb_params_.EK=0.020;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=778;
          if (ilevel_ == 2) bb_params_.levelE=1148;
          if (ilevel_ == 3) bb_params_.levelE=1498;
          if (ilevel_ == 4) bb_params_.levelE=1626;
          if (ilevel_ == 5) bb_params_.levelE=2096;
          if (ilevel_ == 6) bb_params_.levelE=2426;
          if (ilevel_ == 7) bb_params_.levelE=2623;
          if (ilevel_ == 8) bb_params_.levelE=2700;
          if (ilevel_ == 9) bb_params_.levelE=2713;
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 7) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4 ||
              ilevel_ == 5 || ilevel_ == 6 || ilevel_ == 8 ||
              // we suppose here that 2713 keV level is 2+
              ilevel_ == 9) bb_params_.itrans02=2;
          if (ilevel_ == 8)  bb_params_.EK=0.003;
          if (ilevel_ == 9)  bb_params_.EK=0.002;
        } else if (name_starts_with(chnuclide_,"Ru104")) {
          bb_params_.Qbb=1.301;
          bb_params_.Zdbb=46.;
          bb_params_.Adbb=104.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=556;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Cd106")) {
          bb_params_.Qbb=2.771;
          bb_params_.Zdbb=-46.;
          bb_params_.Adbb=106.;
          bb_params_.EK=0.024;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=512;
          if (ilevel_ == 2) bb_params_.levelE=1128;
          if (ilevel_ == 3) bb_params_.levelE=1134;
          if (ilevel_ == 4) bb_params_.levelE=1562;
          if (ilevel_ == 5) bb_params_.levelE=1706;
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5) {
            bb_params_.itrans02=0;
          }
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4) {
            bb_params_.itrans02=2;
          }
        } else if (name_starts_with(chnuclide_,"Cd108")) {
          bb_params_.Qbb=0.269;
          bb_params_.Zdbb=-46.;
          bb_params_.Adbb=108.;
          bb_params_.EK=0.024;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Cd114")) {
          bb_params_.Qbb=0.536;
          bb_params_.Zdbb=50.;
          bb_params_.Adbb=114.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Cd116")) {
          bb_params_.Qbb=2.805;
          bb_params_.Zdbb=50.;
          bb_params_.Adbb=116.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=1294;
          if (ilevel_ == 2) bb_params_.levelE=1757;
          if (ilevel_ == 3) bb_params_.levelE=2027;
          if (ilevel_ == 4) bb_params_.levelE=2112;
          if (ilevel_ == 5) bb_params_.levelE=2225;
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 3) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 4 || ilevel_ == 5) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Sn112")) {
          bb_params_.Qbb=1.919;
          bb_params_.Zdbb=-48.;
          bb_params_.Adbb=112.;
          bb_params_.EK=0.027;
          if (ilevel_ < 0 || ilevel_ > 6) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=618;
          if (ilevel_ == 2) bb_params_.levelE=1224;
          if (ilevel_ == 3) bb_params_.levelE=1312;
          if (ilevel_ == 4) bb_params_.levelE=1433;
          if (ilevel_ == 5) bb_params_.levelE=1469;
          if (ilevel_ == 6) bb_params_.levelE=1871;
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 4 ||
              ilevel_ == 6) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 5) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Sn122")) {
          bb_params_.Qbb=0.368;
          bb_params_.Zdbb=52.;
          bb_params_.Adbb=122.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Sn124")) {
          bb_params_.Qbb=2.288;
          bb_params_.Zdbb=52.;
          bb_params_.Adbb=124.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 8) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=603;
          if (ilevel_ == 2) bb_params_.levelE=1326;
          if (ilevel_ == 3) bb_params_.levelE=1657;
          if (ilevel_ == 4) bb_params_.levelE=1883;
          if (ilevel_ == 5) bb_params_.levelE=2039;
          if (ilevel_ == 6) bb_params_.levelE=2092;
          if (ilevel_ == 7) bb_params_.levelE=2153;
          if (ilevel_ == 8) bb_params_.levelE=2182;
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 4 ||
              ilevel_ == 7) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 5 ||
              ilevel_ == 6 || ilevel_ == 8) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Te120")) {
          bb_params_.Qbb=1.698;
          bb_params_.Zdbb=-50.;
          bb_params_.Adbb=120.;
          bb_params_.EK=0.029;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=1171;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Te128")) {
          bb_params_.Qbb=0.867;
          bb_params_.Zdbb=54.;
          bb_params_.Adbb=128.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=443;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Te130")) {
          bb_params_.Qbb=2.529;
          bb_params_.Zdbb=54.;
          bb_params_.Adbb=130.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 3) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=536;
          if (ilevel_ == 2) bb_params_.levelE=1122;
          if (ilevel_ == 3) bb_params_.levelE=1794;
          if (ilevel_ == 0 || ilevel_ == 3) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Xe136")) {
          bb_params_.Qbb=2.468;
          bb_params_.Zdbb=56.;
          bb_params_.Adbb=136.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=819;
          if (ilevel_ == 2) bb_params_.levelE=1551;
          if (ilevel_ == 3) bb_params_.levelE=1579;
          if (ilevel_ == 4) bb_params_.levelE=2080;
          if (ilevel_ == 5) bb_params_.levelE=2129;
          if (ilevel_ == 6) bb_params_.levelE=2141;
          if (ilevel_ == 7) bb_params_.levelE=2223;
          if (ilevel_ == 8) bb_params_.levelE=2315;
          if (ilevel_ == 9) bb_params_.levelE=2400;
          if (ilevel_ == 0 || ilevel_ == 3
              || ilevel_ == 6 || ilevel_ == 8) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2
              || ilevel_ == 4 || ilevel_ == 5
              || ilevel_ == 7 || ilevel_ == 9) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Ce136")) {
          bb_params_.Qbb=2.419;
          bb_params_.Zdbb=-56.;
          bb_params_.Adbb=136.;
          bb_params_.EK=0.037;
          if (ilevel_ < 0 || ilevel_ > 9) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=819;
          if (ilevel_ == 2) bb_params_.levelE=1551;
          if (ilevel_ == 3) bb_params_.levelE=1579;
          if (ilevel_ == 4) bb_params_.levelE=2080;
          if (ilevel_ == 5) bb_params_.levelE=2129;
          if (ilevel_ == 6) bb_params_.levelE=2141;
          if (ilevel_ == 7) bb_params_.levelE=2223;
          if (ilevel_ == 8) bb_params_.levelE=2315;
          if (ilevel_ == 9) bb_params_.levelE=2400;
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 6 || ilevel_
              == 8) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4 || ilevel_
              == 5 || ilevel_ == 7 || ilevel_ == 9) bb_params_.itrans02=2;
          // only 2L capture is allowed energetically for 2400 keV level
          if (ilevel_ == 9)  bb_params_.EK=0.006;
        } else if (name_starts_with(chnuclide_,"Ce138")) {
          bb_params_.Qbb=0.693;
          bb_params_.Zdbb=-56.;
          bb_params_.Adbb=138.;
          bb_params_.EK=0.037;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Ce142")) {
          bb_params_.Qbb=1.417;
          bb_params_.Zdbb=60.;
          bb_params_.Adbb=142.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Nd148")) {
          bb_params_.Qbb=1.929;
          bb_params_.Zdbb=62.;
          bb_params_.Adbb=148.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=550;
          if (ilevel_ == 2) bb_params_.levelE=1455;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Nd150")) {
          bb_params_.Qbb=3.367;
          bb_params_.Zdbb=62.;
          bb_params_.Adbb=150.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=334;
          if (ilevel_ == 2) bb_params_.levelE=740;
          if (ilevel_ == 3) bb_params_.levelE=1046;
          if (ilevel_ == 4) bb_params_.levelE=1194;
          if (ilevel_ == 5) bb_params_.levelE=1256;
          if (ilevel_ == 0 || ilevel_ == 2 || ilevel_ == 5) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 3 || ilevel_ == 4) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Dy156")) {
          bb_params_.Qbb=2.012;
          bb_params_.Zdbb=-64.;
          bb_params_.Adbb=156.;
          bb_params_.EK=0.050;
          if (ilevel_ < 0 || ilevel_ > 15) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ ==  0) bb_params_.levelE=0;
          if (ilevel_ ==  1) bb_params_.levelE=89;
          if (ilevel_ ==  2) bb_params_.levelE=1050;
          if (ilevel_ ==  3) bb_params_.levelE=1129;
          if (ilevel_ ==  4) bb_params_.levelE=1154;
          if (ilevel_ ==  5) bb_params_.levelE=1168;
          if (ilevel_ ==  6) bb_params_.levelE=1258;
          if (ilevel_ ==  7) bb_params_.levelE=1715;
          if (ilevel_ ==  8) bb_params_.levelE=1771;
          if (ilevel_ ==  9) bb_params_.levelE=1828;
          if (ilevel_ == 10) bb_params_.levelE=1851;
          if (ilevel_ == 11) bb_params_.levelE=1915;
          if (ilevel_ == 12) bb_params_.levelE=1946;
          if (ilevel_ == 13) bb_params_.levelE=1952;
          if (ilevel_ == 14) bb_params_.levelE=1989;
          if (ilevel_ == 15) bb_params_.levelE=2004;
          if (ilevel_ == 0  ||  ilevel_ == 2  ||  ilevel_ == 5  ||
              ilevel_ == 7  ||  ilevel_ == 10  ||  ilevel_ == 14) {
            bb_params_.itrans02=0;
          }
          if (ilevel_ == 1  ||  ilevel_ == 3  ||  ilevel_ == 4  ||
              ilevel_ == 6  ||  ilevel_ == 8  ||  ilevel_ == 9  ||
              ilevel_ == 11  ||  ilevel_ == 15) bb_params_.itrans02=2;
          if (ilevel_ >= 11  &&  ilevel_ <= 13) bb_params_.EK=0.029;
          if (ilevel_ == 14)  bb_params_.EK=0.008;
          if (ilevel_ == 15)  bb_params_.EK=0.004;
        } else if (name_starts_with(chnuclide_,"Dy158")) {
          bb_params_.Qbb=0.285;
          bb_params_.Zdbb=-64.;
          bb_params_.Adbb=158.;
          bb_params_.EK=0.050;
          if (ilevel_ < 0 || ilevel_ > 2) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=80;
          if (ilevel_ == 2) bb_params_.levelE=261;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
          if (ilevel_ == 2)  bb_params_.EK=0.008;
        } else if (name_starts_with(chnuclide_,"W180")) {
          bb_params_.Qbb=0.144;
          bb_params_.Zdbb=-72.;
          bb_params_.Adbb=180.;
          bb_params_.EK=0.065;
          if (ilevel_ < 0 || ilevel_ > 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Hf180 level ", ilevel_
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"W186")) {
          bb_params_.Qbb=0.490;
          bb_params_.Zdbb=76.;
          bb_params_.Adbb=186.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Os186 level ", ilevel_
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=137;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Pt190")) {
          bb_params_.Qbb=1.383;
          bb_params_.Zdbb=-76.;
          bb_params_.Adbb=190.;
          bb_params_.EK=0.074;
          if (ilevel_ < 0 || ilevel_ > 5) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Os190 level ", ilevel_
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=187;
          if (ilevel_ == 2) bb_params_.levelE=558;
          if (ilevel_ == 3) bb_params_.levelE=912;
          if (ilevel_ == 4) bb_params_.levelE=1115;
          if (ilevel_ == 5) bb_params_.levelE=1382;
          if (ilevel_ == 0 || ilevel_ == 3 || ilevel_ == 5) bb_params_.itrans02=0;
          if (ilevel_ == 1 || ilevel_ == 2 || ilevel_ == 4) bb_params_.itrans02=2;
          // for decay to 1382 keV level, electron captures from N or higher atomic shells are possible
          if (ilevel_ == 5)  bb_params_.EK=0.;
        } else if (name_starts_with(chnuclide_,"Pt198")) {
          bb_params_.Qbb=1.047;
          bb_params_.Zdbb=80.;
          bb_params_.Adbb=198.;
          bb_params_.EK=0.;
          if (ilevel_ < 0 || ilevel_ > 1) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Hg198 level ", ilevel_
            ier_=1;
            return;
          }
          if (ilevel_ == 0) bb_params_.levelE=0;
          if (ilevel_ == 1) bb_params_.levelE=412;
          if (ilevel_ == 0) bb_params_.itrans02=0;
          if (ilevel_ == 1) bb_params_.itrans02=2;
        } else if (name_starts_with(chnuclide_,"Bi214")) {
          bb_params_.Qbb=2.180;
          bb_params_.Zdbb=85.;
          bb_params_.Adbb=214.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal At214 level ", ilevel_
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Pb214")) {
          bb_params_.Qbb=4.289;
          bb_params_.Zdbb=84.;
          bb_params_.Adbb=214.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Po214 level ", ilevel_
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Po218")) {
          bb_params_.Qbb=3.141;
          bb_params_.Zdbb=86.;
          bb_params_.Adbb=218.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Rn218 level ", ilevel_
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else if (name_starts_with(chnuclide_,"Rn222")) {
          bb_params_.Qbb=2.052;
          bb_params_.Zdbb=88.;
          bb_params_.Adbb=222.;
          bb_params_.EK=0.;
          if (ilevel_ != 0) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Illegal '" << chnuclide_ << "' daughter's level (" << ilevel_ << ") ! \n";
            // print *, "GENBBsub: illegal Ra222 level ", ilevel_
            ier_=1;
            return;
          }
          bb_params_.levelE=0;
          bb_params_.itrans02=0;
        } else {
          std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                    << "Unknown double beta nuclide '" << chnuclide_ << "' ! \n";
          // print *, "unknown double beta nuclide"
          ier_=1;
          return;
        }
        if (bb_params_.itrans02 == 0) bb_params_.chdspin="0+";
        if (bb_params_.itrans02 == 2) bb_params_.chdspin="2+";
        if (bb_params_.itrans02 == 0
            && name_starts_with(chnuclide_,"Bi214")) bb_params_.chdspin="1-";
        if (bb_params_.modebb < 1 || bb_params_.modebb > 18) {
          std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                    << "Unknown double beta mode (" << bb_params_.modebb << ") ! \n";
          ier_=1;
          return;
        }
        std::string modebb_label = decay0_dbd_mode_label(bb_params_.modebb);
        {
          // checking the consistency of data: (1) energy
          double El=bb_params_.levelE/1000.;
          double e0;
          e0 = std::numeric_limits<double>::quiet_NaN();
          if (bb_params_.Zdbb >= 0.) e0=bb_params_.Qbb;
          if (bb_params_.Zdbb < 0.) e0=bb_params_.Qbb-4.*emass;
          if (bb_params_.modebb == MODEBB_9 || bb_params_.modebb == MODEBB_10) e0=bb_params_.Qbb- bb_params_.EK-2.*emass;
          if (bb_params_.modebb == MODEBB_11 || bb_params_.modebb == MODEBB_12) e0=bb_params_.Qbb-2.* bb_params_.EK;
          if (e0 != e0) {
            std::cerr << "[error] "
                      << "genbb::decay0::genbbsub: "
                      << "Undefined e0 ! Bug!" << "\n";
            ier_=1;
            return;
          }
          if (e0 <= El) {
            std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                      << "Not enough energy for transition to this level : "
                      << "Full energy release and Elevel : e0="
                      <<  e0 << "El=" << El << "\n";
            ier_=1;
            return;
          }
        }
        // (2) spin of level and mode of decay
        int m=bb_params_.modebb;
        bool m_ok = false;
        if (! m_ok && bb_params_.itrans02 == 0 &&
            (m ==  1 || m ==  2 || m ==  3 || m ==  4 || m ==  5 ||
             m ==  6 || m ==  9 || m == 10 || m == 11 || m == 12 ||
             m == 13 || m == 14 || m == 15 || m == 17 || m == 18)) {
          m_ok = true;
        }
        if (! m_ok &&  bb_params_.itrans02 == 2 &&
            (m ==  3 || m ==  7 || m ==  8 || m ==  9 || m == 10 ||
             m == 11 || m == 12 || m == 16)) {
          m_ok = true;
        }
        if (! m_ok) {
          std::cerr << "[error] "<< "genbb::decay0::genbbsub: "
                    << "Decay mode '" << modebb_label << "' and spin '"
                    << bb_params_.chdspin << "' of daughter nucleus level "
                    << bb_params_.itrans02
                    << " are inconsistent ! \n";
          ier_=1;
          return;
        }
        // (3) nuclide and mode of decay
        // + modebb == 11 || modebb == 12) {
        if ( bb_params_.Zdbb >= 0. && (bb_params_.modebb ==  9 || bb_params_.modebb == 10 ||
                                       bb_params_.modebb == 11 || bb_params_.modebb == 12)) {
          std::cerr << "[error] "<< "genbb::decay0::genbbsub: "
                    << "Decay mode '" << modebb_label << "' and nuclide '"
                    << chnuclide_ << "'  "
                    << "are inconsistent ! \n";
          ier_=1;
          return;
        }
      }

      if (i2bbs_ == GENBBSUB_I2BBS_BACKGROUND) {
        if (name_starts_with(chnuclide_,"Ac228")) {
        } else if (name_starts_with(chnuclide_,"Am241")) {
        } else if (name_starts_with(chnuclide_,"Ar39")) {
        } else if (name_starts_with(chnuclide_,"Ar42")) {
        } else if (name_starts_with(chnuclide_,"As79")) {
        } else if (name_starts_with(chnuclide_,"Bi207")) {
        } else if (name_starts_with(chnuclide_,"Bi208")) {
        } else if (name_starts_with(chnuclide_,"Bi210")) {
        } else if (name_starts_with(chnuclide_,"Bi212")) {
        } else if (name_starts_with(chnuclide_,"Bi214")) {
        } else if (name_starts_with(chnuclide_,"C14")) {
        } else if (name_starts_with(chnuclide_,"Ca48")) {
        } else if (name_starts_with(chnuclide_,"Cd113")) {
        } else if (name_starts_with(chnuclide_,"Co60")) {
        } else if (name_starts_with(chnuclide_,"Cs136")) {
        } else if (name_starts_with(chnuclide_,"Cs137")) {
        } else if (name_starts_with(chnuclide_,"Eu147")) {
        } else if (name_starts_with(chnuclide_,"Eu152")) {
        } else if (name_starts_with(chnuclide_,"Eu154")) {
        } else if (name_starts_with(chnuclide_,"Gd146")) {
        } else if (name_starts_with(chnuclide_,"Hf182")) {
        } else if (name_starts_with(chnuclide_,"I126")) {
        } else if (name_starts_with(chnuclide_,"I133")) {
        } else if (name_starts_with(chnuclide_,"I134")) {
        } else if (name_starts_with(chnuclide_,"I135")) {
        } else if (name_starts_with(chnuclide_,"K40")) {
        } else if (name_starts_with(chnuclide_,"K42")) {
        } else if (name_starts_with(chnuclide_,"Kr81")) {
        } else if (name_starts_with(chnuclide_,"Kr85")) {
        } else if (name_starts_with(chnuclide_,"Mn54")) {
        } else if (name_starts_with(chnuclide_,"Na22")) {
        } else if (name_starts_with(chnuclide_,"P32")) {
        } else if (name_starts_with(chnuclide_,"Pa231")) {
        } else if (name_starts_with(chnuclide_,"Pa234m")) {
        } else if (name_starts_with(chnuclide_,"Pb210")) {
        } else if (name_starts_with(chnuclide_,"Pb211")) {
        } else if (name_starts_with(chnuclide_,"Pb212")) {
        } else if (name_starts_with(chnuclide_,"Pb214")) {
        } else if (name_starts_with(chnuclide_,"Ra226")) {
        } else if (name_starts_with(chnuclide_,"Ra228")) {
        } else if (name_starts_with(chnuclide_,"Rb87")) {
        } else if (name_starts_with(chnuclide_,"Rh106")) {
        } else if (name_starts_with(chnuclide_,"Sb125")) {
        } else if (name_starts_with(chnuclide_,"Sb126")) {
        } else if (name_starts_with(chnuclide_,"Sb133")) {
        } else if (name_starts_with(chnuclide_,"Sr90")) {
        } else if (name_starts_with(chnuclide_,"Ta182")) {
        } else if (name_starts_with(chnuclide_,"Te133m")) {
        } else if (name_starts_with(chnuclide_,"Te134")) {
        } else if (name_starts_with(chnuclide_,"Th234")) {
        } else if (name_starts_with(chnuclide_,"Tl207")) {
        } else if (name_starts_with(chnuclide_,"Tl208")) {
        } else if (name_starts_with(chnuclide_,"Xe129m")) {
        } else if (name_starts_with(chnuclide_,"Xe131m")) {
        } else if (name_starts_with(chnuclide_,"Xe133")) {
        } else if (name_starts_with(chnuclide_,"Xe135")) {
        } else if (name_starts_with(chnuclide_,"Y88")) {
        } else if (name_starts_with(chnuclide_,"Y90")) {
        } else if (name_starts_with(chnuclide_,"Zn65")) {
        } else if (name_starts_with(chnuclide_,"Zr96")) {
        }

        /* No C++ support for the following cases :
         * - Artificial
         * - Compton
         * - Moller
         * - Pair
         */
        /*
          } else if (name_starts_with(chnuclide_,"Artificial") {
          nartparts=min0(10, nartparts);
          for (int i=1; i <= nartparts; i++) {
          chn=chart(i);
          chart(i)=" ";
          if (chn(1:1) == "B"  || chn(1:1) == "b") chart(i)="Be";
          if (chn(1:1) == "G"  || chn(1:1) == "g") chart(i)="GP";
          if (chn(1:1) == "P"  || chn(1:1) == "p") chart(i)="Pi";
          if (chart(i) == " ") {
          std::cerr << "[error] " << "genbb::decay0::genbbsub: "
          << "Unknown particle in artificial event !\n";
          ier_=1;
          return;
          } else if (chart(i) == "Be") {
          artemin(i)=artQb(i);
          artemax(i)=artQb(i);
          arttmin(i)=0.;
          arttmax(i)=pi;
          artfmin(i)=0.;
          artfmax(i)=2.*pi;
          } else if (chart(i) == "Pi") {
          artemin(i)=artQb(i);
          artemax(i)=artQb(i);
          arttmin(i)=0.;
          arttmax(i)=pi;
          artfmin(i)=0.;
          artfmax(i)=2.*pi;
          } else {
          arttmin(i)=arttmin(i)/180.*pi;
          arttmax(i)=arttmax(i)/180.*pi;
          artfmin(i)=artfmin(i)/180.*pi;
          artfmax(i)=artfmax(i)/180.*pi;
          }
          }
          } else if ( chnuclide_ == "Compton") {
          arttmin(1)=arttmin(1)/180.*pi;
          arttmax(1)=arttmax(1)/180.*pi;
          artfmin(1)=artfmin(1)/180.*pi;
          artfmax(1)=artfmax(1)/180.*pi;
          } else if ( chnuclide_ == "Moller") {
          arttmin(1)=arttmin(1)/180.*pi;
          arttmax(1)=arttmax(1)/180.*pi;
          artfmin(1)=artfmin(1)/180.*pi;
          artfmax(1)=artfmax(1)/180.*pi;
          } else if ( chnuclide_ == "Pair") {
          chnuclide_="E+E- external";
          arttmin(1)=arttmin(1)/180.*pi;
          arttmax(1)=arttmax(1)/180.*pi;
          artfmin(1)=artfmin(1)/180.*pi;
          artfmax(1)=artfmax(1)/180.*pi;
        */
        else {
          std::cerr << "[error] " << "genbb::decay0::genbbsub: "
                    << "Unknown background & source nuclide '"
                    << chnuclide_ << "' !\n";
          ier_=1;
          return;
        }
      }

      /* The code for output ASCII file has not been ported in C++ */

      bb_params_.istartbb = 0;
      if (istart_ == GENBBSUB_ISTART_INIT) {
        if (i2bbs_ == 1) {
          // Compute daughter level in MeV :
          bb_params_.Edlevel = bb_params_.levelE / 1000.;
          decay0_bb(prng_, event_, &bb_params_);
        }
        // istart_ = GENBBSUB_ISTART_GENERATE;
        return;
      }
      // istart_ = GENBBSUB_ISTART_GENERATE;
    }

    /*********************
     * Double beta decay *
     *********************/
    event_.set_generator(chnuclide_);
    if (i2bbs_ == GENBBSUB_I2BBS_DBD) {
      event_.set_time(0.0);
      decay0_bb(prng_, event_, &bb_params_);
      if (name_starts_with(chnuclide_,"Ca48")) Ti48low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ni58")) Fe58low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ge76")) Se76low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Zn64")) Ni64low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Zn70")) Ge70low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Se74")) Ge74low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Se82")) Kr82low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Sr84")) Kr84low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Zr94")) Mo94low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Zr96")) Mo96low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Mo92")) Zr92low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Mo100")) Ru100low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ru96")) Mo96low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ru104")) Pd104low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Cd106")) Pd106low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Cd108")) Pd108low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Cd114")) Sn114low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Cd116")) Sn116low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Sn112")) Cd112low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Sn122")) Te122low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Sn124")) Te124low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Te120")) Sn120low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Te128")) Xe128low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Te130")) Xe130low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Xe136")) Ba136low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ce136")) Ba136low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ce138")) Ba138low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Ce142")) Nd142low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Nd148")) Sm148low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Nd150")) Sm150low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Dy156")) Gd156low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Dy158")) Gd158low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"W180")) Hf180low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"W186")) Os186low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Pt190")) Os190low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Pt198")) Hg198low(prng_, event_, bb_params_.levelE);
      if (name_starts_with(chnuclide_,"Bi214")) {
        At214low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        At214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_,"Pb214")) {
        Po214low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        Po214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_,"Po218")) {
        Rn218low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        Rn218(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
        npfull0 = event_.get_particles().size();
        Po214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_,"Rn222")) {
        Ra222low(prng_, event_, 0);
        npfull0 = event_.get_particles().size();
        Ra222(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
        npfull0 = event_.get_particles().size();
        Rn218(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
        npfull0 = event_.get_particles().size();
        Po214(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
    }

    /***************
     * Backgrounds *
     ***************/
    if (i2bbs_ == 2) {
      if (name_starts_with(chnuclide_,"Ac228")) Ac228(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Am241")) Am241(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Ar39")) Ar39(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Ar42")) Ar42(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"As79")) As79(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Bi207")) Bi207(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Bi208")) Bi208(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Bi210")) Bi210(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Bi212")) {
        Bi212(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        if (! event_.get_particles ().front().is_alpha()) {
          Po212(prng_, event_, 0., tdnuc1);
          event_.shift_particles_time(tdnuc1, npfull0);
        }
      }
      if (name_starts_with(chnuclide_,"Bi214")) {
        Bi214(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        if (! event_.get_particles ().front().is_alpha()) {
          Po214(prng_, event_, 0., tdnuc1);
          event_.shift_particles_time(tdnuc1, npfull0);
        }
      }
      if (name_starts_with(chnuclide_,"Ca48")) {
        Ca48(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        Sc48(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      if (name_starts_with(chnuclide_,"C14")) C14(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Cd113")) Cd113(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Co60")) Co60(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Cs136")) Cs136(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Cs137")) Cs137(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Eu147")) Eu147(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Eu152")) Eu152(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Eu154")) Eu154(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Gd146")) Gd146(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Hf182")) Hf182(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"I126")) I126(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"I133")) I133(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"I134")) I134(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"I135")) I135(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"K40")) K40(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"K42")) K42(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Kr81")) Kr81(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Kr85")) Kr85(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Mn54")) Mn54(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Na22")) Na22(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"P32")) P32(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Pa231")) Pa231(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Pa234m")) Pa234m(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Pb210")) Pb210(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Pb211")) Pb211(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Pb212")) Pb212(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Pb214")) Pb214(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Ra226")) Ra226(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Ra228")) Ra228(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Rb87")) Rb87(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Rh106")) Rh106(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Sb125")) Sb125(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Sb126")) Sb126(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Sb133")) Sb133(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Sr90")) Sr90(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Ta182")) Ta182(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Te133")) Te133(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Te133m")) Te133m(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Te134")) Te134(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Th234")) Th234(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Tl207")) Tl207(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Tl208")) Tl208(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Xe129m")) Xe129m(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Xe131m")) Xe131m(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Xe133")) Xe133(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Xe135")) Xe135(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Y88")) Y88(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Y90")) Y90(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Zn65")) Zn65(prng_, event_, 0., tdnuc);
      if (name_starts_with(chnuclide_,"Zr96")) {
        Zr96(prng_, event_, 0., tdnuc);
        npfull0 = event_.get_particles().size();
        Nb96(prng_, event_, 0., tdnuc1);
        event_.shift_particles_time(tdnuc1, npfull0);
      }
      //tevst=tdnuc;
      // 2015-11-29: FM+XG: force reference decay time to 0
      // was:
      // event_.set_time(tdnuc);
      // now:
      event_.set_time(0.0);

      /* The following cases have not been ported in C++ (will they ever be ?)
       * - Artificial
       * - Compton
       * - Moller
       * - E+E- external
       */

      /*
        if (name_starts_with(chnuclide_,"Artificial")) {
        tevst=0.;
        for (int j=1; j <=nartparts; j++) {
        if (chart(j) == "Be") {
        decay0_beta(prng_, event_, artQb(j), artZd(j), arttdelay(j),
        artthalf(j), t);
        } else if (chart(j) == "Pi") {
        decay0_pair(prng_, event_, artQb(j), arttdelay(j), artthalf(j), t);
        } else {
        np=nartnpg(j);
        decay0_particle(np, artemin(j), artemax(j), arttmin(j),
        arttmax(j), artfmin(j), artfmax(j),
        arttdelay(j), artthalf(j), t);
        }
        }
        }
        if (name_starts_with(chnuclide_,"Compton")) {
        tevst=0.;
        compton(artemin(1), artemax(1), arttmin(1), arttmax(1),
        artfmin(1), artfmax(1));
        }
        if (name_starts_with(chnuclide_,"Moller")) {
        tevst=0.;
        moller(artemin(1), artemax(1), arttmin(1), arttmax(1),
        artfmin(1), artfmax(1), artQb(1));
        }
        if (name_starts_with(chnuclide_,"E+E- external")) {
        tevst=0.;
        pairext(artemin(1), artemax(1), arttmin(1), arttmax(1),
        artfmin(1), artfmax(1), artZd(1));
        }
      */
    }

    //if (bb_params_.icurrent != bb_params_.nevents) return;
    return;

  }

} // end of namespace bxdecay0
