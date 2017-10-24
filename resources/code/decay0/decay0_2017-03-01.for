	program DECAY0

c Last updated: 1.03.2017.

c Brief instruction on how to use DECAY0 as a standalone program:
c 1. Compile with Fortran compiler;
c 2. Link with CERNLIB library (for the use of random numbers and gauss
c    function);
c 3. Run DECAY0 and answer the questions; in particular, select an option to
c    write generated events in file. After, you can read these events
c    and simulate them with GEANT, EGS, MCNP or other simulation package.
c
c Please refer to: O.A.Ponkratenko, V.I.Tretyak, Yu.G.Zdesenko,
c                  "Event Generator DECAY4 for Simulating Double-Beta 
c                  Processes and Decays of Radioactive Nuclei",
c                  Phys. At. Nucl. 63 (2000) 1282 (nucl-ex/0104018).
c This paper describes mainly DECAY4 generator, and DECAY0 was mentioned
c as initial version of the code.
c Please send questions, comments and proposals to: 
c tretyak@kinr.kiev.ua or tretyak@lngs.infn.it.

c***********************************************************************
c   Generation of events of decay of natural radioactive isotopes and
c                various modes of double beta decay.
c***********************************************************************

c***********************************************************************
c DECAY units: energy and moment - MeV and MeV/c;
c              time              - sec.
c***********************************************************************

	character chfile*40,chnuclide*16,chart*4,chdspin*4
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	common/genbbpar/nevents,ievstart,irndmst,iwrfile,chfile
	common/enrange/ebb1,ebb2,toallevents,levelE,chdspin
	common/artificial/nartparts,    chart(10),
     +                    artemin(10),  artemax(10),
     +                    arttmin(10),  arttmax(10),
     +                    artfmin(10),  artfmax(10),
     +                    artQb(10),    artZd(10),
     +                    arttdelay(10),artthalf(10),
     +                    nartnpg(10)
	common/currentev/icurrent
	call GENBBdia(i2bbs,chnuclide,ilevel,modebb,istart)
	do i=1,nevents
	   icurrent=i
	   call GENBBsub(i2bbs,chnuclide,ilevel,modebb,istart,ier)
	enddo
	end

c***********************************************************************

	subroutine GENBBdia(i2bbs,chnuclide,ilevel,modebb,istart)
c
c Dialog to ask the inputs for GENBBsub subroutine.
c Descriptions of common blocks and parameters see in GENBBsub.
c VIT, 03.12.1995.
c
	character chfile*40,chnuclide*16,chn*16,chart*4,chdspin*4
	character chfile_eta*50,chline*50
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
      common/const/pi,emass,datamass(50)
	common/enrange/ebb1,ebb2,toallevents,levelE,chdspin
	common/genbbpar/nevents,ievstart,irndmst,iwrfile,chfile
	common/artificial/nartparts,    chart(10),
     +                    artemin(10),  artemax(10),
     +                    arttmin(10),  arttmax(10),
     +                    artfmin(10),  artfmax(10),
     +                    artQb(10),    artZd(10),
     +                    arttdelay(10),artthalf(10),
     +                    nartnpg(10)
	common/eta_nme/chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,
     +               chip_P,chip_R
	print *,'     '
	print *,
     +'    DECAY0: Generation of events of decay of natural radioactive'
	print *,
     +'             isotopes and various modes of double beta decay'
	print *,'     '
	print *,' DECAY units: energy   - MeV'
	print *,'              momentum - MeV/c'
	print *,'              time     - sec'
	print *,'              angle    - degree'
1000	print *,'     '
	print *,' Which type of events do you want to generate:'
	print *,'       1. double beta processes'
	print *,'       2. internal or external background ',
     +          'or calibration sources'
	print 1
c1	format('$? ')
1	format(' ? ',$)
	read *,i2bbs
2	print *,'     '
	if(i2bbs.eq.1) then
	   print *,' Double beta nuclides:'
	   print *,'        Ca40     Ca46     Ca48'
	   print *,'        Ni58'
	   print *,'        Zn64     Zn70'
	   print *,'        Ge76'
	   print *,'        Se74     Se82'
	   print *,'        Sr84'
	   print *,'        Zr94     Zr96'
	   print *,'        Mo92     Mo100'
	   print *,'        Ru96     Ru104'
	   print *,'        Cd106    Cd108    Cd114    Cd116'
	   print *,'        Sn112    Sn122    Sn124'
	   print *,'        Te120    Te128    Te130'
	   print *,'        Xe136'
	   print *,'        Ce136    Ce138    Ce142'
	   print *,'        Nd148    Nd150'
	   print *,'        Dy156    Dy158'
	   print *,'        W180     W186'
	   print *,'        Os184    Os192'
	   print *,'        Pt190    Pt198'
	   print *,'        Bi214+At214'
	   print *,'        Pb214+Po214'
	   print *,'        Po218+Rn218+Po214'
	   print *,'        Rn222+Ra222+Rn218+Po214'
	   print 1
	   read 3,chn
3	   format(a)
	   chnuclide=chn
	   print *,'     '
	   if((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +         chn(1:2).eq.'ca').and.chn(3:4).eq.'40') then
	      print *,'transition is possible only to ',
     +                '40-Ar 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +             chn(1:2).eq.'ca').and.chn(3:4).eq.'46') then
4444	      print *,'46-Ti level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.889 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 4444
	      endif
	   elseif((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +             chn(1:2).eq.'ca').and.chn(3:4).eq.'48') then
4	      print *,'48-Ti level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.984 MeV}'
	      print *,'                2. 2+ (2)  {2.421 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 4
	      endif
	   elseif((chn(1:2).eq.'Ni'.or.chn(1:2).eq.'NI'.or.
     +             chn(1:2).eq.'ni').and.chn(3:4).eq.'58') then
5	      print *,'58-Fe level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.811 MeV}'
	      print *,'                2. 2+ (2)  {1.675 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 5
	      endif
	   elseif((chn(1:2).eq.'Zn'.or.chn(1:2).eq.'ZN'.or.
     +             chn(1:2).eq.'zn').and.chn(3:4).eq.'64') then
	      print *,'transition is possible only to ',
     +                '64-Ni 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Zn'.or.chn(1:2).eq.'ZN'.or.
     +             chn(1:2).eq.'zn').and.chn(3:4).eq.'70') then
	      print *,'transition is possible only to ',
     +                '70-Ge 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Ge'.or.chn(1:2).eq.'GE'.or.
     +             chn(1:2).eq.'ge').and.chn(3:4).eq.'76') then
6	      print *,'76-Se level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.559 MeV}'
	      print *,'                2. 0+ (1)  {1.122 MeV}'
	      print *,'                3. 2+ (2)  {1.216 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.3) then
	         print *,'   '
	         go to 6
	      endif
	   elseif((chn(1:2).eq.'Se'.or.chn(1:2).eq.'SE'.or.
     +             chn(1:2).eq.'se').and.chn(3:4).eq.'74') then
7	      print *,'74-Ge level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.596 MeV}'
	      print *,'                2. 2+ (2)  {1.204 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 7
	      endif
	   elseif((chn(1:2).eq.'Se'.or.chn(1:2).eq.'SE'.or.
     +             chn(1:2).eq.'se').and.chn(3:4).eq.'82') then
8	      print *,'82-Kr level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.776 MeV}'
	      print *,'                2. 2+ (2)  {1.475 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 8
	      endif
	   elseif((chn(1:2).eq.'Sr'.or.chn(1:2).eq.'SR'.or.
     +             chn(1:2).eq.'sr').and.chn(3:4).eq.'84') then
81	      print *,'84-Kr level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.882 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 81
	      endif
	   elseif((chn(1:2).eq.'Zr'.or.chn(1:2).eq.'ZR'.or.
     +             chn(1:2).eq.'zr').and.chn(3:4).eq.'94') then
9	      print *,'94-Mo level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.871 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 9
	      endif
	   elseif((chn(1:2).eq.'Zr'.or.chn(1:2).eq.'ZR'.or.
     +             chn(1:2).eq.'zr').and.chn(3:4).eq.'96') then
10	      print *,'96-Mo level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.778 MeV}'
	      print *,'                2. 0+ (1)  {1.148 MeV}'
	      print *,'                3. 2+ (2)  {1.498 MeV}'
	      print *,'                4. 2+ (3)  {1.626 MeV}'
	      print *,'                5. 2+ (4)  {2.096 MeV}'
	      print *,'                6. 2+ (5)  {2.426 MeV}'
	      print *,'                7. 0+ (2)  {2.623 MeV}'
	      print *,'                8. 2+ (6)  {2.700 MeV}'
	      print *,'                9. 2+?(7)  {2.713 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'   '
	         go to 10
	      endif
	   elseif((chn(1:2).eq.'Mo'.or.chn(1:2).eq.'MO'.or.
     +             chn(1:2).eq.'mo').and.chn(3:4).eq.'92') then
11	      print *,'92-Zr level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.934 MeV}'
	      print *,'                2. 0+ (1)  {1.383 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 11
	      endif
	   elseif((chn(1:2).eq.'Mo'.or.chn(1:2).eq.'MO'.or.
     +             chn(1:2).eq.'mo').and.chn(3:5).eq.'100') then
12	      print *,'100-Ru level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.540 MeV}'
	      print *,'                2. 0+ (1)  {1.130 MeV}'
	      print *,'                3. 2+ (2)  {1.362 MeV}'
	      print *,'                4. 0+ (2)  {1.741 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.4) then
	         print *,'   '
	         go to 12
	      endif
	   elseif((chn(1:2).eq.'Ru'.or.chn(1:2).eq.'RU'.or.
     +             chn(1:2).eq.'ru').and.chn(3:4).eq.'96') then
121	      print *,'96-Mo level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.778 MeV}'
	      print *,'                2. 0+ (1)  {1.148 MeV}'
	      print *,'                3. 2+ (2)  {1.498 MeV}'
	      print *,'                4. 2+ (3)  {1.626 MeV}'
	      print *,'                5. 2+ (4)  {2.096 MeV}'
	      print *,'                6. 2+ (5)  {2.426 MeV}'
	      print *,'                7. 0+ (2)  {2.623 MeV}'
	      print *,'                8. 2+ (6)  {2.700 MeV}'
	      print *,'                9. 2+?(7)  {2.713 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'   '
	         go to 121
	      endif
	   elseif((chn(1:2).eq.'Ru'.or.chn(1:2).eq.'RU'.or.
     +             chn(1:2).eq.'ru').and.chn(3:5).eq.'104') then
122	      print *,'104-Pd level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.556 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 122
	      endif
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +             chn(1:2).eq.'cd').and.chn(3:5).eq.'106') then
13	      print *,'106-Pd level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                 1. 2+ (1)  {0.512 MeV}'
	      print *,'                 2. 2+ (2)  {1.128 MeV}'
	      print *,'                 3. 0+ (1)  {1.134 MeV}'
	      print *,'                 4. 2+ (3)  {1.562 MeV}'
	      print *,'                 5. 0+ (2)  {1.706 MeV}'
c	      print *,'                 6. 2+ (4)  {2.741 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'   '
	         go to 13
	      endif
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +             chn(1:2).eq.'cd').and.chn(3:5).eq.'108') then
	      print *,'transition is possible only to ',
     +                '108-Pd 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +             chn(1:2).eq.'cd').and.chn(3:5).eq.'114') then
	      print *,'transition is possible only to ',
     +                '114-Sn 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +             chn(1:2).eq.'cd').and.chn(3:5).eq.'116') then
14	      print *,'116-Sn level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {1.294 MeV}'
	      print *,'                2. 0+ (1)  {1.757 MeV}'
	      print *,'                3. 0+ (2)  {2.027 MeV}'
	      print *,'                4. 2+ (2)  {2.112 MeV}'
	      print *,'                5. 2+ (3)  {2.225 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'   '
	         go to 14
	      endif
	   elseif((chn(1:2).eq.'Sn'.or.chn(1:2).eq.'SN'.or.
     +             chn(1:2).eq.'sn').and.chn(3:5).eq.'112') then
1014	      print *,'112-Cd level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.618 MeV}'
	      print *,'                2. 0+ (1)  {1.224 MeV}'
	      print *,'                3. 2+ (2)  {1.312 MeV}'
	      print *,'                4. 0+ (2)  {1.433 MeV}'
	      print *,'                5. 2+ (3)  {1.469 MeV}'
	      print *,'                6. 0+ (3)  {1.871 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.6) then
	         print *,'   '
	         go to 1014
	      endif
	   elseif((chn(1:2).eq.'Sn'.or.chn(1:2).eq.'SN'.or.
     +             chn(1:2).eq.'sn').and.chn(3:5).eq.'122') then
	      print *,'transition is possible only to ',
     +                '122-Te 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Sn'.or.chn(1:2).eq.'SN'.or.
     +             chn(1:2).eq.'sn').and.chn(3:5).eq.'124') then
1015	      print *,'124-Te level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.603 MeV}'
	      print *,'                2. 2+ (2)  {1.326 MeV}'
	      print *,'                3. 0+ (1)  {1.657 MeV}'
	      print *,'                4. 0+ (2)  {1.833 MeV}'
	      print *,'                5. 2+ (3)  {2.039 MeV}'
	      print *,'                6. 2+ (4)  {2.092 MeV}'
	      print *,'                7. 0+ (3)  {2.153 MeV}'
	      print *,'                8. 2+ (5)  {2.182 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.8) then
	         print *,'   '
	         go to 1015
	      endif
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +             chn(1:2).eq.'te').and.chn(3:5).eq.'120') then
114	      print *,'120-Sn level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {1.171 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 114
	      endif
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +             chn(1:2).eq.'te').and.chn(3:5).eq.'128') then
115	      print *,'128-Xe level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.443 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 115
	      endif
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +             chn(1:2).eq.'te').and.chn(3:5).eq.'130') then
116	      print *,'130-Xe level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.536 MeV}'
	      print *,'                2. 2+ (2)  {1.122 MeV}'
	      print *,'                3. 0+ (1)  {1.794 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.3) then
	         print *,'   '
	         go to 116
	      endif
	   elseif((chn(1:2).eq.'Xe'.or.chn(1:2).eq.'XE'.or.
     +             chn(1:2).eq.'xe').and.chn(3:5).eq.'136') then
15	      print *,'136-Ba level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.819 MeV}'
	      print *,'                2. 2+ (2)  {1.551 MeV}'
	      print *,'                3. 0+ (1)  {1.579 MeV}'
	      print *,'                4. 2+ (3)  {2.080 MeV}'
	      print *,'                5. 2+ (4)  {2.129 MeV}'
	      print *,'                6. 0+ (2)  {2.141 MeV}'
	      print *,'                7. 2+ (5)  {2.223 MeV}'
	      print *,'                8. 0+ (3)  {2.315 MeV}'
	      print *,'                9. 2+ (6)  {2.400 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'   '
	         go to 15
	      endif
	   elseif((chn(1:2).eq.'Ce'.or.chn(1:2).eq.'CE'.or.
     +             chn(1:2).eq.'ce').and.chn(3:5).eq.'136') then
151	      print *,'136-Ba level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.819 MeV}'
	      print *,'                2. 2+ (2)  {1.551 MeV}'
	      print *,'                3. 0+ (1)  {1.579 MeV}'
	      print *,'                4. 2+ (3)  {2.080 MeV}'
	      print *,'                5. 2+ (4)  {2.129 MeV}'
	      print *,'                6. 0+ (2)  {2.141 MeV}'
	      print *,'                7. 2+ (5)  {2.223 MeV}'
	      print *,'                8. 0+ (3)  {2.315 MeV}'
	      print *,'                9. 2+ (6)  {2.400 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'   '
	         go to 151
	      endif
	   elseif((chn(1:2).eq.'Ce'.or.chn(1:2).eq.'CE'.or.
     +             chn(1:2).eq.'ce').and.chn(3:5).eq.'138') then
	      print *,'transition is possible only to ',
     +                '138-Ba 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Ce'.or.chn(1:2).eq.'CE'.or.
     +             chn(1:2).eq.'ce').and.chn(3:5).eq.'142') then
	      print *,'transition is possible only to ',
     +                '142-Nd 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Nd'.or.chn(1:2).eq.'ND'.or.
     +             chn(1:2).eq.'nd').and.chn(3:5).eq.'148') then
16	      print *,'148-Sm level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                 1. 2+ (1)  {0.550 MeV}'
	      print *,'                 2. 2+ (2)  {1.455 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 16
	      endif
	   elseif((chn(1:2).eq.'Nd'.or.chn(1:2).eq.'ND'.or.
     +             chn(1:2).eq.'nd').and.chn(3:5).eq.'150') then
17	      print *,'150-Sm level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.334 MeV}'
	      print *,'                2. 0+ (1)  {0.740 MeV}'
	      print *,'                3. 2+ (2)  {1.046 MeV}'
	      print *,'                4. 2+ (3)  {1.194 MeV}'
	      print *,'                5. 0+ (2)  {1.256 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'   '
	         go to 17
	      endif
	   elseif((chn(1:2).eq.'Dy'.or.chn(1:2).eq.'DY'.or.
     +             chn(1:2).eq.'dy').and.chn(3:5).eq.'156') then
1701	      print *,'156-Gd level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.089 MeV}'
	      print *,'                2. 0+ (1)  {1.050 MeV}'
	      print *,'                3. 2+ (2)  {1.129 MeV}'
	      print *,'                4. 2+ (3)  {1.154 MeV}'
	      print *,'                5. 0+ (2)  {1.168 MeV}'
	      print *,'                6. 2+ (4)  {1.258 MeV}'
	      print *,'                7. 0+ (3)  {1.715 MeV}'
	      print *,'                8. 2+ (5)  {1.771 MeV}'
	      print *,'                9. 2+ (6)  {1.828 MeV}'
	      print *,'               10. 0+ (4)  {1.851 MeV}'
	      print *,'               11. 2+ (7)  {1.915 MeV}'
	      print *,'               12. 1-      {1.946 MeV}'
	      print *,'               13. 0-      {1.952 MeV}'
	      print *,'               14. 0+ (5)  {1.989 MeV}'
	      print *,'               15. 2+ (8)  {2.004 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.15) then
	         print *,'   '
	         go to 1701
	      endif
	   elseif((chn(1:2).eq.'Dy'.or.chn(1:2).eq.'DY'.or.
     +             chn(1:2).eq.'dy').and.chn(3:5).eq.'158') then
1702	      print *,'158-Gd level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.080 MeV}'
	      print *,'                2. 4+ (1)  {0.261 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 1702
	      endif
	   elseif((chn(1:1).eq.'W'.or.chn(1:1).eq.'w').and.
     +           chn(2:4).eq.'180') then
	      print *,'transition is possible only to ',
     +                '180-Hf 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:1).eq.'W'.or.chn(1:1).eq.'w').and.
     +           chn(2:4).eq.'186') then
171	      print *,'186-Os level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.137 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'   '
	         go to 171
	      endif
	   elseif((chn(1:2).eq.'Os'.or.chn(1:2).eq.'OS'.or.
     +             chn(1:2).eq.'os').and.chn(3:5).eq.'184') then
1720	      print *,'184-W level:    0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.111 MeV}'
	      print *,'                2. 2+ (2)  {0.903 MeV}'
	      print *,'                3. 0+ (1)  {1.002 MeV}'
	      print *,'                4. 2+ (3)  {1.121 MeV}'
	      print *,'                5. 0+ (2)  {1.322 MeV}'
	      print *,'                6. 2+ (4)  {1.386 MeV}'
	      print *,'                7. 2+ (5)  {1.431 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.7) then
	         print *,'   '
	         go to 1720
	      endif
	   elseif((chn(1:2).eq.'Os'.or.chn(1:2).eq.'OS'.or.
     +             chn(1:2).eq.'os').and.chn(3:5).eq.'192') then
1721	      print *,'192-Pt level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.317 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 1721
	      endif
	   elseif((chn(1:2).eq.'Pt'.or.chn(1:2).eq.'PT'.or.
     +             chn(1:2).eq.'pt').and.chn(3:5).eq.'190') then
172	      print *,'190-Os level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.187 MeV}'
	      print *,'                2. 2+ (2)  {0.558 MeV}'
	      print *,'                3. 0+ (1)  {0.912 MeV}'
	      print *,'                4. 2+ (3)  {1.115 MeV}'
	      print *,'                5. 0+ (2)  {1.382 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'   '
	         go to 172
	      endif
	   elseif((chn(1:2).eq.'Pt'.or.chn(1:2).eq.'PT'.or.
     +             chn(1:2).eq.'pt').and.chn(3:5).eq.'198') then
173	      print *,'198-Hg level:   0. 0+ (gs)     {0 MeV}'
	      print *,'                1. 2+ (1)  {0.412 MeV}'
	      print 1
	      read *,ilevel
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'   '
	         go to 173
	      endif
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +             chn(1:2).eq.'bi').and.chn(3:5).eq.'214') then
	      print *,'transition is possible only to ',
     +                '214-At 1-(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Pb'.or.chn(1:2).eq.'PB'.or.
     +             chn(1:2).eq.'pb').and.chn(3:5).eq.'214') then
	      print *,'transition is possible only to ',
     +                '214-Po 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Po'.or.chn(1:2).eq.'PO'.or.
     +             chn(1:2).eq.'po').and.chn(3:5).eq.'218') then
	      print *,'transition is possible only to ',
     +                '218-Rn 0+(gs) level'
	      ilevel=0
	   elseif((chn(1:2).eq.'Rn'.or.chn(1:2).eq.'RN'.or.
     +             chn(1:2).eq.'rn').and.chn(3:5).eq.'222') then
	      print *,'transition is possible only to ',
     +                '222-Ra 0+(gs) level'
	      ilevel=0
	   else
	      print *,'unknown double beta nuclide'
	      go to 2
	   endif
18	   print *,'     '
	   print *,' mode of bb-decay:'
	   print *,'      1. 0nubb(mn)         0+ -> 0+     {2n}'
	   print *,'      2. 0nubb(rhc-lambda) 0+ -> 0+     {2n}'
	   print *,'      3. 0nubb(rhc-lambda) 0+ -> 0+, 2+ {N*}'
	   print *,'      4. 2nubb             0+ -> 0+     {2n}'
	   print *,'      5. 0nubbM1           0+ -> 0+     {2n}'
	   print *,'      6. 0nubbM2           0+ -> 0+     (2n}'
	   print *,'      7. 0nubbM3           0+ -> 0+     {2n}'
	   print *,'      8. 0nubbM7           0+ -> 0+     {2n}'
	   print *,'      9. 0nubb(rhc-lambda) 0+ -> 2+     {2n}'
	   print *,'     10. 2nubb             0+ -> 2+     {2n}, {N*}'
	   print *,'     11. 0nuKb+            0+ -> 0+, 2+'
	   print *,'     12. 2nuKb+            0+ -> 0+, 2+'
	   print *,'     13. 0nu2K             0+ -> 0+, 2+'
	   print *,'     14. 2nu2K             0+ -> 0+, 2+'
	   print *,'     15. 2nubb             0+ -> 0+ with bosonic',
	+                   ' neutrinos'
	   print *,'     16. 2nubb             0+ -> 2+ with bosonic',
	+                   ' neutrinos'
	   print *,'     17. 0nubb(rhc-eta)    0+ -> 0+ simplified',
	+                   ' expression'
	   print *,'     18. 0nubb(rhc-eta)    0+ -> 0+ with specific',
	+                   ' NMEs'
	   print *,'     19. 2nubb LV          0+ -> 0+ with Lorentz',
	+                   ' violation'
	   print *,'     20. 0nu4b             0+ -> 0+ quadruple beta',
	+                   ' decay'
	   print *,'         5-8: Majoron(s) with spectral index SI:'
	   print *,'              SI=1 - old M of Gelmini-Roncadelli'
	   print *,'              SI=2 - bulk M of Mohapatra'
	   print *,'              SI=3 - double M, vector M, charged M'
	   print *,'              SI=7'
	   print *,'          20: possible only for Zr96, Xe136, Nd150'
	   print 1
	   read *,modebb0
	   if(modebb0.ge.1 .and. modebb0.le.5)  modebb=modebb0
	   if(modebb0.eq.6)                     modebb=14
	   if(modebb0.eq.7)                     modebb=6
	   if(modebb0.eq.8)                     modebb=13
	   if(modebb0.ge.9 .and. modebb0.le.14) modebb=modebb0-2
	   if(modebb0.ge.15)                    modebb=modebb0
	   if(modebb.lt.1.or.modebb.gt.20) then
	      print *,'   '
	      print *,'unknown mode'
	      go to 18
	   endif
	   ebb1=0.
	   ebb2=4.3
	   if(modebb.eq. 4.or.modebb.eq. 5.or.modebb.eq. 6.or.
     +      modebb.eq. 8.or.modebb.eq.10.or.modebb.eq.13.or.
     +      modebb.eq.14.or.modebb.eq.15.or.modebb.eq.16) then
	      print 19
c19	      format('$do you want to restrict energy range for ',
c     +               'generated particles? ')
19	      format(' do you want to restrict energy range for ',
     +               'generated particles? ',$)
	      read 3,chn
	      if(chn.eq.'y'.or.chn.eq.'Y') then
	         print 20
c20	         format('$range for sum of e-/e+ energies (MeV): ')
20	         format(' range for sum of e-/e+ energies (MeV): ',$)
	         read *,ebb1,ebb2
	      endif
	   endif
	   if(modebb.eq.18) then
	      print 18000
18000	      format(' name of file with NMEs: ',$)
	      read 18001,chfile_eta
18001	      format(a) 
c             file chfile_eta should be of the following structure:
c             line 1 - comment
c             line 2 - comment
c             line 3 - 7 NMEs: chi_GTw, chi_Fw, chi'_GT, chi'_F, chi'_T, chi'_P, chi'_R
	      open(unit=33,file=chfile_eta)
	      read(33,18001) chline
	      read(33,18001) chline
	      read(33,*) chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,
     +                   chip_P,chip_R
	      close(unit=33)
	      print *,'NMEs: ',chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,
     +                chip_P,chip_R
	   endif
	endif
	if(i2bbs.eq.2) then
	   print *,' Background & sources:'
	   print *,'    Ac228             Hf182             Sb125'
	   print *,'    Am241             I126              Sb126'    
	   print *,'    Ar39              I133              Sb133'    
	   print *,'    Ar42              I134              Sr90'    
	   print *,'    As79+Se79m        I135              Ta182'     
	   print *,'    Bi207+Pb207m      K40               Te133'    
	   print *,'    Bi208             K42               Te133m'    
	   print *,'    Bi210             Kr81              Te134'         
	   print *,'    Bi212+Po212       Kr85              Th234'          
	   print *,'    Bi214+Po214       Mn54              Tl207'          
	   print *,'    C14               Na22              Tl208'          
	   print *,'    Ca48+Sc48         P32               Xe129m'         
	   print *,'    Cd113             Pa234m            Xe131m'         
	   print *,'    Co60              Pb210             Xe133'          
	   print *,'    Cs136             Pb211             Xe135'          
	   print *,'    Cs137+Ba137m      Pb212             Y88'
	   print *,'    Eu147             Pb214             Y90'
	   print *,'    Eu152             Ra228             Zn65'
	   print *,'    Eu154             Rb87              Zr96+Nb96'
	   print *,'    Gd146             Rh106             '
	   print *,'    Artificial event (beta decay + internal e+e-',
     +                ' + GEANT particles)'
	   print *,'    Compton effect'
	   print *,'    Moller scattering'
	   print *,'    Pair creation from external gamma quanta'
c	   print *,'    Double Compton'
	   print *,'     '
	   print 1
	   read 3,chn
	   chnuclide=chn
	   if(chn(1:3).eq.'Art'.or.chn(1:3).eq.'ART'.or.
     +        chn(1:3).eq.'art') then
	      print *,'     '
	      print *,'   Emission of up to 10 beta [b], e+e-',
     +                ' internal conversion pairs [p]'
	      print *,'   and any of GEANT particles [G]',
     +                ' in region of energies and angles'
	      print *,'   with time delay and halflife'
	      print *,'     '
	      print *,'GEANT particles:'
	      print *,'       1 - gamma         2 - positron    ',
     +                ' 3 - electron'
	      print *,'       4 - neutrino      5 - muon+       ',
     +                ' 6 - muon-'
	      print *,'       7 - pion0         8 - pion+       ',
     +                ' 9 - pion-'
	      print *,'      10 - kaon0 long   11 - kaon+       ',
     +                '12 - kaon-'
	      print *,'      13 - neutron      14 - proton      ',
     +                '15 - antiproton'
	      print *,'      16 - kaon0 short  17 - eta         ',
     +                '18 - lambda'
	      print *,'      19 - sigma+       20 - sigma0      ',
     +                '21 - sigma-'
	      print *,'      22 - xi0          23 - xi-         ',
     +                '24 - omega'
	      print *,'      25 - antineutron  26 - antilambda  ',
     +                '27 - antisigma-'
	      print *,'      28 - antisigma0   29 - antisigma+  ',
     +                '30 - antixi0'
	      print *,'      31 - antixi+      32 - antiomega+  ',
     +                '45 - deuteron'
	      print *,'      46 - tritium      47 - alpha       ',
     +                '48 - geantino'
	      print *,'      49 - He3          50 - Cerenkov'
	      print *,'     '
	      print 21
c21	      format('$number of parts in artificial event: ')
21	      format(' number of parts in artificial event: ',$)
	      read *,nartparts
	      nartparts=min0(10,nartparts)
	      do i=1,nartparts
22	         print 23,i
c23	         format('$',i2,' identifier (b/p/G): ')
23	         format(' ',i2,' identifier (b/p/G): ',$)
	         read 3,chn
	         chart(i)='  '
	         if(chn(1:1).eq.'B' .or.chn(1:1).eq.'b')  chart(i)='Be'
	         if(chn(1:1).eq.'G' .or.chn(1:1).eq.'g')  chart(i)='GP'
	         if(chn(1:1).eq.'P' .or.chn(1:1).eq.'p')  chart(i)='Pi'
	         if(chart(i).eq.'  ') then
	            print *,'unknown particle'
	            go to 22
	         elseif(chart(i).eq.'Be') then
	            print 24
c24	            format('$   Qbeta and Z of daughter nucleus',
c     +                     ' (Z>0 for beta- and',
c     +                     ' Z<0 for beta+): ')
24	            format('    Qbeta and Z of daughter nucleus',
     +                     ' (Z>0 for beta- and',
     +                     ' Z<0 for beta+): ',$)
	            read *,artQb(i),artZd(i)
	            print 25
c25	            format('$   tdelay, thalf: ')
25	            format('    tdelay, thalf: ',$)
	            read *,arttdelay(i),artthalf(i)
	         elseif(chart(i).eq.'Pi') then
	            print 26
c26	            format('$   Epair, tdelay, thalf: ')
26	            format('    Epair, tdelay, thalf: ',$)
	            read *,artQb(i),arttdelay(i),artthalf(i)
	         else
227	            print 27
c27	            format('$   GEANT particle number, ',
c     +                     'Emin, Emax (MeV): ')
27	            format('    GEANT particle number, ',
     +                     'Emin, Emax (MeV): ',$)
	            read *,l,artemin(i),artemax(i)
	            if(l.lt.1.or.l.gt.50.or.(l.gt.32.and.l.lt.45)) then
	               print *,'unknown particle'
	               go to 227
	            else
	               nartnpg(i)=l
	            endif
	            print 28
c28	            format('$   tetamin, tetamax, phimin,',
c     +                     ' phimax, tdelay, thalf: ')
28	            format('    tetamin, tetamax, phimin,',
     +                     ' phimax, tdelay, thalf: ',$)
	            read *,arttmin(i),arttmax(i),artfmin(i),
     +                     artfmax(i),arttdelay(i),artthalf(i)
	         endif
	      enddo
	   elseif(chn(1:3).eq.'Com'.or.chn(1:3).eq.'COM'.or.
     +        chn(1:3).eq.'com') then
	      print *,'   Ranges for energy and angles of initial',
     +                ' gammas'
	      print 280
c280	      format('$   Emin, Emax (MeV): ')
280	      format('    Emin, Emax (MeV): ',$)
	      read *,artemin(1),artemax(1)
	      print 281
c281	      format('$   tetamin, tetamax, phimin, phimax: ')
281	      format('    tetamin, tetamax, phimin, phimax: ',$)
	      read *,arttmin(1),arttmax(1),artfmin(1),artfmax(1)
	   elseif(chn(1:3).eq.'Mol'.or.chn(1:3).eq.'MOL'.or.
     +        chn(1:3).eq.'mol') then
	      print *,'   Ranges for energy and angles of initial',
     +                ' electron'
	      print 280
	      read *,artemin(1),artemax(1)
	      print 281
	      read *,arttmin(1),arttmax(1),artfmin(1),artfmax(1)
	      print 282
c282	      format('$   lower energy threshold for emitted',
c     +               ' delta rays (MeV): ')
282	      format('    lower energy threshold for emitted',
     +               ' delta rays (MeV): ',$)
	      read *,artQb(1)
	   elseif(chn(1:3).eq.'Pai'.or.chn(1:3).eq.'PAI'.or.
     +        chn(1:3).eq.'pai') then
	      print *,'   Ranges for energy and angles of initial',
     +                ' gammas'
287	      print 283
c283	      format('$   Emin, Emax (MeV): ')
283	      format('    Emin, Emax (MeV): ',$)
	      read *,artemin(1),artemax(1)
	      if(amin1(artemin(1),artemax(1)).lt.1.022) then
	         print *,'energies should be not less than 1.022 MeV'
	         go to 287
	      endif
	      print 284
c284	      format('$   tetamin, tetamax, phimin, phimax: ')
284	      format('    tetamin, tetamax, phimin, phimax: ',$)
	      read *,arttmin(1),arttmax(1),artfmin(1),artfmax(1)
286	      print 285
c285	      format('$   Z of target: ')
285	      format('    Z of target: ',$)
	      read *,artZd(1)
	      if(artZd(1).lt.1.) then
	         print *,'Z should be not less than 1'
	         go to 286
	      endif
	   endif
	endif
c*********************************************************************
	print *,'     '                                    !**********
	print 29                                           ! comment
c29	format('$number of events to generate      : ')    ! if in
29	format(' number of events to generate : ',$)       ! if in
	read *,nevents                                     ! nemo*.car
c	print 30                                           !
c30	format('$number of first event [1]         : ')    !
c30	format(' number of first event [1]         : ',$)  !
c	read 31,ievstart                                   !
31	format(i12)                                        !**********
c*********************************************************************
c	if(ievstart.le.0) ievstart=1
c	if(ievstart.ne.1) then
c	   print 32
c32	   format('$initial random integer for RDMIN  : ')
c32	   format(' initial random integer for RDMIN  : ',$)
c	   read *,irndmst
c	endif
	ievstart=1
	print 32
32	format(' initial scrolling of (0,1) random number generator'
     +       ' [0] : ',$)
	read 31,irndmst
	if(irndmst.lt.0) irndmst=0
	if(irndmst.ne.0) then
	   do i=1,irndmst
	      x=rnd1(d)
	   enddo
	endif
	chfile='no file'
	iwrfile=0
c*********************************************************************
	print 33                                           !**********
c33	format('$to write generated events in file ? ')    ! comment
33	format(' to write generated events in file ? ',$)  ! comment
	read 3,chn                                         ! if in
	if(chn(1:1).eq.'Y'.or.chn(1:1).eq.'y') then        ! nemo*.car
	   iwrfile=1                                       !
	   print 34                                        !
c34	   format('$name of file                      : ') !
34	   format(' name of file                      : ',$)!
	   read 3,chfile                                   !
	endif                                              !**********
c*********************************************************************
	print *,'   '
	istart=-1
	call GENBBsub(i2bbs,chnuclide,ilevel,modebb,istart,ier)
	if(ier.ne.0) then
	   print *,'incorrect input parameter in GENBBsub'
	   go to 1000
	endif
	return
	end

c***********************************************************************

	subroutine GENBBsub(i2bbs,chnuclide,ilevel,modebb,istart,ier)
c
c Subroutine GENBBsub generates the events of decay of natural
c radioactive nuclides and various modes of double beta decay.
c GENBB units: energy and moment - MeV and MeV/c; time - sec.
c Energy release in double beta decay - in accordance with
c G.Audi and A.H.Wapstra, Nucl. Phys. A 595(1995)409.
c
c Call  : character chnuclide*16,chfile*40,chart*4,chdspin*4
c         common/genbbpar/nevents,ievstart,irndmst,iwrfile,chfile
c         common/currentev/icurrent
c         common/enrange/ebb1,ebb2,toallevents,levelE,chdspin
c         common/artificial/nartparts,    chart(10),
c      +                    artemin(10),  artemax(10),
c      +                    arttmin(10),  arttmax(10),
c      +                    artfmin(10),  artfmax(10),
c      +                    artQb(10),    artZd(10),
c      +                    arttdelay(10),artthalf(10)
c      +                    nartnpg(10)
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call GENBBsub(i2bbs,chnuclide,ilevel,modebb,istart,ier)
c
c Input : i2bbs     - i2bbs=1 - to generate 2b-decay,
c                     i2bbs=2 - to generate decay of background nuclide
c                               or calibration source;
c         chnuclide - character*16 name of nuclide:
c                     for i2bbs=1 - Ca40,  Ca46,  Ca48,
c                                   Ni58,
c                                   Zn64,  Zn70,
c                                   Ge76,
c                                   Se74,  Se82,
c                                   Sr84,
c                                   Zr94,  Zr96,
c                                   Mo92,  Mo100,
c                                   Ru96,  Ru104,
c                                   Cd106, Cd108, Cd114, Cd116,
c                                   Sn112, Sn122, Sn124,
c                                   Te120, Te128, Te130,
c                                   Xe136,
c                                   Ce136, Ce138, Ce142,
c                                   Nd148, Nd150,
c                                   Dy156, Dy158,
c                                   W180,  W186,
c                                   Pt190, Pt198,
c                                   Os184, Os192,
c                                   Bi214 (for Bi214+At214),
c                                   Pb214 (for Pb214+Po214),
c                                   Po218 (for Po218+Rn218+Po214),
c                                   Rn222 (for Rn222+Ra222+Rn218+Po214);
c                     for i2bbs=2 - Ac228,
c                                   Am241,
c                                   Ar39,
c                                   Ar42,
c                                   As79 (for As79+Se79m),
c                                   Bi207 (for Bi207+Pb207m),
c                                   Bi208,
c                                   Bi210,
c                                   Bi212 (for Bi212+Po212),
c                                   Bi214 (for Bi214+Po214),
c                                   Ca48 (for Ca48+Sc48),
c                                   C14,
c                                   Cd113,
c                                   Co60,
c                                   Cs136,
c                                   Cs137 (for Cs137+Ba137m),
c                                   Eu147,
c                                   Eu152,
c                                   Eu154,
c                                   Gd146,
c                                   Hf182,
c                                   I126,
c                                   I133,
c                                   I134,
c                                   I135,
c                                   K40,
c                                   K42,
c                                   Kr81,
c                                   Kr85,
c                                   Mn54,
c                                   Na22,
c                                   P32,
c                                   Pa234m,
c                                   Pb210,
c                                   Pb211,
c                                   Pb212,
c                                   Pb214,
c                                   Ra228,
c                                   Rb87,
c                                   Rh106,
c                                   Sb125,
c                                   Sb126,
c                                   Sb133,
c                                   Sr90,
c                                   Ta182,
c                                   Te133,
c                                   Te133m,
c                                   Te134,
c                                   Th234,
c                                   Tl207,
c                                   Tl208,
c                                   Xe129m,
c                                   Xe131m,
c                                   Xe133,
c                                   Xe135,
c                                   Y88,
c                                   Y90,
c                                   Zn95,
c                                   Zr96 (for Zr96+Nb96),
c                                   Art (for artificial event),
c                                   Com (for Compton effect),
c                                   Mol (for Moller scattering),
c                                   Pai (for e+e- pair creation from
c                                        external gammas);
c         ilevel    - (for i2bbs=1 only) level of daughter nucleus occupied
c                     in 2b decay (0 - ground state, 1 - first excited 0+ or
c                     2+ level, 2 - second excited 0+ or 2+ level etc.;
c                     excited levels with other spin than 0+ and 2+ should be
c                     omitted):
c                     for Ca40-Ar40   - 0. 0+ (gs)     {0 MeV},
c                     for Ca46-Ti46   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.889 MeV},
c                     for Ca48-Ti48   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.984 MeV},
c                                       2. 2+ (2)  {2.421 MeV},
c                     for Ni58-Fe58   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.811 MeV},
c                                       2. 2+ (2)  {1.675 MeV},
c                     for Zn64-Ni64   - 0. 0+ (gs)     {0 MeV},
c                     for Zn70-Ge70   - 0. 0+ (gs)     {0 MeV},
c                     for Ge76-Se76   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.559 MeV},
c                                       2. 0+ (1)  {1.122 MeV},
c                                       3. 2+ (2)  {1.216 MeV},
c                     for Se74-Ge74   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.596 MeV},
c                                       2. 2+ (2)  {1.204 MeV},
c                     for Se82-Kr82   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.776 MeV},
c                                       2. 2+ (2)  {1.475 MeV},
c                     for Sr84-Kr84   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.882 MeV},
c                     for Zr94-Mo94   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.871 MeV},
c                     for Zr96-Mo96   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.778 MeV},
c                                       2. 0+ (1)  {1.148 MeV},
c                                       3. 2+ (2)  {1.498 MeV},
c                                       4. 2+ (3)  {1.626 MeV},
c                                       5. 2+ (4)  {2.096 MeV},
c                                       6. 2+ (5)  {2.426 MeV},
c                                       7. 0+ (2)  {2.623 MeV},
c                                       8. 2+ (6)  {2.700 MeV},
c                                       9. 2+?(7)  {2.713 MeV},
c                     for Mo92-Zr92   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.934 MeV},
c                                       2. 0+ (1)  {1.383 MeV},
c                     for Mo100-Ru100 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.540 MeV},
c                                       2. 0+ (1)  {1.130 MeV},
c                                       3. 2+ (2)  {1.362 MeV},
c                                       4. 0+ (2)  {1.741 MeV},
c                     for Ru96-Mo96   - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.778 MeV},
c                                       2. 0+ (1)  {1.148 MeV},
c                                       3. 2+ (2)  {1.498 MeV},
c                                       4. 2+ (3)  {1.626 MeV},
c                                       5. 2+ (4)  {2.096 MeV},
c                                       6. 2+ (5)  {2.426 MeV},
c                                       7. 0+ (2)  {2.623 MeV},
c                                       8. 2+ (6)  {2.700 MeV},
c                                       9. 2+?(7)  {2.713 MeV},
c                     for Ru104-Pd104 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.556 MeV},
c                     for Cd106-Pd106 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.512 MeV},
c                                       2. 2+ (2)  {1.128 MeV},
c                                       3. 0+ (1)  {1.134 MeV},
c                                       4. 2+ (3)  {1.562 MeV},
c                                       5. 0+ (2)  {1.706 MeV},
c                     for Cd108-Pd108 - 0. 0+ (gs)     {0 MeV},
c                     for Cd114-Sn114 - 0. 0+ (gs)     {0 MeV},
c                     for Cd116-Sn116 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {1.294 MeV},
c                                       2. 0+ (1)  {1.757 MeV},
c                                       3. 0+ (2)  {2.027 MeV},
c                                       4. 2+ (2)  {2.112 MeV},
c                                       5. 2+ (3)  {2.225 MeV},
c                     for Sn112-Cd112 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.618 MeV},
c                                       2. 0+ (1)  {1.224 MeV},
c                                       3. 2+ (2)  {1.312 MeV},
c                                       4. 0+ (2)  {1.433 MeV},
c                                       5. 2+ (3)  {1.469 MeV},
c                                       6. 0+ (3)  {1.871 MeV},
c                     for Sn122-Te122 - 0. 0+ (gs)     {0 MeV},
c                     for Sn124-Te124 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.603 MeV},
c                                       2. 2+ (2)  {1.326 MeV},
c                                       3. 0+ (1)  {1.657 MeV},
c                                       4. 0+ (2)  {1.883 MeV},
c                                       5. 2+ (3)  {2.039 MeV},
c                                       6. 2+ (4)  {2.092 MeV},
c                                       7. 0+ (3)  {2.153 MeV},
c                                       8. 2+ (5)  {2.182 MeV},
c                     for Te120-Sn120 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {1.171 MeV},
c                     for Te128-Xe128 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.443 MeV},
c                     for Te130-Xe130 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.536 MeV},
c                                       2. 2+ (2)  {1.122 MeV},
c                                       3. 0+ (1)  {1.794 MeV},
c                     for Xe136-Ba136 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.819 MeV},
c                                       2. 2+ (2)  {1.551 MeV},
c                                       3. 0+ (1)  {1.579 MeV},
c                                       4. 2+ (3)  (2.080 MeV},
c                                       5. 2+ (4)  {2.129 MeV},
c                                       6. 0+ (2)  {2.141 MeV},
c                                       7. 2+ (5)  {2.223 MeV},
c                                       8. 0+ (3)  {2.315 MeV},
c                                       9. 2+ (6)  {2.400 MeV},
c                     for Ce136-Ba136 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.819 MeV},
c                                       2. 2+ (2)  {1.551 MeV},
c                                       3. 0+ (1)  {1.579 MeV},
c                                       4. 2+ (3)  (2.080 MeV},
c                                       5. 2+ (4)  {2.129 MeV},
c                                       6. 0+ (2)  {2.141 MeV},
c                                       7. 2+ (5)  {2.223 MeV},
c                                       8. 0+ (3)  {2.315 MeV},
c                                       9. 2+ (6)  {2.400 MeV},
c                     for Ce138-Ba138 - 0. 0+ (gs)     {0 MeV},
c                     for Ce142-Nd142 - 0. 0+ (gs)     {0 MeV},
c                     for Nd148-Sm148 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.550 MeV},
c                                       2. 2+ (2)  {1.455 MeV},
c                     for Nd150-Sm150 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.334 MeV},
c                                       2. 0+ (1)  {0.740 MeV},
c                                       3. 2+ (2)  {1.046 MeV},
c                                       4. 2+ (3)  {1.194 MeV},
c                                       5. 0+ (2)  {1.256 MeV};
c                     for Dy156-Gd156 - 0. 0+ (gs)     {0 MeV}'
c                                       1. 2+ (1)  {0.089 MeV}'
c                                       2. 0+ (1)  {1.050 MeV}'
c                                       3. 2+ (2)  {1.129 MeV}'
c                                       4. 2+ (3)  {1.154 MeV}'
c                                       5. 0+ (2)  {1.168 MeV}'
c                                       6. 2+ (4)  {1.258 MeV}'
c                                       7. 0+ (3)  {1.715 MeV}'
c                                       8. 2+ (5)  {1.771 MeV}'
c                                       9. 2+ (6)  {1.828 MeV}'
c                                      10. 0+ (4)  {1.851 MeV}'
c                                      11. 2+ (7)  {1.915 MeV}'
c                                      12. 1-      {1.946 MeV}'
c                                      13. 0-      {1.952 MeV}'
c                                      14. 0+ (5)  {1.989 MeV}'
c                                      15. 2+ (8)  {2.004 MeV}'
c                     for Dy158-Gd158 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.080 MeV},
c                                       2. 4+ (1)  {0.261 MeV};
c                     for W180-Hf180  - 0. 0+ (gs)     {0 MeV};
c                     for W186-Os186  - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.137 MeV};
c                     for Os184-W184  - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.111 MeV},
c                                       2. 2+ (2)  {0.903 MeV},
c                                       3. 0+ (1)  {1.002 MeV},
c                                       4. 2+ (3)  {1.121 MeV},
c                                       5. 0+ (2)  {1.322 MeV},
c                                       6. 2+ (4)  {1.386 MeV},
c                                       7. 2+ (5)  {1.431 MeV};
c                     for Os192-Pt192 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.317 MeV};
c                     for Pt190-Os190 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.187 MeV},
c                                       2. 2+ (2)  {0.558 MeV},
c                                       3. 0+ (1)  {0.912 MeV},
c                                       4. 2+ (3)  {1.115 MeV},
c                                       5. 0+ (2)  {1.382 MeV};
c                     for Pt198-Hg198 - 0. 0+ (gs)     {0 MeV},
c                                       1. 2+ (1)  {0.412 MeV};
c                     for Bi214-At214 - 0. 1- (gs)     {0 MeV};
c                     for Pb214-Po214 - 0. 0+ (gs)     {0 MeV};
c                     for Po218-Rn218 - 0. 0+ (gs)     {0 MeV};
c                     for Rn222-Ra222 - 0. 0+ (gs)     {0 MeV};
c         modebb    - (for i2bbs=1 only) mode of 2b decay:
c                      1. 0nubb(mn)         0+ -> 0+     {2n},
c                      2. 0nubb(rhc-lambda) 0+ -> 0+     {2n},
c                      3. 0nubb(rhc-lambda) 0+ -> 0+, 2+ {N*},
c                      4. 2nubb             0+ -> 0+     {2n},
c                      5. 0nubbM1           0+ -> 0+     {2n}
c                         Majoron with spectral index SI=1
c                         (old M of Gelmini-Roncadelli),
c                      6. 0nubbM3           0+ -> 0+     {2n}
c                         Majoron with SI=3 (vector M, double M, charged M),
c                      7. 0nubb(rhc-lambda) 0+ -> 2+     {2n},
c                      8. 2nubb             0+ -> 2+     {2n}, {N*},
c                      9. 0nuKb+            0+ -> 0+, 2+,
c                     10. 2nuKb+            0+ -> 0+, 2+,
c                     11. 0nu2K             0+ -> 0+, 2+,
c                     12. 2nu2K             0+ -> 0+, 2+,
c                     13. 0nubbM7           0+ -> 0+     {2n}
c                         Majoron with SI=7,
c                     14. 0nubbM2           0+ -> 0+     {2n}
c                         Majoron with SI=2 (bulk M of Mohapatra)
c                     15. 2nubb             0+ -> 0+ with bosonic neutrinos,
c                     16. 2nubb             0+ -> 2+ with bosonic neutrinos,
c                     17. 0nubb(rhc-eta)    0+ -> 0+ simplified expression,
c                     18. 0nubb(rhc-eta)    0+ -> 0+ with specified NMEs;
c	                19. 2nubb LV          0+ -> 0+ with Lorentz violation,
c	                20. 0nu4b             0+ -> 0+ quadruple beta decay;
c         istart    - -1 - to check consistency of input data and fill
c                          working arrays without generation of events;
c                      0 - the same but one event will be generated;
c                      1 - to generate all subsequent events. So, for
c                          the first call to GENBBsub istart must be
c                          =0 or -1;
c         nevents   - number of events to generate; it will be used only
c                     for information in GENBB.report file and in output
c                     file with generated events (if asked) - so, one
c                     has to call GENBBsub one time for one decay event;
c         ievstart  - number of first event;
c         irndmst   - (only for ievstart > 1) initial random integer
c                     for RDMIN;
c         iwrfile   - iwrfile=0 - do not write generated events in file,
c                     iwrfile=1 - to write generated events in file;
c         chfile    - (only for iwrfile=1) character*40 name of file;
c         icurrent  - current number of event; if last event, file
c                     GENBB.report is created;
c         ebb1,ebb2 - (only for i2bbs=1) left and right energy limits for
c                     sum of energies of emitted e-/e+; other events will
c                     be thrown away (for modebb = 4,5,6,8,10 and 13);
c
c
c                     For artificial event (i2bbs=2 and chnuclide='Art')
c                     (emission of up to 10 beta, e+e- pairs and all
c                     GEANT particles in region of energies and angles
c                     with time delay and halflife):
c
c         nartparts   - number of parts of artificial event (up to 10);
c         chart       - character*4 array of identifiers:
c                       GP - emission of GEANT particle,
c                       Pi - emission of internal conversion e+/e- pair,
c                       Be - beta decay;
c         artemin,    - arrays of min and max values for particles kinetic
c         artemax       energies (MeV);
c         arttmin,    - arrays of min and max values for particles teta
c         arttmax       angles (degree);
c         artfmin,    - arrays of min and max values for particles phi
c         artfmax       angles (degree);
c         artQb       - (for chart='Be') array of Qbeta values (MeV),
c                       (for chart='Pi') array of pair kinetic energy (MeV);
c         artZd       - (for chart='Be') array of atomic numbers of daughter
c                       nucleus (artZd>0 for beta- and artZd<0 for beta+ decay);
c         arttdelay   - array of time delays: minimum time between current
c                       part of event and previous one (sec);
c         artthalf    - array of half-lives of current part of events (sec);
c         nartnpg     - array of GEANT number particles:
c                        1 - gamma         2 - positron     3 - electron
c                        4 - neutrino      5 - muon+        6 - muon-
c                        7 - pion0         8 - pion+        9 - pion-
c                       10 - kaon0 long   11 - kaon+       12 - kaon-
c                       13 - neutron      14 - proton      15 - antiproton
c                       16 - kaon0 short  17 - eta         18 - lambda
c                       19 - sigma+       20 - sigma0      21 - sigma-
c                       22 - xi0          23 - xi-         24 - omega
c                       25 - antineutron  26 - antilambda  27 - antisigma-
c                       28 - antisigma0   29 - antisigma+  30 - antixi0
c                       31 - antixi+      32 - antiomega+  45 - deuteron
c                       46 - tritium      47 - alpha       48 - geantino
c                       49 - He3          50 - Cerenkov.
c
c                     For chart = 'GP' particle's energy will be uniformly
c                     distributed in the range [artemin,artemax]; particle
c                     will be emitted isotropically in the region of space
c                     determined by [arttmin,arttmax], [artfmin,artfmax].
c
c                     For chart = 'Be', energy will be sampled in [0,artQb] in
c                     accordance with beta decay energy spectrum; beta particle
c                     will be emitted isotropically in full space.
c
c                     For chart = 'Pi', energy of pair is fixed to artQb and
c                     divided half to half for e- and e+; e- and e+ are
c                     emitted in the same direction; this direction is
c                     distributed isotropically in full space.
c
c
c                     For generation of events of Compton effect (i2bbs=2 and
c                     chnuclide='Com'):
c
c         artemin(1), - min and max values for kinetic energy of initial
c         artemax(1)    gamma quantum (MeV);
c         arttmin(1), - min and max values for teta angle of initial particle
c         arttmax(1)    (degree);
c         artfmin(1), - min and max values for phi angle of initial particle
c         artfmax(1)    (degree);
c
c
c                     For generation of events of Moller scattering (i2bbs=2
c                     and chnuclide='Mol'):
c
c         artemin(1), - min and max values for kinetic energy of initial
c         artemax(1)    electron (MeV);
c         arttmin(1), - min and max values for teta angle of initial particle
c         arttmax(1)    (degree);
c         artfmin(1), - min and max values for phi angle of initial particle
c         artfmax(1)    (degree);
c         artQb(1)    - lower energy threshold for emitted delta rays (MeV);
c
c
c                     For generation of events of e+e- pair creation from
c                     external gamma quanta: (i2bbs=2 and chnuclide='Pai'):
c
c         artemin(1), - min and max values for kinetic energy of initial
c         artemax(1)    gamma quantum (MeV);
c         arttmin(1), - min and max values for teta angle of initial particle
c         arttmax(1)    (degree);
c         artfmin(1), - min and max values for phi angle of initial particle
c         artfmax(1)    (degree);
c         artZd(1)    - atomic number Z of target;
c
c Output: ier                   - ier=0/1 - everything is correct/incorrect in
c                                 input parameters;
c         tevst                 - time of event's start (sec);
c         npfull                - full number of emitted particles in event;
c         npgeant(1-npfull)     - array of GEANT numbers for particle identi-
c                                 fication (1 for gamma, 2 for e+, 3 for e-,
c                                 5 for muon+, 6 for muon-, 47 for alpha);
c         pmoment(1-3,1-npfull) - array of x,y,z components of particle momentum
c                                 (MeV/c);
c         ptime(1-npfull)       - array of time shift from previous time to
c                                 calculate when particle was emitted (sec);
c         toallevents           - (only for i2bbs=1 and restricted range for sum
c                                 of energies of emitted e-/e+) coefficient to
c                                 recalculate number of bb events in full range
c                                 of energies:
c                                 full_number=generated_number*toallevents
c                                 (for modebb = 4,5,6,8,10 and 13);
c         levelE                - (only for i2bbs=1) energy (in keV) of level of
c                                 daughter 2b nuclide;
c         chdspin               - (only for i2bbs=1) character*4 spin and parity of
c                                 the level of daughter nuclide in 2b decay.
c
c V.I.Tretyak, 04.12.1995; 3.04.2016.
c
	character chfile*40,chnuclide*16,chn*16,chart*4,chdspin*4
	character chmodebb*45
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	common/genbbpar/nevents,ievstart,irndmst,iwrfile,chfile
        common/const/pi,emass,datamass(50)
	common/enrange/ebb1,ebb2,toallevents,levelE,chdspin
	common/currentev/icurrent
	common/slate/isl(40)
	common/artificial/nartparts,    chart(10),
     +                    artemin(10),  artemax(10),
     +                    arttmin(10),  arttmax(10),
     +                    artfmin(10),  artfmax(10),
     +                    artQb(10),    artZd(10),
     +                    arttdelay(10),artthalf(10),
     +                    nartnpg(10)
        save Qbb,EK,Zdbb,Adbb,istartbb
	common/eta_nme/chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,
     +                 chip_P,chip_R
	ier=0
	if(istart.eq.1) go to 1000
	chn=chnuclide
	if(i2bbs.eq.1) then
	   if((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +        chn(1:2).eq.'ca').and.chn(3:4).eq.'40') then
	      chnuclide='Ca40'
	      Qbb=0.194
	      Zdbb=-18.
	      Adbb=40.
	      EK=0.003
	      if(ilevel.lt.0.or.ilevel.gt.0) then
	         print *,'GENBBsub: illegal Ar40 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +        chn(1:2).eq.'ca').and.chn(3:4).eq.'46') then
	      chnuclide='Ca46'
	      Qbb=0.989
	      Zdbb=22.
	      Adbb=46.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Ti46 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=889
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +        chn(1:2).eq.'ca').and.chn(3:4).eq.'48') then
	      chnuclide='Ca48'
	      Qbb=4.267
	      Zdbb=22.
	      Adbb=48.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Ti48 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=984
	      if(ilevel.eq.2) levelE=2421
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2) itrans02=2
	   elseif((chn(1:2).eq.'Ni'.or.chn(1:2).eq.'NI'.or.
     +        chn(1:2).eq.'ni').and.chn(3:4).eq.'58') then
	      chnuclide='Ni58'
	      Qbb=1.926
	      Zdbb=-26.
	      Adbb=58.
	      EK=0.007
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Fe58 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=811
	      if(ilevel.eq.2) levelE=1675
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2) itrans02=2
	   elseif((chn(1:2).eq.'Zn'.or.chn(1:2).eq.'ZN'.or.
     +        chn(1:2).eq.'zn').and.chn(3:4).eq.'64') then
	      chnuclide='Zn64'
	      Qbb=1.095
	      Zdbb=-28.
	      Adbb=64.
	      EK=0.008
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Ni64 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Zn'.or.chn(1:2).eq.'ZN'.or.
     +        chn(1:2).eq.'zn').and.chn(3:4).eq.'70') then
	      chnuclide='Zn70'
	      Qbb=0.997
	      Zdbb=32.
	      Adbb=70.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Ge70 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Ge'.or.chn(1:2).eq.'GE'.or.
     +        chn(1:2).eq.'ge').and.chn(3:4).eq.'76') then
	      chnuclide='Ge76'
	      Qbb=2.039
	      Zdbb=34.
	      Adbb=76.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.3) then
	         print *,'GENBBsub: illegal Se76 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=559
	      if(ilevel.eq.2) levelE=1122
	      if(ilevel.eq.3) levelE=1216
	      if(ilevel.eq.0.or.ilevel.eq.2) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.3) itrans02=2
	   elseif((chn(1:2).eq.'Se'.or.chn(1:2).eq.'SE'.or.
     +        chn(1:2).eq.'se').and.chn(3:4).eq.'74') then
	      chnuclide='Se74'
	      Qbb=1.209
	      Zdbb=-32.
	      Adbb=74.
	      EK=0.011
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Ge74 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=596
	      if(ilevel.eq.2) levelE=1204
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2) itrans02=2
	   elseif((chn(1:2).eq.'Se'.or.chn(1:2).eq.'SE'.or.
     +        chn(1:2).eq.'se').and.chn(3:4).eq.'82') then
	      chnuclide='Se82'
	      Qbb=2.996
	      Zdbb=36.
	      Adbb=82.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Kr82 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=776
	      if(ilevel.eq.2) levelE=1475
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2) itrans02=2
	   elseif((chn(1:2).eq.'Sr'.or.chn(1:2).eq.'SR'.or.
     +        chn(1:2).eq.'sr').and.chn(3:4).eq.'84') then
	      chnuclide='Sr84'
	      Qbb=1.790
	      Zdbb=-36.
	      Adbb=84.
	      EK=0.014
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Kr84 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=882
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Zr'.or.chn(1:2).eq.'ZR'.or.
     +        chn(1:2).eq.'zr').and.chn(3:4).eq.'94') then
	      chnuclide='Zr94'
	      Qbb=1.142
	      Zdbb=42.
	      Adbb=94.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Mo94 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=871
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Zr'.or.chn(1:2).eq.'ZR'.or.
     +        chn(1:2).eq.'zr').and.chn(3:4).eq.'96') then
	      chnuclide='Zr96'
	      Qbb=3.349
	      Zdbb=42.
	      Adbb=96.
	      EK=0.
	      if(modebb.eq.20) then
	         ilevel=0
	         Qbb=0.635
	         Zdbb=44.
	      endif
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'GENBBsub: illegal Mo96 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=778
	      if(ilevel.eq.2) levelE=1148
	      if(ilevel.eq.3) levelE=1498
	      if(ilevel.eq.4) levelE=1626
	      if(ilevel.eq.5) levelE=2096
	      if(ilevel.eq.6) levelE=2426
	      if(ilevel.eq.7) levelE=2623
	      if(ilevel.eq.8) levelE=2700
	      if(ilevel.eq.9) levelE=2713
	      if(ilevel.eq.0.or.ilevel.eq.2.or.ilevel.eq.7) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.3.or.ilevel.eq.4.or.
     +           ilevel.eq.5.or.ilevel.eq.6.or.ilevel.eq.8.or.
c we suppose here that 2713 keV level is 2+
     +           ilevel.eq.9) itrans02=2
	   elseif((chn(1:2).eq.'Mo'.or.chn(1:2).eq.'MO'.or.
     +        chn(1:2).eq.'mo').and.chn(3:4).eq.'92') then
	      chnuclide='Mo92'
	      Qbb=1.652
	      Zdbb=-40.
	      Adbb=92.
	      EK=0.018
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Zr92 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=934
	      if(ilevel.eq.2) levelE=1383
	      if(ilevel.eq.0.or.ilevel.eq.2) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Mo'.or.chn(1:2).eq.'MO'.or.
     +        chn(1:2).eq.'mo').and.chn(3:5).eq.'100') then
	      chnuclide='Mo100'
	      Qbb=3.034
	      Zdbb=44.
	      Adbb=100.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.4) then
	         print *,'GENBBsub: illegal Ru100 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=540
	      if(ilevel.eq.2) levelE=1130
	      if(ilevel.eq.3) levelE=1362
	      if(ilevel.eq.4) levelE=1741
	      if(ilevel.eq.0.or.ilevel.eq.2.or.ilevel.eq.4) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.3) itrans02=2
	   elseif((chn(1:2).eq.'Ru'.or.chn(1:2).eq.'RU'.or.
     +        chn(1:2).eq.'ru').and.chn(3:4).eq.'96') then
	      chnuclide='Ru96'
	      Qbb=2.715
	      Zdbb=-42.
	      Adbb=96.
	      EK=0.020
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'GENBBsub: illegal Mo96 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=778
	      if(ilevel.eq.2) levelE=1148
	      if(ilevel.eq.3) levelE=1498
	      if(ilevel.eq.4) levelE=1626
	      if(ilevel.eq.5) levelE=2096
	      if(ilevel.eq.6) levelE=2426
	      if(ilevel.eq.7) levelE=2623
	      if(ilevel.eq.8) levelE=2700
	      if(ilevel.eq.9) levelE=2713
	      if(ilevel.eq.0.or.ilevel.eq.2.or.ilevel.eq.7) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.3.or.ilevel.eq.4.or.
     +           ilevel.eq.5.or.ilevel.eq.6.or.ilevel.eq.8.or.
c we suppose here that 2713 keV level is 2+
     +           ilevel.eq.9) itrans02=2
	      if(ilevel.eq.8) EK=0.003
	      if(ilevel.eq.9) EK=0.002
	   elseif((chn(1:2).eq.'Ru'.or.chn(1:2).eq.'RU'.or.
     +        chn(1:2).eq.'ru').and.chn(3:5).eq.'104') then
	      chnuclide='Ru104'
	      Qbb=1.301
	      Zdbb=46.
	      Adbb=104.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Pd104 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=556
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +        chn(1:2).eq.'cd').and.chn(3:5).eq.'106') then
	      chnuclide='Cd106'
	      Qbb=2.775
	      Zdbb=-46.
	      Adbb=106.
              EK=0.024
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'GENBBsub: illegal Pd106 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=512
	      if(ilevel.eq.2) levelE=1128
	      if(ilevel.eq.3) levelE=1134
	      if(ilevel.eq.4) levelE=1562
	      if(ilevel.eq.5) levelE=1706
	      if(ilevel.eq.0.or.ilevel.eq.3.or.ilevel.eq.5)
     +           itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2.or.ilevel.eq.4)
     +           itrans02=2
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +        chn(1:2).eq.'cd').and.chn(3:5).eq.'108') then
	      chnuclide='Cd108'
	      Qbb=0.272
	      Zdbb=-46.
	      Adbb=108.
	      EK=0.024
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Pd108 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +        chn(1:2).eq.'cd').and.chn(3:5).eq.'114') then
	      chnuclide='Cd114'
	      Qbb=0.543
	      Zdbb=50.
	      Adbb=114.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Sn114 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +        chn(1:2).eq.'cd').and.chn(3:5).eq.'116') then
	      chnuclide='Cd116'
	      Qbb=2.813
	      Zdbb=50.
	      Adbb=116.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'GENBBsub: illegal Sn116 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=1294
	      if(ilevel.eq.2) levelE=1757
	      if(ilevel.eq.3) levelE=2027
	      if(ilevel.eq.4) levelE=2112
	      if(ilevel.eq.5) levelE=2225
	      if(ilevel.eq.0.or.ilevel.eq.2.or.ilevel.eq.3) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.4.or.ilevel.eq.5) itrans02=2
	   elseif((chn(1:2).eq.'Sn'.or.chn(1:2).eq.'SN'.or.
     +        chn(1:2).eq.'sn').and.chn(3:5).eq.'112') then
	      chnuclide='Sn112'
	      Qbb=1.920
	      Zdbb=-48.
	      Adbb=112.
	      EK=0.027
	      if(ilevel.lt.0.or.ilevel.gt.6) then
	         print *,'GENBBsub: illegal Cd112 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=618
	      if(ilevel.eq.2) levelE=1224
	      if(ilevel.eq.3) levelE=1312
	      if(ilevel.eq.4) levelE=1433
	      if(ilevel.eq.5) levelE=1469
	      if(ilevel.eq.6) levelE=1871
	      if(ilevel.eq.0.or.ilevel.eq.2.or.ilevel.eq.4.or.
     +           ilevel.eq.6) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.3.or.ilevel.eq.5) itrans02=2
	   elseif((chn(1:2).eq.'Sn'.or.chn(1:2).eq.'SN'.or.
     +        chn(1:2).eq.'sn').and.chn(3:5).eq.'122') then
	      chnuclide='Sn122'
	      Qbb=0.373
	      Zdbb=52.
	      Adbb=122.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Te122 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Sn'.or.chn(1:2).eq.'SN'.or.
     +        chn(1:2).eq.'sn').and.chn(3:5).eq.'124') then
	      chnuclide='Sn124'
	      Qbb=2.291
	      Zdbb=52.
	      Adbb=124.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.8) then
	         print *,'GENBBsub: illegal Te124 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=603
	      if(ilevel.eq.2) levelE=1326
	      if(ilevel.eq.3) levelE=1657
	      if(ilevel.eq.4) levelE=1883
	      if(ilevel.eq.5) levelE=2039
	      if(ilevel.eq.6) levelE=2092
	      if(ilevel.eq.7) levelE=2153
	      if(ilevel.eq.8) levelE=2182
	      if(ilevel.eq.0.or.ilevel.eq.3.or.ilevel.eq.4.or.
     +           ilevel.eq.7) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2.or.ilevel.eq.5.or.
     +           ilevel.eq.6.or.ilevel.eq.8) itrans02=2
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +        chn(1:2).eq.'te').and.chn(3:5).eq.'120') then
	      chnuclide='Te120'
	      Qbb=1.730
	      Zdbb=-50.
	      Adbb=120.
	      EK=0.029
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Sn120 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=1171
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +        chn(1:2).eq.'te').and.chn(3:5).eq.'128') then
	      chnuclide='Te128'
	      Qbb=0.867
	      Zdbb=54.
	      Adbb=128.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Xe128 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=443
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +        chn(1:2).eq.'te').and.chn(3:5).eq.'130') then
	      chnuclide='Te130'
	      Qbb=2.528
	      Zdbb=54.
	      Adbb=130.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.3) then
	         print *,'GENBBsub: illegal Xe130 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=536
	      if(ilevel.eq.2) levelE=1122
	      if(ilevel.eq.3) levelE=1794
	      if(ilevel.eq.0.or.ilevel.eq.3) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2) itrans02=2
	   elseif((chn(1:2).eq.'Xe'.or.chn(1:2).eq.'XE'.or.
     +        chn(1:2).eq.'xe').and.chn(3:5).eq.'136') then
	      chnuclide='Xe136'
	      Qbb=2.458
	      Zdbb=56.
	      Adbb=136.
	      EK=0.
	      if(modebb.eq.20) then
	         ilevel=0
	         Qbb=0.079
	         Zdbb=58.
	      endif
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'GENBBsub: illegal Ba136 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=819
	      if(ilevel.eq.2) levelE=1551
	      if(ilevel.eq.3) levelE=1579
	      if(ilevel.eq.4) levelE=2080
	      if(ilevel.eq.5) levelE=2129
	      if(ilevel.eq.6) levelE=2141
	      if(ilevel.eq.7) levelE=2223
	      if(ilevel.eq.8) levelE=2315
	      if(ilevel.eq.9) levelE=2400
	      if(ilevel.eq.0.or.ilevel.eq.3.or.ilevel.eq.6.or.ilevel
     +           .eq.8) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2.or.ilevel.eq.4.or.ilevel
     +           .eq.5.or.ilevel.eq.7.or.ilevel.eq.9) itrans02=2
	   elseif((chn(1:2).eq.'Ce'.or.chn(1:2).eq.'CE'.or.
     +        chn(1:2).eq.'ce').and.chn(3:5).eq.'136') then
	      chnuclide='Ce136'
	      Qbb=2.379
	      Zdbb=-56.
	      Adbb=136.
              EK=0.037
	      if(ilevel.lt.0.or.ilevel.gt.9) then
	         print *,'GENBBsub: illegal Ba136 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=819
	      if(ilevel.eq.2) levelE=1551
	      if(ilevel.eq.3) levelE=1579
	      if(ilevel.eq.4) levelE=2080
	      if(ilevel.eq.5) levelE=2129
	      if(ilevel.eq.6) levelE=2141
	      if(ilevel.eq.7) levelE=2223
	      if(ilevel.eq.8) levelE=2315
	      if(ilevel.eq.9) levelE=2400
	      if(ilevel.eq.0.or.ilevel.eq.3.or.ilevel.eq.6.or.ilevel
     +           .eq.8) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2.or.ilevel.eq.4.or.ilevel
     +           .eq.5.or.ilevel.eq.7.or.ilevel.eq.9) itrans02=2
c only 2L capture is allowed energetically for 2400 keV level
	      if(ilevel.eq.9) EK=0.006
	   elseif((chn(1:2).eq.'Ce'.or.chn(1:2).eq.'CE'.or.
     +        chn(1:2).eq.'ce').and.chn(3:5).eq.'138') then
	      chnuclide='Ce138'
	      Qbb=0.693
	      Zdbb=-56.
	      Adbb=138.
	      EK=0.037
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Ba138 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Ce'.or.chn(1:2).eq.'CE'.or.
     +        chn(1:2).eq.'ce').and.chn(3:5).eq.'142') then
	      chnuclide='Ce142'
	      Qbb=1.417
	      Zdbb=60.
	      Adbb=142.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Nd142 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Nd'.or.chn(1:2).eq.'ND'.or.
     +        chn(1:2).eq.'nd').and.chn(3:5).eq.'148') then
	      chnuclide='Nd148'
	      Qbb=1.928
	      Zdbb=62.
	      Adbb=148.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Sm148 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=550
	      if(ilevel.eq.2) levelE=1455
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2) itrans02=2
	   elseif((chn(1:2).eq.'Nd'.or.chn(1:2).eq.'ND'.or.
     +        chn(1:2).eq.'nd').and.chn(3:5).eq.'150') then
	      chnuclide='Nd150'
	      Qbb=3.371
	      Zdbb=62.
	      Adbb=150.
	      EK=0.
	      if(modebb.eq.20) then
	         ilevel=0
	         Qbb=2.085
	         Zdbb=64.
	      endif
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'GENBBsub: illegal Sm150 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=334
	      if(ilevel.eq.2) levelE=740
	      if(ilevel.eq.3) levelE=1046
	      if(ilevel.eq.4) levelE=1194
	      if(ilevel.eq.5) levelE=1256
	      if(ilevel.eq.0.or.ilevel.eq.2.or.ilevel.eq.5) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.3.or.ilevel.eq.4) itrans02=2
	   elseif((chn(1:2).eq.'Dy'.or.chn(1:2).eq.'DY'.or.
     +        chn(1:2).eq.'dy').and.chn(3:5).eq.'156') then
	      chnuclide='Dy156'
	      Qbb=2.006
	      Zdbb=-64.
	      Adbb=156.
              EK=0.050
	      if(ilevel.lt.0.or.ilevel.gt.15) then
	         print *,'GENBBsub: illegal Gd156 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq. 0) levelE=0
	      if(ilevel.eq. 1) levelE=89
	      if(ilevel.eq. 2) levelE=1050
	      if(ilevel.eq. 3) levelE=1129
	      if(ilevel.eq. 4) levelE=1154
	      if(ilevel.eq. 5) levelE=1168
	      if(ilevel.eq. 6) levelE=1258
	      if(ilevel.eq. 7) levelE=1715
	      if(ilevel.eq. 8) levelE=1771
	      if(ilevel.eq. 9) levelE=1828
	      if(ilevel.eq.10) levelE=1851
	      if(ilevel.eq.11) levelE=1915
	      if(ilevel.eq.12) levelE=1946
	      if(ilevel.eq.13) levelE=1952
	      if(ilevel.eq.14) levelE=1989
	      if(ilevel.eq.15) levelE=2004
	      if(ilevel.eq.0  .or. ilevel.eq.2  .or. ilevel.eq.5 .or.
     +         ilevel.eq.7  .or. ilevel.eq.10 .or. ilevel.eq.14) 
     +         itrans02=0
	      if(ilevel.eq.1  .or. ilevel.eq.3  .or. ilevel.eq.4 .or.
     +         ilevel.eq.6  .or. ilevel.eq.8  .or. ilevel.eq.9 .or.
     +         ilevel.eq.11 .or. ilevel.eq.15) itrans02=2
	      if(ilevel.ge.11 .and. ilevel.le.13) EK=0.029
	      if(ilevel.eq.14) EK=0.008
	      if(ilevel.eq.15) EK=0.004
	   elseif((chn(1:2).eq.'Dy'.or.chn(1:2).eq.'DY'.or.
     +        chn(1:2).eq.'dy').and.chn(3:5).eq.'158') then
	      chnuclide='Dy158'
	      Qbb=0.283
	      Zdbb=-64.
	      Adbb=156.
              EK=0.050
	      if(ilevel.lt.0.or.ilevel.gt.2) then
	         print *,'GENBBsub: illegal Gd158 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=80
	      if(ilevel.eq.2) levelE=261
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	      if(ilevel.eq.2) EK=0.008
	   elseif((chn(1:1).eq.'W'.or.chn(1:1).eq.'w').and.
     +            chn(2:4).eq.'180') then
	      chnuclide='W180'
	      Qbb=0.143
	      Zdbb=-72.
	      Adbb=180.
	      EK=0.065
	      if(ilevel.lt.0.or.ilevel.gt.0) then
	         print *,'GENBBsub: illegal Hf180 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:1).eq.'W'.or.chn(1:1).eq.'w').and.
     +            chn(2:4).eq.'186') then
	      chnuclide='W186'
	      Qbb=0.492
	      Zdbb=76.
	      Adbb=186.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Os186 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=137
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Os'.or.chn(1:2).eq.'OS'.or.
     +        chn(1:2).eq.'os').and.chn(3:5).eq.'184') then
	      chnuclide='Os184'
	      Qbb=1.451
	      Zdbb=-74.
	      Adbb=184.
	      EK=0.070
	      if(ilevel.lt.0.or.ilevel.gt.7) then
	         print *,'GENBBsub: illegal W184 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=111
	      if(ilevel.eq.2) levelE=903
	      if(ilevel.eq.3) levelE=1002
	      if(ilevel.eq.4) levelE=1121
	      if(ilevel.eq.5) levelE=1322
	      if(ilevel.eq.6) levelE=1386
	      if(ilevel.eq.7) levelE=1431
	      if(ilevel.eq.0.or.ilevel.eq.3.or.ilevel.eq.5) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2.or.ilevel.eq.4.or.
     +           ilevel.eq.6.or.ilevel.eq.7) itrans02=2
c for decay to 1386 keV level, electron captures from LL or higher atomic shells are possible
	      if(ilevel.eq.6) EK=0.012
c for decay to 1431 keV level, electron captures from LM, MM or higher atomic shells are possible
	      if(ilevel.eq.7) EK=0.
	   elseif((chn(1:2).eq.'Os'.or.chn(1:2).eq.'OS'.or.
     +        chn(1:2).eq.'os').and.chn(3:5).eq.'192') then
	      chnuclide='Os192'
	      Qbb=0.408
	      Zdbb=78.
	      Adbb=192.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Pt192 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=317
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Pt'.or.chn(1:2).eq.'PT'.or.
     +        chn(1:2).eq.'pt').and.chn(3:5).eq.'190') then
	      chnuclide='Pt190'
	      Qbb=1.384
	      Zdbb=-76.
	      Adbb=190.
	      EK=0.074
	      if(ilevel.lt.0.or.ilevel.gt.5) then
	         print *,'GENBBsub: illegal Os190 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=187
	      if(ilevel.eq.2) levelE=558
	      if(ilevel.eq.3) levelE=912
	      if(ilevel.eq.4) levelE=1115
	      if(ilevel.eq.5) levelE=1382
	      if(ilevel.eq.0.or.ilevel.eq.3.or.ilevel.eq.5) itrans02=0
	      if(ilevel.eq.1.or.ilevel.eq.2.or.ilevel.eq.4) itrans02=2
c for decay to 1382 keV level, electron captures from N or higher atomic shells are possible
	      if(ilevel.eq.5) EK=0.
	   elseif((chn(1:2).eq.'Pt'.or.chn(1:2).eq.'PT'.or.
     +        chn(1:2).eq.'pt').and.chn(3:5).eq.'198') then
	      chnuclide='Pt198'
	      Qbb=1.049
	      Zdbb=80.
	      Adbb=198.
	      EK=0.
	      if(ilevel.lt.0.or.ilevel.gt.1) then
	         print *,'GENBBsub: illegal Hg198 level ',ilevel
	         ier=1
	         return
	      endif
	      if(ilevel.eq.0) levelE=0
	      if(ilevel.eq.1) levelE=412
	      if(ilevel.eq.0) itrans02=0
	      if(ilevel.eq.1) itrans02=2
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +        chn(1:2).eq.'bi').and.chn(3:5).eq.'214') then
	      chnuclide='Bi214'
	      Qbb=2.180
	      Zdbb=85.
	      Adbb=214.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal At214 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Pb'.or.chn(1:2).eq.'PB'.or.
     +        chn(1:2).eq.'pb').and.chn(3:5).eq.'214') then
	      chnuclide='Pb214'
	      Qbb=4.289
	      Zdbb=84.
	      Adbb=214.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Po214 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Po'.or.chn(1:2).eq.'PO'.or.
     +        chn(1:2).eq.'po').and.chn(3:5).eq.'218') then
	      chnuclide='Po218'
	      Qbb=3.141
	      Zdbb=86.
	      Adbb=218.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Rn218 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   elseif((chn(1:2).eq.'Rn'.or.chn(1:2).eq.'RN'.or.
     +        chn(1:2).eq.'rn').and.chn(3:5).eq.'222') then
	      chnuclide='Rn222'
	      Qbb=2.052
	      Zdbb=88.
	      Adbb=222.
	      EK=0.
	      if(ilevel.ne.0) then
	         print *,'GENBBsub: illegal Ra222 level ',ilevel
	         ier=1
	         return
	      endif
	      levelE=0
	      itrans02=0
	   else
	      print *,'unknown double beta nuclide'
	      ier=1
	      return
	   endif
	   if(itrans02.eq.0) chdspin='0+'
	   if(itrans02.eq.2) chdspin='2+'
	   if(itrans02.eq.0 .and. chnuclide.eq.'Bi214') chdspin='1-'
	   if(modebb.lt.1.or.modebb.gt.20) then
	      print *,'unknown bb mode'
	      ier=1
	      return
	   else
	      if(modebb.eq.1)  chmodebb='0nubb(mn) 0+ -> 0+     {2n}'
	      if(modebb.eq.2)  
     +           chmodebb='0nubb(rhc-lambda) 0+ -> 0+     {2n}'
	      if(modebb.eq.3)  
     +           chmodebb='0nubb(rhc-lambda) 0+ -> 0+, 2+ {N*}'
	      if(modebb.eq.4)  chmodebb='2nubb     0+ -> 0+     {2n}'
	      if(modebb.eq.5)  chmodebb='0nubbM1   0+ -> 0+     {2n}'
	      if(modebb.eq.6)  chmodebb='0nubbM3   0+ -> 0+     {2n}'
	      if(modebb.eq.7)  
     +           chmodebb='0nubb(rhc-lambda) 0+ -> 2+     {2n}'
	      if(modebb.eq.8)
     +           chmodebb='2nubb     0+ -> 2+     {2n}, {N*}'
	      if(modebb.eq.9)  chmodebb='0nuKb+    0+ -> 0+, 2+'
	      if(modebb.eq.10) chmodebb='2nuKb+    0+ -> 0+, 2+'
	      if(modebb.eq.11) chmodebb='0nu2K     0+ -> 0+, 2+'
	      if(modebb.eq.12) chmodebb='2nu2K     0+ -> 0+, 2+'
	      if(modebb.eq.13) chmodebb='0nubbM7   0+ -> 0+     {2n}'
	      if(modebb.eq.14) chmodebb='0nubbM2   0+ -> 0+     {2n}'
	      if(modebb.eq.15) 
     +           chmodebb='2nubb     0+ -> 0+  bosonic nu'
	      if(modebb.eq.16) 
     +           chmodebb='2nubb     0+ -> 2+  bosonic nu'
	      if(modebb.eq.17) 
     +           chmodebb='0nubb(rhc-eta) 0+ -> 0+ {2n} simplified'
	      if(modebb.eq.18) 
     +           chmodebb='0nubb(rhc-eta) 0+ -> 0+ {2n} with NMEs'
	      if(modebb.eq.19) 
     +           chmodebb='2nubb     0+ -> 0+  Lorentz violated'
	      if(modebb.eq.20) 
     +           chmodebb='0nu4b     0+ -> 0+  quadruple beta decay'
	   endif
c checking the consistency of data: (1) energy
	   El=levelE/1000.
	   if(Zdbb.ge.0.)                   e0=Qbb
	   if(Zdbb.lt.0.)                   e0=Qbb-4.*emass
	   if(modebb.eq. 9.or.modebb.eq.10) e0=Qbb-EK-2.*emass
	   if(modebb.eq.11.or.modebb.eq.12) e0=Qbb-2.*EK
	   if(e0.le.El) then
	      print *,'not enough energy for transition to this level:'
	      print *,'full energy release and Elevel = ',e0,El
	      ier=1
	   return
	   endif
c (2) spin of level and mode of decay
	   m=modebb
	   if(itrans02.eq.0. and.
     +        (m.eq. 1.or.m.eq. 2.or.m.eq. 3.or.m.eq. 4.or.m.eq. 5.or.
     +         m.eq. 6.or.m.eq. 9.or.m.eq.10.or.m.eq.11.or.m.eq.12.or.
     +         m.eq.13.or.m.eq.14.or.m.eq.15.or.m.eq.17.or.m.eq.18.or.
     +         m.eq.19.or.m.eq.20)) 
     +         go to 2
	   if(itrans02.eq.2. and.
     +        (m.eq. 3.or.m.eq. 7.or.m.eq. 8.or.m.eq. 9.or.m.eq.10.or.
     +         m.eq.11.or.m.eq.12.or.m.eq.16)) go to 2
	   print 1,chmodebb,chdspin
1	   format(' decay mode and spin of daughter nucleus level'/
     +            ' are inconsistent: ',a,'  ',a)
	   ier=1
	   return
c (3) nuclide and mode of decay
c2	   if(Zdbb.ge.0..and.modebb.eq. 9.or.modebb.eq.10.or.
c     +                       modebb.eq.11.or.modebb.eq.12) then
2	   if(Zdbb.ge.0..and.(modebb.eq. 9.or.modebb.eq.10.or.
     +                       modebb.eq.11.or.modebb.eq.12)) then
            print *,'decay mode and nuclide are inconsistent:'
	      print 3,chmodebb,chnuclide
3	      format(' ',a,'  ',a)
	      ier=1
	      return
	   endif
	endif
c (4) quadruple beta decay
	if(modebb.eq.20) then
	   ier=1
         if(chnuclide.eq.'Zr96'.or.
     +      chnuclide.eq.'Xe136'.or.
     +      chnuclide.eq.'Nd150') ier=0
         if(ier.eq.1) print *,'4beta decay is foreseen only', 
     +      ' for Zr96, Xe136 or Nd150 (g.s. to g.s.)' 
	   if(ier.eq.1) return
	endif
	if(i2bbs.eq.2) then
	   if((chn(1:2).eq.'Ac'.or.chn(1:2).eq.'AC'.or.chn(1:2).eq.'ac')
     +        .and.chn(3:5).eq.'228') then
	      chnuclide='Ac228'
	   elseif((chn(1:2).eq.'Am'.or.chn(1:2).eq.'AM'.or.
     +             chn(1:2).eq.'am').and.chn(3:5).eq.'241') then
	      chnuclide='Am241'
	   elseif((chn(1:2).eq.'Ar'.or.chn(1:2).eq.'AR'.or.
     +             chn(1:2).eq.'ar').and.chn(3:4).eq.'39') then
	      chnuclide='Ar39'
	   elseif((chn(1:2).eq.'Ar'.or.chn(1:2).eq.'AR'.or.
     +             chn(1:2).eq.'ar').and.chn(3:4).eq.'42') then
	      chnuclide='Ar42'
	   elseif((chn(1:2).eq.'As'.or.chn(1:2).eq.'AS'.or.
     +             chn(1:2).eq.'as').and.chn(3:4).eq.'79') then
	      chnuclide='As79'
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +             chn(1:2).eq.'bi').and.chn(3:5).eq.'207') then
	      chnuclide='Bi207'
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +             chn(1:2).eq.'bi').and.chn(3:5).eq.'208') then
	      chnuclide='Bi208'
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +             chn(1:2).eq.'bi').and.chn(3:5).eq.'210') then
	      chnuclide='Bi210'
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +             chn(1:2).eq.'bi').and.chn(3:5).eq.'212') then
	      chnuclide='Bi212'
	   elseif((chn(1:2).eq.'Bi'.or.chn(1:2).eq.'BI'.or.
     +             chn(1:2).eq.'bi').and.chn(3:5).eq.'214') then
	      chnuclide='Bi214'
	   elseif((chn(1:1).eq.'C'.or.chn(1:1).eq.'c')
     +                              .and.chn(2:3).eq.'14') then
	      chnuclide='C14'
	   elseif((chn(1:2).eq.'Ca'.or.chn(1:2).eq.'CA'.or.
     +             chn(1:2).eq.'ca').and.chn(3:4).eq.'48') then
	      chnuclide='Ca48'
	   elseif((chn(1:2).eq.'Cd'.or.chn(1:2).eq.'CD'.or.
     +             chn(1:2).eq.'cd').and.chn(3:5).eq.'113') then
	      chnuclide='Cd113'
	   elseif((chn(1:2).eq.'Co'.or.chn(1:2).eq.'CO'.or.
     +             chn(1:2).eq.'co').and.chn(3:4).eq.'60') then
	      chnuclide='Co60'
	   elseif((chn(1:2).eq.'Cs'.or.chn(1:2).eq.'CS'.or.
     +             chn(1:2).eq.'cs').and.chn(3:5).eq.'136') then
	      chnuclide='Cs136'
	   elseif((chn(1:2).eq.'Cs'.or.chn(1:2).eq.'CS'.or.
     +             chn(1:2).eq.'cs').and.chn(3:5).eq.'137') then
	      chnuclide='Cs137'
	   elseif((chn(1:2).eq.'Eu'.or.chn(1:2).eq.'EU'.or.
     +             chn(1:2).eq.'eu').and.chn(3:5).eq.'147') then
	      chnuclide='Eu147'
	   elseif((chn(1:2).eq.'Eu'.or.chn(1:2).eq.'EU'.or.
     +             chn(1:2).eq.'eu').and.chn(3:5).eq.'152') then
	      chnuclide='Eu152'
	   elseif((chn(1:2).eq.'Eu'.or.chn(1:2).eq.'EU'.or.
     +             chn(1:2).eq.'eu').and.chn(3:5).eq.'154') then
	      chnuclide='Eu154'
	   elseif((chn(1:2).eq.'Gd'.or.chn(1:2).eq.'GD'.or.
     +             chn(1:2).eq.'gd').and.chn(3:5).eq.'146') then
	      chnuclide='Gd146'
	   elseif((chn(1:2).eq.'Hf'.or.chn(1:2).eq.'HF'.or.
     +             chn(1:2).eq.'hf').and.chn(3:5).eq.'182') then
	      chnuclide='Hf182'
	   elseif((chn(1:1).eq.'I'.or.chn(1:1).eq.'i')
     +        .and.chn(2:4).eq.'126') then
	      chnuclide='I126'
	   elseif((chn(1:1).eq.'I'.or.chn(1:1).eq.'i')
     +        .and.chn(2:4).eq.'133') then
	      chnuclide='I133'
	   elseif((chn(1:1).eq.'I'.or.chn(1:1).eq.'i')
     +        .and.chn(2:4).eq.'134') then
	      chnuclide='I134'
	   elseif((chn(1:1).eq.'I'.or.chn(1:1).eq.'i')
     +        .and.chn(2:4).eq.'135') then
	      chnuclide='I135'
	   elseif((chn(1:1).eq.'K'.or.chn(1:1).eq.'k')
     +        .and.chn(2:3).eq.'40') then
	      chnuclide='K40'
	   elseif((chn(1:1).eq.'K'.or.chn(1:1).eq.'k')
     +        .and.chn(2:3).eq.'42') then
	      chnuclide='K42'
	   elseif((chn(1:2).eq.'Kr'.or.chn(1:2).eq.'KR'.or.
     +             chn(1:2).eq.'kr').and.chn(3:4).eq.'81') then
	      chnuclide='Kr81'
	   elseif((chn(1:2).eq.'Kr'.or.chn(1:2).eq.'KR'.or.
     +             chn(1:2).eq.'kr').and.chn(3:4).eq.'85') then
	      chnuclide='Kr85'
	   elseif((chn(1:2).eq.'Mn'.or.chn(1:2).eq.'MN'.or.
     +             chn(1:2).eq.'mn').and.chn(3:4).eq.'54') then
	      chnuclide='Mn54'
	   elseif((chn(1:2).eq.'Na'.or.chn(1:2).eq.'NA'.or.
     +             chn(1:2).eq.'na').and.chn(3:4).eq.'22') then
	      chnuclide='Na22'
	   elseif((chn(1:1).eq.'P'.or.chn(1:1).eq.'p')
     +                              .and.chn(2:3).eq.'32') then
	      chnuclide='P32'
	   elseif((chn(1:2).eq.'Pa'.or.chn(1:2).eq.'PA'.or.
     +             chn(1:2).eq.'pa').and.chn(3:6).eq.'234m') then
	      chnuclide='Pa234m'
	   elseif((chn(1:2).eq.'Pb'.or.chn(1:2).eq.'PB'.or.
     +             chn(1:2).eq.'pb').and.chn(3:5).eq.'210') then
	      chnuclide='Pb210'
	   elseif((chn(1:2).eq.'Pb'.or.chn(1:2).eq.'PB'.or.
     +             chn(1:2).eq.'pb').and.chn(3:5).eq.'211') then
	      chnuclide='Pb211'
	   elseif((chn(1:2).eq.'Pb'.or.chn(1:2).eq.'PB'.or.
     +             chn(1:2).eq.'pb').and.chn(3:5).eq.'212') then
	      chnuclide='Pb212'
	   elseif((chn(1:2).eq.'Pb'.or.chn(1:2).eq.'PB'.or.
     +             chn(1:2).eq.'pb').and.chn(3:5).eq.'214') then
	      chnuclide='Pb214'
	   elseif((chn(1:2).eq.'Ra'.or.chn(1:2).eq.'RA'.or.
     +             chn(1:2).eq.'ra').and.chn(3:5).eq.'228') then
	      chnuclide='Ra228'
	   elseif((chn(1:2).eq.'Rb'.or.chn(1:2).eq.'RB'.or.
     +             chn(1:2).eq.'rb').and.chn(3:4).eq.'87') then
	      chnuclide='Rb87'
	   elseif((chn(1:2).eq.'Rh'.or.chn(1:2).eq.'RH'.or.
     +             chn(1:2).eq.'rh').and.chn(3:5).eq.'106') then
	      chnuclide='Rh106'
	   elseif((chn(1:2).eq.'Sb'.or.chn(1:2).eq.'SB'.or.
     +             chn(1:2).eq.'sb').and.chn(3:5).eq.'125') then
	      chnuclide='Sb125'
	   elseif((chn(1:2).eq.'Sb'.or.chn(1:2).eq.'SB'.or.
     +             chn(1:2).eq.'sb').and.chn(3:5).eq.'126') then
	      chnuclide='Sb126'
	   elseif((chn(1:2).eq.'Sb'.or.chn(1:2).eq.'SB'.or.
     +             chn(1:2).eq.'sb').and.chn(3:5).eq.'133') then
	      chnuclide='Sb133'
	   elseif((chn(1:2).eq.'Sr'.or.chn(1:2).eq.'SR'.or.
     +             chn(1:2).eq.'sr').and.chn(3:4).eq.'90') then
	      chnuclide='Sr90'
	   elseif((chn(1:2).eq.'Ta'.or.chn(1:2).eq.'TA'.or.
     +             chn(1:2).eq.'ta').and.chn(3:5).eq.'182') then
	      chnuclide='Ta182'
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +             chn(1:2).eq.'te').and.chn(3:6).eq.'133m') then
	      chnuclide='Te133m'
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +             chn(1:2).eq.'te').and.chn(3:5).eq.'133') then
	      chnuclide='Te133'
	   elseif((chn(1:2).eq.'Te'.or.chn(1:2).eq.'TE'.or.
     +             chn(1:2).eq.'te').and.chn(3:5).eq.'134') then
	      chnuclide='Te134'
	   elseif((chn(1:2).eq.'Th'.or.chn(1:2).eq.'TH'.or.
     +             chn(1:2).eq.'th').and.chn(3:5).eq.'234') then
	      chnuclide='Th234'
	   elseif((chn(1:2).eq.'Tl'.or.chn(1:2).eq.'TL'.or.
     +             chn(1:2).eq.'tl').and.chn(3:5).eq.'207') then
	      chnuclide='Tl207'
	   elseif((chn(1:2).eq.'Tl'.or.chn(1:2).eq.'TL'.or.
     +             chn(1:2).eq.'tl').and.chn(3:5).eq.'208') then
	      chnuclide='Tl208'
	   elseif((chn(1:2).eq.'Xe'.or.chn(1:2).eq.'XE'.or.
     +             chn(1:2).eq.'xe').and.chn(3:6).eq.'129m') then
	      chnuclide='Xe129m'
	   elseif((chn(1:2).eq.'Xe'.or.chn(1:2).eq.'XE'.or.
     +             chn(1:2).eq.'xe').and.chn(3:6).eq.'131m') then
	      chnuclide='Xe131m'
	   elseif((chn(1:2).eq.'Xe'.or.chn(1:2).eq.'XE'.or.
     +             chn(1:2).eq.'xe').and.chn(3:5).eq.'133') then
	      chnuclide='Xe133'
	   elseif((chn(1:2).eq.'Xe'.or.chn(1:2).eq.'XE'.or.
     +             chn(1:2).eq.'xe').and.chn(3:5).eq.'135') then
	      chnuclide='Xe135'
	   elseif((chn(1:1).eq.'Y'.or.chn(1:1).eq.'y')
     +        .and.chn(2:3).eq.'88') then
	      chnuclide='Y88'
	   elseif((chn(1:1).eq.'Y'.or.chn(1:1).eq.'y')
     +        .and.chn(2:3).eq.'90') then
	      chnuclide='Y90'
	   elseif((chn(1:2).eq.'Zn'.or.chn(1:2).eq.'ZN'.or.
     +             chn(1:2).eq.'zn').and.chn(3:4).eq.'65') then
	      chnuclide='Zn65'
	   elseif((chn(1:2).eq.'Zr'.or.chn(1:2).eq.'ZR'.or.
     +             chn(1:2).eq.'zr').and.chn(3:4).eq.'96') then
	      chnuclide='Zr96'
	   elseif(chn(1:3).eq.'Art'.or.chn(1:3).eq.'ART'.or.
     +        chn(1:3).eq.'art') then
	      chnuclide='Artificial'
	      nartparts=min0(10,nartparts)
              do i=1,nartparts
	         chn=chart(i)
                 chart(i)='  '
	         if(chn(1:1).eq.'B' .or.chn(1:1).eq.'b')  chart(i)='Be'
  	         if(chn(1:1).eq.'G' .or.chn(1:1).eq.'g')  chart(i)='GP'
	         if(chn(1:1).eq.'P' .or.chn(1:1).eq.'p')  chart(i)='Pi'
	         if(chart(i).eq.'  ') then
	            print *,'unknown particle in artificial event'
	            ier=1
	            return
	         elseif(chart(i).eq.'Be') then
	            artemin(i)=artQb(i)
	            artemax(i)=artQb(i)
	            arttmin(i)=0.
	            arttmax(i)=pi
	            artfmin(i)=0.
	            artfmax(i)=2.*pi
	         elseif(chart(i).eq.'Pi') then
	            artemin(i)=artQb(i)
	            artemax(i)=artQb(i)
	            arttmin(i)=0.
	            arttmax(i)=pi
	            artfmin(i)=0.
	            artfmax(i)=2.*pi
	         else
	            arttmin(i)=arttmin(i)/180.*pi
	            arttmax(i)=arttmax(i)/180.*pi
	            artfmin(i)=artfmin(i)/180.*pi
	            artfmax(i)=artfmax(i)/180.*pi
	         endif
	      enddo
	   elseif(chn(1:3).eq.'Com'.or.chn(1:3).eq.'COM'.or.
     +        chn(1:3).eq.'com') then
	      chnuclide='Compton'
	      arttmin(1)=arttmin(1)/180.*pi
	      arttmax(1)=arttmax(1)/180.*pi
	      artfmin(1)=artfmin(1)/180.*pi
	      artfmax(1)=artfmax(1)/180.*pi
	   elseif(chn(1:3).eq.'Mol'.or.chn(1:3).eq.'MOL'.or.
     +        chn(1:3).eq.'mol') then
	      chnuclide='Moller'
	      arttmin(1)=arttmin(1)/180.*pi
	      arttmax(1)=arttmax(1)/180.*pi
	      artfmin(1)=artfmin(1)/180.*pi
	      artfmax(1)=artfmax(1)/180.*pi
	   elseif(chn(1:3).eq.'Pai'.or.chn(1:3).eq.'PAI'.or.
     +        chn(1:3).eq.'pai') then
	      chnuclide='E+E- external'
	      arttmin(1)=arttmin(1)/180.*pi
	      arttmax(1)=arttmax(1)/180.*pi
	      artfmin(1)=artfmin(1)/180.*pi
	      artfmax(1)=artfmax(1)/180.*pi
	   else
	      print *,'unknown background & source nuclide'
	      ier=1
	      return
	   endif
	endif
	if(ievstart.le.0) ievstart=1
c	if(ievstart.eq.1) irndmst=0
c	if(ievstart.ne.1) call rdmin(irndmst)
	if(iwrfile.eq.0) chfile='no file'
	if(chfile.ne.'no file') then
	   call datime(id,it)
	   open(unit=77,file=chfile,status='new')
	   write(77,8) chfile
8	   format(' DECAY0 generated file: ',a)
	   write(77,9) isl(3),isl(2),isl(1),isl(4),isl(5),isl(6)
9	   format(/'  date and time : ',
     +            2x,i2,'.',i2,'.',i4,4x,i2,':',i2,':',i2)
	   write(77,*) ' initial scrolling of (0,1) random number',
     +               ' generator : ',irndmst
	   write(77,*) '   '
	   if(i2bbs.eq.1) then
	      write(77,10) chnuclide
10	      format('  event type: ',a)
	      write(77,*) '             ',chmodebb
	      if(modebb.eq.18) then
	         write(77,*) '             NMEs: ',
     +                     'GTw,Fw,''GT,''F,''T,''P,''R ='
	         write(77,*) chi_GTw,chi_Fw,chip_GT,chip_F,
     +                     chip_T,chip_P,chip_R
	      endif
	      write(77,11) chdspin,levelE/1000.
11	      format(14x,'level, Elevel (MeV) =  ',a,'  ',g13.5,' MeV')
	      if(toallevents.gt.1.) then
	         write(77,*) '   '
	         write(77,*) 'range for sum of energies of emitted ',
     +                       'e-/e+ (MeV)   : ',ebb1,ebb2
	         allevents=anint(nevents*toallevents)
	         write(77,*) 'corresponding number of events in full ',
     +                       'energy range: ',allevents
	      endif
	   end if
	   if(i2bbs.eq.2) then
	      write(77,10) chnuclide
	      if(chnuclide.eq.'Artificial') then
	         write(77,*) ' number of parts in artificial event',
     +                        '             = ',nartparts
	         do i=1,nartparts
	            if(chart(i).eq.'GP') then
	               if(nartnpg(i).eq. 1) chn='Gamma        '
	               if(nartnpg(i).eq. 2) chn='Positron     '
	               if(nartnpg(i).eq. 3) chn='Electron     '
	               if(nartnpg(i).eq. 4) chn='Neutrino     '
	               if(nartnpg(i).eq. 5) chn='Muon+        '
	               if(nartnpg(i).eq. 6) chn='Muon-        '
	               if(nartnpg(i).eq. 7) chn='Pion0        '
	               if(nartnpg(i).eq. 8) chn='Pion+        '
	               if(nartnpg(i).eq. 9) chn='Pion-        '
	               if(nartnpg(i).eq.10) chn='Kaon0 long   '
	               if(nartnpg(i).eq.11) chn='Kaon+        '
	               if(nartnpg(i).eq.12) chn='Kaon-        '
	               if(nartnpg(i).eq.13) chn='Neutron      '
	               if(nartnpg(i).eq.14) chn='Proton       '
	               if(nartnpg(i).eq.15) chn='Antiproton   '
	               if(nartnpg(i).eq.16) chn='Kaon0 short  '
	               if(nartnpg(i).eq.17) chn='Eta          '
	               if(nartnpg(i).eq.18) chn='Lambda       '
	               if(nartnpg(i).eq.19) chn='Sigma+       '
	               if(nartnpg(i).eq.20) chn='Sigma0       '
	               if(nartnpg(i).eq.21) chn='Sigma-       '
	               if(nartnpg(i).eq.22) chn='Xi0          '
	               if(nartnpg(i).eq.23) chn='Xi-          '
	               if(nartnpg(i).eq.24) chn='Omega        '
	               if(nartnpg(i).eq.25) chn='Antineutron  '
	               if(nartnpg(i).eq.26) chn='Antilambda   '
	               if(nartnpg(i).eq.27) chn='Antisigma-   '
	               if(nartnpg(i).eq.28) chn='Antisigma0   '
	               if(nartnpg(i).eq.29) chn='Antisigma+   '
	               if(nartnpg(i).eq.30) chn='Antixi0      '
	               if(nartnpg(i).eq.31) chn='Antixi+      '
	               if(nartnpg(i).eq.32) chn='Antiomega+   '
	               if(nartnpg(i).eq.45) chn='Deuteron     '
	               if(nartnpg(i).eq.46) chn='Tritium      '
	               if(nartnpg(i).eq.47) chn='Alpha        '
	               if(nartnpg(i).eq.48) chn='Geantino     '
	               if(nartnpg(i).eq.49) chn='He3          '
	               if(nartnpg(i).eq.50) chn='Cerenkov     '
	            endif
	            if(chart(i).eq.'Be')     chn='Beta         '
	            if(chart(i).eq.'Pi')     chn='E+E- internal'
	            write(77,12) i,chn,artemin(i),artemax(i)
12	            format(2x,i2,1x,a13,1x,'min and max E',18x,'= ',
     +                     2g16.7)
	            if(chart(i).eq.'Be') write(77,13) artZd(i)
13	            format(19x,'Z of daughter nucleus          = ',
     +                     g16.7)
	            write(77,14) arttmin(i),arttmax(i),artfmin(i),
     +                           artfmax(i)
14	            format(19x,'min and max teta and phi [rad] = ',
     +                     4g16.7)
	            write(77,15) arttdelay(i),artthalf(i)
15	            format(19x,'time of delay and halflife     = ',
     +                     2g16.7)
	         enddo
	      endif
	      if(chnuclide.eq.'Compton') then
	         write(77,16) artemin(1),artemax(1)
16	         format(4x,'initial gamma: min and max E',18x,'= ',
     +                  2g16.7)
	         write(77,17) arttmin(1),arttmax(1),artfmin(1),
     +                        artfmax(1)
17	         format(19x,'min and max teta and phi [rad] = ',
     +                  4g16.7)
	      endif
	      if(chnuclide.eq.'Moller') then
	         write(77,18) artemin(1),artemax(1)
18	         format(4x,'initial e-: min and max E',18x,'= ',
     +                  2g16.7)
	         write(77,19) arttmin(1),arttmax(1),artfmin(1),
     +                        artfmax(1)
19	         format(16x,'min and max teta and phi [rad] = ',
     +                  4g16.7)
	         write(77,20) artQb(1)
20	         format(16x,'energy threshold for delta ray ='
     +                  ,g16.7)
	      endif
	      if(chnuclide.eq.'E+E- external') then
	         write(77,21) artemin(1),artemax(1)
21	         format(4x,'initial gamma: min and max E',18x,'= ',
     +                  2g16.7)
	         write(77,22) arttmin(1),arttmax(1),artfmin(1),
     +                        artfmax(1)
22	         format(19x,'min and max teta and phi [rad] = ',
     +                  4g16.7)
	         write(77,23) artZd(1)
23	         format(19x,'atomic number of target        ='
     +                  ,g16.7)
	      endif
	   endif
	   write(77,*) '   '
	   write(77,*) 'Format of data:'
	   write(77,*) ' for each event    - event''s number,'
	   write(77,*) '                     time of event''s start, '
	   write(77,*) '                     number of emitted',
     +                 ' particles;'
	   write(77,*) ' for each particle - GEANT number of particle,'
	   write(77,*) '                     ',
     +                 'x,y,z components of momentum,'
	   write(77,*) '                     ',
     +                 'time shift from previous time'
	   write(77,*) '   '
	   write(77,*) 'Time - in sec, momentum - in MeV/c'
	   write(77,*) '   '
	   write(77,*) 'First event and full number of events:'
	   write(77,*) ievstart,nevents
	   write(77,*) '   '
	endif
	istartbb=0
	if(istart.eq.-1) then
	   if(i2bbs.eq.1)
     +        call bb(modebb,Qbb,levelE/1000.,EK,Zdbb,Adbb,istartbb)
	   istart=1
	   return
	endif
	istart=1
1000	npfull=0
	if(i2bbs.eq.1) then
	   tevst=0.
	   call bb(modebb,Qbb,levelE/1000.,EK,Zdbb,Adbb,istartbb)
	   if(chnuclide.eq.'Ca40')    call  Ar40low(levelE)
	   if(chnuclide.eq.'Ca46')    call  Ti46low(levelE)
	   if(chnuclide.eq.'Ca48')    call  Ti48low(levelE)
	   if(chnuclide.eq.'Ni58')    call  Fe58low(levelE)
	   if(chnuclide.eq.'Ge76')    call  Se76low(levelE)
	   if(chnuclide.eq.'Zn64')    call  Ni64low(levelE)
	   if(chnuclide.eq.'Zn70')    call  Ge70low(levelE)
	   if(chnuclide.eq.'Se74')    call  Ge74low(levelE)
	   if(chnuclide.eq.'Se82')    call  Kr82low(levelE)
	   if(chnuclide.eq.'Sr84')    call  Kr84low(levelE)
	   if(chnuclide.eq.'Zr94')    call  Mo94low(levelE)
	   if(chnuclide.eq.'Zr96')    call  Mo96low(levelE)
	   if(chnuclide.eq.'Mo92')    call  Zr92low(levelE)
	   if(chnuclide.eq.'Mo100')   call Ru100low(levelE)
	   if(chnuclide.eq.'Ru96')    call  Mo96low(levelE)
	   if(chnuclide.eq.'Ru104')   call Pd104low(levelE)
	   if(chnuclide.eq.'Cd106')   call Pd106low(levelE)
	   if(chnuclide.eq.'Cd108')   call Pd108low(levelE)
	   if(chnuclide.eq.'Cd114')   call Sn114low(levelE)
	   if(chnuclide.eq.'Cd116')   call Sn116low(levelE)
	   if(chnuclide.eq.'Sn112')   call Cd112low(levelE)
	   if(chnuclide.eq.'Sn122')   call Te122low(levelE)
	   if(chnuclide.eq.'Sn124')   call Te124low(levelE)
	   if(chnuclide.eq.'Te120')   call Sn120low(levelE)
	   if(chnuclide.eq.'Te128')   call Xe128low(levelE)
	   if(chnuclide.eq.'Te130')   call Xe130low(levelE)
	   if(chnuclide.eq.'Xe136')   call Ba136low(levelE)
	   if(chnuclide.eq.'Ce136')   call Ba136low(levelE)
	   if(chnuclide.eq.'Ce138')   call Ba138low(levelE)
	   if(chnuclide.eq.'Ce142')   call Nd142low(levelE)
	   if(chnuclide.eq.'Nd148')   call Sm148low(levelE)
	   if(chnuclide.eq.'Nd150')   call Sm150low(levelE)
	   if(chnuclide.eq.'Dy156')   call Gd156low(levelE)
	   if(chnuclide.eq.'Dy158')   call Gd158low(levelE)
	   if(chnuclide.eq.'W180')    call Hf180low(levelE)
	   if(chnuclide.eq.'W186')    call Os186low(levelE)
	   if(chnuclide.eq.'Os184')   call W184low(levelE)
	   if(chnuclide.eq.'Os192')   call Pt192low(levelE)
	   if(chnuclide.eq.'Pt190')   call Os190low(levelE)
	   if(chnuclide.eq.'Pt198')   call Hg198low(levelE)
	   if(chnuclide.eq.'Bi214')   then
	      call At214low(0)
	      npfull0=npfull
	      call at214(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	   endif
	   if(chnuclide.eq.'Pb214')   then
	      call Po214low(0)
	      npfull0=npfull
	      call po214(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	   endif
	   if(chnuclide.eq.'Po218')   then
	      call Rn218low(0)
	      npfull0=npfull
	      call rn218(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	      npfull0=npfull
	      call po214(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	   endif
	   if(chnuclide.eq.'Rn222')   then
	      call Ra222low(0)
	      npfull0=npfull
	      call ra222(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	      npfull0=npfull
	      call rn218(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	      npfull0=npfull
	      call po214(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	   endif
	end if
	if(i2bbs.eq.2) then
	   if(chnuclide.eq.'Ac228')   call ac228(0.,tdnuc)
	   if(chnuclide.eq.'Am241')   call am241(0.,tdnuc)
	   if(chnuclide.eq.'Ar39')    call ar39(0.,tdnuc)
	   if(chnuclide.eq.'Ar42')    call ar42(0.,tdnuc)
	   if(chnuclide.eq.'As79')    call as79(0.,tdnuc)
	   if(chnuclide.eq.'Bi207')   call bi207(0.,tdnuc)
	   if(chnuclide.eq.'Bi208')   call bi208(0.,tdnuc)
	   if(chnuclide.eq.'Bi210')   call bi210(0.,tdnuc)
	   if(chnuclide.eq.'Bi212')   then
	      call bi212(0.,tdnuc)
	      npfull0=npfull
	      if(npgeant(1).ne.47) then
	         call po212(0.,tdnuc1)
	         ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	      endif
	   endif
	   if(chnuclide.eq.'Bi214')   then
	      call bi214(0.,tdnuc)
	      npfull0=npfull
	      if(npgeant(1).ne.47) then
	         call po214(0.,tdnuc1)
	         ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	      endif
	   endif
	   if(chnuclide.eq.'Ca48')   then
	      call ca48(0.,tdnuc)
	      npfull0=npfull
	      call sc48(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	   endif
	   if(chnuclide.eq.'C14')     call c14(0.,tdnuc)
	   if(chnuclide.eq.'Cd113')   call cd113(0.,tdnuc)
	   if(chnuclide.eq.'Co60')    call co60(0.,tdnuc)
	   if(chnuclide.eq.'Cs136')   call cs136(0.,tdnuc)
	   if(chnuclide.eq.'Cs137')   call cs137(0.,tdnuc)
	   if(chnuclide.eq.'Eu147')   call eu147(0.,tdnuc)
	   if(chnuclide.eq.'Eu152')   call eu152(0.,tdnuc)
	   if(chnuclide.eq.'Eu154')   call eu154(0.,tdnuc)
	   if(chnuclide.eq.'Gd146')   call gd146(0.,tdnuc)
	   if(chnuclide.eq.'Hf182')   call hf182(0.,tdnuc)
	   if(chnuclide.eq.'I126')    call i126(0.,tdnuc)
	   if(chnuclide.eq.'I133')    call i133(0.,tdnuc)
	   if(chnuclide.eq.'I134')    call i134(0.,tdnuc)
	   if(chnuclide.eq.'I135')    call i135(0.,tdnuc)
	   if(chnuclide.eq.'K40')     call k40(0.,tdnuc)
	   if(chnuclide.eq.'K42')     call k42(0.,tdnuc)
	   if(chnuclide.eq.'Kr81')    call kr81(0.,tdnuc)
	   if(chnuclide.eq.'Kr85')    call kr85(0.,tdnuc)
	   if(chnuclide.eq.'Mn54')    call mn54(0.,tdnuc)
	   if(chnuclide.eq.'Na22')    call na22(0.,tdnuc)
	   if(chnuclide.eq.'P32')     call p32(0.,tdnuc)
	   if(chnuclide.eq.'Pa234m')  call pa234m(0.,tdnuc)
	   if(chnuclide.eq.'Pb210')   call pb210(0.,tdnuc)
	   if(chnuclide.eq.'Pb211')   call pb211(0.,tdnuc)
	   if(chnuclide.eq.'Pb212')   call pb212(0.,tdnuc)
	   if(chnuclide.eq.'Pb214')   call pb214(0.,tdnuc)
	   if(chnuclide.eq.'Ra228')   call ra228(0.,tdnuc)
	   if(chnuclide.eq.'Rb87')    call rb87(0.,tdnuc)
	   if(chnuclide.eq.'Rh106')   call rh106(0.,tdnuc)
	   if(chnuclide.eq.'Sb125')   call sb125(0.,tdnuc)
	   if(chnuclide.eq.'Sb126')   call sb126(0.,tdnuc)
	   if(chnuclide.eq.'Sb133')   call sb133(0.,tdnuc)
	   if(chnuclide.eq.'Sr90')    call sr90(0.,tdnuc)
	   if(chnuclide.eq.'Ta182')   call ta182(0.,tdnuc)
	   if(chnuclide.eq.'Te133')   call te133(0.,tdnuc)
	   if(chnuclide.eq.'Te133m')  call te133m(0.,tdnuc)
	   if(chnuclide.eq.'Te134')   call te134(0.,tdnuc)
	   if(chnuclide.eq.'Th234')   call th234(0.,tdnuc)
	   if(chnuclide.eq.'Tl207')   call tl207(0.,tdnuc)
	   if(chnuclide.eq.'Tl208')   call tl208(0.,tdnuc)
	   if(chnuclide.eq.'Xe129m')  call xe129m(0.,tdnuc)
	   if(chnuclide.eq.'Xe131m')  call xe131m(0.,tdnuc)
	   if(chnuclide.eq.'Xe133')   call xe133(0.,tdnuc)
	   if(chnuclide.eq.'Xe135')   call xe135(0.,tdnuc)
	   if(chnuclide.eq.'Y88')     call y88(0.,tdnuc)
	   if(chnuclide.eq.'Y90')     call y90(0.,tdnuc)
	   if(chnuclide.eq.'Zn65')    call zn65(0.,tdnuc)
	   if(chnuclide.eq.'Zr96')    then
	      call zr96(0.,tdnuc)
	      npfull0=npfull
	      call nb96(0.,tdnuc1)
	      ptime(npfull0+1)=ptime(npfull0+1)+tdnuc1
	   endif
	   tevst=tdnuc
	   if(chnuclide.eq.'Artificial') then
	      tevst=0.
	      do j=1,nartparts
	         if(chart(j).eq.'Be') then
	            call beta(artQb(j),artZd(j),arttdelay(j),
     +                      artthalf(j),t)
	         elseif(chart(j).eq.'Pi') then
	            call pair(artQb(j),arttdelay(j),artthalf(j),t)
	         else
	            np=nartnpg(j)
                    call particle(np,artemin(j),artemax(j),arttmin(j),
     +                            arttmax(j),artfmin(j),artfmax(j),
     +                            arttdelay(j),artthalf(j),t)
	         endif
	      enddo
	   endif
	   if(chnuclide.eq.'Compton') then
	      tevst=0.
	      call compton(artemin(1),artemax(1),arttmin(1),arttmax(1),
     +                     artfmin(1),artfmax(1))
	   endif
	   if(chnuclide.eq.'Moller') then
	      tevst=0.
	      call moller(artemin(1),artemax(1),arttmin(1),arttmax(1),
     +                    artfmin(1),artfmax(1),artQb(1))
	   endif
	   if(chnuclide.eq.'E+E- external') then
	      tevst=0.
	      call pairext(artemin(1),artemax(1),arttmin(1),arttmax(1),
     +                     artfmin(1),artfmax(1),artZd(1))
	   endif
	endif
	if(chfile.ne.'no file') then
	   write(77,6) icurrent,tevst,npfull
6	   format(i8,g13.6,i4)
	   do j=1,npfull
	      write(77,7) npgeant(j),(pmoment(k,j),k=1,3),ptime(j)
7	      format(i3,3g14.6,g13.6)
	   enddo
	endif
	if(icurrent.ne.nevents) return
c	call rdmout(irndmfin)
c	print *,'final random integer = ',irndmfin
	print *,'toallevents=',toallevents
	return
	end

c***********************************************************************

c***********************************************************************
c****************** Section of brief GENBB history *********************
c***********************************************************************
c                Don't be afraid of perfectness - you'll never reach it.
c                                                          Salvador Dali
c***********************************************************************
c F.Laplanche, 1990:
c     First version of GENBB:
c     (1) ZEBRA organization for output file;
c     (2) emission of electron, gamma, alpha particles; beta decay;
c     (3) 2b2n and 2b0n decay of 100-Mo to ground state of 100-Ru;
c     (4) approximate models of decay of 208-Tl, 212-Bi, 214-Bi and 214-Pb;
c     (5) Compton, double Compton and Moller scattering.
c     Unpublished.
c V.I.Tretyak, November 1991:
c     Correct algorithm for 2b2n electron energies.
c     On the basis of the TRACK program:
c     Yu.G.Zdesenko, V.I.Tretyak, "Calculation of angular and energy distributions 
c     of electrons passed through matter by Monte Carlo method (the TRACK program)", 
c     preprint KINR 86-43, Kiev, 1986;
c     V.I.Tretyak, "Monte Carlo algorithms in simulation of 2beta decay and passage 
c     of electrons through matter", preprint KINR 92-8, Kiev, 1992.
c V.I.Tretyak, August 1992:
c     Models of decay for 40-K, 60-Co, 137-Cs + 137m-Ba, 207-Tl, 208-Tl,
c     210-Bi, 211-Pb, 212-Bi, 212-Pb, 214-Bi, 214-Pb, 228-Ac, 234m-Pa in full
c     accordance with "Table of Isotopes", ed. by C.M.Lederer, 7th ed., 1978.
c     In models were introduced:
c     (1) possibility to emit K-conversion electron and e+e- pair for all
c         transitions in nuclear deexcitation process;
c     (2) Coulomb correction factor for the shape of energy spectra in beta-
c         or beta+ decay.
c     V.I.Tretyak, "Models of decay of natural radioactive nuclides",
c     note NEMO 2/92, 1992, 43 p.
c V.I.Tretyak, August 1993:
c     (1) models of decay for 22-Na, 88-Y, 90-Sr, 90-Y, 207Bi + 207m-Pb in
c         accordance with "Table of Isotopes";
c     (2) double beta decay of 48-Ca (up to the 2.421 MeV 2_2+ excited level of
c         daughter nucleus), 76-Ge (1.216 MeV 2_2+), 82-Se (1.475 MeV 2_2+),
c         96-Zr (1.626 MeV 2_3+), 100-Mo (1.741 MeV 0_2+), 116-Cd (2.225 MeV
c         2_3+), 136-Xe (1.579 MeV 0_1+), 150-Nd (1.256 MeV 0_2+);
c     (3) 9 modes of double beta decay: 0n(mn)[2n], 0n(rc)[2n], 0n(rc)[N*],
c         2n[2n], 0nM1[2n], 0nM2[2n] for 0+ - 0+ transitions and 0n(rc)[2n],
c         0n(rc)[N*], 2n[2n=N*] for 0+ - 2+ transitions.
c         Primakoff-Rosen approximation was used for theoretical distributions.
c     V.I.Tretyak, "Current possibilities of events generation in GENBB code",
c     note NEMO 6/93, 1993, 20 p.
c V.I.Tretyak, November-December 1995:
c     (1) Primakoff-Rosen approximation is not used any more. It gives
c         possibility to generate correctly energy spectra not only for
c         2b- but also for 2b+ and eb+ decayers;
c     (2) 4 new double beta processes: 0nueb+, 2nueb+, 0nu2K, 2nu2K;
c     (3) double beta decay of 58-Ni (up to 2.421 MeV 2_2+ level of 48-Ti),
c         74-Se (1.204 MeV 2_2+), 92-Mo (1.383 MeV 0_1+),
c         94-Zr (0.871 MeV 2_1+), 106-Cd (1.134 MeV 0_1+),
c         114-Cd (0 MeV), 148-Nd (1.455 MeV 2_2+);
c     (4) model of decay of 207-Bi (with 207m-Pb) was improved: L and
c         M conversion electrons, L and M X rays, and K and L Auger
c         electrons are emitted in addition;
c     (5) models of decay of 106-Rh and 208-Bi in accordance with "Table
c         of Isotopes";
c     (6) information about time evolution of decay of natural radioactive
c         nuclides was introduced taking into account the non-zero time of
c         life of excited nuclear levels;
c     (7) subroutines for generation of Compton and Moller scattering
c         were rewritten using the GEANT algorithms;
c     (8) GENBB can produce the output file with generated events or
c         can be used as subroutine inside the main simulation program;
c     (9) ZEBRA structure was removed. Output file (if asked) is written
c         in human eye-seen format. Size of such file is 30-90% of
c         ZEBRA file depending on type of generated events.
c     Unpublished.
c V.I.Tretyak, June 1996:
c     (1) double beta decay of 130-Te (up to level 0.536 MeV 2_1+ of
c         130-Xe);
c     (2) models of decay for 146-Gd, 147-Eu, 182-Hf and 182-Ta in
c         accordance with "Table of Isotopes".
c     Unpublished.
c V.I.Tretyak, November 1996:
c     (1) improved algorithm for generation of double beta events
c         with restricted electrons energy sum;
c     (2) models of decay for 152-Eu and 154-Eu in accordance with
c         "Table of Isotopes", 8th ed., 1996 and NDS;
c     (3) possibility of emission of all GEANT particles (particle's
c         number = 1-32 and 45-50).
c     R.Arnold and V.I.Tretyak, "The NEMO 3 simulation program: Current
c     status", preprint CRN 97-01, 1997, 27 p.
c V.I.Tretyak, August 1997:
c     (1) model of decay for 133-Xe in accordance with TOI-8 (1996).
c     Unpublished.
c V.I.Tretyak, March-May 1998:
c     (1) corrected algorithm for generation of double beta events
c         with restricted electrons energy sum;
c     (2) subroutine for e+e- pair creation by external gamma quanta is
c         rewritten in accordance with GEANT algorithms;
c     (3) angular correlation between conversion electrons (1064 and
c         570 keV) in 207-Bi;
c     (4) models of decay for 54-Mn and beta decay of Ca48+Sc48 and
c         Zr96+Nb96 in accordance with TOI-8, 1996 and NDS;
c     (5) 0nubb decay with Majoron with spectral index = 7.
c V.I.Tretyak, September-October 2002:
c     (1) model of decay for 136-Cs in accordance with TOI-8, 1996 and 
c         NDS, 2002;
c     (2) models of decay of 134-Te (NDS, 1994), 134-I (NDS, 1994) and 
c         135-Xe (NDS, 1998);
c     (3) the program was renamed from GENBB to DECAY0.
c V.I.Tretyak, November-December 2003:
c     (1) models of decay for 126-I and 126-Sb in accordance with NDS, 
c         2002;
c     (2) improvement of the model for 40-K (in accordance with ENSDF, 
c         2002); update of the model for 133-Xe (NDS, 1995);
c     (3) models of decay for 133-Sb, 133-Te, 133m-Te and 133-I (NDS, 1995).
c V.I.Tretyak, February 2004:
c     (1) double beta decay of 64-Zn (O MeV), 70-Zn (0 MeV),
c         108-Cd (0 MeV), 120-Te (up to 1.171 MeV 2_1+), 
c         128-Te (0.443 MeV 2_1+).
c V.I.Tretyak, October 2004:
c     (1) model of decay of 79-As + 79m-Se in accordance with NDS, 2002.
c     (2) 0nubb decay with Majoron with spectral index = 2 (bulk Majoron 
c         of Mohapatra).
c V.I.Tretyak, April-May 2005:
c     (1) some changes for correct work under Linux system (mainly two 
c         operators "save" in proper places). Thanks to O.Chkvorets and
c         K.Zuber&H.Kiel for their questions, and R.Arnold for genbb.car
c         where I found solution;
c     (2) schemes of 208-Bi, 208-Tl, 214-Po and 214-Bi were updated to 
c         the current status of ENSDF (that corresponds to Nucl. Data 
c         Sheets 1986 for 208-Bi and 208-Tl, and Nucl. Data Sheets 2003 
c         for 214-Po and 214-Bi).
c V.I.Tretyak, September-October 2005:
c     (1) update of 207-Bi decay scheme to the NNDC status of 9.09.2005
c         and angular correlation for gammas and conversion electrons
c         emitted in 1064-570 keV cascade (instead of only for 2 electrons).
c V.I.Tretyak, March-April 2006:
c     (1) models of decay of 39-Ar, 42-Ar, 42-K, 113-Cd;
c     (2) double beta decay of:
c         130-Te to excited states of 130-Xe (2_2+ 1.122 MeV, 0_1+ 1.794 MeV).
c V.I.Tretyak, October-December 2006:
c     (1) update of 60-Co scheme to NDS'2003 and introduction of angular 
c         correlation for gammas 1173 and 1333 keV (together with L.Pandola);
c     (2) schemes of decay of 14-C and 32-P were added;
c     (3) update to the last NDS issues or current ENSDF status of the 
c         following nuclei: 22-Na, 40-K, 42-K, 88-Y, 90-Y, 90-Sr, 137-Cs,
c         207-Tl, 210-Bi, 211-Pb, 234m-Pa;
c     (4) change of beta spectra shapes from allowed to non-allowed for:
c         14-C, 22-Na, 32-P, 39-Ar, 40-K, 42-K, 42-Ar, 60-Co, 88-Y, 90-Y,
c         90-Sr, 113-Cd, 137-Cs, 207-Tl, 210-Bi, 234m-Pa;
c     (5) double beta decay of 106-Cd to excited levels of 106-Pd
c         2_3+ 1.562 MeV, 0_2+ 1.706 MeV;
c     (6) RNDM (CERN) random number generator was changed to RANLUX (CERN);
c         thanks to proposal of Victor Tretyak;
c     (7) approximate electron capture from K, L or M shells in EC of 152-Eu.
c V.I.Tretyak, March 2007:
c     (1) update of 214-Pb to NDS 76(1995)127, and conversion from K, L, M shells
c         is introduced;
c     (2) model of 65-Zn in accordance with NDS 69(1993)209 and NNDC online 
c         corrections on 28.03.2007;
c     (3) update of 54-Mn to NDS 107(2006)1393 (in fact, no changes).
c V.I.Tretyak, July-August 2007:
c     (1) corrected values of binding energies of electron on K shell for
c         2K and Kb+ decays of 64-Zn, 74-Se, 92-Mo, 108-Cd and 120-Te;
c     (2) correction of time delay in 137-Cs (thanks to F.Cappella);
c     (3) models of 87-Rb, 210-Pb, 228-Ra and 234-Th in accordance with 
c         last NDS issues and ENSDF files at NNDC site;
c     (4) corrected beta shapes for 22-Na and 88-Y.
c V.I.Tretyak, November-December 2007:
c     (1) corrections in deexcitation of 2148 keV level of 214-Bi 
c         (thanks to V.I.Tretyak-JINR); conversion to L amd M electrons
c         in addition to K (if ratios were experimentally measured);
c     (2) schemes of decay of 129m-Xe and 131m-Xe (last issues of NDS and 
c         ENSDF on NNDC site on 13.11.2007);
c     (3) update of sequence of single beta decays of 48-Ca + 48-Sc and
c         96-Zr + 96-Nb to the last NDS and ENSDF at NNDC site;
c     (4) correction of beta shapes to 1fnu shape for some beta branches
c         of 152-Eu and 154-Eu;
c     (5) double beta decays of beta/alpha decaying nuclides in 222-Rn chain:
c         214-Pb (with subsequent alpha decay of 214-Po),
c         214-Bi (with subsequent alpha decay of 214-At),
c         218-Po (with subsequent alpha decays of 218-Rn + 214-Po),
c         222-Rn (with subsequent alpha decays of 222-Ra + 218-Rn + 214-Po);
c     (6) schemes of 214-At, 218-Rn, 222-Ra (last NDS and ENSDF/NNDC 
c         on 9.12.2007);
c     (7) schemes of decay of 81-Kr and 85-Kr (last issues of NDS and 
c         ENSDF on NNDC site on 9.12.2007).
c V.I.Tretyak, June 2008:
c     (1) 2b decays of 180-W and 186-W are added.
c V.I.Tretyak, September 2008:
c     (1) decay of the 740 keV 0+ level of 150-Sm is corrected in accordance 
c         with ToI'1998 and NDS 75(1995)827.
c V.I.Tretyak, December 2008:
c     (1) 2b decays of 136-Ce, 138-Ce, 142-Ce are added;
c     (2) 2b decay of 136-Xe is possible up to level of 2400 keV (instead
c         of 1579 keV);
c     (3) 2b decay of 84-Sr;
c     (4) 2b decay of 112-Sn (7 levels up to level 0+_3 1871 keV), 122-Sn and 
c         124-Sn (9[10] levels up to level 2+_5 2182 keV).
c V.I.Tretyak, January-February 2009:
c     (1) corrected coefficients in beta shape of 137-Cs (5.6% branch 1176 keV);
c     (2) updated scheme of 208-Tl decay (to NDS 108(2007)1583); KLM conversion;
c         emission of two X rays after conversion from K shell;
c     (3) 2b2nu decay with bosonic neutrinos, 0+ -> 0+ and 0+ -> 2+ transitions,
c         HSD (high state dominance) hypothesis; formulae are from:
c         A.S.Barabash et al., NPB 783(2007)90.
c V.I.Tretyak, May 2009:
c     (1) angular correlation between 559 and 563 keV gamma quanta in 2b
c         decay of 76-Ge to 1122 keV level of 76-Se (accepted from L.Pandola, 2006);
c     (2) angular correlation between 591 and 540 keV gamma quanta in 2b
c         decay of 100-Mo to 1130 keV level of 100-Ru;
c     (3) 5 excited levels of 96-Mo (2096, 2426, 2623, 2700 and 2713 keV) are added
c         for 2b decay of 96-Zr; scheme of 96-Mo decay is updated to NNDC on 
c         19.05.2009 and NDS 109(2008)2501; 2713 keV level is supposed as 2+;
c     (4) 2b decays of 96-Ru (up to level 2713 keV of 96-Mo) and 104-Ru
c         (g.s. and the 1st excited level of 104-Pd) are added; decay schemes
c         of daughter nuclei - in accordance with NNDC on 19.05.2009;
c         2713 keV level is supposed as 2+.
c V.I.Tretyak, February 2010:
c     (1) model of Sb-125 decay (NDS 86(1999)955 and NNDC on 7.02.2010).
c V.I.Tretyak, June-July 2010:
c     (1) 2b0nu decay with right-handed currents related with eta term:
c         approximate scheme and scheme with specific NMEs;
c     (2) eb+/2e decays of 190-Pt to g.s. and 5 excited levels (up to 0+ at 
c         1382 keV) of 190-Os in accordance with NDS 99(2003)275 and NNDC on 
c         30.07.2010;
c     (3) 2b- decays of 198-Pt to g.s. and excited level 412 keV of 198-Hg
c         in accordance with NDS 110(2009)2533 and NNDC on 30.07.2010.
c V.I.Tretyak, December 2010:
c     (1) Model of 2b decay of 156-Dy (NNDC & NDS 99(2003)753); 
c         thanks Fabio Cappella for correction;
c     (2) Model of 2b decay of 158-Dy (NNDC & NDS 101(2004)325).
c V.I.Tretyak, January 2011:
c     (1) Model of decay of 241-Am (NNDC & NDS 107(2006)3323).
c V.I.Tretyak, June 2012:
c     (1) eb+/2e decays of 184-Os to g.s. and 7 excited levels (up to 2+ at 
c         1431 keV) of 184-W in accordance with NDS 111(2010)275 and NNDC on 
c         21.06.2012;
c     (2) 2b- decays of 192-Os to g.s. and excited level 317 keV of 192-Pt
c         in accordance with NDS 84(1998)717 and NNDC on 21.06.2012.
c V.I.Tretyak, August 2012:
c     (1) possibilities to generate forbidden beta decays in 42-K with new
c         experimental correction factors are added (thanks to discussion
c         with A. Lubashevskiy).
c V.I.Tretyak, October 2013:
c     (1) 2e decay of 40-Ca to g.s. of 40-Ar; 2b- decay of 46-Ca to g.s. and
c         excited level 889 keV of 46-Ti in accordance with NNDC on 21.10.2013.
c V.I.Tretyak, April 2016:
c     (1) change of Qbb values to those in the last atomic mass tables:  
c         M. Wang et al., Chinese Phys. C 36(2012)1603;
c     (2) possibility of initial scrolling of (0,1) random number generator
c         (thanks to L. Pandola, D. Chernyak and others for asking);
c     (3) return to older algorithm of energies generation in mode 4 
c         (2b2nu; faster and gives correct results);
c     (4) 2b2nu decay with Lorentz invariance violation (mode 19);
c     (5) 4b0nu decay (quadruple beta decay; mode 20).
c V.I.Tretyak, March 2017:
c     (1) update of Pa234m (1.159 m) decay scheme to NDS 108(2007)681.
c
c***********************************************************************

c***********************************************************************
c****************** Section of double beta decay ***********************
c***********************************************************************

c***********************************************************************

	subroutine bb(modebb,Qbb,Edlevel,EK,Zdbb,Adbb,istartbb)

c Subroutine for sampling the energies and angles of electrons in various
c modes of double beta decay without Primakoff-Rosen approximation.
c
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         common/const/pi,emass
c         common/enrange/ebb1,ebb2,toallevents
c         call bb(modebb,Qbb,Edlevel,EK,Zdbb,Adbb,istartbb)
c Input : modebb    - mode of double beta (- or +) decay:
c                     1  - 0nubb with neutrino mass, 0+ -> 0+,      2n;
c                     2  - 0nubb with rhc-lambda,    0+ -> 0+,      2n;
c                     3  - 0nubb with rhc-lambda,    0+ -> 0+, 2+,  N*;
c                     4  - 2nubb,                    0+ -> 0+,      2n;
c                     5  - 0nuM1bb (Majoron, SI=1),  0+ -> 0+,      2n;
c                          [SI - spectral index]
c                     6  - 0nuM3bb (Majoron, SI=3),  0+ -> 0+,      2n;
c                     7  - 0nubb with rhc-lambda,    0+ -> 2+,      2n;
c                     8  - 2nubb,                    0+ -> 2+,      2n, N*;
c                     9  - 0nuKb+                    0+ -> 0+, 2+;
c                     10 - 2nuKb+                    0+ -> 0+, 2+;
c                     11 - 0nu2K                     0+ -> 0+, 2+;
c                     12 - 2nu2K                     0+ -> 0+, 2+;
c                     13 - 0nuM7bb (Majoron, SI=7)   0+ -> 0+,      2n;
c                     14 - 0nuM2bb (Majoron, SI=2)   0+ -> 0+,      2n;
c                     15 - 2nubb with bosonic nu's   0+ -> 0+;
c                     16 - 2nubb with bosonic nu's   0+ -> 2+;
c                     17 - 0nubb with rhc-eta        0+ -> 0+       simplified expression;
c                     18 - 0nubb with rhc-eta        0+ -> 0+       with specific NMEs;
c                     19 - 2nubb                     0+ -> 0+       with Lorentz violation;
c                     20 - 0nu4b                     0+ -> 0+       quadruple beta decay;
c         Qbb       - energy release in double beta process: difference
c                     between masses of parent and daughter atoms (MeV);
c         Edlevel   - energy of level of daughter nucleus to which transition
c                     occured;
c         EK        - binding energy of electron on K shell of parent atom (MeV)
c                     (for modebb=10 and 11);
c         Zdbb      - atomic number of daughter nucleus (Z>0 for b-b-
c                     and Z<0 for b+b+ and eb+ processes);
c         Adbb      - mass number of daughter nucleus
c         istartbb  - must be =0 for first call of bb for a given mode;
c         pi,emass  - 3.1415927 and electron rest mass (MeV);
c         ebb1,ebb2 - for modes with continuous distribution of sum of
c                     e-/e+ energies (4,5,6,8,10,13,14,15,16), left and right
c                     limits for E sum in which events will be generated;
c Output: tevst               - time of event's start (sec) (as supposed,
c                               =0 here);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (1 - gamma, 2 - e+, 3 - e-);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum
c                               (MeV/c);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec)
c                               (as supposed, =0 here);
c         toallevents         - coefficient to calculate the corresponding
c                               number of bb events in full range of energies:
c                               full_number=generated_number*toallevents
c                               (for modes 4,5,6,8,10 and 13).
c
c V.I.Tretyak, 26.11.1995; 17.02.2009; 3.04.2016.

	double precision dens,denf
	character chhelp*4,chfile*40
	external dshelp1
	external fe12_mod4,  fe12_mod5,  fe12_mod6,  fe12_mod8,
     +         fe12_mod13, fe12_mod14, fe12_mod15, fe12_mod16,
     +         fe12_mod19, 
     +         fe2_mod4,   fe2_mod5,   fe2_mod6,   fe2_mod8,
     +         fe2_mod13,  fe2_mod14,  fe2_mod15,  fe2_mod16,
     +         fe2_mod19,  
     +         fe1_mod10
	dimension spthe1(4300),spthe2(4300)
      save spthe1,spmax
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                ptime(100)
      common/const/pi,emass,datamass(50)
	common/enrange/ebb1,ebb2,toallevents,lhelp,chhelp
	common/denrange/dens,denf,mode
	common/helpbb/Zd,Ad,e0,e1
	common/eta_nme/chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,
     +               chip_P,chip_R
	twopi=2.*pi
	Zd=Zdbb
	Ad=Adbb
	if(Zdbb.ge.0.)                   e0=Qbb-Edlevel
	if(Zdbb.lt.0.)                   e0=Qbb-Edlevel-4.*emass
	if(modebb.eq. 9.or.modebb.eq.10) e0=Qbb-Edlevel-EK-2.*emass
	if(modebb.eq.11.or.modebb.eq.12) e0=Qbb-Edlevel-2.*EK
	if(modebb.eq.9) then
c fixed energies of e+ and X-ray; no angular correlation
	   call particle(2,e0,e0,0.,pi,0.,twopi,0.,0.,t)
	   call particle(1,EK,EK,0.,pi,0.,twopi,0.,0.,t)
	   return
	endif
	if(modebb.eq.11) then
c one gamma and two X-rays with fixed energies; no angular correlation
	   call particle(1,e0,e0,0.,pi,0.,twopi,0.,0.,t)
	   call particle(1,EK,EK,0.,pi,0.,twopi,0.,0.,t)
	   call particle(1,EK,EK,0.,pi,0.,twopi,0.,0.,t)
	   return
	endif
	if(modebb.eq.12) then
c fixed energies of two X-rays; no angular correlation
	   call particle(1,EK,EK,0.,pi,0.,twopi,0.,0.,t)
	   call particle(1,EK,EK,0.,pi,0.,twopi,0.,0.,t)
	   return
	endif
	if(istartbb.ne.0) go to 1
c calculate the theoretical energy spectrum of first particle with step
c of 1 keV and find its maximum
	print *,'wait, please: calculation of theoretical spectrum'
	if(ebb1.lt.0.) ebb1=0.
	if(ebb2.gt.e0) ebb2=e0
	spmax=-1.
	b2amin=+1.e20 ! coefficients in angular correlation 
	b2amax=-1.e20 ! for eta-h term of 2b0nu
	relerr=1.e-4
	do i=1,int(e0*1000.)
	   e1=i/1000.
	   e1h=e1
	   spthe1(i)=0.
	   if(modebb.eq.1)  spthe1(i)=fe1_mod1(e1h)
	   if(modebb.eq.2)  spthe1(i)=fe1_mod2(e1h)
	   if(modebb.eq.3)  spthe1(i)=fe1_mod3(e1h)
	   elow=amax1(1.e-4,ebb1-e1+1.e-4)
	   ehigh=amax1(1.e-4,ebb2-e1+1.e-4)
c	   print *,'e1,elow,ehigh=',e1,elow,ehigh
	   if(modebb.eq.4.and.e1.lt.e0)  spthe1(i)=
cc     +      gauss(fe12_mod4,1.e-4,e0-e1+1.e-4,relerr)
c correction for restricted energy sum (ebb1<=e1+e2<=ebb2)
     +        gauss(fe12_mod4,elow,ehigh,relerr)
	   if(modebb.eq.5.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod5,elow,ehigh,relerr)
	   if(modebb.eq.6.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod6,elow,ehigh,relerr)
	   if(modebb.eq.7)  spthe1(i)=fe1_mod7(e1h)
	   if(modebb.eq.8.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod8,elow,ehigh,relerr)
	   if(modebb.eq.10) spthe1(i)=fe1_mod10(e1h)
	   if(modebb.eq.13.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod13,elow,ehigh,relerr)
	   if(modebb.eq.14.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod14,elow,ehigh,relerr)
	   if(modebb.eq.15.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod15,elow,ehigh,relerr)
	   if(modebb.eq.16.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod16,elow,ehigh,relerr)
	   if(modebb.eq.17)  spthe1(i)=fe1_mod17(e1h)
	   if(modebb.eq.18)  spthe1(i)=fe1_mod18(e1h)
	   if(modebb.eq.19.and.e1.lt.e0)  spthe1(i)=
     +        gauss(fe12_mod19,elow,ehigh,relerr)
	   if(spthe1(i).gt.spmax) spmax=spthe1(i)
c	   print *,'spthe1=',spthe1(i)
	enddo
	do i=int(e0*1000.)+1,4300
	   spthe1(i)=0.
	enddo
c	open(unit=33,file='th-e1-spectrum.dat')
c	do i=1,4300
c	   write(33,*) i,spthe1(i)
c	enddo
	toallevents=1.
	if(modebb.eq. 4.or.modebb.eq. 5.or.modebb.eq. 6.or.
     +   modebb.eq. 8.or.modebb.eq.13.or.modebb.eq.14.or.
     +   modebb.eq.15.or.modebb.eq.16.or.modebb.eq.19) then
	   mode=modebb
	   dens=0.d0
	   denf=e0
	   r1=dgmlt1(dshelp1,0.d0,denf,8,8,d_el)
	   dens=ebb1
	   denf=ebb2
	   r2=dgmlt1(dshelp1,0.d0,denf,8,8,d_el)
	   toallevents=r1/r2
	elseif(modebb.eq.10) then
	   toallevents=gauss(fe1_mod10,1.e-4,e0+1.e-4,relerr)
     +              /gauss(fe1_mod10,ebb1+1.e-4,ebb2+1.e-4,relerr)
	endif
	if(modebb.eq.20) then
	   emax=e0/4.
	   tmax=emax/emass
	   pmax=sqrt(tmax*(tmax+2.))
	   spmax=((tmax+1.)*pmax*fermi(Zd,emax))**4
c	   print *,'emax,spmax=',emax,spmax
	endif
	istartbb=1
	print *,'starting the generation'
1	if(modebb.eq.20) then
	   t0=e0/emass
4	   t1=rnd1(d)*t0
	   t2=rnd1(d)*t0
	   t3=rnd1(d)*t0
	   t4=t0-t1-t2-t3
c	   print *,'t1,t2,t3,t4=',t1,t2,t3,t4
	   if(t4.lt.0.) goto 4
	   p1=sqrt(t1*(t1+2.))
	   p2=sqrt(t2*(t2+2.))
	   p3=sqrt(t3*(t3+2.))
	   p4=sqrt(t4*(t4+2.))
	   r=(t1+1.)*p1*fermi(Zd,t1*emass)
     +    *(t2+1.)*p2*fermi(Zd,t2*emass)
     +    *(t3+1.)*p3*fermi(Zd,t3*emass)
     +    *(t4+1.)*p4*fermi(Zd,t4*emass)
c	   print *,'r,spmax=',r,spmax
	   rr=rnd1(d)*spmax
	   if(rr.gt.r) goto 4
c isotropical emission of 4 electrons
 	   call particle(3,t1*emass,t1*emass,0.,pi,0.,twopi,0.,0.,t)
 	   call particle(3,t2*emass,t2*emass,0.,pi,0.,twopi,0.,0.,t)
 	   call particle(3,t3*emass,t3*emass,0.,pi,0.,twopi,0.,0.,t)
 	   call particle(3,t4*emass,t4*emass,0.,pi,0.,twopi,0.,0.,t)
	   return
	endif
c sampling the energies: first e-/e+
c1	e1=e0*rnd1(d)
	if(modebb.ne.10) e1=ebb2*rnd1(d)
	if(modebb.eq.10) e1=ebb1+(ebb2-ebb1)*rnd1(d)
	k=nint(e1*1000.)
	if(k.lt.1) k=1
	if(spmax*rnd1(d).gt.spthe1(k)) go to 1
c second e-/e+ or X-ray
	if    (modebb.eq.1.or.modebb.eq.2.or.modebb.eq.3.or.
     +       modebb.eq.7.or.modebb.eq.17.or.modebb.eq.18) then
c modes with no emission of other particles beside of two e-/e+:
c energy of second e-/e+ is calculated
	   e2=e0-e1
	elseif(modebb.eq. 4.or.modebb.eq. 5.or.modebb.eq. 6.or.
     +       modebb.eq. 8.or.modebb.eq.13.or.modebb.eq.14.or.
     +       modebb.eq.15.or.modebb.eq.16.or.modebb.eq.19) then
c something else is emitted - energy of second e-/e+ is random
	re2s=amax1(0.,ebb1-e1)
	re2f=ebb2-e1

	f2max=-1.
	ke2s=max0(1,int(re2s*1000.))
	ke2f=int(re2f*1000.)
	do ke2=ke2s,ke2f
	   e2=ke2/1000.
c	   if(modebb.eq. 4) spthe2(ke2)=fe2_mod4(e2)
	   if(modebb.eq. 5) spthe2(ke2)=fe2_mod5(e2)
	   if(modebb.eq. 6) spthe2(ke2)=fe2_mod6(e2)
	   if(modebb.eq. 8) spthe2(ke2)=fe2_mod8(e2)
	   if(modebb.eq.13) spthe2(ke2)=fe2_mod13(e2)
	   if(modebb.eq.14) spthe2(ke2)=fe2_mod14(e2)
	   if(modebb.eq.15) spthe2(ke2)=fe2_mod15(e2)
	   if(modebb.eq.16) spthe2(ke2)=fe2_mod16(e2)
c	   if(modebb.eq.19) spthe2(ke2)=fe2_mod19(e2)
	   if(spthe2(ke2).gt.f2max) f2max=spthe2(ke2)
	enddo

cc	   if(modebb.eq.4)
cc     +        call tgold(0.,e0-e1,fe2_mod4,1.e-3,2,e2max,f2max)
	   if(modebb.eq.4)
     +      call tgold(re2s,re2f,fe2_mod4,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.5)
c     +        call tgold(re2s,re2f,fe2_mod5,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.6)
c     +        call tgold(re2s,re2f,fe2_mod6,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.13)
c     +        call tgold(re2s,re2f,fe2_mod13,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.14)
c     +        call tgold(re2s,re2f,fe2_mod14,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.8)
c     +        call tgold(re2s,re2f,fe2_mod8,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.15)
c     +        call tgold(re2s,re2f,fe2_mod15,1.e-3,2,e2max,f2max)
c	   if(modebb.eq.16)
c     +        call tgold(re2s,re2f,fe2_mod16,1.e-3,2,e2max,f2max)
	   if(modebb.eq.19)
     +        call tgold(re2s,re2f,fe2_mod19,1.e-3,2,e2max,f2max)
cc	print *,'e1,re2s,re2f=',e1,re2s,re2f
cc	print *,'tgold: e2max,f2max=',e2max,f2max
c	print *,'real f2max=',f2max
c	pause

c2	   e2=(e0-e1)*rnd1(d)
2	   e2=re2s+(re2f-re2s)*rnd1(d)
	   if(modebb.eq.4) fe2=fe2_mod4(e2)
	   if(modebb.eq.5) fe2=fe2_mod5(e2)
	   if(modebb.eq.6) fe2=fe2_mod6(e2)
	   if(modebb.eq.13) fe2=fe2_mod13(e2)
	   if(modebb.eq.14) fe2=fe2_mod14(e2)
	   if(modebb.eq.8) fe2=fe2_mod8(e2)
	   if(modebb.eq.15) fe2=fe2_mod15(e2)
	   if(modebb.eq.16) fe2=fe2_mod16(e2)
	   if(modebb.eq.19) fe2=fe2_mod19(e2)
	   if(f2max*rnd1(d).gt.fe2) go to 2
c	   allevents=allevents+1.
c	   if(e1+e2.lt.ebb1.or.e1+e2.gt.ebb2) go to 1
cc	   if(rnd1(d).lt.0.5) then
cc	      eh=e1
cc	      e1=e2
cc	      e2=eh
cc	   endif
	elseif(modebb.eq.10) then
c energy of X-ray is fixed; no angular correlation
c	   allevents=allevents+1.
c	   if(e1.lt.ebb1.or.e1.gt.ebb2) go to 1
	   call particle(2,e1,e1,0.,pi,0.,twopi,0.,0.,t)
	   call particle(1,EK,EK,0.,pi,0.,twopi,0.,0.,t)
	   return
	endif
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	b1=p1/(e1+emass)
	b2=p2/(e2+emass)
c sampling the angles with angular correlation
	a=1.
	b=-b1*b2
	c=0.
	if(modebb.eq.2) b=b1*b2
	if(modebb.eq.3) then
	   w1=e1+emass
	   w2=e2+emass
	   a=3.*(w1*w2+emass**2)*(p1**2+p2**2)
	   b=-p1*p2*((w1+w2)**2+4.*(w1*w2+emass**2))
	   c=2.*p1**2*p2**2
	endif
	if(modebb.eq.7) then
	   w1=e1+emass
	   w2=e2+emass
	   a=5.*(w1*w2+emass**2)*(p1**2+p2**2)-p1**2*p2**2
	   b=-p1*p2*(10.*(w1*w2+emass**2)+p1**2+p2**2)
	   c=3.*p1**2*p2**2
	endif
	if(modebb.eq.8) b=b1*b2/3.
	if(modebb.eq.15) then
	   a=9.*(e0-e1-e2)**2+21.*(e2-e1)**2
	   b=-b1*b2*(9.*(e0-e1-e2)**2-7.*(e2-e1)**2)
	endif
	if(modebb.eq.16) b=b1*b2/3.
	if(modebb.eq.17) b=b1*b2
	if(modebb.eq.18) then
	   et0=e0/emass+1. ! total energies in the units of electron mass
	   et1=e1/emass+1.
	   et2=e2/emass+1.
	   a1=(et1*et2-1.)*(et1-et2)**2/(2.*et1*et2)
	   a2=-2.*(et1-et2)**2/(9.*et1*et2)
	   a3=2.*(et1*et2-1.)/(81.*et1*et2)
	   r=3.107526e-3*Adbb**(1./3.)
	   rksi=3./137.036*Zdbb+r*et0
	   a4=8.*(et1*et2+1.)/(r**2*et1*et2)
	   a5=-8.*(rksi*(et1*et2+1.)-2.*r*et0)/(3.*r**2*et1*et2)
	   a6=2.*((rksi**2+4.*r**2)*(et1*et2+1.)-4.*rksi*r*et0)/
     +      (9.*r**2*et1*et2)
	   chi_1plus =chip_GT+3.*chip_F-6.*chip_T
	   chi_1minus=chip_GT-3.*chip_F-6.*chip_T
	   chi_2plus =chi_GTw+chi_Fw-chi_1minus/9.
	   a_eta=a1*chi_2plus**2+a2*chi_2plus*chi_1minus+a3*chi_1minus**2
     +        +a4*chip_R**2+a5*chip_R*chip_P+a6*chip_P**2
	   b_eta=(et1-et2)**2*chi_2plus**2/2.-4.*chi_1minus**2/81.
     +        +8.*(rksi*chip_P/6.-chip_R)**2/r**2-8.*chip_P**2/9.
	   if(a_eta.ne.0.) then
	      b=b_eta/a_eta*b1*b2
	   else
	      print *,'a_eta=0'
	   endif
	endif
	romaxt=a+abs(b)+c
3	phi1=twopi*rnd1(d)
	ctet1=1.-2.*rnd1(d)
	stet1=sqrt(1.-ctet1*ctet1)
	phi2=twopi*rnd1(d)
	ctet2=1.-2.*rnd1(d)
	stet2=sqrt(1.-ctet2*ctet2)
	ctet=ctet1*ctet2+stet1*stet2*cos(phi1-phi2)
	if(romaxt*rnd1(d).gt.a+b*ctet+c*ctet**2) go to 3
	npfull=npfull+1
	if(Zdbb.ge.0.) npgeant(npfull)=3
	if(Zdbb.lt.0.) npgeant(npfull)=2
	pmoment(1,npfull)=p1*stet1*cos(phi1)
	pmoment(2,npfull)=p1*stet1*sin(phi1)
	pmoment(3,npfull)=p1*ctet1
	ptime(npfull)=0.
	npfull=npfull+1
	if(Zdbb.ge.0.) npgeant(npfull)=3
	if(Zdbb.lt.0.) npgeant(npfull)=2
	pmoment(1,npfull)=p2*stet2*cos(phi2)
	pmoment(2,npfull)=p2*stet2*sin(phi2)
	pmoment(3,npfull)=p2*ctet2
	ptime(npfull)=0.
	return
	end

c***********************************************************************

	function fe1_mod1(e1)
c probability distribution for energy of first e-/e+ for modebb=1
c (0nu2b with m(nu), 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	fe1_mod1=0.
	if(e1.gt.e0) return
	e2=e0-e1
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe1_mod1=(e1+emass)*p1*fermi(Zdbb,e1)*
     +           (e2+emass)*p2*fermi(Zdbb,e2)
	return
	end

c***********************************************************************

	function fe1_mod2(e1)
c probability distribution for energy of first e-/e+ for modebb=2
c (0nu2b with rhc, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	fe1_mod2=0.
	if(e1.gt.e0) return
	e2=e0-e1
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe1_mod2=(e1+emass)*p1*fermi(Zdbb,e1)*
     +           (e2+emass)*p2*fermi(Zdbb,e2)*
     +           (e0-2.*e1)**2
	return
	end

c***********************************************************************

	function fe1_mod3(e1)
c probability distribution for energy of first e-/e+ for modebb=3
c (0nu2b with rhc, 0+ -> 0+ or 0+ -> 2+, N* mechanism)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	fe1_mod3=0.
	if(e1.gt.e0) return
	e2=e0-e1
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe1_mod3=p1*fermi(Zdbb,e1)*p2*fermi(Zdbb,e2)*
     +           (2.*p1**2*p2**2+9.*((e1+emass)*(e2+emass)+emass**2)*
     +           (p1**2+p2**2))
	return
	end

c***********************************************************************

	function fe12_mod4(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=4 (as tsimpr needs)
c (2nu2b, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod4=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod4=(e1+emass)*p1*fermi(Zdbb,e1)*
     +            (e2+emass)*p2*fermi(Zdbb,e2)*
     +            (e0-e1-e2)**5
	return
	end

	function fe2_mod4(e2)
c probability distribution for energy of second e-/e+ for modebb=4
c (2nu2b, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod4=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod4=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**5
	return
	end

c***********************************************************************

	function fe12_mod5(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=5 (as tsimpr needs)
c (0nu2b with Gelmini-Roncadelli Majoron (spectral index = 1),
c 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod5=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod5=(e1+emass)*p1*fermi(Zdbb,e1)*
     +            (e2+emass)*p2*fermi(Zdbb,e2)*
     +            (e0-e1-e2)
	return
	end

	function fe2_mod5(e2)
c probability distribution for energy of second e-/e+ for modebb=5
c (0nu2b with Gelmini-Roncadelli Majoron (spectral index = 1),
c 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod5=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod5=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)
	return
	end

c***********************************************************************

	function fe12_mod6(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=6 (as tsimpr needs)
c (0nu2b with massive vector etc. Majoron (spectral index = 3),
c 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod6=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod6=(e1+emass)*p1*fermi(Zdbb,e1)*
     +            (e2+emass)*p2*fermi(Zdbb,e2)*
     +            (e0-e1-e2)**3
	return
	end

	function fe2_mod6(e2)
c probability distribution for energy of second e-/e+ for modebb=6
c (0nu2b with massive vector etc. Majoron (spectral index = 3),
c 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod6=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod6=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**3
	return
	end

c***********************************************************************

	function fe1_mod7(e1)
c probability distribution for energy of first e-/e+ for modebb=7
c (0nu2b with rhc, 0+ -> 2+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	fe1_mod7=0.
	if(e1.gt.e0) return
	e2=e0-e1
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe1_mod7=p1*fermi(Zdbb,e1)*p2*fermi(Zdbb,e2)*
     +           ((e1+emass)*(e2+emass)+emass**2)*(p1**2+p2**2)
	return
	end

c***********************************************************************

	function fe12_mod8(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=8 (as tsimpr needs)
c (2nu2b, 0+ -> 2+, 2n or N* mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod8=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod8=(e1+emass)*p1*fermi(Zdbb,e1)*
     +            (e2+emass)*p2*fermi(Zdbb,e2)*
     +            (e0-e1-e2)**7*(e1-e2)**2
	return
	end

	function fe2_mod8(e2)
c probability distribution for energy of second e-/e+ for modebb=8
c (2nu2b, 0+ -> 2+, 2n or N* mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod8=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod8=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**7*(e1-e2)**2
	return
	end

c***********************************************************************

	function fe1_mod10(e1)
c probability distribution for energy of e+ for modebb=10 (2nueb+)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	fe1_mod10=0.
	if(e1.gt.e0) return
	p1=sqrt(e1*(e1+2.*emass))
	fe1_mod10=(e1+emass)*p1*fermi(Zdbb,e1)*(e0-e1)**5
	return
	end

c***********************************************************************

	function fe12_mod13(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=13 (as tsimpr needs)
c (0nu2b with Majoron with spectral index = 7, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod13=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod13=(e1+emass)*p1*fermi(Zdbb,e1)*
     +             (e2+emass)*p2*fermi(Zdbb,e2)*
     +             (e0-e1-e2)**7
	return
	end

	function fe2_mod13(e2)
c probability distribution for energy of second e-/e+ for modebb=13
c (0nu2b with Majoron with spectral index = 7, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod13=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod13=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**7
	return
	end

c***********************************************************************

	function fe12_mod14(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=14 (as tsimpr needs)
c (0nu2b with Mohapatra Majoron with spectral index = 2, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod14=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod14=(e1+emass)*p1*fermi(Zdbb,e1)*
     +             (e2+emass)*p2*fermi(Zdbb,e2)*
     +             (e0-e1-e2)**2
	return
	end

	function fe2_mod14(e2)
c probability distribution for energy of second e-/e+ for modebb=14
c (0nu2b with Mohapatra Majoron with spectral index = 2, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod14=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod14=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**2
	return
	end

c***********************************************************************

	function fe12_mod15(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=15 (as tsimpr needs)
c (2nu2b, 0+ -> 0+, bosonic neutrinos, HSD: A.S.Barabash et al., NPB 783(2007)90,
c eq. (27a) integrated in Enu1)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod15=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod15=(e1+emass)*p1*fermi(Zdbb,e1)*
     +             (e2+emass)*p2*fermi(Zdbb,e2)*
     +             (e0-e1-e2)**5*(9.*(e0-e1-e2)**2+21.*(e2-e1)**2)
	return
	end

	function fe2_mod15(e2)
c probability distribution for energy of second e-/e+ for modebb=4
c (2nu2b, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod15=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod15=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**5*
     +            (9.*(e0-e1-e2)**2+21.*(e2-e1)**2)
	return
	end

c***********************************************************************

	function fe12_mod16(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=16 (as tsimpr needs)
c (2nu2b, 0+ -> 2+, bosonic neutrinos, HSD: A.S.Barabash et al., NPB 783(2007)90,
c eq. (27b) integrated in Enu1)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod16=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod16=(e1+emass)*p1*fermi(Zdbb,e1)*
     +             (e2+emass)*p2*fermi(Zdbb,e2)*
     +             (e0-e1-e2)**5*(e2-e1)**2
	return
	end

	function fe2_mod16(e2)
c probability distribution for energy of second e-/e+ for modebb=4
c (2nu2b, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod16=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod16=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**5*(e2-e1)**2
	return
	end

c***********************************************************************

	function fe1_mod17(e1)
c probability distribution for energy of first e-/e+ for modebb=17
c (0nu2b with rhc-eta, 0+ -> 0+, 2n mechanism, simplified expression)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	fe1_mod17=0.
	if(e1.gt.e0) return
	e2=e0-e1
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe1_mod17=(e1+emass)*p1*fermi(Zdbb,e1)*
     +          (e2+emass)*p2*fermi(Zdbb,e2)
	return
	end

c***********************************************************************

	function fe1_mod18(e1)
c probability distribution for energy of the first e-/e+ for modebb=18
c (0nu2b with right-handed currents, eta term, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,xxx
	common/const/pi,emass,datamass(50)
	common/eta_nme/chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,
     +               chip_P,chip_R
	fe1_mod18=0.
	if(e1.gt.e0) return
	e2=e0-e1
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
c total energies in the units of electron mass
	et0=e0/emass+1.
	et1=e1/emass+1.
	et2=e2/emass+1.
	a1=(et1*et2-1.)*(et1-et2)**2/(2.*et1*et2)
	a2=-2.*(et1-et2)**2/(9.*et1*et2)
	a3=2.*(et1*et2-1.)/(81.*et1*et2)
	r=3.107526e-3*Adbb**(1./3.)
	rksi=3./137.036*Zdbb+r*et0
	a4=8.*(et1*et2+1.)/(r**2*et1*et2)
	a5=-8.*(rksi*(et1*et2+1.)-2.*r*et0)/(3.*r**2*et1*et2)
	a6=2.*((rksi**2+4.*r**2)*(et1*et2+1.)-4.*rksi*r*et0)/
     +     (9.*r**2*et1*et2)
	chi_1plus =chip_GT+3.*chip_F-6.*chip_T
	chi_1minus=chip_GT-3.*chip_F-6.*chip_T
	chi_2plus =chi_GTw+chi_Fw-chi_1minus/9.
	a_eta=a1*chi_2plus**2+a2*chi_2plus*chi_1minus+a3*chi_1minus**2
     +     +a4*chip_R**2+a5*chip_R*chip_P+a6*chip_P**2
c	print *,'fe1_mod18:'
c	print *,'chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,chip_P,chip_R'
c	print *,chi_GTw,chi_Fw,chip_GT,chip_F,chip_T,chip_P,chip_R
c	print *,'e1,r,rksi,a_eta=',e1,r,rksi,a_eta
c	if(e1.eq.e2) pause
	fe1_mod18=(e1+emass)*p1*fermi(Zdbb,e1)*
     +          (e2+emass)*p2*fermi(Zdbb,e2)*a_eta
	return
	end

c***********************************************************************

	function fe12_mod19(e2)
c two-dimensional probability distribution for energies of e-/e+ for
c modebb=19 (as tsimpr needs)
c (2nu2b with violation of Lorentz invariance; also equivalent to
c 0nu2b with Majoron with spectral index = 4, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe12_mod19=0.
	if(e2.gt.e0-e1) return
	p1=sqrt(e1*(e1+2.*emass))
	p2=sqrt(e2*(e2+2.*emass))
	fe12_mod19=(e1+emass)*p1*fermi(Zdbb,e1)*
     +             (e2+emass)*p2*fermi(Zdbb,e2)*
     +             (e0-e1-e2)**4
	return
	end

	function fe2_mod19(e2)
c probability distribution for energy of second e-/e+ for modebb=19
c (0nu2b with Majoron with spectral index = 7, 0+ -> 0+, 2n mechanism)
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	fe2_mod19=0.
	if(e2.gt.e0-e1) return
	p2=sqrt(e2*(e2+2.*emass))
	fe2_mod19=(e2+emass)*p2*fermi(Zdbb,e2)*(e0-e1-e2)**4
	return
	end

c***********************************************************************

	subroutine dshelp1(m,du1,df1,d_el)
	double precision d_el(2),df1(2),du1(2),dens,denf,d
	external dshelp2
	common/denrange/dens,denf,mode
	do i=1,m
	   d_el(1)=du1(i)
	   d=dmax1(0.d0,dens-d_el(1))
	   df1(i)=dgmlt2(dshelp2,d,denf-d_el(1),16,8,d_el)
	enddo
	return
	end

c***********************************************************************

	subroutine dshelp2(m,du2,df2,d_el)
	double precision d_el(2),df2(2),du2(2),dens,denf
	common/denrange/dens,denf,mode
	common/helpbb/Zdbb,Adbb,e0,e1
	common/const/pi,emass,datamass(50)
	do i=1,m
	   d_el(2)=du2(i)
	   e1=d_el(1)
	   e2=d_el(2)
	   df2(i)=0.d0
	   if(e1.gt.0..and.e2.gt.0..and.e1+e2.lt.e0) then
	      if(mode.eq.4) df2(i)=fe12_mod4(e2)
	      if(mode.eq.5) df2(i)=fe12_mod5(e2)
	      if(mode.eq.6) df2(i)=fe12_mod6(e2)
	      if(mode.eq.13) df2(i)=fe12_mod13(e2)
	      if(mode.eq.14) df2(i)=fe12_mod14(e2)
	      if(mode.eq.8) df2(i)=fe12_mod8(e2)
	      if(mode.eq.15) df2(i)=fe12_mod15(e2)
	      if(mode.eq.16) df2(i)=fe12_mod16(e2)
	      if(mode.eq.19) df2(i)=fe12_mod19(e2)
	   endif
	   if(d_el(1)+d_el(2).lt.dens.or.d_el(1)+d_el(2).gt.denf)
     +        df2(i)=0.d0
	enddo
	return
	end

c***********************************************************************

c***********************************************************************
c**************** Section of radioactive isotopes **********************
c***********************************************************************

c***********************************************************************

	subroutine Ac228(tcnuc,tdnuc)
c Scheme of 228Ac decay ("Table of Isotopes", 7th ed., 1978).
c Two-, three- and four-figured labels correspond to energies of
c 228Th excited levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 8.08.1992, 22.10.1995.
	thnuc=22068.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.20) go to  2027   !  0.20%
	if(pbeta.le. 0.40) go to  2010   !  0.20%
	if(pbeta.le. 0.44) go to  1965   !  0.04%
	if(pbeta.le. 0.67) go to  1945   !  0.23%
	if(pbeta.le. 0.77) go to  1900   !  0.10%
	if(pbeta.le. 0.91) go to  1893   !  0.14%
	if(pbeta.le. 1.02) go to  1760   !  0.11%
	if(pbeta.le. 1.31) go to  1744   !  0.29%
	if(pbeta.le. 2.81) go to  1724   !  1.50%
	if(pbeta.le. 4.91) go to  1689   !  2.10%
	if(pbeta.le. 6.41) go to  1683   !  1.50%
	if(pbeta.le.11.11) go to  1646   !  4.70%
	if(pbeta.le.11.91) go to  1643   !  0.80%
	if(pbeta.le.13.11) go to  1638   !  1.20%
	if(pbeta.le.13.18) go to  1547   !  0.07%
	if(pbeta.le.13.38) go to  1539   !  0.20%
	if(pbeta.le.21.38) go to  1532   !  8.00%
	if(pbeta.le.21.58) go to  1489   !  0.20%
	if(pbeta.le.23.48) go to  1450   !  1.90%
	if(pbeta.le.24.98) go to  1432   !  1.50%
	if(pbeta.le.25.18) go to  1344   !  0.20%
	if(pbeta.le.25.98) go to  1227   !  0.80%
	if(pbeta.le.29.58) go to  1169   !  3.60%
	if(pbeta.le.34.58) go to  1154   !  5.00%
	if(pbeta.le.39.98) go to  1123   !  5.40%
	if(pbeta.le.40.08) go to  1060   !  0.10%
	if(pbeta.le.42.08) go to  1022   !  2.00%
	if(pbeta.le.42.28) go to  1016   !  0.20%
	if(pbeta.le.42.38) go to   979   !  0.10%
	if(pbeta.le.74.33) go to   969   ! 31.95%
	if(pbeta.le.74.63) go to   968   !  0.30%
	if(pbeta.le.74.86) go to   944   !  0.23%
	if(pbeta.le.75.00) go to   875   !  0.14%
	if(pbeta.le.75.20) go to   519   !  0.20%
	if(pbeta.le.88.20) go to   396   ! 13.00%
	if(pbeta.le.89.00) go to   187   !  0.80%
	                   go to    58   ! 11.00%
c-----------------------------------------------------------------------
2027	call beta(0.110,90.,0.,0.,t)
20270	thlev=0.
	p=100.*rnd1(d)
	if(p.le.31.) go to 20271   ! 31%
	             go to 20272   ! 69%
20271	call nucltransK(1.509,0.110,3.2e-3,0.,tclev,thlev,tdlev)
	go to 96900
20272	call nucltransK(1.004,0.110,3.0e-3,0.,tclev,thlev,tdlev)
	go to 10220
c-----------------------------------------------------------------------
2010	call beta(0.127,90.,0.,0.,t)
20100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.42.) go to 20101   ! 42%
	if(p.le.72.) go to 20102   ! 30%
	             go to 20103   ! 28%
20101	call nucltransK(1.952,0.110,2.8e-3,1.6e-4,tclev,thlev,tdlev)
	go to 58000
20102	call nucltransK(1.823,0.110,7.0e-3,1.7e-4,tclev,thlev,tdlev)
	go to 18700
20103	call nucltransK(0.920,0.110,0.7e+0,0.,tclev,thlev,tdlev)
	go to 10910
c-----------------------------------------------------------------------
1965	call beta(0.172,90.,0.,0.,t)
19650	thlev=0.
	p=100.*rnd1(d)
	if(p.le.33.) go to 19651   ! 33%
	             go to 19652   ! 67%
19651	call nucltransK(1.966,0.110,1.2e-3,2.9e-4,tclev,thlev,tdlev)
	go to 10000
19652	call nucltransK(1.907,0.110,1.8e-3,2.7e-4,tclev,thlev,tdlev)
	go to 58000
c-----------------------------------------------------------------------
1945	call beta(0.192,90.,0.,0.,t)
19450	thlev=0.
	p=100.*rndm(d)
	if(p.le.31.4) go to 19451   ! 31.4%
	if(p.le.42.4) go to 19452   ! 11.0%
	if(p.le.44.3) go to 19453   !  1.9%
	if(p.le.75.7) go to 19454   ! 31.4%
	if(p.le.87.8) go to 19455   ! 12.1%
	if(p.le.89.0) go to 19456   !  1.2%
	if(p.le.94.0) go to 19457   !  5.0%
	if(p.le.96.0) go to 19458   !  2.0%
	              go to 19459   !  4.0%
19451	call nucltransK(1.887,0.110,3.0e-3,1.3e-4,tclev,thlev,tdlev)
	go to 58000
19452	call nucltransK(1.758,0.110,1.0e-2,2.0e-4,tclev,thlev,tdlev)
	go to 18700
19453	call nucltransK(1.549,0.110,1.7e-3,0.6e-4,tclev,thlev,tdlev)
	go to 39600
19454	call nucltransK(0.975,0.110,4.0e-2,0.,tclev,thlev,tdlev)
	go to 96900
19455	call nucltransK(0.922,0.110,4.5e-2,0.,tclev,thlev,tdlev)
	go to 10220
19456	call nucltransK(0.853,0.110,5.5e-2,0.,tclev,thlev,tdlev)
	go to 10910
19457	call nucltransK(0.791,0.110,6.5e-2,0.,tclev,thlev,tdlev)
	go to 11540
19458	call nucltransK(0.745,0.110,7.5e-2,0.,tclev,thlev,tdlev)
	go to 12000
19459	call nucltransK(0.220,0.110,2.1e+0,0.,tclev,thlev,tdlev)
	go to 17240
c-----------------------------------------------------------------------
1900	call beta(0.237,90.,0.,0.,t)
19000	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.7) go to 19001   !  1.7%
	if(p.le.20.7) go to 19002   ! 19.0%
	if(p.le.21.7) go to 19003   !  1.0%
	if(p.le.31.7) go to 19004   ! 10.0%
	if(p.le.67.9) go to 19005   ! 36.2%
	              go to 19006   ! 32.1%
19001	call nucltransK(1.900,0.110,3.0e-3,1.3e-4,tclev,thlev,tdlev)
	go to 10000
19002	call nucltransK(1.842,0.110,8.0e-3,2.0e-4,tclev,thlev,tdlev)
	go to 58000
19003	call nucltransK(1.712,0.110,3.5e-3,0.8e-4,tclev,thlev,tdlev)
	go to 18700
19004	call nucltransK(1.504,0.110,1.7e-3,0.5e-4,tclev,thlev,tdlev)
	go to 39600
19005	call nucltransK(0.884,0.110,4.3e-3,0.,tclev,thlev,tdlev)
	go to 10160
19006	call nucltransK(0.449,0.110,1.6e-2,0.,tclev,thlev,tdlev)
	go to 14500
c-----------------------------------------------------------------------
1893	call beta(0.244,90.,0.,0.,t)
18930	thlev=0.
	p=100.*rnd1(d)
	if(p.le.17.0) go to 18931   ! 17.0%
	if(p.le.22.6) go to 18932   !  5.6%
	if(p.le.38.6) go to 18933   ! 16.0%
	if(p.le.47.6) go to 18934   !  9.0%
	if(p.le.74.8) go to 18935   ! 27.2%
	if(p.le.76.8) go to 18936   !  2.0%
	if(p.le.77.8) go to 18937   !  1.0%
                      go to 18938   ! 22.2%
18931	call nucltransK(1.835,0.110,6.0e-3,2.0e-4,tclev,thlev,tdlev)
	go to 58000
18932	call nucltransK(1.706,0.110,1.0e-2,1.0e-4,tclev,thlev,tdlev)
	go to 18700
18933	call nucltransK(0.940,0.110,1.0e-1,0.,tclev,thlev,tdlev)
	go to 95200
18934	call nucltransK(0.924,0.110,4.5e-2,0.,tclev,thlev,tdlev)
	go to 96900
18935	call nucltransK(0.870,0.110,5.2e-2,0.,tclev,thlev,tdlev)
	go to 10220
18936	call nucltransK(0.739,0.110,3.3e-1,0.,tclev,thlev,tdlev)
	go to 11540
18937	call nucltransK(0.693,0.110,1.2e-1,0.,tclev,thlev,tdlev)
	go to 12000
18938	call nucltransK(0.461,0.110,2.8e-1,0.,tclev,thlev,tdlev)
	go to 14320
c-----------------------------------------------------------------------
1760	call beta(0.377,90.,0.,0.,t)
17600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.62.) go to 17601   ! 62%
	             go to 17602   ! 38%
17601	call nucltransK(1.702,0.110,1.4e-3,1.1e-4,tclev,thlev,tdlev)
	go to 58000
17602	call nucltransK(1.574,0.110,1.7e-3,0.7e-4,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
1744	call beta(0.393,90.,0.,0.,t)
17440	thlev=0.
	p=100.*rnd1(d)
	if(p.le.32.) go to 17441   ! 32%
	if(p.le.94.) go to 17442   ! 62%
	             go to 17443   !  6%
17441	call nucltransK(1.686,0.110,1.4e-3,1.6e-4,tclev,thlev,tdlev)
	go to 58000
17442	call nucltransK(1.557,0.110,1.7e-3,0.6e-4,tclev,thlev,tdlev)
	go to 18700
17443	call nucltransK(1.348,0.110,2.0e-3,0.2e-4,tclev,thlev,tdlev)
	go to 39600
c-----------------------------------------------------------------------
1724	call beta(0.413,90.,0.,0.,t)
17240	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.0) go to 17241   !  2.0%
	if(p.le.15.0) go to 17242   ! 13.0%
	if(p.le.15.8) go to 17243   !  0.8%
	if(p.le.89.0) go to 17244   ! 73.2%
                      go to 17245   ! 11.0%
17241	call nucltransK(1.724,0.110,3.7e-3,0.7e-4,tclev,thlev,tdlev)
	go to 10000
17242	call nucltransK(1.666,0.110,1.0e-2,1.2e-4,tclev,thlev,tdlev)
	go to 58000
17243	call nucltransK(1.537,0.110,4.0e-3,0.4e-4,tclev,thlev,tdlev)
	go to 18700
17244	call nucltransK(0.755,0.110,6.9e-2,0.,tclev,thlev,tdlev)
	go to 96900
17245	call nucltransK(0.702,0.110,9.5e-2,0.,tclev,thlev,tdlev)
	go to 10220
c-----------------------------------------------------------------------
1689	call beta(0.448,90.,0.,0.,t)
16890	thlev=0.
	p=100.*rnd1(d)
	if(p.le.72.3) go to 16891   ! 72.3%
	if(p.le.98.0) go to 16892   ! 25.7%
	              go to 16893   !  2.0%
16891	call nucltransK(1.631,0.110,7.4e-3,1.2e-4,tclev,thlev,tdlev)
	go to 58000
16892	call nucltransK(1.502,0.110,1.7e-3,0.5e-4,tclev,thlev,tdlev)
	go to 18700
16893	call nucltransK(0.666,0.110,7.5e-3,0.,tclev,thlev,tdlev)
	go to 10220
c-----------------------------------------------------------------------
1683	call beta(0.454,90.,0.,0.,t)
16830	thlev=0.
	p=100.*rnd1(d)
	if(p.le.22.) go to 16831   ! 22%
	if(p.le.90.) go to 16832   ! 68%
	if(p.le.96.) go to 16833   !  6%
	             go to 16834   !  4%
16831	call nucltransK(1.625,0.110,1.5e-3,0.8e-4,tclev,thlev,tdlev)
	go to 58000
16832	call nucltransK(1.496,0.110,1.7e-3,0.5e-4,tclev,thlev,tdlev)
	go to 18700
16833	call nucltransK(1.287,0.110,2.2e-3,0.2e-4,tclev,thlev,tdlev)
	go to 39600
16834	call nucltransK(1.165,0.110,2.6e-3,0.1e-4,tclev,thlev,tdlev)
	go to 51900
c-----------------------------------------------------------------------
1646	call beta(0.491,90.,0.,0.,t)
16460	thlev=0.
	p=100.*rnd1(d)
	if(p.le.75.0) go to 16461   ! 75.0%
	if(p.le.95.0) go to 16462   ! 20.0%
	if(p.le.96.0) go to 16463   !  1.0%
	if(p.le.96.4) go to 16464   !  0.4%
	if(p.le.97.4) go to 16465   !  1.0%
	if(p.le.99.5) go to 16466   !  2.1%
	              go to 16467   !  0.5%
16461	call nucltransK(1.588,0.110,4.7e-3,0.5e-4,tclev,thlev,tdlev)
	go to 58000
16462	call nucltransK(1.459,0.110,5.0e-3,0.3e-4,tclev,thlev,tdlev)
	go to 18700
16463	call nucltransK(0.677,0.110,2.2e-2,0.,tclev,thlev,tdlev)
	go to 96900
16464	call nucltransK(0.624,0.110,8.0e-3,0.,tclev,thlev,tdlev)
	go to 10220
16465	call nucltransK(0.555,0.110,1.6e-1,0.,tclev,thlev,tdlev)
	go to 10910
16466	call nucltransK(0.523,0.110,1.2e-2,0.,tclev,thlev,tdlev)
	go to 11230
16467	call nucltransK(0.420,0.110,1.8e-2,0.,tclev,thlev,tdlev)
	go to 12270
c-----------------------------------------------------------------------
1643	call beta(0.494,90.,0.,0.,t)
16430	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.0) go to 16431   !  1.0%
	if(p.le.51.7) go to 16432   ! 50.7%
	if(p.le.61.7) go to 16433   ! 10.0%
	if(p.le.70.7) go to 16434   !  9.0%
	              go to 16435   ! 29.3%
16431	call nucltransK(1.315,0.110,1.8e-2,0.6e-4,tclev,thlev,tdlev)
	go to 32800
16432	call nucltransK(1.247,0.110,2.1e-2,0.4e-4,tclev,thlev,tdlev)
	go to 39600
16433	call nucltransK(0.675,0.110,7.0e-3,0.,tclev,thlev,tdlev)
	go to 96900
16434	call nucltransK(0.620,0.110,8.0e-3,0.,tclev,thlev,tdlev)
	go to 10220
16435	call nucltransK(0.210,0.110,7.9e-2,0.,tclev,thlev,tdlev)
	go to 14320
c-----------------------------------------------------------------------
1638	call beta(0.499,90.,0.,0.,t)
16380	thlev=0.
	p=100.*rnd1(d)
	if(p.le.38.) go to 16381   ! 38%
	if(p.le.96.) go to 16382   ! 58%
	             go to 16383   !  4%
16381	call nucltransK(1.638,0.110,4.0e-3,0.5e-4,tclev,thlev,tdlev)
	go to 10000
16382	call nucltransK(1.581,0.110,1.1e-2,1.1e-4,tclev,thlev,tdlev)
	go to 58000
16383	call nucltransK(0.516,0.110,1.2e-2,0.,tclev,thlev,tdlev)
	go to 11230
c-----------------------------------------------------------------------
1547	call beta(0.590,90.,0.,0.,t)
15470	thlev=0.
	p=100.*rnd1(d)
	if(p.le.50.) go to 15471   ! 50%
	if(p.le.86.) go to 15472   ! 36%
	             go to 15473   ! 14%
15471	call nucltransK(1.169,0.110,2.7e-3,0.2e-4,tclev,thlev,tdlev)
	go to 37800
15472	call nucltransK(0.378,0.110,2.2e-2,0.,tclev,thlev,tdlev)
	go to 11690
15473	call nucltransK(0.373,0.110,2.2e-2,0.,tclev,thlev,tdlev)
	go to 11750
c-----------------------------------------------------------------------
1539	call beta(0.598,90.,0.,0.,t)
15390	thlev=0.
	p=100.*rnd1(d)
	if(p.le.12.) go to 15391   ! 12%
	if(p.le.18.) go to 15392   !  6%
	if(p.le.32.) go to 15393   ! 14%
	             go to 15394   ! 68%
15391	call nucltransK(1.480,0.110,1.8e-3,0.5e-4,tclev,thlev,tdlev)
	go to 58000
15392	call nucltransK(1.143,0.110,2.6e-2,0.3e-4,tclev,thlev,tdlev)
	go to 39600
15393	call nucltransK(1.020,0.110,1.0e-2,0.,tclev,thlev,tdlev)
	go to 51900
15394	call nucltransK(0.571,0.110,1.5e-1,0.,tclev,thlev,tdlev)
	go to 96800
c-----------------------------------------------------------------------
1532	call beta(0.605,90.,0.,0.,t)
15320	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.4) go to 15321   !  0.4%
	if(p.le.30.7) go to 15322   ! 30.3%
	if(p.le.46.7) go to 15323   ! 16.0%
	if(p.le.51.3) go to 15324   !  4.6%
	if(p.le.52.3) go to 15325   !  1.0%
	if(p.le.53.0) go to 15326   !  0.7%
	              go to 15327   ! 47.0%
15321	call nucltransK(1.136,0.110,2.8e-3,0.2e-4,tclev,thlev,tdlev)
	go to 39600
15322	call nucltransK(0.563,0.110,5.0e-2,0.,tclev,thlev,tdlev)
	go to 96900
15323	call nucltransK(0.509,0.110,6.0e-2,0.,tclev,thlev,tdlev)
	go to 10220
15324	call nucltransK(0.441,0.110,3.0e-1,0.,tclev,thlev,tdlev)
	go to 10910
15325	call nucltransK(0.378,0.110,4.5e-1,0.,tclev,thlev,tdlev)
	go to 11540
15326	call nucltransK(0.357,0.110,1.7e+0,0.,tclev,thlev,tdlev)
	go to 11750
15327	call nucltransK(0.100,0.020,4.0e+0,0.,tclev,thlev,tdlev)
	go to 14320
c-----------------------------------------------------------------------
1489	call beta(0.648,90.,0.,0.,t)
14890	thlev=0.
	p=100.*rnd1(d)
	if(p.le.22.) go to 14891   ! 22%
	             go to 14892   ! 78%
14891	call nucltransK(0.399,0.110,2.0e-2,0.,tclev,thlev,tdlev)
	go to 10910
14892	call nucltransK(0.314,0.110,0.6e+0,0.,tclev,thlev,tdlev)
	go to 11750
c-----------------------------------------------------------------------
1450	call beta(0.687,90.,0.,0.,t)
14500	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.0) go to 14501   !  3.0%
	if(p.le.15.0) go to 14502   ! 12.0%
	if(p.le.16.5) go to 14503   !  1.5%
	if(p.le.58.0) go to 14504   ! 41.5%
	if(p.le.82.0) go to 14505   ! 24.0%
	              go to 14506   ! 18.0%
14501	call nucltransK(1.054,0.110,3.2e-2,0.,tclev,thlev,tdlev)
	go to 39600
14502	call nucltransK(0.498,0.110,4.2e-2,0.,tclev,thlev,tdlev)
	go to 95200
14503	call nucltransK(0.481,0.110,2.5e-1,0.,tclev,thlev,tdlev)
	go to 96800
14504	call nucltransK(0.328,0.110,4.4e-2,0.,tclev,thlev,tdlev)
	go to 11230
14505	call nucltransK(0.282,0.110,1.3e+0,0.,tclev,thlev,tdlev)
	go to 11690
14506	call nucltransK(0.224,0.110,1.5e+0,0.,tclev,thlev,tdlev)
	go to 12270
c-----------------------------------------------------------------------
1432	call beta(0.705,90.,0.,0.,t)
14320	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.0) go to 14321   !  1.0%
	if(p.le. 3.0) go to 14322   !  2.0%
	if(p.le.64.8) go to 14323   ! 61.8%
	if(p.le.92.2) go to 14324   ! 27.4%
	if(p.le.98.2) go to 14325   !  6.0%
	if(p.le.99.0) go to 14326   !  0.8%
	if(p.le.99.6) go to 14327   !  0.6%
	              go to 14328   !  0.4%
14321	call nucltransK(1.374,0.110,1.4e-2,0.7e-4,tclev,thlev,tdlev)
	go to 58000
14322	call nucltransK(1.245,0.110,2.0e-2,0.4e-4,tclev,thlev,tdlev)
	go to 18700
14323	call nucltransK(0.463,0.110,4.7e-2,0.,tclev,thlev,tdlev)
	go to 96900
14324	call nucltransK(0.410,0.110,8.3e-2,0.,tclev,thlev,tdlev)
	go to 10220
14325	call nucltransK(0.341,0.110,1.2e-1,0.,tclev,thlev,tdlev)
	go to 10910
14326	call nucltransK(0.308,0.110,3.5e-2,0.,tclev,thlev,tdlev)
	go to 11230
14327	call nucltransK(0.264,0.110,5.0e-2,0.,tclev,thlev,tdlev)
	go to 11690
14328	call nucltransK(0.258,0.110,5.0e-2,0.,tclev,thlev,tdlev)
	go to 11750
c-----------------------------------------------------------------------
1344	call beta(0.793,90.,0.,0.,t)
13440	thlev=0.
	p=100.*rnd1(d)
	if(p.le.27.0) go to 13441   ! 27.0%
	if(p.le.64.5) go to 13442   ! 37.5%
	if(p.le.95.0) go to 13443   ! 30.5%
	              go to 13444   !  5.0%
13441	call nucltransK(1.017,0.110,3.5e-3,0.,tclev,thlev,tdlev)
	go to 32800
13442	call nucltransK(0.948,0.110,3.7e-3,0.,tclev,thlev,tdlev)
	go to 39600
13443	call nucltransK(0.825,0.110,5.0e-3,0.,tclev,thlev,tdlev)
	go to 51900
13444	call nucltransK(0.169,0.110,1.4e-1,0.,tclev,thlev,tdlev)
	go to 11750
c-----------------------------------------------------------------------
1227	call beta(0.910,90.,0.,0.,t)
12270	thlev=0.
	p=100.*rnd1(d)
	if(p.le.10.) go to 12271   ! 10%
	if(p.le.68.) go to 12272   ! 58%
	if(p.le.79.) go to 12273   ! 11%
	if(p.le.97.) go to 12274   ! 18%
	             go to 12275   !  3%
12271	call nucltransK(1.040,0.110,3.5e-3,0.,tclev,thlev,tdlev)
	go to 18700
12272	call nucltransK(0.830,0.110,1.8e-2,0.,tclev,thlev,tdlev)
	go to 39600
12273	call nucltransK(0.707,0.110,1.0e-1,0.,tclev,thlev,tdlev)
	go to 51900
12274	call nucltransK(0.204,0.110,9.0e-2,0.,tclev,thlev,tdlev)
	go to 10220
12275	call nucltransK(0.136,0.110,1.7e+0,0.,tclev,thlev,tdlev)
	go to 10910
c-----------------------------------------------------------------------
12000	thlev=0.
	call nucltransK(0.178,0.110,6.0e+1,0.,tclev,thlev,tdlev)
	go to 10220
c-----------------------------------------------------------------------
11750	thlev=0.
	p=100.*rnd1(d)
	if(p.le.67.) go to 11751   ! 67%
	             go to 11752   ! 33%
11751	call nucltransK(0.988,0.110,3.5e-3,0.,tclev,thlev,tdlev)
	go to 18700
11752	call nucltransK(0.796,0.110,5.2e-3,0.,tclev,thlev,tdlev)
	go to 37800
c-----------------------------------------------------------------------
1169	call beta(0.968,90.,0.,0.,t)
11690	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.0) go to 11691   ! 11.0%
	if(p.le.38.8) go to 11692   ! 27.8%
	if(p.le.84.5) go to 11693   ! 45.7%
	if(p.le.84.8) go to 11694   !  0.3%
	if(p.le.93.8) go to 11695   !  9.0%
	if(p.le.98.9) go to 11696   !  5.1%
	              go to 11697   !  1.1%
11691	call nucltransK(1.110,0.110,2.9e-3,0.1e-4,tclev,thlev,tdlev)
	go to 58000
11692	call nucltransK(0.840,0.110,1.4e-2,0.,tclev,thlev,tdlev)
	go to 32800
11693	call nucltransK(0.772,0.110,1.5e-2,0.,tclev,thlev,tdlev)
	go to 39600
11694	call nucltransK(0.649,0.110,2.4e-2,0.,tclev,thlev,tdlev)
	go to 51900
11695	call nucltransK(0.200,0.110,9.5e-2,0.,tclev,thlev,tdlev)
	go to 96900
11696	call nucltransK(0.146,0.110,1.2e+0,0.,tclev,thlev,tdlev)
	go to 10220
11697	call nucltransK(0.078,0.020,2.2e-1,0.,tclev,thlev,tdlev)
	go to 10910
c-----------------------------------------------------------------------
1154	call beta(0.983,90.,0.,0.,t)
11540	thlev=0.
	p=100.*rnd1(d)
	if(p.le.14.9) go to 11541   ! 14.9%
	if(p.le.25.8) go to 11542   ! 10.9%
	if(p.le.40.7) go to 11543   ! 14.9%
	if(p.le.61.4) go to 11544   ! 20.7%
	if(p.le.84.1) go to 11545   ! 22.7%
	if(p.le.93.0) go to 11546   !  8.9%
	if(p.le.97.0) go to 11547   !  4.0%
	              go to 11548   !  3.0%
11541	call nucltransK(1.154,0.110,7.5e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
11542	call nucltransK(1.096,0.110,2.8e-2,0.1e-4,tclev,thlev,tdlev)
	go to 58000
11543	call nucltransK(0.967,0.110,2.0e-2,0.,tclev,thlev,tdlev)
	go to 18700
11544	call nucltransK(0.322,0.110,5.2e-1,0.,tclev,thlev,tdlev)
	go to 83200
11545	call nucltransK(0.279,0.110,1.3e+0,0.,tclev,thlev,tdlev)
	go to 87500
11546	call nucltransK(0.185,0.110,5.4e+1,0.,tclev,thlev,tdlev)
	go to 96900
11547	call nucltransK(0.174,0.110,1.4e+0,0.,tclev,thlev,tdlev)
	go to 97900
11548	call nucltransK(0.138,0.110,4.9e+0,0.,tclev,thlev,tdlev)
	go to 10160
c-----------------------------------------------------------------------
1123	call beta(1.014,90.,0.,0.,t)
11230	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.4) go to 11231   !  1.4%
	if(p.le. 5.4) go to 11232   !  4.0%
	if(p.le. 5.6) go to 11233   !  0.2%
	if(p.le.73.8) go to 11234   ! 68.2%
	if(p.le.85.8) go to 11235   ! 12.0%
	if(p.le.98.1) go to 11236   ! 12.3%
	              go to 11237   !  1.9%
11231	call nucltransK(1.123,0.110,6.5e-2,0.1e-4,tclev,thlev,tdlev)
	go to 10000
11232	call nucltransK(1.065,0.110,3.2e-3,0.,tclev,thlev,tdlev)
	go to 58000
11233	call nucltransK(0.936,0.110,0.1e+0,0.,tclev,thlev,tdlev)
	go to 18700
11234	call nucltransK(0.795,0.110,1.9e-2,0.,tclev,thlev,tdlev)
	go to 32800
11235	call nucltransK(0.727,0.110,1.0e-2,0.,tclev,thlev,tdlev)
	go to 39600
11236	call nucltransK(0.154,0.110,0.2e+0,0.,tclev,thlev,tdlev)
	go to 96900
11237	call nucltransK(0.100,0.020,3.3e-1,0.,tclev,thlev,tdlev)
	go to 10220
c-----------------------------------------------------------------------
10910	thlev=0.
	p=100.*rnd1(d)
	if(p.le.21.) go to 10911   ! 21%
	             go to 10912   ! 79%
10911	call nucltransK(1.033,0.110,9.5e-3,0.,tclev,thlev,tdlev)
	go to 58000
10912	call nucltransK(0.904,0.110,2.6e-2,0.,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
1060	call beta(1.077,90.,0.,0.,t)
10600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.74.) go to 10601   ! 74%
	if(p.le.87.) go to 10602   ! 13%
	             go to 10603   ! 13%
10601	call nucltransK(1.002,0.110,3.5e-3,0.,tclev,thlev,tdlev)
	go to 58000
10602	call nucltransK(0.664,0.110,7.0e-3,0.,tclev,thlev,tdlev)
	go to 39600
10603	call nucltransK(0.541,0.110,1.1e-2,0.,tclev,thlev,tdlev)
	go to 51900
c-----------------------------------------------------------------------
1022	call beta(1.115,90.,0.,0.,t)
10220	thlev=0.
	p=100.*rnd1(d)
	if(p.le.73.) go to 10221   ! 73%
	             go to 10222   ! 27%
10221	call nucltransK(0.964,0.110,9.2e-3,0.,tclev,thlev,tdlev)
	go to 58000
10222	call nucltransK(0.836,0.110,1.4e-2,0.,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
1016	call beta(1.121,90.,0.,0.,t)
10160	thlev=0.
	p=100.*rnd1(d)
	if(p.le.19.) go to 10161   ! 19%
	if(p.le.66.) go to 10162   ! 47%
	if(p.le.82.) go to 10163   ! 16%
	             go to 10164   ! 18%
10161	call nucltransK(1.017,0.110,2.4e-2,0.,tclev,thlev,tdlev)
	go to 10000
10162	call nucltransK(0.958,0.110,3.8e-3,0.,tclev,thlev,tdlev)
	go to 58000
10163	call nucltransK(0.688,0.110,2.1e-2,0.,tclev,thlev,tdlev)
	go to 32800
10164	call nucltransK(0.620,0.110,1.4e-1,0.,tclev,thlev,tdlev)
	go to 39600
c-----------------------------------------------------------------------
979	call beta(1.158,90.,0.,0.,t)
97900	thlev=0.
	p=100.*rnd1(d)
	if(p.le.35.) go to 97901   ! 35%
	             go to 97902   ! 65%
97901	call nucltransK(0.651,0.110,7.5e-3,0.,tclev,thlev,tdlev)
	go to 32800
97902	call nucltransK(0.583,0.110,9.5e-3,0.,tclev,thlev,tdlev)
	go to 39600
c-----------------------------------------------------------------------
969	call beta(1.168,90.,0.,0.,t)
96900	thlev=0.
	p=100.*rnd1(d)
	if(p.le.37.0) go to 96901   ! 37.0%
	if(p.le.98.8) go to 96902   ! 61.8%
	              go to 96903   !  1.2%
96901	call nucltransK(0.969,0.110,1.0e-2,0.,tclev,thlev,tdlev)
	go to 10000
96902	call nucltransK(0.911,0.110,1.2e-2,0.,tclev,thlev,tdlev)
	go to 58000
96903	call nucltransK(0.782,0.110,6.8e-2,0.,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
968	call beta(1.169,90.,0.,0.,t)
96800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.22.) go to 96801   ! 22%
	             go to 96802   ! 78%
96801	call nucltransK(0.641,0.110,1.1e-1,0.,tclev,thlev,tdlev)
	go to 32800
96802	call nucltransK(0.572,0.110,1.3e-1,0.,tclev,thlev,tdlev)
	go to 39600
c-----------------------------------------------------------------------
95200	thlev=0.
	p=100.*rnd1(d)
	if(p.le.91.) go to 95201   ! 91%
	if(p.le.94.) go to 95202   !  3%
	             go to 95203   !  6%
95201	call nucltransK(0.894,0.110,4.2e-3,0.,tclev,thlev,tdlev)
	go to 58000
95202	call nucltransK(0.624,0.110,1.2e-1,0.,tclev,thlev,tdlev)
	go to 32800
95203	call nucltransK(0.556,0.110,3.5e-2,0.,tclev,thlev,tdlev)
	go to 39600
c-----------------------------------------------------------------------
944	call beta(1.193,90.,0.,0.,t)
94400	thlev=0.
	p=100.*rnd1(d)
	if(p.le.42.5) go to 94401   ! 42.5%
	if(p.le.57.5) go to 94402   ! 15.0%
	              go to 94403   ! 42.5%
94401	call nucltransK(0.944,0.110,1.1e-2,0.,tclev,thlev,tdlev)
	go to 10000
94402	call nucltransK(0.888,0.110,7.5e-1,0.,tclev,thlev,tdlev)
	go to 58000
94403	call nucltransK(0.616,0.110,8.5e-3,0.,tclev,thlev,tdlev)
	go to 32800
c-----------------------------------------------------------------------
875	call beta(1.262,90.,0.,0.,t)
87500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.15.) go to 87501   ! 15%
	if(p.le.26.) go to 87502   ! 11%
	if(p.le.60.) go to 87503   ! 34%
	             go to 87504   ! 40%
87501	call nucltransK(0.874,0.110,1.3e-2,0.,tclev,thlev,tdlev)
	go to 10000
87502	call nucltransK(0.816,0.110,0.5e+0,0.,tclev,thlev,tdlev)
	go to 58000
87503	call nucltransK(0.546,0.110,1.1e-2,0.,tclev,thlev,tdlev)
	go to 32800
87504	call nucltransK(0.479,0.110,1.4e-2,0.,tclev,thlev,tdlev)
	go to 39600
c-----------------------------------------------------------------------
83200	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.) go to 83201   !  4%
	if(p.le.27.) go to 83202   ! 23%
	             go to 83203   ! 73%
83201	call electron(0.721,tclev,thlev,tdlev)      ! only ec
c	call gamma(0.110,tdlev,0.,tdlev)            ! for real time
	call gamma(0.110,0.,0.,tdlev)               ! for time shift
	go to 10000
83202	call nucltransK(0.771,0.110,1.7e-2,0.,tclev,thlev,tdlev)
	go to 58000
83203	call nucltransK(0.504,0.110,1.2e-2,0.,tclev,thlev,tdlev)
	go to 32800
c-----------------------------------------------------------------------
519	call beta(1.618,90.,0.,0.,t)
51900	thlev=0.
	p=100.*rnd1(d)
	if(p.le.90.) go to 51901   ! 90%
	             go to 51902   ! 10%
51901	call nucltransK(0.332,0.110,4.7e-1,0.,tclev,thlev,tdlev)
	go to 18700
51902	call nucltransK(0.141,0.110,0.9e+0,0.,tclev,thlev,tdlev)
	go to 37800
c-----------------------------------------------------------------------
396	call beta(1.741,90.,0.,0.,t)
39600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.73.) go to 39601   ! 73%
	             go to 39602   ! 27%
39601	call nucltransK(0.338,0.110,1.0e-2,0.,tclev,thlev,tdlev)
	go to 58000
39602	call nucltransK(0.209,0.110,7.9e-2,0.,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
37800	thlev=0.
	call nucltransK(0.191,0.110,4.2e-1,0.,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
32800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.47.) go to 32801   ! 47%
	             go to 32802   ! 53%
32801	call nucltransK(0.328,0.110,4.4e-2,0.,tclev,thlev,tdlev)
	go to 10000
32802	call nucltransK(0.270,0.110,3.4e-2,0.,tclev,thlev,tdlev)
	go to 58000
c-----------------------------------------------------------------------
187	call beta(1.950,90.,0.,0.,t)
18700	thlev=0.16e-9
	call nucltransK(0.129,0.020,2.7e+0,0.,tclev,thlev,tdlev)
	go to 58000
c-----------------------------------------------------------------------
58	call beta(2.079,90.,0.,0.,t)
58000	thlev=0.40e-9
	call nucltransK(0.058,0.020,1.2e+2,0.,tclev,thlev,tdlev)
c-----------------------------------------------------------------------
10000	return
	end

c***********************************************************************

	subroutine Am241(tcnuc,tdnuc)
c Model for scheme of Am241 decay (NDS 107(2006)3323 and ENSDF at NNDC site 
c on 15.01.2011). Decays to excited levels of 237-Np with probabilities <0.01% 
c are neglected.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 23.01.2011.
	thnuc=1.365144e10
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	palpha=100.*rnd1(d)
	if(palpha.le. 0.015) go to   226
	if(palpha.le. 1.672) go to   159
	if(palpha.le. 1.682) go to   130
	if(palpha.le.14.758) go to   103
	if(palpha.le.99.406) go to    60
	if(palpha.le.99.631) go to    33
	                     go to 10000
c-----------------------------------------------------------------------
226	call alpha(5.322,0.,0.,t)
22600	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.43) go to 22601         
	if(p.le.34.21) go to 22602         
	               go to 22603  
22601	call nucltransKLM(0.150,0.119,1.5e-1,0.022,3.4e-2,0.005,8.4e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 76000
22602	call nucltransKLM(0.123,0.119,1.9e-1,0.022,4.13,0.005,1.59,
     +                    0.,tclev,thlev,tdlev)
	go to 10300
22603	call nucltransKLM(0.067,0.119,0.,0.022,23.,0.005,8.1,
     +                    0.,tclev,thlev,tdlev)
	go to 15900
c-----------------------------------------------------------------------
159	call alpha(5.388,0.,0.,t)
15900	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.34) go to 15901         
	if(p.le.21.79) go to 15902         
	               go to 15903  
15901	call nucltransKLM(0.125,0.119,2.3e-1,0.022,5.5e-2,0.005,1.7e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 33000
15902	call nucltransKLM(0.099,0.119,0.,0.022,11.3,0.005,4.33,
     +                    0.,tclev,thlev,tdlev)
	go to 60000
15903	call nucltransKLM(0.056,0.119,0.,0.022,49.,0.005,18.,
     +                    0.,tclev,thlev,tdlev)
	go to 10300
c-----------------------------------------------------------------------
130	call alpha(5.416,0.,0.,t)
13000	thlev=0.
	call nucltransKLM(0.054,0.119,0.,0.022,23.2,0.005,7.7,
     +                    0.,tclev,thlev,tdlev)
	go to 76000
c-----------------------------------------------------------------------
103	call alpha(5.443,0.,0.,t)
10300	thlev=80.e-12
	p=100.*rnd1(d)
	if(p.le. 0.18) go to 10301         
	if(p.le. 0.21) go to 10302         
	               go to 10303  
10301	call nucltransKLM(0.103,0.119,0.,0.022,9.1e-2,0.005,3.0e-2,
     +                    0.,tclev,thlev,tdlev)
	return
10302	call nucltransKLM(0.070,0.119,0.,0.022,2.5e-1,0.005,8.4e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 33000
10303	call nucltransKLM(0.043,0.119,0.,0.022,124.,0.005,43.,
     +                    0.,tclev,thlev,tdlev)
	go to 60000
c-----------------------------------------------------------------------
76000	thlev=56.e-12
	p=100.*rnd1(d)
	if(p.le. 7.02) go to 76001         
	               go to 76002  
76001	call nucltransKLM(0.076,0.119,0.,0.022,39.4,0.005,15.0,
     +                    0.,tclev,thlev,tdlev)
	return
76002	call nucltransKLM(0.043,0.119,0.,0.022,59.,0.005,21.,
     +                    0.,tclev,thlev,tdlev)
	go to 33000
c-----------------------------------------------------------------------
60	call alpha(5.486,0.,0.,t)
60000	thlev=67.e-9
	p=100.*rnd1(d)
	if(p.le.78.20) go to 60001         
	               go to 60002  
60001	call nucltransKLM(0.060,0.119,0.,0.022,0.84,0.005,0.32,
     +                    0.,tclev,thlev,tdlev)
	return
60002	call nucltransKLM(0.026,0.119,0.,0.022,6.,0.005,2.,
     +                    0.,tclev,thlev,tdlev)
	go to 33000
c-----------------------------------------------------------------------
33	call alpha(5.512,0.,0.,t)
33000	thlev=54.e-12
	call nucltransKLM(0.033,0.119,0.,0.022,138.,0.005,47.,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call alpha(5.544,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Ar39(tcnuc,tdnuc)
c Model for Ar39 decay (Nucl. Phys. A 633(1998)1).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 12.09.2005; 29.10.2006.
	thnuc=8.488762e9
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
c	call beta(0.565,19.,0.,0.,t)
c change to the 1st forbidden unique shape
	call beta_1fu(0.565,19.,0.,0.,t,0.,0.,0.,0.)
	return
	end

c***********************************************************************

	subroutine Ar42(tcnuc,tdnuc)
c Model for Ar42 decay (Nucl. Data Sheets 92(2001)1).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 12.09.2005; 29.10.2006.
	thnuc=1.0382166e9
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
c	call beta(0.599,19.,0.,0.,t)
c change to the 1st forbidden unique shape
	call beta_1fu(0.599,19.,0.,0.,t,0.,0.,0.,0.)
	return
	end

c***********************************************************************

	subroutine As79(tcnuc,tdnuc)
c Model for scheme of As79+Se79m decay ("Table of Isotopes", 8th ed., 
c 1998 and Nucl. Data Sheets 96(2002)1).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 1.10.2004.
	thnuc=540.6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.24) go to 1089
	if(pbeta.le. 0.67) go to 1080
	if(pbeta.le. 2.43) go to 975
	if(pbeta.le. 2.69) go to 572
	if(pbeta.le. 3.79) go to 528
	if(pbeta.le. 5.24) go to 365
	                   go to 96
c-----------------------------------------------------------------------
1089	call beta(1.192,34.,0.,0.,t)
10890	thlev=0.
	p=100.*rnd1(d)
	if(p.le.53.70) go to 10891   
	               go to 10892   
10891	call nucltransK(0.993,0.013,4.0e-4,0.,tclev,thlev,tdlev)
	go to 96000
10892	call nucltransK(0.724,0.013,8.5e-4,0.,tclev,thlev,tdlev)
	go to 36500
c-----------------------------------------------------------------------
1080	call beta(1.201,34.,0.,0.,t)
10800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.68.97) go to 10801   
	               go to 10802   
10801	call nucltransK(0.715,0.013,8.5e-4,0.,tclev,thlev,tdlev)
	go to 36500
10802	call nucltransK(0.552,0.013,1.5e-3,0.,tclev,thlev,tdlev)
	go to 52800
c-----------------------------------------------------------------------
975	call beta(1.306,34.,0.,0.,t)
97500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.79.37) go to 97501   
	if(p.le.94.45) go to 97502   
	               go to 97503   
97501	call nucltransK(0.879,0.013,5.5e-4,0.,tclev,thlev,tdlev)
	go to 96000
97502	call nucltransK(0.447,0.013,2.5e-3,0.,tclev,thlev,tdlev)
	go to 52800
97503	call nucltransK(0.402,0.013,3.2e-3,0.,tclev,thlev,tdlev)
	go to 57200
c-----------------------------------------------------------------------
572	call beta(1.709,34.,0.,0.,t)
57200	thlev=1.6e-11
	p=100.*rnd1(d)
	if(p.le.95.33) go to 57201   
	               go to 57202   
57201	call nucltransK(0.476,0.013,1.0e-3,0.,tclev,thlev,tdlev)
	go to 96000
57202	call nucltransK(0.207,0.013,1.8e-2,0.,tclev,thlev,tdlev)
	go to 36500
c-----------------------------------------------------------------------
528	call beta(1.753,34.,0.,0.,t)
52800	thlev=3.1e-12
	call nucltransK(0.432,0.013,2.7e-3,0.,tclev,thlev,tdlev)
	go to 96000
c-----------------------------------------------------------------------
365	call beta(1.916,34.,0.,0.,t)
36500	thlev=9.4e-11
	call nucltransK(0.365,0.013,2.0e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
96	call beta(2.185,34.,0.,0.,t)
96000	thlev=235.2
	p=100.*rnd1(d)
	if(p.le.99.944) go to 96001   
	                go to 96002   
96001	call nucltransK(0.096,0.013,9.39,0.,tclev,thlev,tdlev) ! IT to Se79 (gs)
	return
96002	call beta(0.247,35.,tclev,thlev,tdlev)                 ! beta to Br79 (gs)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine At214(tcnuc,tdnuc)
c Model for scheme of At214 decay (NDS 99(2003)649 and ENSDF at NNDC site 
c on 9.12.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 9.12.2007.
	thnuc=558.e-9
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	palpha=100.*rnd1(d)
	if(palpha.le.0.32) go to   563
	if(palpha.le.0.90) go to   348
	if(palpha.le.1.05) go to   320
	                   go to 10000
c-----------------------------------------------------------------------
563	call alpha(8.267,0.,0.,t)
	thlev=0.
	call nucltransK(0.563,0.091,8.6e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
348	call alpha(8.478,0.,0.,t)
	thlev=0.
	call nucltransK(0.348,0.091,7.9e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
320	call alpha(8.505,0.,0.,t)
	thlev=0.
	call nucltransK(0.320,0.091,3.9e-1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call alpha(8.819,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end
c***********************************************************************

	subroutine Bi207(tcnuc,tdnuc)
c Scheme of Bi207+Pb207m decay (Nucl. Data Sheets 70(1993)315)
c with NNDC corrections of 10.10.2000 and 20.04.2005.
c To describe the deexcitation processes in atomic shell of Pb207,
c the information of PC Nuclear Data File retrieval program and data
c base (last updated on 16-Aug-1994) was used.
c Gammas, beta+, e+e- pairs, K, L and M conversion electrons, K, L and M
c X-rays and K and L Auger electrons are emitted.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 7.07.1995, 22.10.1995, 11.09.2005, 3.10.2005.
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	thnuc=1.0382166E+09
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	EbindK=0.088
	EbindL=0.015
	EbindM=0.003
	cg=1.
	npe570=0
	npe1064=0
	npg570=0
	npg1064=0
	pdecay=100.*rnd1(d)
	if(pdecay.le.99.988) go to 1  ! 99.988 EC
	                     go to 2  !  0.012 b+
c-----------------------------------------------------------------------
c EC to Pb207 or Pb207m
1	pec=pdecay
	if(pec.le. 7.027) go to 2340  !  7.027%
	if(pec.le.90.992) go to 1633  ! 83.965%
	                  go to  570  !  8.996%
c-----------------------------------------------------------------------
c b+ to Pb207
2	call beta(0.807,-82.,0.,0.,t)
	go to 57000
c-----------------------------------------------------------------------
2340	if(rnd1(d).le.0.70) then
	   call PbAtShell(88,0.,0.,t)
	else
	   call PbAtShell(15,0.,0.,t)
	end if
23400	thlev=0.
	p=100.*rnd1(d)
	if(p.le.98.13) go to 23401
	               go to 23402
23401	Egamma=1.770
	cK=3.51e-3
	cL=0.49e-3
	cM=0.13e-3
	cp=2.5e-4
	p=rnd1(d)*(cg+cK+cL+cM+cp)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call PbAtShell(88,0.,0.,tdlev)
	else if(p.le.cg+cK+cL) then
	   call electron(Egamma-EbindL,tclev,thlev,tdlev)
	   call PbAtShell(15,0.,0.,tdlev)
	else if(p.le.cg+cK+cL+cM) then
	   call electron(Egamma-EbindM,tclev,thlev,tdlev)
	   call PbAtShell(3,0.,0.,tdlev)
	else
	   call pair(Egamma-1.022,tclev,thlev,tdlev)
	end if
	go to 57000
23402	Egamma=1.442
	cK=2.7e-3
	cL=0.4e-3
	cM=0.1e-3
	cp=0.2e-4
	p=rnd1(d)*(cg+cK+cL+cM+cp)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call PbAtShell(88,0.,0.,tdlev)
	else if(p.le.cg+cK+cL) then
	   call electron(Egamma-EbindL,tclev,thlev,tdlev)
	   call PbAtShell(15,0.,0.,tdlev)
	else if(p.le.cg+cK+cL+cM) then
	   call electron(Egamma-EbindM,tclev,thlev,tdlev)
	   call PbAtShell(3,0.,0.,tdlev)
	else
	   call pair(Egamma-1.022,tclev,thlev,tdlev)
	end if
	go to 89800
c-----------------------------------------------------------------------
c The used (many years) value of L/K probabilities 19.8/73.3=0.2701 is
c confirmed by recent direct measurements L/K=0.269+-0.036 
c [N.Coron et al., EPJA 48(2012)89].
c VIT, 13.07.2012.
1633	p=rnd1(d)
	if(p.le.0.733) then              ! 73.3% EC from K shell
	   call PbAtShell(88,0.,0.,t)
	elseif(p.le.0.931) then          ! 19.8% EC from L shell
	   call PbAtShell(15,0.,0.,t)    
	else                             !  6.9% EC from M shell
	   call PbAtShell(3,0.,0.,t)     
	end if
16330	thlev=0.80
	Egamma=1.064
	cK=9.42e-2
	cL=2.47e-2
	cM=0.73e-2
	p=rnd1(d)*(cg+cK+cL+cM)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg1064=npfull
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   npe1064=npfull
	   call PbAtShell(88,0.,0.,tdlev)
	else if(p.le.cg+cK+cL) then
	   call electron(Egamma-EbindL,tclev,thlev,tdlev)
	   npe1064=npfull
	   call PbAtShell(15,0.,0.,tdlev)
	else
	   call electron(Egamma-EbindM,tclev,thlev,tdlev)
	   npe1064=npfull
	   call PbAtShell(3,0.,0.,tdlev)
	end if
	go to 57000
c-----------------------------------------------------------------------
89800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.99.245) go to 89801
	                go to 89802
89801	Egamma=0.898
	cK=2.01e-2
	cL=0.34e-2
	p=rnd1(d)*(cg+cK+cL)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	elseif(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call PbAtShell(88,0.,0.,tdlev)
	else
	   call electron(Egamma-EbindL,tclev,thlev,tdlev)
	   call PbAtShell(15,0.,0.,tdlev)
	end if
	return
89802	Egamma=0.328
	cK=0.2850
	cL=0.0486
	cM=0.0151
	p=rnd1(d)*(cg+cK+cL+cM)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call PbAtShell(88,0.,0.,tdlev)
	else if(p.le.cg+cK+cL) then
	   call electron(Egamma-EbindL,tclev,thlev,tdlev)
	   call PbAtShell(15,0.,0.,tdlev)
	else
	   call electron(Egamma-EbindM,tclev,thlev,tdlev)
	   call PbAtShell(3,0.,0.,tdlev)
	end if
	go to 57000
c-----------------------------------------------------------------------
570	p=rnd1(d)
	if(p.le.0.7965) then
	   call PbAtShell(88,0.,0.,t)
	elseif(p.le.0.9466) then
	   call PbAtShell(15,0.,0.,t)
	else
	   call PbAtShell(3,0.,0.,t)
	end if
57000	thlev=130.5e-12
	Egamma=0.570
	cK=1.55e-2
	cL=0.45e-2
	cM=0.15e-2
	p=rnd1(d)*(cg+cK+cL+cM)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg570=npfull
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   npe570=npfull
	   call PbAtShell(88,0.,0.,tdlev)
	else if(p.le.cg+cK+cL) then
	   call electron(Egamma-EbindL,tclev,thlev,tdlev)
	   npe570=npfull
	   call PbAtShell(15,0.,0.,tdlev)
	else
	   call electron(Egamma-EbindM,tclev,thlev,tdlev)
	   npe570=npfull
	   call PbAtShell(3,0.,0.,tdlev)
	end if
c-----------------------------------------------------------------------
c Angular correlation between gammas and conversion electrons of 1064 and 
c 570 keV; values of angular coefficients are taken from P.Kleinheinz
c et al., Nucl. Phys. A 93(1967)63. For K, L and M electrons the same 
c coefficients are used.
c Thanks to V.Vasilyev for correcting formula in previous DECAY0 version
c for case of two conversion electrons emitted.
	if    (npg1064.ne.0 .and. npg570.ne.0) then
	   a2=0.231
	   a4=-0.023
	   np1064=npg1064
	   np570=npg570
	elseif(npe1064.ne.0 .and. npg570.ne.0) then
	   a2=0.223
	   a4=-0.020
	   np1064=npe1064
	   np570=npg570
	elseif(npg1064.ne.0 .and. npe570.ne.0) then
	   a2=0.275
	   a4=-0.012
	   np1064=npg1064
	   np570=npe570
	elseif(npe1064.ne.0 .and. npe570.ne.0) then
	   a2=0.271
	   a4=-0.010
	   np1064=npe1064
	   np570=npe570
	else
	   return
	endif
	p1064=sqrt(pmoment(1,np1064)**2+pmoment(2,np1064)**2+
     +             pmoment(3,np1064)**2)
	p570=sqrt(pmoment(1,np570)**2+pmoment(2,np570)**2+
     +            pmoment(3,np570)**2)
	twopi=6.2831853
3	phi1=twopi*rnd1(d)
	ctet1=1.-2.*rnd1(d)
	stet1=sqrt(1.-ctet1*ctet1)
	phi2=twopi*rnd1(d)
	ctet2=1.-2.*rnd1(d)
	stet2=sqrt(1.-ctet2*ctet2)
	ctet=ctet1*ctet2+stet1*stet2*cos(phi1-phi2)
	p2=(3.*ctet**2-1.)/2.
	p4=(35.*ctet**4-30.*ctet**2+3.)/8.
	if(rnd1(d)*(1.+abs(a2)+abs(a4)).gt.1.+a2*p2+a4*p4) go to 3
	pmoment(1,np1064)=p1064*stet1*cos(phi1)
	pmoment(2,np1064)=p1064*stet1*sin(phi1)
	pmoment(3,np1064)=p1064*ctet1
	pmoment(1,np570)=p570*stet2*cos(phi2)
	pmoment(2,np570)=p570*stet2*sin(phi2)
	pmoment(3,np570)=p570*ctet2
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Bi208(tcnuc,tdnuc)
c Scheme of Bi208 decay (NDS 47(1986)797 + ToI-1978).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 17.12.1995; 10.05.2005.
	thnuc=1.161288E+13
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.43.6)                    Egamma=0.088 ! EC-K 43.6%
	if(pdecay.gt.43.6.and.pdecay.le.83.8) Egamma=0.016 ! EC-L 40.2%
	if(pdecay.gt.83.8)                    Egamma=0.004 ! EC-M 16.2%
	call gamma(Egamma,0.,0.,t)
c-----------------------------------------------------------------------
2615	thlev=32.e-12
	call nucltransK(2.615,0.088,8.5e-3,4.3e-4,tclev,thlev,tdlev)
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Bi210(tcnuc,tdnuc)
c Scheme of Bi210 decay ("Table of Isotopes", 7th ed., 1978).
c Three-figured labels correspond to energies of 206Tl excited
c levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 14.08.1992, 22.10.1995; 30.10.2006.
c Update to NDS 99(2003)949 and empirical correction to the beta shape, VIT, 28.10.2006. 
	thnuc=433036.8
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.1.32e-4) go to 10000   !  0.000132% alfa to 206Tl
	                      go to 20000   ! 99.999868% beta to 210Po
c-----------------------------------------------------------------------
10000	palfa=100.*rnd1(d)
	if(palfa.le.60.) go to 304   ! 60%
	                 go to 265   ! 40%
c-----------------------------------------------------------------------
304	call alpha(4.656,0.,0.,t)
	thlev=4.e-12
	call nucltransK(0.304,0.086,3.9e-1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
265	call alpha(4.694,0.,0.,t)
	thlev=3.e-9
	call nucltransK(0.265,0.086,1.6e-1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c20000	call beta(1.161,84.,0.,0.,t)
c experimental correction factor to allowed spectrum from
c H.Daniel, NP 31(1962)293 and RMP 40(1968)659:
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1
20000	call beta1(1.162,84.,0.,0.,t,28.466,0.578,-0.658,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Bi212(tcnuc,tdnuc)
c Scheme of Bi212 decay ("Table of Isotopes", 7th ed., 1978).
c Two-, three- and four-figured labels correspond to energies of
c 208Tl or 212Po excited levels in keV. Beta-alfa decays to 208Pb
c are not considered (p=0.014%).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 4.08.1992, 22.10.1995.
	thnuc=3636.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=rnd1(d)
	if(pdecay.le.0.36) go to 10000   !  36% alfa to 208Tl
	                   go to 20000   !  64% beta to 212Po
c-----------------------------------------------------------------------
10000	palfa=100.*rnd1(d)
	if(palfa.le. 1.10) go to   493   !   1.10%
	if(palfa.le. 1.25) go to   473   !   0.15%
	if(palfa.le. 2.92) go to   328   !   1.67%
	if(palfa.le.72.80) go to    40   !  69.88%
	                   go to 10001   !  27.20%
c-----------------------------------------------------------------------
493	call alpha(5.607,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 5.) go to 49301   !  5%
	if(p.le.99.) go to 49302   ! 94%
	             go to 49303   !  1%
49301	call nucltransK(0.493,0.086,2.8e-2,0.,tclev,thlev,tdlev)
	return
49302	call nucltransK(0.453,0.086,0.18,0.,tclev,thlev,tdlev)
	go to 40000
49303	call nucltransK(0.164,0.086,0.75,0.,tclev,thlev,tdlev)
	go to 32800
c-----------------------------------------------------------------------
473	call alpha(5.626,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.68.) go to 47301   ! 68%
	if(p.le.87.) go to 47302   ! 19%
	             go to 47303   ! 13%
47301	call nucltransK(0.474,0.086,0.14,0.,tclev,thlev,tdlev)
	return
47302	call nucltransK(0.434,0.086,0.14,0.,tclev,thlev,tdlev)
	go to 40000
47303	call nucltransK(0.145,0.086,2.8,0.,tclev,thlev,tdlev)
	go to 32800
c-----------------------------------------------------------------------
328	call alpha(5.769,0.,0.,t)
32800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.29.) go to 32801   ! 29%
	             go to 32802   ! 71%
32801	call nucltransK(0.328,0.086,0.33,0.,tclev,thlev,tdlev)
	return
32802	call nucltransK(0.288,0.086,0.53,0.,tclev,thlev,tdlev)
	go to 40000
c-----------------------------------------------------------------------
40	call alpha(6.051,0.,0.,t)
40000	thlev=6.e-12
	call nucltransK(0.040,0.015,22.55,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10001	call alpha(6.090,0.,0.,t)
	return
c-----------------------------------------------------------------------
20000	pbeta=64.*rnd1(d)
	if(pbeta.le. 0.660) go to  1806  !  0.660%
	if(pbeta.le. 0.687) go to  1801  !  0.027%
	if(pbeta.le. 0.937) go to  1680  !  0.250%
	if(pbeta.le. 2.837) go to  1621  !  1.900%
	if(pbeta.le. 4.337) go to  1513  !  1.500%
	if(pbeta.le. 8.737) go to   727  !  4.400%
	                    go to 20001  ! 55.263%
c-----------------------------------------------------------------------
1806	call beta(0.440,84.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.17.) go to 18061   ! 17%
	             go to 18062   ! 83%
18061	call nucltransK(1.806,0.093,2.6e-2,1.7e-4,tclev,thlev,tdlev)
	return
18062	call nucltransK(1.079,0.093,2.0e-2,0.,tclev,thlev,tdlev)
	go to 72700
c-----------------------------------------------------------------------
1801	call beta(0.445,84.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.35.) go to 18011   ! 35%
	             go to 18012   ! 65%
18011	call electron(1.708,tclev,thlev,tdlev)       ! only ec
	call gamma(0.093,0.,0.,tdlev)
	return
18012	call nucltransK(1.074,0.093,7.0e-3,0.,tclev,thlev,tdlev)
	go to 72700
c-----------------------------------------------------------------------
1680	call beta(0.566,84.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.28.) go to 16801   ! 28%
	             go to 16802   ! 72%
16801	call nucltransK(1.680,0.093,2.8e-3,1.0e-4,tclev,thlev,tdlev)
	return
16802	call nucltransK(0.952,0.093,4.5e-2,0.,tclev,thlev,tdlev)
	go to 72700
c-----------------------------------------------------------------------
1621	call beta(0.625,84.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.80.) go to 16211   ! 80%
	             go to 16212   ! 20%
16211	call nucltransK(1.621,0.093,7.0e-3,1.2e-4,tclev,thlev,tdlev)
	return
16212	call nucltransK(0.893,0.093,4.5e-2,0.,tclev,thlev,tdlev)
	go to 72700
c-----------------------------------------------------------------------
1513	call beta(0.733,84.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.22.) go to 15131   ! 22%
	             go to 15132   ! 78%
15131	call nucltransK(1.513,0.093,3.5e-3,0.7e-4,tclev,thlev,tdlev)
	return
15132	call nucltransK(0.786,0.093,4.1e-2,0.,tclev,thlev,tdlev)
	go to 72700
c-----------------------------------------------------------------------
727	call beta(1.519,84.,0.,0.,t)
72700	thlev=0.
	call nucltransK(0.727,0.093,1.7e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
20001	call beta(2.246,84.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Bi214(tcnuc,tdnuc)
c Scheme of Bi214 decay ("Table of Isotopes", 7th ed., 1978).
c Two-, three- and four-figured labels correspond to energies of
c 210Tl or 214Po excited levels in keV. Beta-alfa decays to 210Pb
c are not considered (p=2.8e-3%).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.08.1992, 22.10.1995.
c VIT, 31.05.2005, updated to NDS 99(2003)649. Not well known alpha decays to 
c 210Tl levels with E>253 keV are omitted.
	thnuc=1194.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.0.021) go to 10000   !  0.021% alfa to 210Tl
	                    go to 20000   ! 99.979% beta to 214Po
c-----------------------------------------------------------------------
10000	palfa=100.*rnd1(d)
	if(palfa.le. 5.86) go to   253   !  5.86%
	if(palfa.le.60.36) go to    63   ! 54.50%
	                   go to 10001   ! 39.64%
c-----------------------------------------------------------------------
253	call alpha(5.273,0.,0.,t)
	thlev=0.
	call nucltransK(0.191,0.086,1.3,0.,tclev,thlev,tdlev)
	go to 63000
c-----------------------------------------------------------------------
63	call alpha(5.452,0.,0.,t)
63000	thlev=0.
	call nucltransK(0.063,0.015,6.48,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10001	call alpha(5.516,0.,0.,t)
	return
c-----------------------------------------------------------------------
20000	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.001) go to  3184   !  0.001%
	if(pbeta.le. 0.002) go to  3160   !  0.001%
	if(pbeta.le. 0.003) go to  3143   !  0.001%
	if(pbeta.le. 0.008) go to  3082   !  0.005%
	if(pbeta.le. 0.012) go to  3054   !  0.004%
	if(pbeta.le. 0.017) go to  3014   !  0.005%
	if(pbeta.le. 0.024) go to  3003   !  0.007%
	if(pbeta.le. 0.034) go to  3000   !  0.010%
	if(pbeta.le. 0.043) go to  2986   !  0.009%
	if(pbeta.le. 0.060) go to  2979   !  0.017%
	if(pbeta.le. 0.102) go to  2941   !  0.042%
	if(pbeta.le. 0.104) go to  2935   !  0.002%
	if(pbeta.le. 0.105) go to  2929   !  0.001%
	if(pbeta.le. 0.128) go to  2922   !  0.023%
	if(pbeta.le. 0.129) go to  2920   !  0.001%
	if(pbeta.le. 0.134) go to  2897   !  0.005%
	if(pbeta.le. 0.145) go to  2894   !  0.011%
	if(pbeta.le. 0.156) go to  2880   !  0.011%
	if(pbeta.le. 0.170) go to  2870   !  0.014%
	if(pbeta.le. 0.184) go to  2861   !  0.014%
	if(pbeta.le. 0.186) go to  2827   !  0.002%
	if(pbeta.le. 0.222) go to  2786   !  0.036%
	if(pbeta.le. 0.258) go to  2770   !  0.036%
	if(pbeta.le. 0.819) go to  2729   !  0.561%
	if(pbeta.le. 1.097) go to  2719   !  0.278%
	if(pbeta.le. 1.151) go to  2699   !  0.054%
	if(pbeta.le. 1.204) go to  2698   !  0.053%
	if(pbeta.le. 1.467) go to  2695   !  0.263%
	if(pbeta.le. 1.594) go to  2662   !  0.127%
	if(pbeta.le. 1.615) go to  2631   !  0.021%
	if(pbeta.le. 1.699) go to  2605   !  0.084%
	if(pbeta.le. 1.752) go to  2545   !  0.053%
	if(pbeta.le. 1.892) go to  2508   !  0.140%
	if(pbeta.le. 2.085) go to  2505   !  0.193%
	if(pbeta.le. 3.417) go to  2482   !  1.332%
	if(pbeta.le. 6.232) go to  2448   !  2.815%
	if(pbeta.le. 6.312) go to  2423   !  0.080%
	if(pbeta.le. 6.872) go to  2293   !  0.560%
	if(pbeta.le. 7.073) go to  2266   !  0.201%
	if(pbeta.le.12.802) go to  2204   !  5.729%
	if(pbeta.le.13.635) go to  2193   !  0.833%
	if(pbeta.le.14.056) go to  2148   !  0.421%
	if(pbeta.le.18.323) go to  2119   !  4.267%
	if(pbeta.le.18.419) go to  2088   !  0.096%
	if(pbeta.le.20.623) go to  2017   !  2.204%
	if(pbeta.le.21.995) go to  2011   !  1.372%
	if(pbeta.le.23.137) go to  1995   !  1.142%
	if(pbeta.le.24.730) go to  1890   !  1.593%
	if(pbeta.le.32.923) go to  1847   !  8.193%
	if(pbeta.le.49.996) go to  1764   ! 17.073%
	if(pbeta.le.50.109) go to  1743   !  0.113%
	if(pbeta.le.67.963) go to  1730   ! 17.854%
	if(pbeta.le.68.113) go to  1713   !  0.150%
	if(pbeta.le.68.834) go to  1661   !  0.721%
	if(pbeta.le.71.789) go to  1543   !  2.955%
	if(pbeta.le.72.600) go to  1415   !  0.811%
	if(pbeta.le.80.042) go to  1378   !  7.442%
	if(pbeta.le.81.745) go to   609   !  1.703%
	                    go to 20001   ! 18.255%
c-----------------------------------------------------------------------
3184	call beta(0.088,84.,0.,0.,t)
31840	thlev=0.
	call nucltransK(3.184,0.093,4.0e-4,8.0e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
3160	call beta(0.112,84.,0.,0.,t)
31600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.41.) go to 31601   ! 41%
	             go to 31602   ! 59%
31601	call nucltransK(3.160,0.093,4.0e-4,8.0e-4,tclev,thlev,tdlev)
	return
31602	call nucltransK(2.551,0.093,6.0e-4,4.6e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
3143	call beta(0.129,84.,0.,0.,t)
31430	thlev=0.
	call nucltransK(3.143,0.093,4.0e-4,8.0e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
3082	call beta(0.190,84.,0.,0.,t)
30820	thlev=0.
	call nucltransK(3.082,0.093,4.2e-4,8.0e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
3054	call beta(0.218,84.,0.,0.,t)
30540	thlev=0.
	p=100.*rnd1(d)
	if(p.le.60.0) go to 30541   ! 60.0%
	if(p.le.82.9) go to 30542   ! 22.9%
	              go to 30543   ! 17.1%
30541	call nucltransK(3.054,0.093,1.0e-3,8.0e-4,tclev,thlev,tdlev)
	return
30542	call nucltransK(2.445,0.093,1.5e-3,5.2e-4,tclev,thlev,tdlev)
	go to 60900
30543	call nucltransK(1.637,0.093,3.5e-3,0.5e-4,tclev,thlev,tdlev)
	go to 14150
c-----------------------------------------------------------------------
3014	call beta(0.258,84.,0.,0.,t)
30140	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.9) go to 30141   !  0.9%
	if(p.le.27.8) go to 30142   ! 26.9%
	if(p.le.41.7) go to 30143   ! 13.4%
	if(p.le.61.8) go to 30144   ! 20.6%
	              go to 30145   ! 38.2%
30141	call nucltransK(2.405,0.093,3.0e-3,4.1e-4,tclev,thlev,tdlev)
	go to 60900
30142	call nucltransK(1.636,0.093,7.0e-3,1.2e-4,tclev,thlev,tdlev)
	go to 13780
30143	call nucltransK(1.598,0.093,8.0e-3,1.1e-4,tclev,thlev,tdlev)
	go to 14150
30144	call nucltransK(1.471,0.093,9.0e-3,0.9e-4,tclev,thlev,tdlev)
	go to 15430
30145	call nucltransK(1.285,0.093,1.2e-2,0.5e-4,tclev,thlev,tdlev)
	go to 17300
c-----------------------------------------------------------------------
3003	call beta(0.269,84.,0.,0.,t)
30030	thlev=0.
	call nucltransK(1.156,0.093,1.8e-2,3.0e-6,tclev,thlev,tdlev)
	go to 18470
c-----------------------------------------------------------------------
3000	call beta(0.272,84.,0.,0.,t)
30000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.84.6) go to 30001   ! 84.6%
	              go to 30002   ! 15.4%
30001	call nucltransK(3.000,0.093,1.4e-3,6.5e-4,tclev,thlev,tdlev)
	return
30002	call nucltransK(2.391,0.093,2.8e-3,4.0e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2986	call beta(0.286,84.,0.,0.,t)
29860	thlev=0.
	p=100.*rnd1(d)
	if(p.le.83.0) go to 29861   ! 83.0%
	              go to 29862   ! 17.0%
29861	call nucltransK(2.377,0.093,2.8e-3,4.0e-4,tclev,thlev,tdlev)
	go to 60900
29862	call nucltransK(1.711,0.093,6.0e-3,1.3e-4,tclev,thlev,tdlev)
	go to 12750
c-----------------------------------------------------------------------
2979	call beta(0.293,84.,0.,0.,t)
29790	thlev=0.
	p=100.*rnd1(d)
	if(p.le.83.6) go to 29791   ! 83.6%
	              go to 29792   ! 16.4%
29791	call nucltransK(2.979,0.093,1.4e-3,6.5e-4,tclev,thlev,tdlev)
	return
29792	call nucltransK(2.369,0.093,2.8e-3,4.0e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2941	call beta(0.331,84.,0.,0.,t)
29410	thlev=0.
	p=100.*rnd1(d)
	if(p.le.52.1) go to 29411   ! 52.1%
	if(p.le.71.7) go to 29412   ! 19.6%
	              go to 29413   ! 28.3%
29411	call nucltransK(2.331,0.093,3.0e-3,3.8e-4,tclev,thlev,tdlev)
	go to 60900
29412	call nucltransK(1.666,0.093,7.0e-3,1.1e-4,tclev,thlev,tdlev)
	go to 12750
29413	call nucltransK(1.279,0.093,1.2e-2,1.5e-5,tclev,thlev,tdlev)
	go to 16610
c-----------------------------------------------------------------------
2935	call beta(0.337,84.,0.,0.,t)
29350	thlev=0.
	p=100.*rnd1(d)
	if(p.le.21.3) go to 29351   ! 21.3%
	              go to 29352   ! 78.7%
29351	call nucltransK(2.935,0.093,1.5e-3,6.3e-4,tclev,thlev,tdlev)
	return
29352	call nucltransK(2.325,0.093,3.0e-3,3.7e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2929	call beta(0.343,84.,0.,0.,t)
29290	thlev=0.
	p=100.*rnd1(d)
	if(p.le.73.3) go to 29291   ! 73.3%
	              go to 29292   ! 26.7%
29291	call nucltransK(2.929,0.093,1.5e-3,6.2e-4,tclev,thlev,tdlev)
	return
29292	call nucltransK(2.319,0.093,3.0e-3,3.7e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2922	call beta(0.350,84.,0.,0.,t)
29220	thlev=0.
	p=100.*rnd1(d)
	if(p.le.60.9) go to 29221   ! 60.9%
	              go to 29222   ! 39.1%
29221	call nucltransK(2.922,0.093,4.5e-4,8.0e-4,tclev,thlev,tdlev)
	return
29222	call nucltransK(2.312,0.093,3.0e-3,3.7e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2920	call beta(0.352,84.,0.,0.,t)
29200	thlev=0.
	call nucltransK(2.310,0.093,3.0e-3,3.7e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2897	call beta(0.375,84.,0.,0.,t)
28970	thlev=0.
	call nucltransK(2.287,0.093,3.0e-3,3.6e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2894	call beta(0.378,84.,0.,0.,t)
28940	thlev=0.
	p=100.*rnd1(d)
	if(p.le.26.1) go to 28941   ! 26.1%
	if(p.le.48.3) go to 28942   ! 22.2%
	if(p.le.78.3) go to 28943   ! 30.0%
	              go to 28944   ! 21.7%
28941	call nucltransK(2.894,0.093,1.7e-3,6.1e-4,tclev,thlev,tdlev)
	return
28942	call nucltransK(2.284,0.093,3.0e-3,3.6e-4,tclev,thlev,tdlev)
	go to 60900
28943	call nucltransK(1.516,0.093,9.0e-3,6.7e-5,tclev,thlev,tdlev)
	go to 13780
28944	call nucltransK(0.626,0.093,7.5e-2,0.,tclev,thlev,tdlev)
	go to 22660
c-----------------------------------------------------------------------
2880	call beta(0.392,84.,0.,0.,t)
28800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.87.6) go to 28801   ! 87.6%
	              go to 28802   ! 12.4%
28801	call nucltransK(2.880,0.093,1.7e-3,6.0e-4,tclev,thlev,tdlev)
	return
28802	call nucltransK(2.270,0.093,3.0e-3,3.5e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2870	call beta(0.402,84.,0.,0.,t)
28700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.63.5) go to 28701   ! 63.5%
	              go to 28702   ! 36.5%
28701	call nucltransK(2.260,0.093,3.0e-3,3.5e-4,tclev,thlev,tdlev)
	go to 60900
28702	call nucltransK(1.595,0.093,8.0e-3,9.1e-5,tclev,thlev,tdlev)
	go to 12750
c-----------------------------------------------------------------------
2861	call beta(0.411,84.,0.,0.,t)
28610	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.7) go to 28611   !  2.7%
	if(p.le.41.5) go to 28612   ! 38.8%
	              go to 28613   ! 58.5%
28611	call nucltransK(2.861,0.093,1.8e-3,6.0e-4,tclev,thlev,tdlev)
	return
28612	call nucltransK(2.252,0.093,3.5e-3,3.4e-4,tclev,thlev,tdlev)
	go to 60900
28613	call nucltransK(1.014,0.093,2.2e-2,0.,tclev,thlev,tdlev)
	go to 18470
c-----------------------------------------------------------------------
2827	call beta(0.445,84.,0.,0.,t)
28270	thlev=0.
	call nucltransK(2.827,0.093,1.8e-3,5.8e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
2786	call beta(0.486,84.,0.,0.,t)
27860	thlev=0.
	p=100.*rnd1(d)
	if(p.le.15.4) go to 27861   ! 15.4%
	if(p.le.24.4) go to 27862   !  9.0%
	if(p.le.63.6) go to 27863   ! 39.2%
	              go to 27864   ! 36.4%
27861	call nucltransK(2.786,0.093,1.8e-3,5.7e-4,tclev,thlev,tdlev)
	return
27862	call nucltransK(2.177,0.093,3.5e-3,3.1e-4,tclev,thlev,tdlev)
	go to 60900
27863	call nucltransK(1.021,0.093,1.2e-2,0.,tclev,thlev,tdlev)
	go to 17640
27864	call nucltransK(0.939,0.093,1.4e-2,0.,tclev,thlev,tdlev)
	go to 18470
c-----------------------------------------------------------------------
2770	call beta(0.502,84.,0.,0.,t)
27700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.54.6) go to 27701   ! 54.6%
	if(p.le.58.5) go to 27702   !  3.9%
	              go to 27703   ! 41.5%
27701	call nucltransK(2.770,0.093,1.8e-3,5.6e-4,tclev,thlev,tdlev)
	return
27702	call nucltransK(2.160,0.093,3.5e-3,3.1e-4,tclev,thlev,tdlev)
	go to 60900
27703	call nucltransK(1.393,0.093,1.0e-2,3.6e-5,tclev,thlev,tdlev)
	go to 13780
c-----------------------------------------------------------------------
2729	call beta(0.543,84.,0.,0.,t)
27290	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.2) go to 27291   !  1.2%
	if(p.le. 6.0) go to 27292   !  4.8%
	if(p.le.71.5) go to 27293   ! 65.5%
	if(p.le.79.4) go to 27294   !  7.9%
	if(p.le.82.6) go to 27295   !  3.2%
	if(p.le.85.7) go to 27296   !  3.1%
	              go to 27297   ! 14.3%
27291	call nucltransK(2.120,0.093,3.5e-3,2.9e-4,tclev,thlev,tdlev)
	go to 60900
27292	call nucltransK(1.067,0.093,2.1e-2,1.4e-7,tclev,thlev,tdlev)
	go to 16610
27293	call nucltransK(0.964,0.093,1.4e-2,0.,tclev,thlev,tdlev)
	go to 17640
27294	call nucltransK(0.734,0.093,2.7e-2,0.,tclev,thlev,tdlev)
	go to 19950
27295	call nucltransK(0.525,0.093,6.0e-2,0.,tclev,thlev,tdlev)
	go to 22040
27296	call nucltransK(0.520,0.093,7.0e-2,0.,tclev,thlev,tdlev)
	go to 22090
27297	call nucltransK(0.281,0.093,3.3e-1,0.,tclev,thlev,tdlev)
	go to 24480
c-----------------------------------------------------------------------
2719	call beta(0.553,84.,0.,0.,t)
27190	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.7) go to 27191   !  0.7%
	if(p.le.33.6) go to 27192   ! 32.9%
	if(p.le.41.8) go to 27193   !  8.2%
	if(p.le.83.6) go to 27194   ! 41.8%
	if(p.le.90.7) go to 27195   !  7.1%
	if(p.le.97.0) go to 27196   !  6.3%
	              go to 27197   !  3.0%
27191	call nucltransK(2.719,0.093,2.0e-3,5.4e-4,tclev,thlev,tdlev)
	return
27192	call nucltransK(2.110,0.093,3.5e-3,2.9e-4,tclev,thlev,tdlev)
	go to 60900
27193	call nucltransK(1.341,0.093,1.0e-2,2.6e-5,tclev,thlev,tdlev)
	go to 13780
27194	call nucltransK(1.304,0.093,1.0e-2,1.9e-5,tclev,thlev,tdlev)
	go to 14150
27195	call nucltransK(0.976,0.093,2.6e-2,0.,tclev,thlev,tdlev)
	go to 17430
27196	call nucltransK(0.709,0.093,2.9e-2,0.,tclev,thlev,tdlev)
	go to 20110
27197	call nucltransK(0.600,0.093,9.0e-2,0.,tclev,thlev,tdlev)
	go to 21190
c-----------------------------------------------------------------------
2699	call beta(0.573,84.,0.,0.,t)
26990	thlev=0.
	p=100.*rnd1(d)
	if(p.le.5.3) go to 26991   !  5.3%
	             go to 26992   ! 94.7%
26991	call nucltransK(2.699,0.093,2.0e-3,5.3e-4,tclev,thlev,tdlev)
	return
26992	call nucltransK(2.090,0.093,4.0e-3,2.8e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2698	call beta(0.574,84.,0.,0.,t)
26980	thlev=0.
	p=100.*rnd1(d)
	if(p.le.29.5) go to 26981   ! 29.5%
	if(p.le.44.8) go to 26982   ! 15.3%
	if(p.le.63.3) go to 26983   ! 18.5%
	if(p.le.76.0) go to 26984   ! 12.7%
	              go to 26985   ! 24.0%
26981	call nucltransK(1.156,0.093,1.6e-2,2.9e-6,tclev,thlev,tdlev)
	go to 15430
26982	call nucltransK(1.038,0.093,2.0e-2,0.,tclev,thlev,tdlev)
	go to 16610
26983	call nucltransK(0.935,0.093,2.8e-2,0.,tclev,thlev,tdlev)
	go to 17640
26984	call nucltransK(0.688,0.093,6.5e-2,0.,tclev,thlev,tdlev)
	go to 20110
26985	call nucltransK(0.494,0.093,7.0e-2,0.,tclev,thlev,tdlev)
	go to 22040
c-----------------------------------------------------------------------
2695	call beta(0.577,84.,0.,0.,t)
26950	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.9) go to 26951   ! 11.9%
	if(p.le.15.4) go to 26952   !  3.5%
	if(p.le.17.4) go to 26953   !  2.0%
	if(p.le.48.7) go to 26954   ! 30.7%
	if(p.le.57.3) go to 26955   !  9.2%
	if(p.le.59.6) go to 26956   !  2.3%
	if(p.le.72.3) go to 26957   ! 12.7%
	if(p.le.82.3) go to 26958   ! 10.0%
	if(p.le.88.4) go to 26959   !  6.1%
	if(p.le.90.7) go to 26960   !  2.3%
	              go to 26961   !  9.3%
26951	call nucltransK(2.695,0.093,2.0e-3,5.3e-4,tclev,thlev,tdlev)
	return
26952	call nucltransK(2.085,0.093,4.0e-3,2.8e-4,tclev,thlev,tdlev)
	go to 60900
26953	call nucltransK(1.420,0.093,9.5e-3,4.2e-5,tclev,thlev,tdlev)
	go to 12750
26954	call nucltransK(1.317,0.093,1.2e-2,2.1e-5,tclev,thlev,tdlev)
	go to 13780
26955	call nucltransK(1.033,0.093,2.2e-2,0.,tclev,thlev,tdlev)
	go to 16610
26956	call nucltransK(0.952,0.093,2.8e-2,0.,tclev,thlev,tdlev)
	go to 17430
26957	call nucltransK(0.930,0.093,1.5e-2,0.,tclev,thlev,tdlev)
	go to 17640
26958	call nucltransK(0.847,0.093,1.9e-2,0.,tclev,thlev,tdlev)
	go to 18470
26959	call nucltransK(0.700,0.093,3.0e-2,0.,tclev,thlev,tdlev)
	go to 19950
26960	call nucltransK(0.677,0.093,7.5e-2,0.,tclev,thlev,tdlev)
	go to 20170
26961	call nucltransK(0.486,0.093,8.0e-2,0.,tclev,thlev,tdlev)
	go to 22090
c-----------------------------------------------------------------------
2662	call beta(0.610,84.,0.,0.,t)
26620	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.2) go to 26621   !  0.2%
	if(p.le.55.0) go to 26622   ! 54.8%
	if(p.le.63.7) go to 26623   !  8.7%
	if(p.le.95.6) go to 26624   ! 31.9%
	              go to 26625   !  4.4%
26621	call nucltransK(2.662,0.093,2.0e-3,5.1e-4,tclev,thlev,tdlev)
	return
26622	call nucltransK(2.053,0.093,4.0e-3,2.6e-4,tclev,thlev,tdlev)
	go to 60900
26623	call nucltransK(1.284,0.093,1.3e-2,1.6e-5,tclev,thlev,tdlev)
	go to 13780
26624	call nucltransK(1.119,0.093,1.9e-2,1.2e-6,tclev,thlev,tdlev)
	go to 15430
26625	call nucltransK(0.950,0.093,2.8e-2,0.,tclev,thlev,tdlev)
	go to 17130
c-----------------------------------------------------------------------
2631	call beta(0.641,84.,0.,0.,t)
26310	thlev=0.
	p=100.*rnd1(d)
	if(p.le.3.8) go to 26311   !  3.8%
	             go to 26312   ! 96.2%
26311	call nucltransK(2.631,0.093,2.2e-3,5.0e-4,tclev,thlev,tdlev)
	return
26312	call nucltransK(2.022,0.093,4.0e-3,2.5e-4,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
2605	call beta(0.667,84.,0.,0.,t)
26050	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.5) go to 26051   !  0.5%
	if(p.le. 7.1) go to 26052   !  6.6%
	if(p.le.21.7) go to 26053   ! 14.6%
	if(p.le.44.2) go to 26054   ! 22.5%
	if(p.le.56.1) go to 26055   ! 11.9%
	              go to 26056   ! 43.9%
26051	call nucltransK(2.605,0.093,2.2e-3,4.9e-4,tclev,thlev,tdlev)
	return
26052	call nucltransK(1.995,0.093,4.5e-3,2.4e-4,tclev,thlev,tdlev)
	go to 60900
26053	call nucltransK(1.330,0.093,1.1e-2,2.4e-5,tclev,thlev,tdlev)
	go to 12750
26054	call nucltransK(0.943,0.093,2.8e-2,0.,tclev,thlev,tdlev)
	go to 16610
26055	call nucltransK(0.840,0.093,4.0e-2,0.,tclev,thlev,tdlev)
	go to 17640
26056	call nucltransK(0.396,0.093,1.3e-1,0.,tclev,thlev,tdlev)
	go to 22090
c-----------------------------------------------------------------------
2545	call beta(0.727,84.,0.,0.,t)
25450	thlev=0.
	p=100.*rnd1(d)
	if(p.le.77.4) go to 25451   ! 77.4%
	              go to 25452   ! 22.6%
25451	call nucltransK(1.936,0.093,3.0e-3,2.1e-4,tclev,thlev,tdlev)
	go to 60900
25452	call nucltransK(1.167,0.093,1.6e-2,3.6e-6,tclev,thlev,tdlev)
	go to 13780
c-----------------------------------------------------------------------
2508	call beta(0.764,84.,0.,0.,t)
25080	thlev=0.
	p=100.*rnd1(d)
	if(p.le.49.8) go to 25081   ! 49.8%
	if(p.le.84.8) go to 25082   ! 35.0%
	if(p.le.93.5) go to 25083   !  8.7%
	              go to 25084   !  6.5%
25081	call nucltransK(1.899,0.093,5.0e-3,2.0e-4,tclev,thlev,tdlev)
	go to 60900
25082	call nucltransK(1.130,0.093,1.8e-2,1.6e-6,tclev,thlev,tdlev)
	go to 13780
25083	call nucltransK(0.965,0.093,2.6e-2,0.,tclev,thlev,tdlev)
	go to 15430
25084	call nucltransK(0.497,0.093,7.0e-2,0.,tclev,thlev,tdlev)
	go to 20110
c-----------------------------------------------------------------------
2505	call beta(0.767,84.,0.,0.,t)
25050	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.0) go to 25051   !  3.0%
	if(p.le.86.0) go to 25052   ! 83.0%
	if(p.le.93.8) go to 25053   !  7.8%
	              go to 25054   !  6.2%
25051	call nucltransK(2.505,0.093,2.4e-3,4.5e-4,tclev,thlev,tdlev)
	return
25052	call nucltransK(1.896,0.093,5.0e-3,2.0e-4,tclev,thlev,tdlev)
	go to 60900
25053	call nucltransK(1.231,0.093,1.4e-2,9.2e-6,tclev,thlev,tdlev)
	go to 12750
25054	call nucltransK(0.962,0.093,2.6e-2,0.,tclev,thlev,tdlev)
	go to 15430
c-----------------------------------------------------------------------
2482	call beta(0.790,84.,0.,0.,t)
24820	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.1) go to 24821   !  0.1%
	if(p.le.16.7) go to 24822   ! 16.6%
	if(p.le.51.0) go to 24823   ! 34.3%
	if(p.le.56.9) go to 24824   !  5.9%
	if(p.le.58.3) go to 24825   !  1.4%
	if(p.le.70.7) go to 24826   ! 12.4%
	if(p.le.80.9) go to 24827   ! 10.2%
	if(p.le.81.4) go to 24828   !  0.5%
	if(p.le.83.5) go to 24829   !  2.1%
	if(p.le.84.8) go to 24830   !  1.3%
	              go to 24831   ! 15.2%
24821	call nucltransK(2.483,0.093,2.5e-3,4.4e-4,tclev,thlev,tdlev)
	return
24822	call nucltransK(1.873,0.093,5.0e-3,1.9e-4,tclev,thlev,tdlev)
	go to 60900
24823	call nucltransKLM(1.208,0.093,1.6e-3,0.017,2.5e-4,0.004,8.0e-5,
     +                    6.4e-5,tclev,thlev,tdlev)
	go to 12750
24824	call nucltransK(1.105,0.093,1.0e-2,7.8e-7,tclev,thlev,tdlev)
	go to 13780
24825	call nucltransKLM(0.940,0.093,1.4e-2,0.017,2.5e-3,0.004,5.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 15430
24826	call nucltransK(0.821,0.093,3.7e-2,0.,tclev,thlev,tdlev)
	go to 16610
24827	call nucltransKLM(0.753,0.093,2.4e-2,0.017,4.4e-3,0.004,6.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 17300
24828	call nucltransKLM(0.635,0.093,3.6e-2,0.017,7.0e-3,0.004,7.0e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 18470
24829	call nucltransKLM(0.488,0.093,8.9e-3,0.017,1.5e-3,0.004,4.5e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 19950
24830	call nucltransK(0.394,0.093,1.3e-1,0.,tclev,thlev,tdlev)
	go to 20880
24831	call nucltransK(0.274,0.093,3.6e-1,0.,tclev,thlev,tdlev)
	go to 22090
c-----------------------------------------------------------------------
2448	call beta(0.824,84.,0.,0.,t)
24480	thlev=0.
	p=100.*rnd1(d)
	if(p.le.54.3) go to 24481   ! 54.3%
	if(p.le.66.8) go to 24482   ! 12.5%
	if(p.le.68.6) go to 24483   !  1.8%
	if(p.le.78.1) go to 24484   !  9.5%
	if(p.le.80.8) go to 24485   !  2.7%
	if(p.le.83.7) go to 24486   !  2.9%
	if(p.le.94.4) go to 24487   ! 10.7%
	if(p.le.96.0) go to 24488   !  1.6%
	if(p.le.98.8) go to 24489   !  2.8%
	              go to 24490   !  1.2%
24481	call nucltransK(2.448,0.093,6.0e-4,9.4e-4,tclev,thlev,tdlev)
	return
24482	call nucltransK(1.838,0.093,1.2e-3,5.3e-4,tclev,thlev,tdlev)
	go to 60900
24483	call nucltransKLM(1.173,0.093,4.4e-3,0.017,8.3e-4,0.004,2.8e-4,
     +                    6.2e-6,tclev,thlev,tdlev)
	go to 12750
24484	call nucltransKLM(1.070,0.093,2.0e-3,0.017,3.1e-4,0.004,1.0e-4,
     +                    5.5e-6,tclev,thlev,tdlev)
	go to 13780
24485	call nucltransKLM(1.032,0.093,2.1e-3,0.017,3.3e-4,0.004,1.1e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 14150
24486	call nucltransKLM(0.904,0.093,2.7e-3,0.017,4.2e-4,0.004,1.4e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 15430
24487	call nucltransKLM(0.786,0.093,3.5e-3,0.017,5.5e-4,0.004,1.9e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 16610
24488	call nucltransKLM(0.705,0.093,4.3e-3,0.017,6.9e-4,0.004,2.2e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 17430
24489	call nucltransKLM(0.683,0.093,4.6e-3,0.017,7.3e-4,0.004,2.4e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 17640
24490	call nucltransKLM(0.453,0.093,8.0e-2,0.017,1.7e-2,0.004,5.6e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 19950
c-----------------------------------------------------------------------
2423	call beta(0.849,84.,0.,0.,t)
24230	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 7.2) go to 24231   !  7.2%
	if(p.le.24.5) go to 24232   ! 17.3%
	if(p.le.65.4) go to 24233   ! 40.9%
	if(p.le.74.8) go to 24234   !  9.4%
	              go to 24235   ! 25.2%
24231	call nucltransK(2.423,0.093,6.5e-4,9.2e-4,tclev,thlev,tdlev)
	return
24232	call nucltransK(1.814,0.093,1.2e-3,5.1e-4,tclev,thlev,tdlev)
	go to 60900
24233	call nucltransK(1.046,0.093,2.8e-3,1.4e-6,tclev,thlev,tdlev)
	go to 13780
24234	call nucltransK(0.693,0.093,5.7e-3,0.,tclev,thlev,tdlev)
	go to 17300
24235	call nucltransK(0.659,0.093,3.5e-2,0.,tclev,thlev,tdlev)
	go to 17640
c-----------------------------------------------------------------------
2293	call beta(0.979,84.,0.,0.,t)
22930	thlev=0.
	p=100.*rnd1(d)
	if(p.le.54.6) go to 22931   ! 54.6%
	if(p.le.93.2) go to 22932   ! 38.6%
	if(p.le.97.9) go to 22933   !  4.7%
	              go to 22934   !  2.1%
22931	call nucltransK(2.293,0.093,3.0e-3,3.6e-4,tclev,thlev,tdlev)
	return
22932	call nucltransK(1.684,0.093,7.0e-3,1.2e-4,tclev,thlev,tdlev)
	go to 60900
22933	call nucltransK(0.916,0.093,1.8e-2,0.,tclev,thlev,tdlev)
	go to 13780
22934	call nucltransK(0.878,0.093,2.0e-2,0.,tclev,thlev,tdlev)
	go to 14150
c-----------------------------------------------------------------------
2266	call beta(1.006,84.,0.,0.,t)
22660	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 9.0) go to 22661   !  9.0%
	if(p.le.31.9) go to 22662   ! 22.9%
	if(p.le.36.9) go to 22663   !  5.0%
	if(p.le.54.8) go to 22664   ! 17.9%
	if(p.le.90.6) go to 22665   ! 35.8%
	              go to 22666   !  9.4%
22661	call nucltransK(2.266,0.093,1.8e-3,4.4e-4,tclev,thlev,tdlev)
	return
22662	call nucltransK(1.657,0.093,1.3e-3,3.9e-4,tclev,thlev,tdlev)
	go to 60900
22663	call nucltransK(0.991,0.093,1.3e-2,0.,tclev,thlev,tdlev)
	go to 12750
22664	call nucltransK(0.723,0.093,2.8e-2,0.,tclev,thlev,tdlev)
	go to 15430
22665	call nucltransK(0.537,0.093,6.0e-2,0.,tclev,thlev,tdlev)
	go to 17300
22666	call nucltransK(0.502,0.093,7.0e-2,0.,tclev,thlev,tdlev)
	go to 17640
c-----------------------------------------------------------------------
22090	thlev=0.
	p=100.*rnd1(d)
	if(p.le.82.1) go to 22091   ! 82.1%
	              go to 22092   ! 17.9%
22091	call nucltransK(1.599,0.093,8.0e-3,9.2e-5,tclev,thlev,tdlev)
	go to 60900
22092	call nucltransK(0.934,0.093,2.8e-2,0.,tclev,thlev,tdlev)
	go to 12750
c-----------------------------------------------------------------------
2204	call beta(1.068,84.,0.,0.,t)
22040	thlev=0.
	p=100.*rnd1(d)
	if(p.le.87.9) go to 22041   ! 87.9%
	if(p.le.92.2) go to 22042   !  4.3%
	if(p.le.94.2) go to 22043   !  2.0%
	if(p.le.94.5) go to 22044   !  0.3%
	if(p.le.95.3) go to 22045   !  0.8%
	if(p.le.96.9) go to 22046   !  1.6%
	if(p.le.99.0) go to 22047   !  2.1%
	              go to 22048   !  1.0%
22041	call nucltransK(2.204,0.093,3.5e-3,3.2e-4,tclev,thlev,tdlev)
	return
22042	call nucltransK(1.595,0.093,5.5e-3,9.1e-5,tclev,thlev,tdlev)
	go to 60900
22043	call nucltransKLM(0.826,0.093,2.9e-2,0.017,5.0e-3,0.004,2.0e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 13780
22044	call nucltransKLM(0.789,0.093,3.3e-2,0.017,5.7e-3,0.004,1.9e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 14150
22045	call nucltransKLM(0.661,0.093,3.3e-2,0.017,6.0e-3,0.004,2.0e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 15430
22046	call nucltransKLM(0.543,0.093,5.0e-2,0.017,1.1e-2,0.004,9.0e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 17130
22047	call nucltransKLM(0.474,0.093,7.0e-2,0.017,1.5e-2,0.004,4.9e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 17300
22048	call nucltransKLM(0.461,0.093,1.4e-1,0.017,2.3e-2,0.004,7.4e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 17430
c-----------------------------------------------------------------------
2193	call beta(1.079,84.,0.,0.,t)
21930	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.1) go to 21931   !  4.1%
	if(p.le.87.2) go to 21932   ! 83.1%
	if(p.le.87.8) go to 21933   !  0.6%
	if(p.le.92.5) go to 21934   !  4.7%
	              go to 21935   !  7.5%
21931	call nucltransK(2.193,0.093,2.0e-3,4.1e-4,tclev,thlev,tdlev)
	return
21932	call nucltransK(1.583,0.093,5.4e-3,8.7e-5,tclev,thlev,tdlev)
	go to 60900
21933	call nucltransKLM(0.918,0.093,2.6e-3,0.017,4.1e-4,0.004,1.4e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 12750
21934	call nucltransKLM(0.815,0.093,1.9e-2,0.017,3.6e-3,0.004,1.4e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 13780
21935	call nucltransKLM(0.649,0.093,3.4e-2,0.017,6.0e-3,0.004,3.0e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 15430
c-----------------------------------------------------------------------
2148	call beta(1.122,84.,0.,0.,t)
21480	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.2) go to 21481   !  3.2%
	if(p.le.89.0) go to 21482   ! 85.8%
	if(p.le.93.1) go to 21483   !  4.1%
	              go to 21484   !  6.9%
21481	call nucltransK(2.148,0.093,3.5e-3,3.0e-4,tclev,thlev,tdlev)
	return
21482	call nucltransK(1.539,0.093,8.0e-3,1.0e-4,tclev,thlev,tdlev)
	go to 60900
21483	call nucltransK(0.873,0.093,3.5e-2,0.,tclev,thlev,tdlev)
	go to 12750
21484	call nucltransK(0.770,0.093,4.5e-2,0.,tclev,thlev,tdlev)
	go to 13780
c-----------------------------------------------------------------------
2119	call beta(1.151,84.,0.,0.,t)
21190	thlev=0.
	p=100.*rnd1(d)
	if(p.le.26.7) go to 21191   ! 26.7%
	if(p.le.76.4) go to 21192   ! 49.7%
	if(p.le.77.3) go to 21193   !  0.9%
	if(p.le.89.0) go to 21194   ! 11.7%
	              go to 21195   ! 11.0%
21191	call nucltransK(2.119,0.093,3.5e-3,2.9e-4,tclev,thlev,tdlev)
	return
21192	call nucltransK(1.509,0.093,6.3e-3,6.5e-5,tclev,thlev,tdlev)
	go to 60900
21193	call nucltransK(0.741,0.093,3.1e-2,0.,tclev,thlev,tdlev)
	go to 13780
21194	call nucltransKLM(0.703,0.093,4.5e-2,0.017,7.6e-3,0.004,2.6e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 14150
21195	call nucltransKLM(0.389,0.093,2.1e-1,0.017,3.7e-2,0.004,1.2e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 17300
c-----------------------------------------------------------------------
2088	call beta(1.181,84.,0.,0.,t)
20880	thlev=0.
	p=100.*rnd1(d)
	if(p.le.40.5) go to 20881   ! 40.5%
	              go to 20882   ! 59.5%
20881	call nucltransK(1.479,0.093,9.0e-3,5.7e-5,tclev,thlev,tdlev)
	go to 60900
20882	call nucltransK(0.711,0.093,6.0e-2,0.,tclev,thlev,tdlev)
	go to 13780
c-----------------------------------------------------------------------
2017	call beta(1.253,84.,0.,0.,t)
20170	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.27) go to 20171   !  0.27%
	if(p.le.98.01) go to 20172   ! 97.74%
	if(p.le.99.41) go to 20173   !  1.40%
	if(p.le.99.75) go to 20174   !  0.34%
	               go to 20175   !  0.25%
20171	p=100.*rnd1(d)
	if(p.le.95.08) then                       ! electron conversion
	   call electron(1.923,tclev,thlev,tdlev)          
	   call gamma(0.093,0.,0.,tdlev)
	else                                      ! pair conversion
	   call pair(0.995,tclev,thlev,tdlev)
	endif
	return
20172	call nucltransKLM(1.408,0.093,3.1e-3,0.017,5.7e-4,0.004,1.9e-4,
     +                    5.7e-5,tclev,thlev,tdlev)
	go to 60900
20173	call nucltransKLM(0.640,0.093,1.4e-2,0.017,3.7e-3,0.004,1.2e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 13780
20174	call nucltransKLM(0.356,0.093,4.6e-2,0.017,2.4e-2,0.004,8.1e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 16610
20175	call nucltransKLM(0.253,0.093,6.9e-1,0.017,1.2e-1,0.004,3.8e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 17640
c-----------------------------------------------------------------------
2011	call beta(1.259,84.,0.,0.,t)
20110	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.4) go to 20111   !  3.4%
	if(p.le.94.7) go to 20112   ! 91.3%
	if(p.le.98.7) go to 20113   !  4.0%
	              go to 20114   !  1.3%
20111	call nucltransK(2.011,0.093,2.2e-3,3.2e-4,tclev,thlev,tdlev)
	return
20112	call nucltransKLM(1.402,0.093,4.4e-3,0.017,7.7e-4,0.004,2.3e-4,
     +                    3.8e-5,tclev,thlev,tdlev)
	go to 60900
20113	call nucltransK(0.633,0.093,4.5e-2,0.,tclev,thlev,tdlev)
	go to 13780
20114	call nucltransK(0.595,0.093,5.3e-2,0.,tclev,thlev,tdlev)
	go to 14150
c-----------------------------------------------------------------------
1995	call beta(1.275,84.,0.,0.,t)
19950	thlev=0.
	p=100.*rnd1(d)
	if(p.le.60.3) go to 19951   ! 60.3%
	if(p.le.90.8) go to 19952   ! 30.5%
	if(p.le.93.5) go to 19953   !  2.7%
	              go to 19954   !  6.5%
19951	call nucltransKLM(1.385,0.093,1.3e-3,0.017,2.0e-4,0.004,6.4e-5,
     +                    1.8e-4,tclev,thlev,tdlev)
	go to 60900
19952	call nucltransKLM(0.720,0.093,1.1e-2,0.017,2.7e-3,0.004,9.3e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 12750
19953	call nucltransK(0.617,0.093,6.8e-3,0.,tclev,thlev,tdlev)
	go to 13780
19954	call nucltransKLM(0.333,0.093,2.0e-2,0.017,3.5e-3,0.004,1.1e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 16610
c-----------------------------------------------------------------------
1890	call beta(1.380,84.,0.,0.,t)
18900	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 5.0) go to 18901   !  5.0%
	if(p.le.96.2) go to 18902   ! 91.2%
	              go to 18903   !  3.8%
18901	call nucltransK(1.890,0.093,2.8e-3,2.6e-4,tclev,thlev,tdlev)
	return
18902	call nucltransKLM(1.281,0.093,9.5e-3,0.017,1.6e-3,0.004,5.5e-4,
     +                    1.6e-5,tclev,thlev,tdlev)
	go to 60900
18903	call nucltransKLM(0.616,0.093,5.6e-3,0.017,9.0e-4,0.004,3.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 12750
c-----------------------------------------------------------------------
1847	call beta(1.423,84.,0.,0.,t)
18470	thlev=0.
	p=100.*rnd1(d)
	if(p.le.25.7) go to 18471   ! 25.7%
	if(p.le.97.0) go to 18472   ! 71.3%
	if(p.le.97.3) go to 18473   !  0.3%
	if(p.le.98.2) go to 18474   !  0.9%
	              go to 18475   !  1.8%
18471	call nucltransK(1.847,0.093,2.5e-3,2.4e-4,tclev,thlev,tdlev)
	return
18472	call nucltransKLM(1.238,0.093,1.0e-2,0.017,1.8e-3,0.004,5.5e-4,
     +                    1.0e-5,tclev,thlev,tdlev)
	go to 60900
18473	call nucltransKLM(0.832,0.093,8.2e-3,0.017,1.8e-3,0.004,6.4e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 10150
18474	call nucltransKLM(0.573,0.093,6.4e-3,0.017,1.1e-3,0.004,3.4e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 12750
18475	call nucltransKLM(0.470,0.093,8.0e-2,0.017,1.6e-2,0.004,5.1e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 13780
c-----------------------------------------------------------------------
1764	call beta(1.505,84.,0.,0.,t)
17640	thlev=0.
	p=100.*rnd1(d)
	if(p.le.87.61) go to 17641   ! 87.61%
	if(p.le.97.01) go to 17642   !  9.40%
	if(p.le.99.06) go to 17643   !  2.05%
	if(p.le.99.97) go to 17644   !  0.91%
	               go to 17645   !  0.03%
17641	call nucltransK(1.764,0.093,6.0e-3,1.5e-4,tclev,thlev,tdlev)
	return
17642	call nucltransKLM(1.155,0.093,1.2e-2,0.017,2.0e-3,0.004,6.3e-4,
     +                    2.8e-6,tclev,thlev,tdlev)
	go to 60900
17643	call nucltransKLM(0.387,0.093,1.3e-1,0.017,2.8e-2,0.004,8.9e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 13780
17644	call nucltransKLM(0.349,0.093,2.9e-1,0.017,5.0e-2,0.004,1.6e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 14150
17645	call nucltransKLM(0.221,0.093,5.6e-1,0.017,1.6e-1,0.004,5.4e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 15430
c-----------------------------------------------------------------------
1743	call beta(1.527,84.,0.,0.,t)
17430	thlev=0.
	call nucltransKLM(1.134,0.093,4.7e-3,0.017,9.0e-4,0.004,2.9e-4,
     +                    2.8e-6,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
1730	call beta(1.540,84.,0.,0.,t)
17300	thlev=0.
	p=100.*rnd1(d)
	if(p.le.15.66) go to 17301   ! 15.66%
	if(p.le.97.92) go to 17302   ! 82.26%
	if(p.le.99.55) go to 17303   !  1.63%
	               go to 17304   !  0.45%
17301	call nucltransK(1.730,0.093,2.7e-3,1.9e-4,tclev,thlev,tdlev)
	return
17302	call nucltransKLM(1.120,0.093,1.3e-2,0.017,2.2e-3,0.004,6.7e-4,
     +                    1.2e-6,tclev,thlev,tdlev)
	go to 60900
17303	call nucltransKLM(0.455,0.093,1.0e-2,0.017,1.7e-3,0.004,5.3e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 12750
17304	call nucltransKLM(0.352,0.093,1.6e-1,0.017,3.7e-2,0.004,1.2e-2,
     +                    0.,tclev,thlev,tdlev)
	go to 13780
c-----------------------------------------------------------------------
1713	call beta(1.540,84.,0.,0.,t)
17130	thlev=0.
	p=100.*rnd1(d)
	if(p.le.65.36) go to 17131   ! 65.36%
	               go to 17132   ! 34.64%
17131	call nucltransK(1.104,0.093,1.2e-2,7.6e-7,tclev,thlev,tdlev)
	go to 60900
17132	call nucltransK(0.698,0.093,6.0e-2,0.,tclev,thlev,tdlev)
	go to 10150
c-----------------------------------------------------------------------
1661	call beta(1.609,84.,0.,0.,t)
16610	thlev=0.
	p=100.*rnd1(d)
	if(p.le.78.23) go to 16611   ! 78.23%
	               go to 16612   ! 21.77%
16611	call nucltransK(1.661,0.093,3.0e-3,1.5e-4,tclev,thlev,tdlev)
	return
16612	call nucltransK(1.052,0.093,1.5e-2,0.,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
1543	call beta(1.727,84.,0.,0.,t)
15430	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.00) go to 15431   !  6.00%
	if(p.le.99.26) go to 15432   ! 93.26%
	if(p.le.99.38) go to 15433   !  0.12%
	               go to 15434   !  0.62%
15431	call nucltransK(1.543,0.093,2.7e-3,1.1e-4,tclev,thlev,tdlev)
	return
15432	call nucltransKLM(0.934,0.093,2.0e-2,0.017,3.5e-3,0.004,1.2e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 60900
15433	call nucltransKLM(0.528,0.093,2.0e-2,0.017,6.4e-3,0.004,2.1e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 10150
15434	call nucltransKLM(0.269,0.093,3.3e-2,0.017,5.8e-3,0.004,1.8e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 12750
c-----------------------------------------------------------------------
1415	call beta(1.855,84.,0.,0.,t)
14150	thlev=99.e-12
	p=100.*rnd1(d)
	if(p.le.28.05) go to 14151   ! 28.05%
	               go to 14152   ! 71.95%
14151	p=100.*rnd1(d)
	if(p.le.99.63) then                       ! electron conversion
	   call electron(1.322,tclev,thlev,tdlev)          
	   call gamma(0.093,0.,0.,tdlev)
	else                                      ! pair conversion
	   call pair(0.393,tclev,thlev,tdlev)
	endif
	return
14152	call nucltransKLM(0.806,0.093,8.7e-3,0.017,2.0e-3,0.004,6.6e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
1378	call beta(1.892,84.,0.,0.,t)
13780	thlev=0.
	p=100.*rnd1(d)
	if(p.le.44.47) go to 13781   ! 44.47%
	               go to 13782   ! 55.53%
13781	call nucltransKLM(1.378,0.093,3.3e-3,0.017,5.9e-4,0.004,2.0e-4,
     +                    4.8e-5,tclev,thlev,tdlev)
	return
13782	call nucltransKLM(0.768,0.093,1.3e-2,0.017,2.7e-3,0.004,9.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
12750	thlev=0.
	call nucltransKLM(0.665,0.093,4.8e-3,0.017,7.7e-4,0.004,2.5e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
10150	thlev=0.
	call nucltransKLM(0.406,0.093,3.5e-2,0.017,1.5e-2,0.004,5.1e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 60900
c-----------------------------------------------------------------------
609	call beta(2.661,84.,0.,0.,t)
60900	thlev=0.
	call nucltransKLM(0.609,0.093,1.5e-2,0.017,4.2e-3,0.004,1.4e-3,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
20001	call beta(3.270,84.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine C14(tcnuc,tdnuc)
c Scheme of C14 beta decay, NPA 523(1991)1 and ToI'1998.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 5.11.2006.
	thnuc=1.798734e11
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
c experimental corrections to the allowed beta shape from
c F.E.Wietfeldt et al., PRC 52(1995)1028
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1
	call beta1(0.156,7.,0.,0.,t,0.,0.19418,0.,0.)
	return
	end

c***********************************************************************

	subroutine Ca48(tcnuc,tdnuc)
c Scheme of Ca48 beta decay. 
c It is supposed that decay goes to excited 5+ level of Sc48 (E_exc=131 keV)
c with T1/2=1.1e21 y calculated in M.Aunola et al., Europhys. Lett. 46(1999)577 
c (transition to g.s. is suppressed by factor of ~1e-10; to 4+ excited level 
c with E_exc=252 keV - by factor of ~1e-5).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 07.05.1998; update of 13.08.2007.
	thnuc=3.47e28
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	call beta(0.151,21.,0.,0.,t)
	tclev=0.
	thlev=0.
	call nucltransK(0.131,0.004,8.1e-3,0.,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

	subroutine Cd113(tcnuc,tdnuc)
c Scheme of Cd113 beta decay.
c Half-life and coefficients in the shape correction factor are taken from:
c F.A.Danevich et al., Phys. At. Nuclei 59(1996)1.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 31.03.2006.
	thnuc=2.42987e23
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	c1=1.01*7.
	c2=1.48*7.
	c3=0.684
c Q_beta=0.320 MeV, G.Audi et al., Nucl. Phys. A 729(2003)337.
	call beta2(0.320,49.,0.,0.,t,3,c1,c2,c3,0.)
	return
	end

c***********************************************************************

	subroutine Co60(tcnuc,tdnuc)
c Scheme of Co60 decay ("Table of Isotopes", 7th ed., 1978).
c Four-figured labels correspond to energies of 60Ni excited
c levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 3.08.1992, 22.10.1995.
c Updated to NDS 100(2003)347, VIT, 16.10.2006;
c angular correlation of 1173 and 1333 keV gammas, L.Pandola + VIT, 18.10.2006;
c 2nd forbidden unique shape for beta decay to 1333 keV level, VIT, 27.10.2006.
        common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	thnuc=0.166344192e+09
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	npg1173=0
	npg1333=0
	pbeta=100.*rnd1(d)
	if(pbeta.le.99.880) go to 2506   ! 99.880%
	                    go to 1333   !  0.120%
c-----------------------------------------------------------------------
2506	call beta(0.318,28.,0.,0.,t)
	thlev=0.3e-12
	p=100.*rnd1(d)
	if(p.le. 0.000002) go to 25061   !  0.000002%
	if(p.le.99.992449) go to 25062   ! 99.992447%
	                   go to 25063   !  0.007551%
25061	call nucltransK(2.506,0.008,8.6e-5,0.,tclev,thlev,tdlev)
	return
c25062	call nucltransK(1.173,0.008,1.7e-4,6.2e-6,tclev,thlev,tdlev)
c longer code for angular correlation of gammas 1173 and 1333 keV
25062	Egamma=1.173
	EbindK=0.008
	cg=1.
	cK=1.7e-4
	cp=6.2e-6
	p=rnd1(d)*(cg+cK+cp)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg1173=npfull
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call gamma(EbindK,0.,0.,tdlev)
	else
	   call pair(Egamma-1.022,tclev,thlev,tdlev)
	end if
	go to 13330
25063	call nucltransK(0.347,0.008,5.5e-3,0.,tclev,thlev,tdlev)
	go to 2159
c-----------------------------------------------------------------------
2159	thlev=0.
	p=100.*rnd1(d)
	if(p.le.13.64) go to 21591      ! 13.64%
	               go to 21592      ! 86.36%
21591	call nucltransK(2.159,0.008,4.9e-5,3.9e-4,tclev,thlev,tdlev)
	return
21592	call nucltransK(0.826,0.008,3.3e-4,0.,tclev,thlev,tdlev)
	go to 13330
c-----------------------------------------------------------------------
c1333	call beta(1.491,28.,0.,0.,t)
c change to the 2nd forbidden unique shape in accordance with 
c H.Daniel, RMP 40(1968)659 and J.L.Wolfson, Can. J. Phys. 34(1956)256
c cf(e) = pel**4 + c1*pel**2*pnu**2 + c2*pnu**4,
1333	call beta2(1.491,28.,0.,0.,t,2,3.333333,1.,0.,0.)
13330	thlev=0.9e-12
c	call nucltransK(1.333,0.008,1.3e-4,3.4e-5,tclev,thlev,tdlev)
c longer code for angular correlation of gammas 1173 and 1333 keV
	Egamma=1.333
	EbindK=0.008
	cg=1.
	cK=1.3e-4
	cp=3.4e-5
	p=rnd1(d)*(cg+cK+cp)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg1333=npfull
	else if(p.le.cg+cK) then
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call gamma(EbindK,0.,0.,tdlev)
	else
	   call pair(Egamma-1.022,tclev,thlev,tdlev)
	end if
c-----------------------------------------------------------------------
c Angular correlation between gammas 1173 and 1333 keV, L.Pandola + VIT
	if(npg1333.ne.0.and.npg1173.ne.0) then 
	   p1333=sqrt(pmoment(1,npg1333)**2+pmoment(2,npg1333)**2+
     +                pmoment(3,npg1333)**2)
	   p1173=sqrt(pmoment(1,npg1173)**2+pmoment(2,npg1173)**2+
     +                pmoment(3,npg1173)**2)
c Coefficients in formula 1+a2*ctet**2+a4*ctet**4 are from:
c R.D.Evans, "The Atomic Nucleus", Krieger Publ. Comp., 1985, p. 240 (4(2)2(2)0 cascade).
c They correspond to coefficients in formula 1+a2*p2+a4*p4, a2=0.1020, a4=0.0091 in
c K.Siegbahn, "Alpha-, Beta- and Gamma-Ray Spectroscopy", North-Holland Publ. Comp., 1968, p. 1033.
	   a2=1./8.
	   a4=1./24.
	   twopi=6.2831853
1	   phi1=twopi*rnd1(d)
	   ctet1=1.-2.*rnd1(d)
	   stet1=sqrt(1.-ctet1*ctet1)
	   phi2=twopi*rnd1(d)
	   ctet2=1.-2.*rnd1(d)
	   stet2=sqrt(1.-ctet2*ctet2)
	   ctet=ctet1*ctet2+stet1*stet2*cos(phi1-phi2)
	   if(rnd1(d)*(1.+abs(a2)+abs(a4)).gt.1.+a2*ctet**2+a4*ctet**4) 
     +        go to 1 
	   pmoment(1,npg1333)=p1333*stet1*cos(phi1)
	   pmoment(2,npg1333)=p1333*stet1*sin(phi1)
	   pmoment(3,npg1333)=p1333*ctet1
	   pmoment(1,npg1173)=p1173*stet2*cos(phi2)
	   pmoment(2,npg1173)=p1173*stet2*sin(phi2)
	   pmoment(3,npg1173)=p1173*ctet2
	endif
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Cs136(tcnuc,tdnuc)
c Model for scheme of Cs136 decay ("Table of Isotopes", 8th ed., 
c 1996 and Nucl. Data Sheets 95(2002)837).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 11.09.2002.
	thnuc=1.137024e+6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 2.025) go to 2374 !  2.025%
	if(pbeta.le. 2.233) go to 2357 !  0.208%
	if(pbeta.le.72.009) go to 2207 ! 69.776%
	if(pbeta.le.82.431) go to 2140 ! 10.422%
	if(pbeta.le.87.097) go to 2054 !  4.666%
	                    go to 1867 ! 12.903%
c-----------------------------------------------------------------------
2374	call beta(0.174,56.,0.,0.,t)
23740	thlev=0.
	p=100.*rnd1(d)
	if(p.le.48.02) go to 23741   ! 48.02%
	if(p.le.73.36) go to 23742   ! 25.34%
	if(p.le.77.36) go to 23743   !  4.00%
	               go to 23744   ! 22.64%
23741	call nucltransK(0.507,0.037,1.1e-2,0.,tclev,thlev,tdlev)
	go to 18670
23742	call nucltransK(0.320,0.037,3.5e-2,0.,tclev,thlev,tdlev)
	go to 20540
23743	call nucltransK(0.234,0.037,2.0e-2,0.,tclev,thlev,tdlev)
	go to 21400
23744	call nucltransK(0.167,0.037,2.5e-1,0.,tclev,thlev,tdlev)
	go to 22070
c-----------------------------------------------------------------------
2357	call beta(0.191,56.,0.,0.,t)
23570	thlev=0.
	p=100.*rnd1(d)
	if(p.le.47.12) go to 23571   ! 47.12%
	if(p.le.85.24) go to 23572   ! 38.12%
	               go to 23573   ! 14.76%
23571	call nucltransK(1.538,0.037,6.0e-4,0.2e-4,tclev,thlev,tdlev)
	go to 81900
23572	call nucltransK(0.490,0.037,1.2e-2,0.,tclev,thlev,tdlev)
	go to 18670
23573	call nucltransK(0.303,0.037,4.5e-2,0.,tclev,thlev,tdlev)
	go to 20540
c-----------------------------------------------------------------------
2207	call beta(0.341,56.,0.,0.,t)
22070	thlev=3.11e-9
	p=100.*rnd1(d)
	if(p.le.61.84) go to 22071   ! 61.84%
	if(p.le.76.78) go to 22072   ! 14.94%
	if(p.le.88.48) go to 22073   ! 11.70%
	               go to 22074   ! 11.52%
22071	call nucltransK(0.341,0.037,3.0e-2,0.,tclev,thlev,tdlev)
	go to 18670
22072	call nucltransK(0.176,0.037,5.0e-2,0.,tclev,thlev,tdlev)
	go to 20310
22073	call nucltransK(0.153,0.037,4.3e-1,0.,tclev,thlev,tdlev)
	go to 20540
22074	call nucltransK(0.067,0.037,6.9e-1,0.,tclev,thlev,tdlev)
	go to 21400
c-----------------------------------------------------------------------
2140	call beta(0.408,56.,0.,0.,t)
21400	thlev=1.6e-9
	p=100.*rnd1(d)
	if(p.le. 0.27) go to 21401   !  0.27%
	if(p.le.60.13) go to 21402   ! 59.86%
	if(p.le.62.88) go to 21403   !  2.75%
	               go to 21404   ! 37.12%
21401	call nucltransK(1.321,0.037,1.7e-3,0.1e-4,tclev,thlev,tdlev)
	go to 81900
21402	call nucltransK(0.273,0.037,1.6e-2,0.,tclev,thlev,tdlev)
	go to 18670
21403	call nucltransK(0.109,0.037,1.47,0.,tclev,thlev,tdlev)
	go to 20310
21404	call nucltransK(0.086,0.037,3.5e-1,0.,tclev,thlev,tdlev)
	go to 20540
c-----------------------------------------------------------------------
2054	call beta(0.494,56.,0.,0.,t)
20540	thlev=0.
	p=100.*rnd1(d)
	if(p.le.97.90) go to 20541   ! 97.90%
	               go to 20542   !  2.10%
20541	call nucltransK(1.235,0.037,1.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 81900
20542	call nucltransK(0.187,0.037,1.9e-1,0.,tclev,thlev,tdlev)
	go to 18670
c-----------------------------------------------------------------------
20310	thlev=0.3084
	call nucltransK(0.164,0.037,2.26,0.,tclev,thlev,tdlev)
	go to 18670
c-----------------------------------------------------------------------
1867	call beta(0.681,56.,0.,0.,t)
18670	thlev=0.
	call nucltransK(1.048,0.037,1.5e-3,0.,tclev,thlev,tdlev)
	go to 81900
c-----------------------------------------------------------------------
81900	thlev=1.930e-12
	call nucltransK(0.819,0.037,2.7e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Cs137(tcnuc,tdnuc)
c Model for scheme of Cs137 decay (Nucl. Data Sheets 72(1994)355)
c (really it is model for (Cs137 + Ba137m)-decay but not the model of
c Cs137 decay alone).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 31.08.1992, 11.07.1995, 06.11.1995;
c VIT, 30.10.2006 (update to NDS 81(1997)579 and corrections to the beta shapes).
	thnuc=0.9489110E+09
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.94.4) go to 1
	                   go to 2
c-----------------------------------------------------------------------
c1	call beta(0.514,56.,0.,0.,t)
c change to the 1st forbidden unique shape without experimental corrections
1	call beta_1fu(0.514,56.,0.,0.,t,0.,0.,0.,0.)
	thlev=153.12
	call nucltransKL(0.662,0.037,9.0e-2,0.006,1.6e-2,0.,
c    +                   tdlev,thlev,tdlev)
c corrected; thanks to F.Cappella 7.08.2007
     +                   tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c2	call beta(1.176,56.,0.,0.,t)
c change to 2nd forbidden non-unique shape with experimental correction factor
c from S.T.Hsue et al., NP 86(1966)47: p_nu^2+0.004*p_el^2
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1
c2	call beta1(1.176,56.,0.,0.,t,0.,-0.8690502,0.1888145,0.)
c wrong numerical coefficients; corrected on 30.01.2009, VIT
2	call beta1(1.176,56.,0.,0.,t,0.,-0.6060315,0.0921520,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Eu147(tcnuc,tdnuc)
c Scheme of 147Eu decay ("Table of Isotopes", 7th ed., 1978).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 10.03.1996.
	thnuc=1.9008e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le. 0.002) then
	   call alpha(2.908,0.,0.,t)
	   return
	endif
	if(pdecay.le. 0.202) go to  1646
	if(pdecay.le. 0.502) go to  1549
	if(pdecay.le. 0.552) go to  1471
	if(pdecay.le. 1.552) go to  1453
	if(pdecay.le. 2.052) go to  1318
	if(pdecay.le. 2.252) go to  1304
	if(pdecay.le.11.352) go to  1077
	if(pdecay.le.11.582) go to  1063
	if(pdecay.le.17.102) go to  1054
	if(pdecay.le.17.182) go to  1007
	if(pdecay.le.35.382) go to   799
	if(pdecay.le.57.592) go to   197
	if(pdecay.le.76.792) go to   121
	                     go to 10000
c-----------------------------------------------------------------------
1646	call gamma(0.049,0.,0.,t)
	thlev=0.
	call nucltransK(1.449,0.047,5.0e-4,0.8e-4,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
1549	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.31.) go to 15491
	             go to 15492
15491	call nucltransK(1.427,0.047,5.0e-4,0.7e-4,tclev,thlev,tdlev)
	go to 12100
15492	call nucltransK(0.750,0.047,1.8e-3,0.,tclev,thlev,tdlev)
	go to 79900
c-----------------------------------------------------------------------
1471	call gamma(0.049,0.,0.,t)
	thlev=0.
	call nucltransK(1.350,0.047,5.5e-4,0.6e-4,tclev,thlev,tdlev)
	go to 12100
c-----------------------------------------------------------------------
1453	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.) go to 14531
	             go to 14532
14531	call nucltransK(1.332,0.047,5.5e-4,0.5e-4,tclev,thlev,tdlev)
	go to 12100
14532	call nucltransK(1.256,0.047,6.0e-4,0.4e-4,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
1318	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.22.8) go to 13181
	if(p.le.68.3) go to 13182
	              go to 13183
13181	call nucltransK(1.318,0.047,5.5e-4,0.5e-4,tclev,thlev,tdlev)
	return
13182	call nucltransK(1.197,0.047,6.5e-4,0.3e-4,tclev,thlev,tdlev)
	go to 12100
13183	call nucltransK(1.120,0.047,7.5e-4,0.2e-4,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
1304	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.15.) go to 13041
	             go to 13042
13041	call nucltransK(1.107,0.047,7.5e-4,0.1e-4,tclev,thlev,tdlev)
	go to 19700
13042	call nucltransK(0.505,0.047,4.0e-3,0.,tclev,thlev,tdlev)
	go to 79900
c-----------------------------------------------------------------------
1077	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.62.5) go to 10771
	if(p.le.98.5) go to 10772
	              go to 10773
10771	call nucltransK(1.077,0.047,4.3e-3,0.1e-4,tclev,thlev,tdlev)
	return
10772	call nucltransK(0.956,0.047,5.5e-3,0.,tclev,thlev,tdlev)
	go to 12100
10773	call nucltransK(0.880,0.047,9.5e-3,0.,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
1063	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.40.) go to 10631
	             go to 10632
10631	call nucltransK(1.063,0.047,1.1e-3,0.1e-4,tclev,thlev,tdlev)
	return
10632	call nucltransK(0.942,0.047,1.3e-3,0.,tclev,thlev,tdlev)
	go to 12100
c-----------------------------------------------------------------------
1054	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.57.) go to 10541
	             go to 10542
10541	call nucltransK(0.933,0.047,1.3e-3,0.,tclev,thlev,tdlev)
	go to 12100
10542	call nucltransK(0.857,0.047,1.6e-3,0.,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
1007	call gamma(0.049,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.45.) go to 10071
	             go to 10072
10071	call nucltransK(0.886,0.047,1.5e-3,0.,tclev,thlev,tdlev)
	go to 12100
10072	call nucltransK(0.809,0.047,9.0e-3,0.,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
799	call gamma(0.049,0.,0.,t)
79900	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.2) go to 79901
	if(p.le.71.7) go to 79902
	              go to 79903
79901	call nucltransK(0.799,0.047,4.5e-3,0.,tclev,thlev,tdlev)
	return
79902	call nucltransK(0.678,0.047,1.4e-2,0.,tclev,thlev,tdlev)
	go to 12100
79903	call nucltransK(0.601,0.047,1.8e-2,0.,tclev,thlev,tdlev)
	go to 19700
c-----------------------------------------------------------------------
197	p=100.*rnd1(d)
	if(p.le.99.4) call gamma(0.049,0.,0.,t)
	if(p.gt.99.4) call beta(0.511,-62.,0.,0.,t)
19700	thlev=1.3e-9
	p=100.*rnd1(d)
	if(p.le.97.2) go to 19701
	              go to 19702
19701	call nucltransK(0.197,0.047,2.2e-1,0.,tclev,thlev,tdlev)
	return
19702	call nucltransK(0.076,0.047,3.5e-0,0.,tclev,thlev,tdlev)
	go to 12100
c-----------------------------------------------------------------------
121	p=100.*rnd1(d)
	if(p.le.99.5) call gamma(0.049,0.,0.,t)
	if(p.gt.99.5) call beta(0.587,-62.,0.,0.,t)
12100	thlev=0.77e-9
	call nucltransK(0.121,0.047,1.1e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	p=100.*rnd1(d)
	if(p.le.99.3) call gamma(0.049,0.,0.,t)
	if(p.gt.99.3) call beta(0.708,-62.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Eu152(tcnuc,tdnuc)
c Scheme of 152Eu decay ("Table of Isotopes", 8th ed., 1996 and
c NDS 79(1996)1).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 16.11.1996.
c VIT, approximate electron capture from K, L or M shells, 27.12.2006.
c VIT, correction to the 1fnu shape for Qbeta=1.474, 13.11.2007.
	thnuc=4.273413e8
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.72.08) go to 1      ! EC to 152Sm
	                    go to 2      ! b- to 152Gd
c-----------------------------------------------------------------------
c-----------------------------------------------------------------------
c1	call gamma(0.049,0.,0.,tdlev)
c approximate electron capture from K (82%), L (14%) or M (4%) shell
1	pKLM=100.*rnd1(d)
	if(pKLM.le.82.)                   call gamma(0.047,0.,0.,tdlev)
	if(pKLM.gt.82. .and. pKLM.le.96.) call gamma(0.008,0.,0.,tdlev)
	if(pKLM.gt.96.)                   call gamma(0.001,0.,0.,tdlev)
	pec=100.*rnd1(d)
	if(pec.le. 0.071) go to 1769
	if(pec.le. 0.118) go to 1757
	if(pec.le. 0.180) go to 1730
	if(pec.le. 1.416) go to 1650
	if(pec.le. 1.445) go to 1613
	if(pec.le. 4.292) go to 1579
	if(pec.le.38.592) go to 1530
	if(pec.le.39.883) go to 1372
	if(pec.le.40.744) go to 1293
	if(pec.le.64.629) go to 1234
	if(pec.le.94.069) go to 1086
	if(pec.le.94.152) go to 1041
	if(pec.le.94.471) go to 1023
	if(pec.le.96.179) go to  810
	if(pec.le.97.359) go to  366
	                  go to  122
c-----------------------------------------------------------------------
1769	thlev=0.
	p=100.*rnd1(d)
	if(p.le.15.21) go to 17691
	if(p.le.25.62) go to 17692
	if(p.le.65.65) go to 17693
	if(p.le.88.07) go to 17694
	if(p.le.99.28) go to 17695
	               go to 17696
17691	call nucltransK(1.769,0.047,8.0e-4,0.9e-4,tclev,thlev,tdlev)
	return
17692	call nucltransK(1.647,0.047,4.0e-4,0.5e-4,tclev,thlev,tdlev)
	go to 122
17693	call nucltransK(0.959,0.047,2.5e-3,0.,tclev,thlev,tdlev)
	go to 810
17694	call nucltransK(0.806,0.047,1.4e-3,0.,tclev,thlev,tdlev)
	go to 963
17695	call nucltransK(0.536,0.047,1.0e-2,0.,tclev,thlev,tdlev)
	go to 1234
17696	call nucltransK(0.239,0.047,1.0e-1,0.,tclev,thlev,tdlev)
	go to 1530
c-----------------------------------------------------------------------
1757	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.43) go to 17571
	if(p.le.14.38) go to 17572
	if(p.le.81.12) go to 17573
	if(p.le.85.46) go to 17574
	               go to 17575
17571	call nucltransK(1.635,0.047,3.5e-4,0.5e-4,tclev,thlev,tdlev)
	go to 122
17572	call nucltransK(1.390,0.047,5.0e-4,0.2e-4,tclev,thlev,tdlev)
	go to 366
17573	call nucltransK(0.671,0.047,1.1e-2,0.,tclev,thlev,tdlev)
	go to 1086
17574	call nucltransK(0.523,0.047,3.5e-3,0.,tclev,thlev,tdlev)
	go to 1234
17575	call nucltransK(0.386,0.047,7.0e-3,0.,tclev,thlev,tdlev)
	go to 1372
c-----------------------------------------------------------------------
1730	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.26) go to 17301
	if(p.le.66.17) go to 17302
	if(p.le.79.35) go to 17303
	               go to 17304
17301	call nucltransK(1.608,0.047,4.0e-4,0.8e-4,tclev,thlev,tdlev)
	go to 122
17302	call nucltransK(1.364,0.047,5.3e-4,0.3e-4,tclev,thlev,tdlev)
	go to 366
17303	call nucltransK(0.644,0.047,2.2e-3,0.,tclev,thlev,tdlev)
	go to 1086
17304	call nucltransK(0.496,0.047,4.0e-3,0.,tclev,thlev,tdlev)
	go to 1234
c-----------------------------------------------------------------------
1650	thlev=0.
	p=100.*rnd1(d)
	if(p.le.30.00) go to 16501
	if(p.le.31.85) go to 16502
	if(p.le.34.02) go to 16503
	if(p.le.86.93) go to 16504
	if(p.le.99.47) go to 16505
	               go to 16506
16501	call nucltransK(0.769,0.047,8.0e-3,0.,tclev,thlev,tdlev)
	go to 122
16502	call nucltransK(0.769,0.047,8.0e-3,0.,tclev,thlev,tdlev)
	go to 810
16503	call nucltransK(0.769,0.047,8.0e-3,0.,tclev,thlev,tdlev)
	go to 963
16504	call nucltransK(0.769,0.047,8.0e-3,0.,tclev,thlev,tdlev)
	go to 1086
16505	call nucltransK(0.769,0.047,8.0e-3,0.,tclev,thlev,tdlev)
	go to 1234
16506	call nucltransK(0.769,0.047,8.0e-3,0.,tclev,thlev,tdlev)
	go to 1293
c-----------------------------------------------------------------------
1613	thlev=0.
	p=100.*rnd1(d)
	if(p.le.71.28) go to 16131
	if(p.le.94.09) go to 16132
	               go to 16133
16131	call nucltransK(0.906,0.047,2.8e-3,0.,tclev,thlev,tdlev)
	go to 707
16132	call nucltransK(0.572,0.047,2.8e-3,0.,tclev,thlev,tdlev)
	go to 1041
16133	call nucltransK(0.391,0.047,7.0e-3,0.,tclev,thlev,tdlev)
	go to 1222
c-----------------------------------------------------------------------
1579	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.04) go to 15791
	if(p.le.92.32) go to 15792
	if(p.le.96.69) go to 15793
	if(p.le.97.13) go to 15794
	if(p.le.98.06) go to 15795
	if(p.le.98.26) go to 15796
	if(p.le.99.79) go to 15797
	               go to 15798
15791	call nucltransK(1.458,0.047,4.5e-4,0.4e-4,tclev,thlev,tdlev)
	go to 122
15792	call nucltransK(1.213,0.047,6.2e-4,0.1e-4,tclev,thlev,tdlev)
	go to 366
15793	call nucltransK(0.769,0.047,1.5e-3,0.,tclev,thlev,tdlev)
	go to 810
15794	call nucltransK(0.616,0.047,7.0e-3,0.,tclev,thlev,tdlev)
	go to 963
15795	call nucltransK(0.557,0.047,3.0e-3,0.,tclev,thlev,tdlev)
	go to 1023
15796	call nucltransK(0.538,0.047,9.5e-3,0.,tclev,thlev,tdlev)
	go to 1041
15797	call nucltransK(0.494,0.047,4.0e-3,0.,tclev,thlev,tdlev)
	go to 1086
15798	call nucltransK(0.208,0.047,3.5e-2,0.,tclev,thlev,tdlev)
	go to 1372
c-----------------------------------------------------------------------
1530	thlev=0.
	p=100.*rnd1(d)
	if(p.le.84.56) go to 15301
	if(p.le.84.80) go to 15302
	if(p.le.85.32) go to 15303
	if(p.le.86.97) go to 15304
	if(p.le.98.22) go to 15305
	               go to 15306
15301	call nucltransK(1.408,0.047,5.0e-4,0.3e-4,tclev,thlev,tdlev)
	go to 122
15302	call nucltransK(0.719,0.047,2.0e-3,0.,tclev,thlev,tdlev)
	go to 810
15303	call nucltransK(0.566,0.047,1.4e-2,0.,tclev,thlev,tdlev)
	go to 963
15304	call nucltransK(0.489,0.047,1.4e-2,0.,tclev,thlev,tdlev)
	go to 1041
15305	call nucltransK(0.444,0.047,5.7e-3,0.,tclev,thlev,tdlev)
	go to 1086
15306	call nucltransK(0.296,0.047,1.5e-2,0.,tclev,thlev,tdlev)
	go to 1234
c-----------------------------------------------------------------------
1372	thlev=0.
	p=100.*rnd1(d)
	if(p.le.19.62) go to 13721
	if(p.le.88.70) go to 13722
	if(p.le.90.70) go to 13723
	if(p.le.90.81) go to 13724
	if(p.le.98.82) go to 13725
	               go to 13726
13721	call nucltransK(1.250,0.047,1.6e-3,0.1e-4,tclev,thlev,tdlev)
	go to 122
13722	call nucltransK(1.005,0.047,2.6e-3,0.,tclev,thlev,tdlev)
	go to 366
13723	call nucltransK(0.665,0.047,6.3e-3,0.,tclev,thlev,tdlev)
	go to 707
13724	call nucltransK(0.561,0.047,3.5e-3,0.,tclev,thlev,tdlev)
	go to 810
13725	call nucltransK(0.331,0.047,1.2e-2,0.,tclev,thlev,tdlev)
	go to 1041
13726	call nucltransK(0.286,0.047,6.6e-2,0.,tclev,thlev,tdlev)
	go to 1086
c-----------------------------------------------------------------------
1293	thlev=0.
	p=100.*rnd1(d)
	if(p.le.16.39) go to 12931
	if(p.le.22.12) go to 12932
	if(p.le.64.58) go to 12933
	if(p.le.68.91) go to 12934
	if(p.le.88.66) go to 12935
	if(p.le.89.98) go to 12936
	               go to 12937
12931	call nucltransK(1.293,0.047,1.3e-3,0.1e-4,tclev,thlev,tdlev)
	return
12932	call nucltransK(1.171,0.047,1.6e-3,0.,tclev,thlev,tdlev)
	go to 122
12933	call nucltransK(0.926,0.047,3.0e-3,0.,tclev,thlev,tdlev)
	go to 366
12934	call nucltransK(0.482,0.047,2.0e-2,0.,tclev,thlev,tdlev)
	go to 810
12935	call nucltransK(0.329,0.047,1.2e-2,0.,tclev,thlev,tdlev)
	go to 963
12936	call nucltransK(0.270,0.047,7.9e-2,0.,tclev,thlev,tdlev)
	go to 1023
12937	call nucltransK(0.252,0.047,2.3e-2,0.,tclev,thlev,tdlev)
	go to 1041
c-----------------------------------------------------------------------
1234	thlev=0.
	p=100.*rnd1(d)
	if(p.le.76.33) go to 12341
	if(p.le.99.76) go to 12342
	if(p.le.99.78) go to 12343
	               go to 12344
12341	call nucltransK(1.112,0.047,2.0e-3,0.2e-4,tclev,thlev,tdlev)
	go to 122
12342	call nucltransK(0.867,0.047,3.5e-3,0.,tclev,thlev,tdlev)
	go to 366
12343	call nucltransK(0.423,0.047,2.7e-2,0.,tclev,thlev,tdlev)
	go to 810
12344	call nucltransK(0.148,0.047,5.8e-1,0.,tclev,thlev,tdlev)
	go to 1086
c-----------------------------------------------------------------------
1222	thlev=0.
	p=100.*rnd1(d)
	if(p.le.80.65) go to 12221
	               go to 12222
12221	call nucltransK(0.855,0.047,1.6e-3,0.,tclev,thlev,tdlev)
	go to 366
12222	call nucltransK(0.515,0.047,3.7e-3,0.,tclev,thlev,tdlev)
	go to 707
c-----------------------------------------------------------------------
1086	thlev=0.85e-12
	p=100.*rnd1(d)
	if(p.le.40.36) go to 10861
	if(p.le.98.77) go to 10862
	if(p.le.99.86) go to 10863
	               go to 10864
10861	call nucltransK(1.086,0.047,2.1e-3,0.,tclev,thlev,tdlev)
	return
10862	call nucltransK(0.964,0.047,2.7e-3,0.,tclev,thlev,tdlev)
	go to 122
10863	call nucltransK(0.719,0.047,5.2e-3,0.,tclev,thlev,tdlev)
	go to 366
10864	call nucltransK(0.275,0.047,1.0e-1,0.,tclev,thlev,tdlev)
	go to 810
c-----------------------------------------------------------------------
1041	thlev=0.
	p=100.*rnd1(d)
	if(p.le.71.23) go to 10411
	               go to 10412
10411	call nucltransK(0.919,0.047,1.2e-3,0.,tclev,thlev,tdlev)
	go to 122
10412	call nucltransK(0.675,0.047,2.3e-3,0.,tclev,thlev,tdlev)
	go to 366
c-----------------------------------------------------------------------
1023	thlev=6.7e-12
	p=100.*rnd1(d)
	if(p.le.35.73) go to 10231
	if(p.le.91.56) go to 10232
	if(p.le.92.40) go to 10233
	               go to 10234
10231	call nucltransK(0.901,0.047,3.1e-3,0.,tclev,thlev,tdlev)
	go to 122
10232	call nucltransK(0.656,0.047,5.7e-2,0.,tclev,thlev,tdlev)
	go to 366
10233	call nucltransK(0.316,0.047,4.8e-2,0.,tclev,thlev,tdlev)
	go to 707
10234	call nucltransK(0.213,0.047,1.7e-1,0.,tclev,thlev,tdlev)
	go to 810
c-----------------------------------------------------------------------
963	thlev=28.2e-15
	p=100.*rnd1(d)
	if(p.le.45.143) go to 96301
	if(p.le.99.994) go to 96302
	if(p.le.99.995) go to 96303
	                go to 96304
96301	call nucltransK(0.963,0.047,1.1e-3,0.,tclev,thlev,tdlev)
	return
96302	call nucltransK(0.842,0.047,1.4e-3,0.,tclev,thlev,tdlev)
	go to 122
96303	call nucltransK(0.279,0.047,1.8e-2,0.,tclev,thlev,tdlev)
	go to 685
96304	call nucltransK(0.153,0.047,8.7e-2,0.,tclev,thlev,tdlev)
	go to 810
c-----------------------------------------------------------------------
810	thlev=7.2e-12
	p=100.*rnd1(d)
	if(p.le.21.66) go to 81001
	if(p.le.78.06) go to 81002
	if(p.le.99.21) go to 81003
	               go to 81004
81001	call nucltransK(0.810,0.047,4.0e-3,0.,tclev,thlev,tdlev)
	return
81002	call nucltransK(0.689,0.047,4.3e-2,0.,tclev,thlev,tdlev)
	go to 122
81003	call nucltransK(0.444,0.047,1.8e-2,0.,tclev,thlev,tdlev)
	go to 366
81004	call nucltransK(0.126,0.047,1.0e-0,0.,tclev,thlev,tdlev)
	go to 685
c-----------------------------------------------------------------------
707	thlev=10.1e-12
	call nucltransK(0.340,0.047,3.8e-4,0.,tclev,thlev,tdlev)
	go to 366
c-----------------------------------------------------------------------
685	thlev=6.2e-12
	p=100.*rnd1(d)
	if(p.le. 1.43) go to 68501
	               go to 68502
68501	call electron(0.638,tclev,thlev,tdlev)
	call gamma(0.047,0.,0.,tdlev)
	return
68502	call nucltransK(0.563,0.047,9.5e-3,0.,tclev,thlev,tdlev)
	go to 122
c-----------------------------------------------------------------------
366	thlev=57.7e-12
	call nucltransK(0.245,0.047,1.1e-1,0.,tclev,thlev,tdlev)
	go to 122
c-----------------------------------------------------------------------
122	thlev=1.428e-9
	call nucltransK(0.122,0.047,1.2e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c-----------------------------------------------------------------------
2	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.071) go to  1692
	if(pbeta.le. 6.421) go to  1643
	if(pbeta.le. 6.778) go to  1606
	if(pbeta.le.15.339) go to  1434
	if(pbeta.le.15.981) go to  1318
	if(pbeta.le.16.063) go to  1282
	if(pbeta.le.65.291) go to  1123
	if(pbeta.le.66.325) go to  1109
	if(pbeta.le.67.395) go to   931
	if(pbeta.le.70.748) go to   755
	                    go to   344
c-----------------------------------------------------------------------
1692	call beta(0.126,64.,0.,0.,t)
16920	thlev=0.
	p=100.*rnd1(d)
	if(p.le.84.03) go to 16921
	               go to 16922
16921	call nucltransK(1.348,0.050,1.5e-3,0.2e-4,tclev,thlev,tdlev)
	go to 34400
16922	call nucltransK(0.937,0.050,3.2e-3,0.,tclev,thlev,tdlev)
	go to 75500
c-----------------------------------------------------------------------
1643	call beta(0.175,64.,0.,0.,t)
16430	thlev=0.
	p=100.*rnd1(d)
	if(p.le.89.21) go to 16431
	if(p.le.94.47) go to 16432
	if(p.le.96.83) go to 16433
	if(p.le.99.75) go to 16434
	if(p.le.99.76) go to 16435
	               go to 16436
16431	call nucltransK(1.299,0.050,7.5e-4,0.3e-4,tclev,thlev,tdlev)
	go to 34400
16432	call nucltransK(0.713,0.050,2.2e-3,0.,tclev,thlev,tdlev)
	go to 93100
16433	call nucltransK(0.534,0.050,4.5e-3,0.,tclev,thlev,tdlev)
	go to 11090
16434	call nucltransK(0.520,0.050,1.8e-2,0.,tclev,thlev,tdlev)
	go to 11230
16435	call nucltransK(0.325,0.050,1.3e-2,0.,tclev,thlev,tdlev)
	go to 13180
16436	call nucltransK(0.209,0.050,4.0e-2,0.,tclev,thlev,tdlev)
	go to 14340
c-----------------------------------------------------------------------
1606	call beta(0.212,64.,0.,0.,t)
16060	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 7.64) go to 16061
	if(p.le.40.86) go to 16062
	if(p.le.72.09) go to 16063
	if(p.le.91.36) go to 16064
	if(p.le.95.35) go to 16065
	if(p.le.99.99) go to 16066
	               go to 16067
16061	call nucltransK(1.606,0.050,1.2e-3,0.5e-4,tclev,thlev,tdlev)
	return
16062	call nucltransK(1.261,0.050,2.7e-3,0.5e-4,tclev,thlev,tdlev)
	go to 34400
16063	call nucltransK(0.990,0.050,3.0e-3,0.,tclev,thlev,tdlev)
	go to 61500
16064	call nucltransK(0.675,0.050,7.6e-3,0.,tclev,thlev,tdlev)
	go to 93100
16065	call nucltransK(0.558,0.050,1.1e-2,0.,tclev,thlev,tdlev)
	go to 10480
16066	call nucltransK(0.496,0.050,9.7e-2,0.,tclev,thlev,tdlev)
	go to 11090
16067	call nucltransK(0.482,0.050,5.0e-3,0.,tclev,thlev,tdlev)
	go to 11230
c-----------------------------------------------------------------------
1434	call beta(0.384,64.,0.,0.,t)
14340	thlev=0.
	p=100.*rnd1(d)
	if(p.le.71.07) go to 14341
	if(p.le.90.54) go to 14342
	if(p.le.96.87) go to 14343
	if(p.le.99.99) go to 14344
	               go to 14345
14341	call nucltransK(1.090,0.050,2.3e-3,0.,tclev,thlev,tdlev)
	go to 34400
14342	call nucltransK(0.679,0.050,6.9e-3,0.,tclev,thlev,tdlev)
	go to 75500
14343	call nucltransK(0.503,0.050,1.4e-2,0.,tclev,thlev,tdlev)
	go to 93100
14344	call nucltransK(0.325,0.050,6.3e-2,0.,tclev,thlev,tdlev)
	go to 11090
14345	call nucltransK(0.115,0.050,1.4e-0,0.,tclev,thlev,tdlev)
	go to 13180
c-----------------------------------------------------------------------
1318	call beta(0.500,64.,0.,0.,t)
13180	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.87) go to 13181
	if(p.le.62.27) go to 13182
	if(p.le.76.12) go to 13183
	if(p.le.77.39) go to 13184
	if(p.le.84.76) go to 13185
	if(p.le.92.35) go to 13186
	if(p.le.92.79) go to 13187
	               go to 13188
13181	call nucltransK(1.318,0.050,1.6e-3,0.1e-4,tclev,thlev,tdlev)
	return
13182	call nucltransK(0.974,0.050,5.6e-3,0.,tclev,thlev,tdlev)
	go to 34400
13183	call nucltransK(0.703,0.050,6.0e-3,0.,tclev,thlev,tdlev)
	go to 61500
13184	call nucltransK(0.563,0.050,1.0e-2,0.,tclev,thlev,tdlev)
	go to 75500
13185	call nucltransK(0.388,0.050,4.5e-1,0.,tclev,thlev,tdlev)
	go to 93100
13186	call nucltransK(0.271,0.050,8.4e-2,0.,tclev,thlev,tdlev)
	go to 10480
13187	call nucltransK(0.209,0.050,5.0e-1,0.,tclev,thlev,tdlev)
	go to 11090
13188	call nucltransK(0.195,0.050,4.9e-2,0.,tclev,thlev,tdlev)
	go to 11230
c-----------------------------------------------------------------------
1282	call beta(0.536,64.,0.,0.,t)
12820	thlev=0.
	p=100.*rnd1(d)
	if(p.le.58.41) go to 12821
	if(p.le.98.13) go to 12822
	               go to 12823
12821	call nucltransK(0.527,0.050,9.4e-2,0.,tclev,thlev,tdlev)
	go to 75500
12822	call nucltransK(0.352,0.050,3.8e-2,0.,tclev,thlev,tdlev)
	go to 93100
12823	call nucltransK(0.172,0.050,3.7e-1,0.,tclev,thlev,tdlev)
	go to 11090
c-----------------------------------------------------------------------
1123	call beta(0.695,64.,0.,0.,t)
11230	thlev=0.
	p=100.*rnd1(d)
	if(p.le.93.11) go to 11231
	if(p.le.99.26) go to 11232
	               go to 11233
11231	call nucltransK(0.779,0.050,1.9e-3,0.,tclev,thlev,tdlev)
	go to 34400
11232	call nucltransK(0.368,0.050,9.7e-3,0.,tclev,thlev,tdlev)
	go to 75500
11233	call nucltransK(0.193,0.050,5.0e-2,0.,tclev,thlev,tdlev)
	go to 93100
c-----------------------------------------------------------------------
1109	call beta(0.709,64.,0.,0.,t)
11090	thlev=0.
	p=100.*rnd1(d)
	if(p.le.50.00) go to 11091
	if(p.le.97.50) go to 11092
	               go to 11093
11091	call nucltransK(1.109,0.050,2.2e-3,0.,tclev,thlev,tdlev)
	return
11092	call nucltransK(0.765,0.050,5.2e-3,0.,tclev,thlev,tdlev)
	go to 34400
11093	call nucltransK(0.494,0.050,1.5e-2,0.,tclev,thlev,tdlev)
	go to 61500
c-----------------------------------------------------------------------
10480	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.88) go to 10481
	if(p.le.65.79) go to 10482
	if(p.le.83.77) go to 10483
	               go to 10484
10481	call electron(0.998,tclev,thlev,tdlev)
	call gamma(0.050,0.,0.,tdlev)
	return
10482	call nucltransK(0.703,0.050,6.0e-3,0.,tclev,thlev,tdlev)
	go to 34400
10483	call electron(0.383,tclev,thlev,tdlev)
	call gamma(0.050,0.,0.,tdlev)
	go to 61500
10484	call nucltransK(0.117,0.050,1.4e-0,0.,tclev,thlev,tdlev)
	go to 93100
c-----------------------------------------------------------------------
931	call beta(0.887,64.,0.,0.,t)
93100	thlev=7.3e-12
	p=100.*rnd1(d)
	if(p.le.12.40) go to 93101
	if(p.le.90.91) go to 93102
	if(p.le.99.55) go to 93103
	               go to 93104
93101	call nucltransK(0.931,0.050,3.2e-3,0.,tclev,thlev,tdlev)
	return
93102	call nucltransK(0.586,0.050,2.4e-2,0.,tclev,thlev,tdlev)
	go to 34400
93103	call nucltransK(0.315,0.050,5.2e-2,0.,tclev,thlev,tdlev)
	go to 61500
93104	call nucltransK(0.175,0.050,3.5e-1,0.,tclev,thlev,tdlev)
	go to 75500
c-----------------------------------------------------------------------
755	call beta(1.063,64.,0.,0.,t)
75500	thlev=7.3e-12
	call nucltransK(0.411,0.050,2.4e-2,0.,tclev,thlev,tdlev)
	go to 34400
c-----------------------------------------------------------------------
61500	thlev=37.e-12
	p=100.*rnd1(d)
	if(p.le.11.35) go to 61501
	               go to 61502
61501	call electron(0.565,tclev,thlev,tdlev)
	call gamma(0.050,0.,0.,tdlev)
	return
61502	call nucltransK(0.271,0.050,8.3e-2,0.,tclev,thlev,tdlev)
	go to 34400
c-----------------------------------------------------------------------
c344	call beta(1.474,64.,0.,0.,t)
c correction to the 1st forbidden non-unique shape in accordance with
c L.M.Langer et al., PR 119(1960)1308
344	call beta1(1.474,64.,0.,0.,t,0.,-0.4026,0.0928,0.)
34400	thlev=31.9e-12
	call nucltransK(0.344,0.050,4.0e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Eu154(tcnuc,tdnuc)
c Scheme of 154Eu decay ("Table of Isotopes", 8th ed., 1996 and
c NDS 69(1993)507).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.11.1996.
c VIT, correction to the 1fnu shape for Qbeta=1.846, 13.11.2007.
	thnuc=2.711670e8
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.0.020) go to 1      !  0.020% EC to 154Sm
	                    go to 2      ! 99.980% b- to 154Gd
c-----------------------------------------------------------------------
c-----------------------------------------------------------------------
1	call gamma(0.049,0.,0.,tdlev)
	if(pdecay.le.0.005) go to 267
	                    go to  82
c-----------------------------------------------------------------------
267	thlev=172.e-12
	call nucltransK(0.185,0.047,2.7e-1,0.,tclev,thlev,tdlev)
	go to 82
c-----------------------------------------------------------------------
82	thlev=3.02e-9
	call nucltransK(0.082,0.047,4.9+0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c-----------------------------------------------------------------------
2	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.019) go to  1839
	if(pbeta.le. 0.087) go to  1797
	if(pbeta.le.28.587) go to  1720
	if(pbeta.le.29.417) go to  1661
	if(pbeta.le.29.564) go to  1646
	if(pbeta.le.31.174) go to  1617
	if(pbeta.le.31.271) go to  1560
	if(pbeta.le.31.571) go to  1531
	if(pbeta.le.31.679) go to  1418
	if(pbeta.le.67.879) go to  1398
	if(pbeta.le.68.599) go to  1264
	if(pbeta.le.68.909) go to  1252
	if(pbeta.le.85.610) go to  1128
	if(pbeta.le.89.110) go to   996
	if(pbeta.le.89.810) go to   815
	if(pbeta.le.90.000) go to   371
	                    go to   123
c-----------------------------------------------------------------------
1839	call beta(0.130,64.,0.,0.,t)
18390	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.0) go to 18391
	if(p.le. 6.8) go to 18392
	if(p.le.38.1) go to 18393
	if(p.le.87.8) go to 18394
	if(p.le.94.0) go to 18395
	              go to 18396
18391	call nucltransK(1.839,0.050,1.0e-3,1.0e-4,tclev,thlev,tdlev)
	return
18392	call nucltransK(1.717,0.050,1.1e-3,0.7e-4,tclev,thlev,tdlev)
	go to 12300
18393	call nucltransK(1.023,0.050,3.8e-3,0.,tclev,thlev,tdlev)
	go to 81500
18394	call nucltransK(0.790,0.050,5.0e-3,0.,tclev,thlev,tdlev)
	go to 10480
18395	call nucltransK(0.193,0.050,2.8e-1,0.,tclev,thlev,tdlev)
	go to 16460
18396	call nucltransK(0.063,0.050,1.4e+1,0.,tclev,thlev,tdlev)
	go to 17750
c-----------------------------------------------------------------------
1797	call beta(0.172,64.,0.,0.,t)
17970	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.4) go to 17971
	if(p.le. 4.0) go to 17972
	if(p.le.15.3) go to 17973
	if(p.le.58.7) go to 17974
	if(p.le.77.0) go to 17975
	if(p.le.82.0) go to 17976
	if(p.le.91.6) go to 17977
	if(p.le.99.9) go to 17978
	              go to 17979
17971	call nucltransK(1.674,0.050,5.0e-4,0.9e-4,tclev,thlev,tdlev)
	go to 12300
17972	call nucltransK(1.426,0.050,6.0e-4,0.4e-4,tclev,thlev,tdlev)
	go to 37100
17973	call nucltransK(0.982,0.050,1.2e-3,0.,tclev,thlev,tdlev)
	go to 81500
17974	call nucltransK(0.801,0.050,1.8e-3,0.,tclev,thlev,tdlev)
	go to 99600
17975	call nucltransK(0.669,0.050,2.5e-3,0.,tclev,thlev,tdlev)
	go to 11280
17976	call nucltransK(0.556,0.050,1.1e-2,0.,tclev,thlev,tdlev)
	go to 12410
17977	call nucltransK(0.533,0.050,4.0e-3,0.,tclev,thlev,tdlev)
	go to 12640
17978	call nucltransK(0.393,0.050,3.0e-2,0.,tclev,thlev,tdlev)
	go to 14040
17979	call nucltransK(0.266,0.050,2.0e-2,0.,tclev,thlev,tdlev)
	go to 15310
c-----------------------------------------------------------------------
17750	thlev=0.
	p=100.*rnd1(d)
	if(p.le.19.6) go to 17751
	if(p.le.62.3) go to 17752
	if(p.le.79.4) go to 17753
	if(p.le.88.4) go to 17754
	if(p.le.92.2) go to 17755
	if(p.le.98.7) go to 17756
	              go to 17757
17751	call nucltransK(1.776,0.050,1.0e-3,0.8e-4,tclev,thlev,tdlev)
	return
17752	call nucltransK(1.652,0.050,1.6e-3,0.6e-4,tclev,thlev,tdlev)
	go to 12300
17753	call nucltransK(1.405,0.050,1.4e-3,0.2e-4,tclev,thlev,tdlev)
	go to 37100
17754	call nucltransK(1.095,0.050,2.3e-3,0.,tclev,thlev,tdlev)
	go to 68100
17755	call nucltransK(0.960,0.050,3.0e-3,0.,tclev,thlev,tdlev)
	go to 81500
17756	call nucltransK(0.728,0.050,6.0e-3,0.,tclev,thlev,tdlev)
	go to 10480
17757	call nucltransK(0.648,0.050,1.4e-2,0.,tclev,thlev,tdlev)
	go to 11280
c-----------------------------------------------------------------------
1720	call beta(0.249,64.,0.,0.,t)
17200	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.272) go to 17201
	if(p.le. 9.404) go to 17202
	if(p.le.79.950) go to 17203
	if(p.le.97.361) go to 17204
	if(p.le.98.150) go to 17205
	if(p.le.98.362) go to 17206
	if(p.le.98.594) go to 17207
	if(p.le.98.629) go to 17208
	if(p.le.98.665) go to 17209
	if(p.le.98.674) go to 17210
	if(p.le.99.513) go to 17211
	if(p.le.99.986) go to 17212
	                go to 17213
17201	call nucltransK(1.596,0.050,5.0e-4,0.7e-4,tclev,thlev,tdlev)
	go to 12300
17202	call nucltransK(0.904,0.050,1.4e-3,0.,tclev,thlev,tdlev)
	go to 81500
17203	call nucltransK(0.723,0.050,2.2e-3,0.,tclev,thlev,tdlev)
	go to 99600
17204	call nucltransK(0.592,0.050,3.3e-3,0.,tclev,thlev,tdlev)
	go to 11280
17205	call nucltransK(0.478,0.050,1.6e-2,0.,tclev,thlev,tdlev)
	go to 12410
17206	call nucltransK(0.468,0.050,3.5e-2,0.,tclev,thlev,tdlev)
	go to 12520
17207	call nucltransK(0.322,0.050,9.0e-2,0.,tclev,thlev,tdlev)
	go to 13980
17208	call nucltransK(0.305,0.050,9.5e-2,0.,tclev,thlev,tdlev)
	go to 14140
17209	call nucltransK(0.301,0.050,1.6e-2,0.,tclev,thlev,tdlev)
	go to 14180
17210	call nucltransK(0.209,0.050,3.0e-1,0.,tclev,thlev,tdlev)
	go to 15100
17211	call nucltransK(0.188,0.050,5.5e-2,0.,tclev,thlev,tdlev)
	go to 15310
17212	call nucltransK(0.160,0.050,4.5e-1,0.,tclev,thlev,tdlev)
	go to 15600
17213	call nucltransK(0.058,0.050,1.2e-0,0.,tclev,thlev,tdlev)
	go to 16610
c-----------------------------------------------------------------------
1661	call beta(0.308,64.,0.,0.,t)
16610	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.03) go to 16611
	if(p.le. 8.84) go to 16612
	if(p.le.75.84) go to 16613
	if(p.le.79.11) go to 16614
	if(p.le.89.76) go to 16615
	if(p.le.94.78) go to 16616
	if(p.le.95.18) go to 16617
	if(p.le.98.45) go to 16618
	               go to 16619
16611	call nucltransK(1.538,0.050,1.2e-3,0.4e-4,tclev,thlev,tdlev)
	go to 12300
16612	call nucltransK(1.290,0.050,1.8e-3,0.1e-4,tclev,thlev,tdlev)
	go to 37100
16613	call nucltransK(0.845,0.050,4.0e-3,0.,tclev,thlev,tdlev)
	go to 81500
16614	call nucltransK(0.665,0.050,7.0e-3,0.,tclev,thlev,tdlev)
	go to 99600
16615	call nucltransK(0.613,0.050,1.2e-2,0.,tclev,thlev,tdlev)
	go to 10480
16616	call nucltransK(0.533,0.050,1.2e-2,0.,tclev,thlev,tdlev)
	go to 11280
16617	call nucltransK(0.420,0.050,1.4e-1,0.,tclev,thlev,tdlev)
	go to 12410
16618	call nucltransK(0.397,0.050,3.5e-2,0.,tclev,thlev,tdlev)
	go to 12640
16619	call nucltransK(0.130,0.050,1.0e-0,0.,tclev,thlev,tdlev)
	go to 15310
c-----------------------------------------------------------------------
1646	call beta(0.323,64.,0.,0.,t)
16460	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.26) go to 16461
	if(p.le. 2.57) go to 16462
	if(p.le. 3.97) go to 16463
	if(p.le. 6.77) go to 16464
	if(p.le.51.79) go to 16465
	if(p.le.56.52) go to 16466
	if(p.le.82.63) go to 16467
	if(p.le.84.79) go to 16468
	if(p.le.89.70) go to 16469
	if(p.le.91.41) go to 16470
	if(p.le.95.37) go to 16471
	if(p.le.99.02) go to 16472
	               go to 16473
16461	call nucltransK(1.523,0.050,1.2e-3,0.4e-4,tclev,thlev,tdlev)
	go to 12300
16462	call nucltransK(1.275,0.050,1.8e-3,0.1e-4,tclev,thlev,tdlev)
	go to 37100
16463	call nucltransK(0.928,0.050,3.5e-3,0.,tclev,thlev,tdlev)
	go to 71800
16464	call nucltransK(0.830,0.050,5.7e-3,0.,tclev,thlev,tdlev)
	go to 81500
16465	call nucltransK(0.650,0.050,7.3e-3,0.,tclev,thlev,tdlev)
	go to 99600
16466	call nucltransK(0.598,0.050,1.4e-2,0.,tclev,thlev,tdlev)
	go to 10480
16467	call nucltransK(0.518,0.050,1.3e-2,0.,tclev,thlev,tdlev)
	go to 11280
16468	call nucltransK(0.394,0.050,8.5e-3,0.,tclev,thlev,tdlev)
	go to 12520
16469	call nucltransK(0.382,0.050,3.4e-2,0.,tclev,thlev,tdlev)
	go to 12640
16470	call nucltransK(0.368,0.050,9.0e-3,0.,tclev,thlev,tdlev)
	go to 12770
16471	call nucltransK(0.352,0.050,3.5e-2,0.,tclev,thlev,tdlev)
	go to 12940
16472	call nucltransK(0.242,0.050,3.5e-2,0.,tclev,thlev,tdlev)
	go to 14040
16473	call nucltransK(0.228,0.050,1.4e-1,0.,tclev,thlev,tdlev)
	go to 14180
c-----------------------------------------------------------------------
1617	call beta(0.352,64.,0.,0.,t)
16170	thlev=0.
	p=100.*rnd1(d)
	if(p.le.43.76) go to 16171
	if(p.le.97.79) go to 16172
	if(p.le.97.80) go to 16173
	if(p.le.98.37) go to 16174
	if(p.le.99.00) go to 16175
	if(p.le.99.43) go to 16176
	if(p.le.99.73) go to 16177
	if(p.le.99.85) go to 16178
	               go to 16179
16171	call nucltransK(1.494,0.050,5.6e-4,0.5e-4,tclev,thlev,tdlev)
	go to 12300
16172	call nucltransK(1.246,0.050,7.6e-4,0.2e-4,tclev,thlev,tdlev)
	go to 37100
16173	call nucltransK(0.801,0.050,1.8e-3,0.,tclev,thlev,tdlev)
	go to 81500
16174	call nucltransK(0.621,0.050,2.8e-3,0.,tclev,thlev,tdlev)
	go to 99600
16175	call nucltransK(0.569,0.050,3.5e-3,0.,tclev,thlev,tdlev)
	go to 10480
16176	call nucltransK(0.488,0.050,5.0e-3,0.,tclev,thlev,tdlev)
	go to 11280
16177	call nucltransK(0.481,0.050,5.0e-3,0.,tclev,thlev,tdlev)
	go to 11360
16178	call nucltransK(0.375,0.050,4.0e-2,0.,tclev,thlev,tdlev)
	go to 12410
16179	call nucltransK(0.219,0.050,2.0e-1,0.,tclev,thlev,tdlev)
	go to 13980
c-----------------------------------------------------------------------
1560	call beta(0.409,64.,0.,0.,t)
15600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.90.61) go to 15601
	if(p.le.90.62) go to 15602
	if(p.le.92.94) go to 15603
	if(p.le.98.83) go to 15604
	               go to 15605
15601	call nucltransK(1.189,0.050,1.1e-3,0.1e-4,tclev,thlev,tdlev)
	go to 37100
15602	call nucltransK(0.563,0.050,6.0e-2,0.,tclev,thlev,tdlev)
	go to 99600
15603	call nucltransK(0.296,0.050,1.6e-2,0.,tclev,thlev,tdlev)
	go to 12640
15604	call nucltransK(0.283,0.050,1.7e-2,0.,tclev,thlev,tdlev)
	go to 12770
15605	call nucltransK(0.163,0.050,5.0e-1,0.,tclev,thlev,tdlev)
	go to 13980
c-----------------------------------------------------------------------
1531	call beta(0.438,64.,0.,0.,t)
15310	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.99) go to 15311
	if(p.le. 4.80) go to 15312
	if(p.le.12.06) go to 15313
	if(p.le.52.17) go to 15314
	if(p.le.82.25) go to 15315
	if(p.le.90.87) go to 15316
	if(p.le.91.69) go to 15317
	if(p.le.95.70) go to 15318
	if(p.le.96.26) go to 15319
	if(p.le.96.75) go to 15320
	if(p.le.98.55) go to 15321
	if(p.le.99.59) go to 15322
	               go to 15323
15311	call nucltransK(1.531,0.050,1.1e-3,0.4e-4,tclev,thlev,tdlev)
	return
15312	call nucltransK(1.408,0.050,3.7e-3,0.2e-4,tclev,thlev,tdlev)
	go to 12300
15313	call nucltransK(1.161,0.050,2.2e-3,0.1e-4,tclev,thlev,tdlev)
	go to 37100
15314	call nucltransK(0.851,0.050,3.9e-3,0.,tclev,thlev,tdlev)
	go to 68100
15315	call nucltransK(0.716,0.050,1.3e-2,0.,tclev,thlev,tdlev)
	go to 81500
15316	call nucltransK(0.535,0.050,2.5e-2,0.,tclev,thlev,tdlev)
	go to 99600
15317	call nucltransK(0.484,0.050,1.6e-2,0.,tclev,thlev,tdlev)
	go to 10480
15318	call nucltransK(0.404,0.050,2.8e-2,0.,tclev,thlev,tdlev)
	go to 11280
15319	call nucltransK(0.290,0.050,1.8e-2,0.,tclev,thlev,tdlev)
	go to 12410
15320	call nucltransK(0.280,0.050,1.9e-2,0.,tclev,thlev,tdlev)
	go to 12520
15321	call nucltransK(0.267,0.050,8.0e-2,0.,tclev,thlev,tdlev)
	go to 12640
15322	call nucltransK(0.238,0.050,1.2e-1,0.,tclev,thlev,tdlev)
	go to 12940
15323	call nucltransK(0.117,0.050,2.0e-1,0.,tclev,thlev,tdlev)
	go to 14140
c-----------------------------------------------------------------------
15100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.20.) go to 15101
	             go to 15102
15101	call nucltransK(1.510,0.050,6.0e-4,0.5e-4,tclev,thlev,tdlev)
	return
15102	call nucltransK(1.387,0.050,6.5e-4,0.3e-4,tclev,thlev,tdlev)
	go to 12300
c-----------------------------------------------------------------------
1418	call beta(0.551,64.,0.,0.,t)
14180	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.51) go to 14181
	if(p.le.20.34) go to 14182
	if(p.le.68.31) go to 14183
	if(p.le.69.27) go to 14184
	if(p.le.90.86) go to 14185
	if(p.le.91.87) go to 14186
	if(p.le.95.71) go to 14187
	if(p.le.96.56) go to 14188
	if(p.le.97.71) go to 14189
	if(p.le.98.30) go to 14190
	if(p.le.98.94) go to 14191
	if(p.le.99.45) go to 14192
	               go to 14193
14181	call nucltransK(1.418,0.050,1.4e-3,0.2e-4,tclev,thlev,tdlev)
	return
14182	call nucltransK(1.295,0.050,1.6e-3,0.1e-4,tclev,thlev,tdlev)
	go to 12300
14183	call nucltransK(1.047,0.050,2.5e-3,0.,tclev,thlev,tdlev)
	go to 37100
14184	call nucltransK(0.737,0.050,5.5e-3,0.,tclev,thlev,tdlev)
	go to 68100
14185	call nucltransK(0.603,0.050,3.8e-2,0.,tclev,thlev,tdlev)
	go to 81500
14186	call nucltransK(0.422,0.050,1.4e-1,0.,tclev,thlev,tdlev)
	go to 99600
14187	call nucltransK(0.371,0.050,3.2e-2,0.,tclev,thlev,tdlev)
	go to 10480
14188	call nucltransK(0.290,0.050,6.5e-2,0.,tclev,thlev,tdlev)
	go to 11280
14189	call nucltransK(0.236,0.050,1.2e-1,0.,tclev,thlev,tdlev)
	go to 11820
14190	call nucltransK(0.177,0.050,6.0e-2,0.,tclev,thlev,tdlev)
	go to 12410
14191	call nucltransK(0.167,0.050,7.0e-2,0.,tclev,thlev,tdlev)
	go to 12520
14192	call nucltransK(0.124,0.050,1.2e-0,0.,tclev,thlev,tdlev)
	go to 12940
14193	call nucltransK(0.123,0.050,1.2e-0,0.,tclev,thlev,tdlev)
	go to 12960
c-----------------------------------------------------------------------
14140	thlev=0.
	p=100.*rnd1(d)
	if(p.le.21.22) go to 14141
	if(p.le.97.01) go to 14142
	if(p.le.99.68) go to 14143
	if(p.le.99.79) go to 14144
	               go to 14145
14141	call nucltransK(1.414,0.050,6.1e-4,0.4e-4,tclev,thlev,tdlev)
	return
14142	call nucltransK(1.291,0.050,7.2e-4,0.2e-4,tclev,thlev,tdlev)
	go to 12300
14143	call nucltransK(0.599,0.050,3.5e-3,0.,tclev,thlev,tdlev)
	go to 81500
14144	call nucltransK(0.167,0.050,4.0e-1,0.,tclev,thlev,tdlev)
	go to 12520
14145	call nucltransK(0.120,0.050,1.8e-1,0.,tclev,thlev,tdlev)
	go to 12940
c-----------------------------------------------------------------------
14040	thlev=0.
	call nucltransK(1.033,0.050,1.1e-3,0.,tclev,thlev,tdlev)
	go to 37100
c-----------------------------------------------------------------------
1398	call beta(0.571,64.,0.,0.,t)
13980	thlev=0.
	p=100.*rnd1(d)
	if(p.le.96.877) go to 13981
	if(p.le.99.338) go to 13982
	if(p.le.99.876) go to 13983
	if(p.le.99.896) go to 13984
	if(p.le.99.902) go to 13985
	if(p.le.99.929) go to 13986
	                go to 13987
13981	call nucltransK(1.274,0.050,7.4e-4,0.2e-4,tclev,thlev,tdlev)
	go to 12300
13982	call nucltransK(0.582,0.050,3.4e-3,0.,tclev,thlev,tdlev)
	go to 81500
13983	call nucltransK(0.401,0.050,7.0e-2,0.,tclev,thlev,tdlev)
	go to 99600
13984	call nucltransK(0.270,0.050,2.2e-2,0.,tclev,thlev,tdlev)
	go to 11280
13985	call nucltransK(0.260,0.050,2.3e-2,0.,tclev,thlev,tdlev)
	go to 11360
13986	call nucltransK(0.156,0.050,9.0e-2,0.,tclev,thlev,tdlev)
	go to 12410
13987	call nucltransK(0.146,0.050,9.5e-2,0.,tclev,thlev,tdlev)
	go to 12520
c-----------------------------------------------------------------------
12960	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.73) go to 12961
	if(p.le.73.72) go to 12962
	if(p.le.74.45) go to 12963
	if(p.le.78.83) go to 12964
	               go to 12965
12961	call electron(1.245,tclev,thlev,tdlev)         ! only ec
	call gamma(0.050,0.,0.,tdlev)
	return
12962	call nucltransK(1.173,0.050,2.2e-3,0.,tclev,thlev,tdlev)
	go to 12300
12963	call electron(0.565,tclev,thlev,tdlev)         ! only ec
	call gamma(0.050,0.,0.,tdlev)
	go to 68100
12964	call nucltransK(0.480,0.050,1.6e-2,0.,tclev,thlev,tdlev)
	go to 81500
12965	call nucltransK(0.299,0.050,6.0e-2,0.,tclev,thlev,tdlev)
	go to 99600
c-----------------------------------------------------------------------
12940	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.51) go to 12941
	if(p.le.47.79) go to 12942
	if(p.le.83.25) go to 12943
	               go to 12944
12941	call nucltransK(1.294,0.050,1.8e-3,0.1e-4,tclev,thlev,tdlev)
	return
12942	call nucltransK(1.171,0.050,2.2e-3,0.1e-4,tclev,thlev,tdlev)
	go to 12300
12943	call nucltransK(0.923,0.050,3.5e-3,0.,tclev,thlev,tdlev)
	go to 37100
12944	call nucltransK(0.112,0.050,1.7e-0,0.,tclev,thlev,tdlev)
	go to 11820
c-----------------------------------------------------------------------
12770	thlev=0.
	call nucltransK(0.906,0.050,1.4e-3,0.,tclev,thlev,tdlev)
	go to 37100
c-----------------------------------------------------------------------
1264	call beta(0.705,64.,0.,0.,t)
12640	thlev=0.
	p=100.*rnd1(d)
	if(p.le.30.09) go to 12641
	if(p.le.95.92) go to 12642
	if(p.le.97.76) go to 12643
	               go to 12644
12641	call nucltransK(1.141,0.050,2.1e-3,0.,tclev,thlev,tdlev)
	go to 12300
12642	call nucltransK(0.893,0.050,3.7e-3,0.,tclev,thlev,tdlev)
	go to 37100
12643	call nucltransK(0.546,0.050,1.2e-2,0.,tclev,thlev,tdlev)
	go to 71800
12644	call nucltransK(0.267,0.050,9.5e-2,0.,tclev,thlev,tdlev)
	go to 99600
c-----------------------------------------------------------------------
1252	call beta(0.717,64.,0.,0.,t)
12520	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.76) go to 12521
	if(p.le.80.51) go to 12522
	               go to 12523
12521	call nucltransK(1.252,0.050,3.5e-3,0.,tclev,thlev,tdlev)
	return
12522	call nucltransK(1.129,0.050,9.1e-4,0.1e-4,tclev,thlev,tdlev)
	go to 12300
12523	call nucltransK(0.881,0.050,1.5e-3,0.,tclev,thlev,tdlev)
	go to 37100
c-----------------------------------------------------------------------
12410	thlev=0.
	p=100.*rnd1(d)
	if(p.le.54.62) go to 12411
	if(p.le.99.02) go to 12412
	if(p.le.99.68) go to 12413
	               go to 12414
12411	call nucltransK(1.241,0.050,7.7e-4,0.2e-4,tclev,thlev,tdlev)
	return
12412	call nucltransK(1.118,0.050,9.3e-4,0.1e-4,tclev,thlev,tdlev)
	go to 12300
12413	call nucltransK(0.561,0.050,4.0e-3,0.,tclev,thlev,tdlev)
	go to 68100
12414	call nucltransK(0.426,0.050,7.0e-3,0.,tclev,thlev,tdlev)
	go to 81500
c-----------------------------------------------------------------------
11820	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.21) go to 11821
	if(p.le.84.00) go to 11822
	if(p.le.84.84) go to 11823
	               go to 11824
11821	call electron(1.132,tclev,thlev,tdlev)
	call gamma(0.050,0.,0.,tdlev)
	return
11822	call nucltransK(1.059,0.050,2.5e-3,0.,tclev,thlev,tdlev)
	go to 12300
11823	call electron(0.451,tclev,thlev,tdlev)
	call gamma(0.050,0.,0.,tdlev)
	go to 68100
11824	call nucltransK(0.367,0.050,3.3e-2,0.,tclev,thlev,tdlev)
	go to 81500
c-----------------------------------------------------------------------
11360	thlev=0.
	p=100.*rnd1(d)
	if(p.le.71.94) go to 11361
	               go to 11362
11361	call nucltransK(1.136,0.050,2.2e-3,0.,tclev,thlev,tdlev)
	return
11362	call nucltransK(1.013,0.050,2.8e-3,0.,tclev,thlev,tdlev)
	go to 12300
c-----------------------------------------------------------------------
1128	call beta(0.841,64.,0.,0.,t)
11280	thlev=0.
	p=100.*rnd1(d)
	if(p.le.79.629) go to 11281
	if(p.le.99.855) go to 11282
	if(p.le.99.938) go to 11283
	if(p.le.99.987) go to 11284
	                go to 11285
11281	call nucltransK(1.005,0.050,2.8e-3,0.,tclev,thlev,tdlev)
	go to 12300
11282	call nucltransK(0.757,0.050,5.2e-3,0.,tclev,thlev,tdlev)
	go to 37100
11283	call nucltransK(0.312,0.050,5.5e-2,0.,tclev,thlev,tdlev)
	go to 81500
11284	call nucltransK(0.132,0.050,9.5e-1,0.,tclev,thlev,tdlev)
	go to 99600
11285	call nucltransK(0.080,0.050,6.0e-0,0.,tclev,thlev,tdlev)
	go to 10480
c-----------------------------------------------------------------------
10480	thlev=0.
	p=100.*rnd1(d)
	if(p.le.23.98) go to 10481
	if(p.le.86.75) go to 10482
	if(p.le.90.58) go to 10483
	               go to 10484
10481	call nucltransK(0.925,0.050,3.3e-3,0.,tclev,thlev,tdlev)
	go to 12300
10482	call nucltransK(0.677,0.050,5.1e-2,0.,tclev,thlev,tdlev)
	go to 37100
10483	call nucltransK(0.330,0.050,4.5e-2,0.,tclev,thlev,tdlev)
	go to 71800
10484	call nucltransK(0.232,0.050,1.4e-1,0.,tclev,thlev,tdlev)
	go to 81500
c-----------------------------------------------------------------------
996	call beta(0.973,64.,0.,0.,t)
99600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.46.43) go to 99601
	if(p.le.98.59) go to 99602
	if(p.le.99.95) go to 99603
	if(p.le.99.98) go to 99604
	               go to 99605
99601	call nucltransK(0.996,0.050,2.8e-3,0.,tclev,thlev,tdlev)
	return
99602	call nucltransK(0.873,0.050,3.7e-3,0.,tclev,thlev,tdlev)
	go to 12300
99603	call nucltransK(0.625,0.050,8.0e-3,0.,tclev,thlev,tdlev)
	go to 37100
99604	call nucltransK(0.315,0.050,5.2e-2,0.,tclev,thlev,tdlev)
	go to 68100
99605	call nucltransK(0.181,0.050,3.5e-1,0.,tclev,thlev,tdlev)
	go to 81500
c-----------------------------------------------------------------------
815	call beta(1.154,64.,0.,0.,t)
81500	thlev=6.9e-12
	p=100.*rnd1(d)
	if(p.le.17.86) go to 81501
	if(p.le.80.18) go to 81502
	if(p.le.99.75) go to 81503
	               go to 81504
81501	call nucltransK(0.816,0.050,4.3e-3,0.,tclev,thlev,tdlev)
	return
81502	call nucltransK(0.692,0.050,4.6e-2,0.,tclev,thlev,tdlev)
	go to 12300
81503	call nucltransK(0.444,0.050,1.9e-2,0.,tclev,thlev,tdlev)
	go to 37100
81504	call nucltransK(0.135,0.050,8.7e-1,0.,tclev,thlev,tdlev)
	go to 68100
c-----------------------------------------------------------------------
71800	thlev=7.8e-12
	call nucltransK(0.347,0.050,3.9e-2,0.,tclev,thlev,tdlev)
	go to 37100
c-----------------------------------------------------------------------
68100	thlev=4.0e-12
	p=100.*rnd1(d)
	if(p.le. 2.06) go to 68101
	               go to 68102
68101	call electron(0.631,tclev,thlev,tdlev)
	call gamma(0.050,0.,0.,tdlev)
	return
68102	call nucltransK(0.558,0.050,1.1e-2,0.,tclev,thlev,tdlev)
	go to 12300
c-----------------------------------------------------------------------
371	call beta(1.598,64.,0.,0.,t)
37100	thlev=45.2e-12
	call nucltransK(0.248,0.050,1.1e-1,0.,tclev,thlev,tdlev)
	go to 12300
c-----------------------------------------------------------------------
c123	call beta(1.846,64.,0.,0.,t)
c correction to the 1st forbidden non-unique shape in accordance with
c L.M.Langer et al., PR 119(1960)1308
123	call beta1(1.846,64.,0.,0.,t,0.,-0.2280,0.04465,0.)
12300	thlev=1.186e-9
	call nucltransK(0.123,0.050,1.2e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Gd146(tcnuc,tdnuc)
c Scheme of 146Gd decay ("Table of Isotopes", 7th ed., 1978).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 10.03.1996.
	thnuc=4.173e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le. 0.3) go to 806
	if(pdecay.le. 0.8) go to 743
	if(pdecay.le.77.2) go to 385
	                   go to 230
c-----------------------------------------------------------------------
806	call gamma(0.049,0.,0.,t)
80600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.36.) go to 80601
	             go to 80602
80601	call nucltransK(0.576,0.049,1.8e-2,0.,tclev,thlev,tdlev)
	go to 23000
80602	call nucltransK(0.421,0.049,4.5e-2,0.,tclev,thlev,tdlev)
	go to 38500
c-----------------------------------------------------------------------
743	call gamma(0.049,0.,0.,t)
74300	thlev=0.
	call nucltransK(0.743,0.049,1.0e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
385	p=100.*rnd1(d)
	if(p.le.99.91) call gamma(0.049,0.,0.,t)
	if(p.gt.99.91) call beta(0.343,-63.,0.,0.,t)
38500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.0.4) go to 38501
	             go to 38502
38501	call nucltransK(0.269,0.049,8.0e-2,0.,tclev,thlev,tdlev)
	go to 11500
38502	call nucltransK(0.155,0.049,6.5e-1,0.,tclev,thlev,tdlev)
	go to 23000
c-----------------------------------------------------------------------
230	call gamma(0.049,0.,0.,t)
23000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.0.2) go to 23001
	             go to 23002
23001	call nucltransK(0.230,0.049,1.4e-1,0.,tclev,thlev,tdlev)
	return
23002	call nucltransK(0.115,0.049,1.5e-0,0.,tclev,thlev,tdlev)
	go to 11500
c-----------------------------------------------------------------------
11500	thlev=0.
	call nucltransK(0.115,0.049,1.5e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Hf182(tcnuc,tdnuc)
c Scheme of 182Hf decay ("Table of Isotopes", 7th ed., 1978).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 5.03.1996.
	thnuc=2.84011e14
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	go to 270
c-----------------------------------------------------------------------
270	call beta(0.160,73.,0.,0.,t)
	thlev=1.2e-9
	p=100.*rnd1(d)
	if(p.le.91.77) go to 27001
	if(p.le.92.00) go to 27002
	               go to 27003
27001	call nucltransK(0.270,0.067,3.1e-1,0.,tclev,thlev,tdlev)
	return
27002	call nucltransK(0.173,0.067,9.5e-2,0.,tclev,thlev,tdlev)
	go to 98000
27003	call nucltransK(0.156,0.067,1.5e-1,0.,tclev,thlev,tdlev)
	go to 11400
c-----------------------------------------------------------------------
11400	thlev=0.
	call nucltransK(0.114,0.067,4.5e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
98000	thlev=0.
	call nucltransK(0.098,0.067,5.0e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine I126(tcnuc,tdnuc)
c Model for scheme of I126 decay (J.Katakura et al., Nucl. Data Sheets 
c 97(2002)765).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 25.11.2003.
	thnuc=1.1172e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.47.300) go to 1 ! 47.300% beta- to 126Xe
	if(pdecay.le.98.992) go to 2 ! 51.692% EC    to 126Te
	                     go to 3 !  1.008% beta+ to 126Te
c-----------------------------------------------------------------------
c beta-
c-----------------------------------------------------------------------
1	pbeta=100.*rnd1(d)
	if(pbeta.le. 7.65) go to 880 !  7.65%
	if(pbeta.le.78.22) go to 389 ! 70.57%
	call beta(1.258,54.,0.,0.,t) ! 21.78%
        return
c-----------------------------------------------------------------------
880	call beta(0.378,54.,0.,0.,t)
88000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.20.51) go to 88001   
	               go to 88002   
88001	call nucltransK(0.880,0.035,2.2e-3,0.,tclev,thlev,tdlev)
	return
88002	call nucltransK(0.491,0.035,9.5e-3,0.,tclev,thlev,tdlev)
	go to 38900
c-----------------------------------------------------------------------
389	call beta(0.869,54.,0.,0.,t)
38900	thlev=41.3e-12
	p=100.*rnd1(d)
	call nucltransK(0.389,0.035,1.9e-2,0.,tclev,thlev,tdlev)
	return
c----------------------------------------------------------------------
c EC
c----------------------------------------------------------------------
2	call gamma(0.032,0.,0.,t)
	pec=100.*rnd1(d)
	if(pec.le. 0.014) go to 2045 !  0.014%
	if(pec.le. 0.015) go to 1873 !  0.001%
	if(pec.le. 8.630) go to 1420 !  8.615%
	if(pec.le.63.800) go to  666 ! 55.170%
        return                       ! 36.200%
c----------------------------------------------------------------------
2045	thlev=0.
	p=100.*rnd1(d)
	if(p.le.66.00) go to 20451   
	               go to 20452   
20451	call nucltransK(2.045,0.032,3.0e-4,2.3e-4,tclev,thlev,tdlev)
	return
20452	call nucltransK(1.379,0.032,1.2e-3,0.7e-4,tclev,thlev,tdlev)
	go to 66600
c----------------------------------------------------------------------
1873	thlev=0.
	call nucltransK(1.207,0.032,1.1e-3,0.1e-4,tclev,thlev,tdlev)
	go to 66600
c----------------------------------------------------------------------
1420	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.83) go to 14201  
	               go to 14202  
14201	call nucltransK(1.420,0.032,7.0e-4,0.2e-4,tclev,thlev,tdlev)
	return
14202	call nucltransK(0.754,0.032,2.8e-3,0.,tclev,thlev,tdlev)
	go to 66600
c----------------------------------------------------------------------
666	continue
66600	thlev=0.
	call nucltransK(0.666,0.032,3.8e-3,0.,tclev,thlev,tdlev)
	return
c----------------------------------------------------------------------
c beta+
c----------------------------------------------------------------------
3	pbeta=100.*rnd1(d)
	if(pbeta.le.19.64) go to 1666 ! 19.64%
	call beta(1.133,-52.,0.,0.,t) ! 80.36%
        return	
c-----------------------------------------------------------------------
1666	call beta(0.467,-52.,0.,0.,t)
	thlev=0.
	call nucltransK(0.666,0.032,3.8e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

        subroutine I133(tcnuc,tdnuc)
c Scheme of I133 decay in accordance with S.Rab, NDS 75(1995)491.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.12.2003.
	thnuc=74880.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
        pbeta=100.*rnd1(d)
        if(pbeta.le. 0.42) go to 1590
        if(pbeta.le. 1.68) go to 1386
        if(pbeta.le. 2.08) go to 1350
        if(pbeta.le. 5.89) go to 1298
        if(pbeta.le. 9.10) go to 1236
        if(pbeta.le. 9.73) go to 1052
        if(pbeta.le.13.94) go to  875
        if(pbeta.le.15.77) go to  744
        if(pbeta.le.98.96) go to  530
	                   go to  233
c-----------------------------------------------------------------------
1590    call beta(0.181,54.,0.,0.,t)
15900	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.72) go to 15901
	if(p.le.33.78) go to 15902
	if(p.le.85.06) go to 15903
	if(p.le.90.33) go to 15904
	if(p.le.98.95) go to 15905
	               go to 15906
15901	call nucltransK(1.590,0.035,1.0e-3,1.1e-4,tclev,thlev,tdlev)
        return
15902	call nucltransK(1.060,0.035,1.7e-3,0.,tclev,thlev,tdlev)
        go to 53000
15903	call nucltransK(0.910,0.035,2.0e-2,0.,tclev,thlev,tdlev)
        go to 68000
15904	call nucltransK(0.679,0.035,5.5e-3,0.,tclev,thlev,tdlev)
        go to 91100
15905	call nucltransK(0.538,0.035,8.5e-3,0.,tclev,thlev,tdlev)
        go to 10520
15906	call nucltransK(0.204,0.035,1.5e-1,0.,tclev,thlev,tdlev)
        go to 13860
c-----------------------------------------------------------------------
1386    call beta(0.385,54.,0.,0.,t)
13860	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.72) go to 13861
	               go to 13862
13861	call nucltransK(1.386,0.035,3.5e-3,0.,tclev,thlev,tdlev)
        return
13862	call nucltransK(0.856,0.035,2.6e-3,0.,tclev,thlev,tdlev)
        go to 53000
c-----------------------------------------------------------------------
1350    call beta(0.421,54.,0.,0.,t)
13500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.37.48) go to 13501
	if(p.le.40.53) go to 13502
	if(p.le.79.26) go to 13503
	if(p.le.90.00) go to 13504
	               go to 13505
13501	call nucltransK(1.350,0.035,9.9e-4,0.6e-4,tclev,thlev,tdlev)
        return
13502	call nucltransK(1.088,0.035,1.3e-3,0.,tclev,thlev,tdlev)
        go to 26300
13503	call nucltransK(0.821,0.035,3.1e-3,0.,tclev,thlev,tdlev)
        go to 53000
13504	call nucltransK(0.670,0.035,5.0e-3,0.,tclev,thlev,tdlev)
        go to 68000
13505	call nucltransK(0.439,0.035,1.4e-2,0.,tclev,thlev,tdlev)
        go to 91100
c-----------------------------------------------------------------------
1298    call beta(0.473,54.,0.,0.,t)
12980	thlev=0.
	p=100.*rnd1(d)
	if(p.le.62.29) go to 12981
	if(p.le.62.52) go to 12982
	if(p.le.74.71) go to 12983
	if(p.le.89.13) go to 12984
	if(p.le.97.51) go to 12985
	if(p.le.99.07) go to 12986
	               go to 12987
12981	call nucltransK(1.298,0.035,9.6e-4,0.5e-4,tclev,thlev,tdlev)
        return
12982	call nucltransK(1.036,0.035,1.5e-3,0.,tclev,thlev,tdlev)
        go to 26300
12983	call nucltransK(0.768,0.035,3.5e-3,0.,tclev,thlev,tdlev)
        go to 53000
12984	call nucltransK(0.618,0.035,5.9e-3,0.,tclev,thlev,tdlev)
        go to 68000
12985	call nucltransK(0.423,0.035,1.5e-2,0.,tclev,thlev,tdlev)
        go to 87500
12986	call nucltransK(0.387,0.035,2.0e-2,0.,tclev,thlev,tdlev)
        go to 91100
12987	call nucltransK(0.246,0.035,8.0e-2,0.,tclev,thlev,tdlev)
        go to 10520
c-----------------------------------------------------------------------
1236    call beta(0.535,54.,0.,0.,t)
12360	thlev=0.
	p=100.*rnd1(d)
	if(p.le.47.94) go to 12361
	if(p.le.95.88) go to 12362
	if(p.le.96.51) go to 12363
	               go to 12364
12361	call nucltransK(1.236,0.035,1.0e-3,0.1e-4,tclev,thlev,tdlev)
        return
12362	call nucltransK(0.707,0.035,4.3e-3,0.,tclev,thlev,tdlev)
        go to 53000
12363	call nucltransK(0.556,0.035,7.0e-3,0.,tclev,thlev,tdlev)
        go to 68000
12364	call nucltransK(0.361,0.035,3.0e-2,0.,tclev,thlev,tdlev)
        go to 87500
c-----------------------------------------------------------------------
1052    call beta(0.719,54.,0.,0.,t)
10520	thlev=0.
	p=100.*rnd1(d)
	if(p.le.90.26) go to 10521
	if(p.le.98.37) go to 10522
	               go to 10523
10521	call nucltransK(1.052,0.035,2.0e-3,0.,tclev,thlev,tdlev)
        return
10522	call nucltransK(0.790,0.035,3.0e-3,0.,tclev,thlev,tdlev)
        go to 26300
10523	call nucltransK(0.372,0.035,2.5e-2,0.,tclev,thlev,tdlev)
        go to 68000
c-----------------------------------------------------------------------
91100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.31.08) go to 91101
	if(p.le.69.59) go to 91102
	               go to 91103
91101	call nucltransK(0.911,0.035,3.0e-3,0.,tclev,thlev,tdlev)
        return
91102	call nucltransK(0.649,0.035,6.0e-3,0.,tclev,thlev,tdlev)
        go to 26300
91103	call nucltransK(0.382,0.035,2.0e-2,0.,tclev,thlev,tdlev)
        go to 53000
c-----------------------------------------------------------------------
875	call beta(0.896,54.,0.,0.,t)
87500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.97.75) go to 87501
	               go to 87502
87501	call nucltransK(0.875,0.035,2.2e-3,0.,tclev,thlev,tdlev)
        return
87502	call nucltransK(0.345,0.035,3.0e-2,0.,tclev,thlev,tdlev)
        go to 53000
c-----------------------------------------------------------------------
744	call beta(1.027,54.,0.,0.,t)
74400	thlev=0.
	call nucltransK(0.510,0.035,9.0e-3,0.,tclev,thlev,tdlev)
        go to 23300
c-----------------------------------------------------------------------
68000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.77.66) go to 68001
	if(p.le.96.42) go to 68002
	               go to 68003
68001	call nucltransK(0.680,0.035,5.4e-3,0.,tclev,thlev,tdlev)
        return
68002	call nucltransK(0.418,0.035,1.6e-2,0.,tclev,thlev,tdlev)
        go to 26300
68003	call nucltransK(0.150,0.035,3.0e-1,0.,tclev,thlev,tdlev)
        go to 53000
c-----------------------------------------------------------------------
530	call beta(1.241,54.,0.,0.,t)
53000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.99.87) go to 53001
	               go to 53002
53001	call nucltransK(0.530,0.035,8.2e-3,0.,tclev,thlev,tdlev)
        return
53002	call nucltransK(0.267,0.035,6.0e-2,0.,tclev,thlev,tdlev)
        go to 26300
c-----------------------------------------------------------------------
26300	thlev=0.
	call nucltransK(0.263,0.035,5.8e-2,0.,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
233	call beta(1.538,54.,0.,0.,t)
23300	thlev=189216.
	call nucltransK(0.233,0.035,8.8,0.,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

        subroutine I134(tcnuc,tdnuc)
c Scheme of I134 decay in accordance with Yu.V.Sergeenkov, 
c NDS 71(1994)557.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 8.10.2002.
	thnuc=3168.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
        pbeta=100.*rnd1(d)
        if(pbeta.le. 0.368) go to 3492
        if(pbeta.le. 0.435) go to 3477
        if(pbeta.le. 2.216) go to 3375
        if(pbeta.le. 3.300) go to 3360
        if(pbeta.le. 3.509) go to 3314
        if(pbeta.le. 3.567) go to 3300
        if(pbeta.le. 3.786) go to 3256
        if(pbeta.le. 5.129) go to 3084
        if(pbeta.le.35.372) go to 2867
        if(pbeta.le.35.889) go to 2773
        if(pbeta.le.42.754) go to 2654
        if(pbeta.le.58.871) go to 2588
        if(pbeta.le.62.950) go to 2548
        if(pbeta.le.69.516) go to 2408
        if(pbeta.le.80.460) go to 2353
        if(pbeta.le.82.689) go to 2302
        if(pbeta.le.84.281) go to 2272
        if(pbeta.le.87.564) go to 1920
                            go to 1731
c-----------------------------------------------------------------------
3492    call beta(0.678,54.,0.,0.,t)
34920	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 5.17) go to 34921   !  5.17%
	               go to 34922   ! 94.83%
34921	call nucltransK(2.646,0.035,1.5e-4,5.2e-4,tclev,thlev,tdlev)
        go to 84700
34922	call nucltransK(1.190,0.035,2.0e-3,0.2e-4,tclev,thlev,tdlev)
        go to 23020
c-----------------------------------------------------------------------
3477    call beta(0.693,54.,0.,0.,t)
34770	thlev=0.
	p=100.*rnd1(d)
	if(p.le.18.77) go to 34771   ! 18.77%
	               go to 34772   ! 81.23%
34771	call nucltransK(2.630,0.035,1.5e-4,5.1e-4,tclev,thlev,tdlev)
        go to 84700
34772	call nucltransK(0.162,0.035,2.5e-1,0.,tclev,thlev,tdlev)
        go to 33140
c-----------------------------------------------------------------------
3375    call beta(0.795,54.,0.,0.,t)
33750   thlev=0.
	p=100.*rnd1(d)
        if(p.le.21.79) go to 33751
        if(p.le.33.52) go to 33752
        if(p.le.78.21) go to 33753
                       go to 33754
33751   call nucltransK(1.644,0.035,1.5e-3,1.2e-4,tclev,thlev,tdlev)
        go to 17310
33752   call nucltransK(1.239,0.035,1.7e-3,0.4e-4,tclev,thlev,tdlev)
        go to 21370
33753   call nucltransK(1.103,0.035,2.1e-3,0.1e-4,tclev,thlev,tdlev)
        go to 22720
33754   call nucltransK(0.967,0.035,2.5e-3,0.,tclev,thlev,tdlev)
        go to 24080
c-----------------------------------------------------------------------
3360    call beta(0.810,54.,0.,0.,t)
33600   thlev=0.
	p=100.*rnd1(d)
        if(p.le. 6.16) go to 33601
        if(p.le.23.64) go to 33602
                       go to 33603
33601   call nucltransK(2.513,0.035,2.0e-4,4.6e-4,tclev,thlev,tdlev)
        go to 84700
33602   call nucltransK(1.629,0.035,9.0e-4,1.1e-4,tclev,thlev,tdlev)
        go to 17310
33603   call nucltransK(0.707,0.035,5.0e-3,0.,tclev,thlev,tdlev)
        go to 26540
c----------------------------------------------------------------------
3314    call beta(0.856,54.,0.,0.,t)
33140   thlev=0.
	p=100.*rnd1(d)
        if(p.le.63.81) go to 33141
                       go to 33142
33141	call nucltransK(2.467,0.035,2.0e-4,4.5e-4,tclev,thlev,tdlev)
        go to 84700
33142	call nucltransK(1.395,0.035,1.2e-3,0.7e-4,tclev,thlev,tdlev)
        go to 19200
c-----------------------------------------------------------------------
3300    call beta(0.870,54.,0.,0.,t)
33000   thlev=0.
	call nucltransK(2.453,0.035,2.0e-4,4.4e-4,tclev,thlev,tdlev)
        go to 84700
c-----------------------------------------------------------------------
3256    call beta(0.914,54.,0.,0.,t)
32560   thlev=0.
	p=100.*rnd1(d)
        if(p.le.35.78) go to 32561
                       go to 32562
32561	call nucltransK(2.409,0.035,2.1e-4,4.1e-4,tclev,thlev,tdlev)
        go to 84700
32562	call nucltransK(1.336,0.035,1.2e-3,0.6e-4,tclev,thlev,tdlev)
        go to 19200
c-----------------------------------------------------------------------
3084    call beta(1.086,54.,0.,0.,t)
30840   thlev=0.
	p=100.*rnd1(d)
        if(p.le. 3.95) go to 30841
        if(p.le.59.80) go to 30842
        if(p.le.90.32) go to 30843
                       go to 30844
30841   call nucltransK(2.237,0.035,3.0e-4,3.2e-4,tclev,thlev,tdlev)
        go to 84700
30842   call nucltransK(1.470,0.035,1.0e-3,0.9e-4,tclev,thlev,tdlev)
        go to 16140
30843   call nucltransK(1.353,0.035,1.2e-3,0.6e-4,tclev,thlev,tdlev)
        go to 17310
30844   call nucltransK(1.164,0.035,1.6e-3,0.2e-4,tclev,thlev,tdlev)
        go to 19200
c-----------------------------------------------------------------------
2867    call beta(1.303,54.,0.,0.,t)
28670   thlev=0.
	p=100.*rnd1(d)
        if(p.le. 0.62) go to 28671
        if(p.le.30.54) go to 28672
        if(p.le.43.73) go to 28673
        if(p.le.49.75) go to 28674
        if(p.le.86.25) go to 28675
        if(p.le.93.65) go to 28676
        if(p.le.97.99) go to 28677
        if(p.le.99.50) go to 28678
                       go to 28679
28671   call nucltransK(2.021,0.035,3.0e-4,2.3e-4,tclev,thlev,tdlev)
        go to 84700
28672   call nucltransK(1.136,0.035,1.6e-3,0.3e-4,tclev,thlev,tdlev)
        go to 17310
28673   call nucltransK(0.948,0.035,2.4e-3,0.,tclev,thlev,tdlev)
        go to 19200
28674   call nucltransK(0.731,0.035,3.4e-3,0.,tclev,thlev,tdlev)
        go to 21370
28675   call nucltransK(0.595,0.035,7.2e-3,0.,tclev,thlev,tdlev)
        go to 22720
28676   call nucltransK(0.514,0.035,8.0e-3,0.,tclev,thlev,tdlev)
        go to 23530
28677   call nucltransK(0.459,0.035,1.1e-2,0.,tclev,thlev,tdlev)
        go to 24080
28678   call nucltransK(0.320,0.035,3.7e-2,0.,tclev,thlev,tdlev)
        go to 25480
28679   call nucltransK(0.279,0.035,5.2e-2,0.,tclev,thlev,tdlev)
        go to 25880
c-----------------------------------------------------------------------
2773    call beta(1.397,54.,0.,0.,t)
27730   thlev=0.
	p=100.*rnd1(d)
        if(p.le.34.62) go to 27731
                       go to 27732
27731   call nucltransK(1.926,0.035,4.0e-4,2.0e-4,tclev,thlev,tdlev)
        go to 84700
27732   call nucltransK(1.159,0.035,7.0e-4,0.3e-4,tclev,thlev,tdlev)
        go to 16140
c-----------------------------------------------------------------------
2654    call beta(1.516,54.,0.,0.,t)
26540   thlev=0.
	p=100.*rnd1(d)
        if(p.le.71.82) go to 26541
        if(p.le.98.18) go to 26542
                       go to 26543
26541   call nucltransK(1.807,0.035,6.0e-4,1.7e-4,tclev,thlev,tdlev)
        go to 84700
26542   call nucltransK(1.040,0.035,2.0e-3,0.,tclev,thlev,tdlev)
        go to 16140
26543   call nucltransK(0.922,0.035,2.1e-3,0.,tclev,thlev,tdlev)
        go to 17310
c-----------------------------------------------------------------------
2588    call beta(1.582,54.,0.,0.,t)
25880   thlev=0.
	p=100.*rnd1(d)
        if(p.le.15.66) go to 25881
        if(p.le.44.90) go to 25882
        if(p.le.85.87) go to 25883
                       go to 25884
25881   call nucltransK(1.741,0.035,6.0e-4,0.8e-4,tclev,thlev,tdlev)
        go to 84700
25882   call nucltransK(0.975,0.035,1.7e-3,0.,tclev,thlev,tdlev)
        go to 16140
25883   call nucltransK(0.857,0.035,2.9e-3,0.,tclev,thlev,tdlev)
        go to 17310
25884   call nucltransK(0.235,0.035,8.5e-2,0.,tclev,thlev,tdlev)
        go to 23530
c-----------------------------------------------------------------------
2548    call beta(1.622,54.,0.,0.,t)
25480   thlev=0.
	p=100.*rnd1(d)
        if(p.le.13.78) go to 25481
        if(p.le.63.11) go to 25482
        if(p.le.75.78) go to 25483
                       go to 25484
25481   call nucltransK(0.816,0.035,4.0e-3,0.,tclev,thlev,tdlev)
        go to 17310
25482   call nucltransK(0.628,0.035,4.9e-3,0.,tclev,thlev,tdlev)
        go to 19200
25483   call nucltransK(0.411,0.035,2.0e-2,0.,tclev,thlev,tdlev)
        go to 21370
25484   call nucltransK(0.139,0.035,4.5e-1,0.,tclev,thlev,tdlev)
        go to 24080
c-----------------------------------------------------------------------
2408    call beta(1.762,54.,0.,0.,t)
24080   thlev=0.
	p=100.*rnd1(d)
        if(p.le.84.57) go to 24081
                       go to 24082
24081   call nucltransK(0.677,0.035,5.3e-3,0.,tclev,thlev,tdlev)
        go to 17310
24082   call nucltransK(0.489,0.035,9.6e-3,0.,tclev,thlev,tdlev)
        go to 19200
c-----------------------------------------------------------------------
2353    call beta(1.817,54.,0.,0.,t)
23530   thlev=0.
	p=100.*rnd1(d)
        if(p.le. 4.42) go to 23531
        if(p.le.73.01) go to 23532
                       go to 23533
23531   call nucltransK(0.739,0.035,3.3e-3,0.,tclev,thlev,tdlev)
        go to 16140
23532   call nucltransK(0.622,0.035,6.1e-3,0.,tclev,thlev,tdlev)
        go to 17310
23533   call nucltransK(0.433,0.035,1.6e-2,0.,tclev,thlev,tdlev)
        go to 19200
c-----------------------------------------------------------------------
2302    call beta(1.868,54.,0.,0.,t)
23020   thlev=0.
	p=100.*rnd1(d)
        if(p.le.88.08) go to 23021
                       go to 23022
23021   call nucltransK(1.455,0.035,1.1e-3,0.8e-4,tclev,thlev,tdlev)
        go to 84700
23022   call nucltransK(0.571,0.035,9.0e-3,0.,tclev,thlev,tdlev)
        go to 17310
c-----------------------------------------------------------------------
2272    call beta(1.898,54.,0.,0.,t)
22720   thlev=0.
	p=100.*rnd1(d)
        if(p.le.57.01) go to 22721
                       go to 22722
22721   call nucltransK(0.541,0.035,7.7e-3,0.,tclev,thlev,tdlev)
        go to 17310
22722   call nucltransK(0.135,0.035,3.5e-1,0.,tclev,thlev,tdlev)
        go to 21370
c-----------------------------------------------------------------------
21370   thlev=0.
	p=100.*rnd1(d)
        if(p.le.96.64) go to 21371
                       go to 21372
21371   call nucltransK(0.405,0.035,1.8e-2,0.,tclev,thlev,tdlev)
        go to 17310
21372   call nucltransK(0.217,0.035,1.2e-1,0.,tclev,thlev,tdlev)
        go to 19200
c-----------------------------------------------------------------------
1920    call beta(2.250,54.,0.,0.,t)
19200   thlev=0.
	p=100.*rnd1(d)
        if(p.le.94.36) go to 19201
                       go to 19202
19201   call nucltransK(1.073,0.035,1.9e-3,0.1e-4,tclev,thlev,tdlev)
        go to 84700
19202   call nucltransK(0.188,0.035,1.7e-1,0.,tclev,thlev,tdlev)
        go to 17310
c-----------------------------------------------------------------------
1731    call beta(2.439,54.,0.,0.,t)
17310   thlev=0.
	call nucltransK(0.884,0.035,2.2e-3,0.,tclev,thlev,tdlev)
        go to 84700
c-----------------------------------------------------------------------
16140   thlev=0.
	p=100.*rnd1(d)
        if(p.le.50.83) go to 16141
                       go to 16142
16141   call nucltransK(1.614,0.035,3.0e-4,0.5e-4,tclev,thlev,tdlev)
        return
16142   call nucltransK(0.767,0.035,3.2e-3,0.,tclev,thlev,tdlev)
        go to 84700
c-----------------------------------------------------------------------
84700   thlev=1.9e-12
	call nucltransK(0.847,0.035,2.4e-3,0.,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
        end

c***********************************************************************

        subroutine I135(tcnuc,tdnuc)
c Scheme of I135 decay (Yu.V.Sergeenkov et al., Nucl. Data Sheets 
c 84(1998)115).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 12.10.2002.
	thnuc=23652.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
        pbeta=100.*rnd1(d)
        if(pbeta.le. 0.013) go to 2478
        if(pbeta.le. 0.155) go to 2475
        if(pbeta.le. 0.282) go to 2466
        if(pbeta.le. 0.422) go to 2447
        if(pbeta.le. 1.449) go to 2409
        if(pbeta.le. 2.366) go to 2372
        if(pbeta.le. 3.752) go to 2357
        if(pbeta.le. 8.518) go to 2255
        if(pbeta.le.15.896) go to 2233
        if(pbeta.le.15.919) go to 2152
        if(pbeta.le.15.989) go to 2112
        if(pbeta.le.17.574) go to 2093
        if(pbeta.le.18.681) go to 2046
        if(pbeta.le.26.657) go to 1968
        if(pbeta.le.26.707) go to 1927
        if(pbeta.le.27.315) go to 1894
        if(pbeta.le.36.089) go to 1791
        if(pbeta.le.57.825) go to 1678
        if(pbeta.le.65.801) go to 1565
        if(pbeta.le.73.279) go to 1458
        if(pbeta.le.96.810) go to 1260
        if(pbeta.le.98.106) go to 1132
                            go to  527
c-----------------------------------------------------------------------
2478    call beta(0.170,54.,0.,0.,t)
24780   thlev=0.
	p=100.*rnd1(d)
        if(p.le.9.72) go to 24781
                      go to 24782
24781   call nucltransK(2.477,0.035,2.0e-4,4.5e-4,tclev,thlev,tdlev)
        return
24782   call nucltransK(2.189,0.035,3.0e-4,3.1e-4,tclev,thlev,tdlev)
        go to 28800
c-----------------------------------------------------------------------
2475    call beta(0.173,54.,0.,0.,t)
24750   thlev=0.
	p=100.*rnd1(d)
        if(p.le.45.00) go to 24751
                       go to 24752
24751   call nucltransK(1.948,0.035,2.4e-4,2.1e-4,tclev,thlev,tdlev)
        go to 52700
24752   call nucltransK(1.344,0.035,4.0e-4,0.7e-4,tclev,thlev,tdlev)
        go to 11320
c-----------------------------------------------------------------------
2466    call beta(0.182,54.,0.,0.,t)
24660   thlev=0.
	p=100.*rnd1(d)
        if(p.le.56.69) go to 24661
        if(p.le.81.89) go to 24662
                       go to 24663
24661   call nucltransK(2.466,0.035,4.0e-4,5.3e-4,tclev,thlev,tdlev)
        return
24662   call nucltransK(1.335,0.035,1.2e-3,0.6e-4,tclev,thlev,tdlev)
        go to 11320
24663   call nucltransK(0.685,0.035,4.0e-3,0.,tclev,thlev,tdlev)
        go to 17810
c-----------------------------------------------------------------------
2447    call beta(0.201,54.,0.,0.,t)
24470   thlev=0.
	p=100.*rnd1(d)
        if(p.le.46.81) go to 24471
                       go to 24472
24471   call nucltransK(1.316,0.035,4.5e-4,0.5e-4,tclev,thlev,tdlev)
        go to 11320
24472   call nucltransK(0.656,0.035,1.6e-3,0.,tclev,thlev,tdlev)
        go to 17910
c-----------------------------------------------------------------------
2409    call beta(0.239,54.,0.,0.,t)
24090   thlev=0.
	p=100.*rnd1(d)
        if(p.le.93.48) go to 24091
        if(p.le.96.40) go to 24092
                       go to 24093
24091   call nucltransK(2.409,0.035,3.5e-4,4.1e-4,tclev,thlev,tdlev)
        return
24092   call nucltransK(0.960,0.035,2.6e-3,0.,tclev,thlev,tdlev)
        go to 14480
24093   call nucltransK(0.617,0.035,7.0e-3,0.,tclev,thlev,tdlev)
        go to 17910
c-----------------------------------------------------------------------
2372    call beta(0.276,54.,0.,0.,t)
23720   thlev=0.
	p=100.*rnd1(d)
        if(p.le. 0.66) go to 23721
                       go to 23722
23721   call nucltransK(1.845,0.035,2.6e-4,1.8e-4,tclev,thlev,tdlev)
        go to 52700
23722   call nucltransK(1.240,0.035,1.4e-3,0.5e-4,tclev,thlev,tdlev)
        go to 11320
c-----------------------------------------------------------------------
2357    call beta(0.291,54.,0.,0.,t)
23570   thlev=0.
	p=100.*rnd1(d)
        if(p.le.41.91) go to 23571
        if(p.le.45.02) go to 23572
        if(p.le.51.45) go to 23573
        if(p.le.55.42) go to 23574
        if(p.le.64.74) go to 23575
        if(p.le.86.41) go to 23576
                       go to 23577
23571   call nucltransK(1.831,0.035,2.6e-4,1.6e-4,tclev,thlev,tdlev)
        go to 52700
23572   call nucltransK(1.226,0.035,1.4e-3,0.4e-4,tclev,thlev,tdlev)
        go to 11320
23573   call nucltransK(1.097,0.035,1.4e-3,0.,tclev,thlev,tdlev)
        go to 12600
23574   call nucltransK(0.679,0.035,6.0e-3,0.,tclev,thlev,tdlev)
        go to 16780
23575   call nucltransK(0.576,0.035,8.5e-3,0.,tclev,thlev,tdlev)
        go to 17810
23576   call nucltransK(0.430,0.035,1.8e-2,0.,tclev,thlev,tdlev)
        go to 19270
23577   call nucltransK(0.264,0.035,6.5e-2,0.,tclev,thlev,tdlev)
        go to 20930
c-----------------------------------------------------------------------
2255    call beta(0.393,54.,0.,0.,t)
22550   thlev=0.
	p=100.*rnd1(d)
        if(p.le.12.88) go to 22551
        if(p.le.89.34) go to 22552
        if(p.le.92.51) go to 22553
        if(p.le.93.48) go to 22554
        if(p.le.97.07) go to 22555
        if(p.le.99.79) go to 22556
                       go to 22557
22551   call nucltransK(2.255,0.035,3.7e-4,3.8e-4,tclev,thlev,tdlev)
        return
22552   call nucltransK(1.124,0.035,1.7e-3,0.2e-4,tclev,thlev,tdlev)
        go to 11320
22553   call nucltransK(0.995,0.035,1.9e-3,0.,tclev,thlev,tdlev)
        go to 12600
22554   call nucltransK(0.807,0.035,2.6e-3,0.,tclev,thlev,tdlev)
        go to 14480
22555   call nucltransK(0.798,0.035,4.0e-3,0.,tclev,thlev,tdlev)
        go to 14580
22556   call nucltransK(0.690,0.035,5.5e-3,0.,tclev,thlev,tdlev)
        go to 15650
22557   call nucltransK(0.163,0.035,2.2e-1,0.,tclev,thlev,tdlev)
        go to 20930
c-----------------------------------------------------------------------
2233    call beta(0.415,54.,0.,0.,t)
22330   thlev=0.
	p=100.*rnd1(d)
        if(p.le.55.75) go to 22331
        if(p.le.77.64) go to 22332
        if(p.le.94.09) go to 22333
        if(p.le.98.39) go to 22334
        if(p.le.99.68) go to 22335
                       go to 22336
22331   call nucltransK(1.706,0.035,2.8e-4,1.0e-4,tclev,thlev,tdlev)
        go to 52700
22332   call nucltransK(1.102,0.035,1.4e-3,0.1e-4,tclev,thlev,tdlev)
        go to 11320
22333   call nucltransK(0.973,0.035,1.8e-3,0.,tclev,thlev,tdlev)
        go to 12600
22334   call nucltransK(0.452,0.035,1.6e-2,0.,tclev,thlev,tdlev)
        go to 17810
22335   call nucltransK(0.306,0.035,4.0e-2,0.,tclev,thlev,tdlev)
        go to 19270
22336   call nucltransK(0.184,0.035,4.0e-2,0.,tclev,thlev,tdlev)
        go to 20490
c-----------------------------------------------------------------------
2152    call beta(0.496,54.,0.,0.,t)
21520   thlev=0.
	call nucltransK(2.152,0.035,2.0e-4,2.9e-4,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
2112    call beta(0.536,54.,0.,0.,t)
21120   thlev=0.
	call nucltransK(2.112,0.035,2.0e-4,2.7e-4,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
2093    call beta(0.555,54.,0.,0.,t)
20930   thlev=0.
	p=100.*rnd1(d)
        if(p.le.72.79) go to 20931
        if(p.le.81.26) go to 20932
        if(p.le.98.25) go to 20933
                       go to 20934
20931   call nucltransK(1.566,0.035,2.8e-4,0.7e-4,tclev,thlev,tdlev)
        go to 52700
20932   call nucltransK(0.961,0.035,2.6e-3,0.,tclev,thlev,tdlev)
        go to 11320
20933   call nucltransK(0.415,0.035,2.0e-2,0.,tclev,thlev,tdlev)
        go to 16780
20934   call nucltransK(0.166,0.035,2.2e-1,0.,tclev,thlev,tdlev)
        go to 19270
c-----------------------------------------------------------------------
20490   thlev=0.
	call nucltransK(1.522,0.035,9.0e-4,0.9e-4,tclev,thlev,tdlev)
        go to 52700
c-----------------------------------------------------------------------
2046    call beta(0.602,54.,0.,0.,t)
20460   thlev=0.
	p=100.*rnd1(d)
        if(p.le.79.31) go to 20461
        if(p.le.93.16) go to 20462
        if(p.le.97.90) go to 20463
                       go to 20464
20461   call nucltransK(2.046,0.035,4.5e-4,2.3e-4,tclev,thlev,tdlev)
        return
20462   call nucltransK(0.785,0.035,3.6e-3,0.,tclev,thlev,tdlev)
        go to 12600
20463   call nucltransK(0.588,0.035,8.5e-3,0.,tclev,thlev,tdlev)
        go to 14580
20464   call nucltransK(0.255,0.035,6.5e-2,0.,tclev,thlev,tdlev)
        go to 17910
c-----------------------------------------------------------------------
1968    call beta(0.680,54.,0.,0.,t)
19680   thlev=0.
	p=100.*rnd1(d)
        if(p.le. 0.21) go to 19681
        if(p.le.84.72) go to 19682
        if(p.le.93.05) go to 19683
        if(p.le.95.98) go to 19684
                       go to 19685
19681   call nucltransK(1.442,0.035,0.8e-4,1.0e-3,tclev,thlev,tdlev)
        go to 52700
19682   call nucltransK(0.837,0.035,2.5e-3,0.,tclev,thlev,tdlev)
        go to 11320
19683   call nucltransK(0.708,0.035,5.0e-3,0.,tclev,thlev,tdlev)
        go to 12600
19684   call nucltransK(0.403,0.035,1.8e-2,0.,tclev,thlev,tdlev)
        go to 15650
19685   call nucltransK(0.290,0.035,4.6e-2,0.,tclev,thlev,tdlev)
        go to 16780
c-----------------------------------------------------------------------
1927    call beta(0.721,54.,0.,0.,t)
19270   thlev=0.
	p=100.*rnd1(d)
        if(p.le.58.50) go to 19271
        if(p.le.63.05) go to 19272
                       go to 19273
19271   call nucltransK(1.927,0.035,5.0e-4,1.4e-4,tclev,thlev,tdlev)
        return
19272   call nucltransK(0.796,0.035,4.0e-3,0.,tclev,thlev,tdlev)
        go to 11320
19273   call nucltransK(0.362,0.035,2.8e-2,0.,tclev,thlev,tdlev)
        go to 15650
c-----------------------------------------------------------------------
1894    call beta(0.754,54.,0.,0.,t)
18940   thlev=0.
	call nucltransK(1.368,0.035,9.0e-4,0.2e-4,tclev,thlev,tdlev)
        go to 52700
c-----------------------------------------------------------------------
1791    call beta(0.857,54.,0.,0.,t)
17910   thlev=0.
	p=100.*rnd1(d)
        if(p.le.86.68) go to 17911
        if(p.le.98.81) go to 17912
        if(p.le.99.17) go to 17913
        if(p.le.99.18) go to 17914
        if(p.le.99.60) go to 17915
        if(p.le.99.92) go to 17916
                       go to 17917
17911   call nucltransK(1.791,0.035,6.5e-4,1.6e-4,tclev,thlev,tdlev)
        return
17912   call nucltransK(1.503,0.035,7.5e-4,0.3e-4,tclev,thlev,tdlev)
        go to 28800
17913   call nucltransK(0.531,0.035,9.3e-3,0.,tclev,thlev,tdlev)
        go to 12600
17914   call nucltransK(0.343,0.035,3.0e-2,0.,tclev,thlev,tdlev)
        go to 14480
17915   call nucltransK(0.334,0.035,3.5e-2,0.,tclev,thlev,tdlev)
        go to 14580
17916   call nucltransK(0.248,0.035,8.0e-3,0.,tclev,thlev,tdlev)
        go to 15440
17917   call nucltransK(0.113,0.035,6.0e-1,0.,tclev,thlev,tdlev)
        go to 16780
c-----------------------------------------------------------------------
17810   thlev=0.
	p=100.*rnd1(d)
        if(p.le.1.29) go to 17811
                      go to 17812
17811   call nucltransK(1.255,0.035,4.7e-4,0.3e-4,tclev,thlev,tdlev)
        go to 52700
17812   call nucltransK(0.645,0.035,4.5e-3,0.,tclev,thlev,tdlev)
        go to 11320
c-----------------------------------------------------------------------
1678    call beta(0.970,54.,0.,0.,t)
16780   thlev=0.
	p=100.*rnd1(d)
        if(p.le.42.57) go to 16781
        if(p.le.74.58) go to 16782
        if(p.le.90.20) go to 16783
        if(p.le.91.38) go to 16784
        if(p.le.99.94) go to 16785
                       go to 16786
16781   call nucltransK(1.678,0.035,5.6e-4,0.7e-4,tclev,thlev,tdlev)
        return
16782   call nucltransK(0.547,0.035,9.1e-3,0.,tclev,thlev,tdlev)
        go to 11320
16783   call nucltransK(0.418,0.035,1.6e-2,0.,tclev,thlev,tdlev)
        go to 12600
16784   call nucltransK(0.230,0.035,1.0e-1,0.,tclev,thlev,tdlev)
        go to 14480
16785   call nucltransK(0.221,0.035,1.0e-1,0.,tclev,thlev,tdlev)
        go to 14580
16786   call nucltransK(0.113,0.035,6.0e-1,0.,tclev,thlev,tdlev)
        go to 15650
c-----------------------------------------------------------------------
1565    call beta(1.083,54.,0.,0.,t)
15650   thlev=0.
	p=100.*rnd1(d)
        if(p.le.93.00) go to 15651
        if(p.le.99.62) go to 15652
                       go to 15653
15651   call nucltransK(1.039,0.035,6.4e-4,0.,tclev,thlev,tdlev)
        go to 52700
15652   call nucltransK(0.434,0.035,1.6e-2,0.,tclev,thlev,tdlev)
        go to 11320
15653   call nucltransK(0.305,0.035,4.0e-2,0.,tclev,thlev,tdlev)
        go to 12600
c-----------------------------------------------------------------------
15440   thlev=0.
	p=100.*rnd1(d)
        if(p.le.81.25) go to 15441
                       go to 15442
15441   call nucltransK(1.544,0.035,9.0e-4,1.0e-4,tclev,thlev,tdlev)
        return
15442   call nucltransK(1.255,0.035,1.2e-3,0.5e-4,tclev,thlev,tdlev)
        go to 28800
c-----------------------------------------------------------------------
1458    call beta(1.190,54.,0.,0.,t)
14580   thlev=0.
	p=100.*rnd1(d)
        if(p.le.90.44) go to 14581
        if(p.le.99.59) go to 14582
        if(p.le.99.61) go to 14583
                       go to 14584
14581   call nucltransK(1.458,0.035,7.0e-4,0.9e-4,tclev,thlev,tdlev)
        return
14582   call nucltransK(1.169,0.035,1.3e-3,0.,tclev,thlev,tdlev)
        go to 28800
14583   call nucltransK(0.326,0.035,3.5e-2,0.,tclev,thlev,tdlev)
        go to 11320
14584   call nucltransK(0.197,0.035,1.5e-1,0.,tclev,thlev,tdlev)
        go to 12600
c-----------------------------------------------------------------------
14480   thlev=0.
	p=100.*rnd1(d)
        if(p.le.75.65) go to 14481
                       go to 14482
14481   call nucltransK(1.448,0.035,7.0e-4,0.9e-4,tclev,thlev,tdlev)
        return
14482   call nucltransK(1.160,0.035,1.3e-3,0.,tclev,thlev,tdlev)
        go to 28800
c-----------------------------------------------------------------------
1260    call beta(1.388,54.,0.,0.,t)
12600   thlev=0.
	p=100.*rnd1(d)
        if(p.le.96.99) go to 12601
                       go to 12602
12601   call nucltransK(1.260,0.035,1.2e-3,0.1e-4,tclev,thlev,tdlev)
        return
12602   call nucltransK(0.972,0.035,1.8e-3,0.,tclev,thlev,tdlev)
        go to 28800
c-----------------------------------------------------------------------
1132    call beta(1.516,54.,0.,0.,t)
11320   thlev=0.
	call nucltransK(1.132,0.035,1.3e-3,0.,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
527     call beta(2.121,54.,0.,0.,t)
52700   thlev=917.4
	call nucltransK(0.527,0.035,2.4e-1,0.,tclev,thlev,tdlev)
	return                        
c-----------------------------------------------------------------------
28800   thlev=0.
	call nucltransK(0.288,0.035,4.7e-2,0.,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
        end

c***********************************************************************

	subroutine K40(tcnuc,tdnuc)
c Scheme of K40 decay (J.A.Cameron et al., ENSDF 29.10.2002).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 3.08.1992, 22.10.1995, 28.11.2003;
c 3rd forbidden unique shape for beta decay, VIT, 27.10.2006.
	thnuc=3.94775e+16
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.89.140) then
c	 call beta(1.311,+20.,0.,0.,t)                       ! 89.140% b- 40Ca(gs)
c change to the 3rd forbidden unique shape in accordance with
c H.Daniel, RMP 40(1968)659 and W.H.Kelly et al., Nucl. Phys. 11(1959)492
c cf(e) = pel**6 + c1*pel**4*pnu**2 + c2*pel**2*pnu**4 + c3*pnu**6
	 call beta2(1.311,+20.,0.,0.,t,3,7.,7.,1.,0.)
	elseif(pdecay.le.99.800) then                        ! 10.660% ec 40Ar(1461)
	 call gamma(0.003,0.,0.,t)
	 thlev=1.12e-12
	 call nucltransK(1.461,0.003,3.0e-5,7.3e-5,tclev,thlev,tdlev)
	elseif(pdecay.le.99.999) then                        !  0.199% ec 40Ar(gs)
	 call gamma(0.003,0.,0.,t)
	else
         call beta(0.483,-18.,0.,0.,t)                       !  0.001% b+ 40Ar(gs)
	end if
	return
	end

c***********************************************************************

	subroutine K42(tcnuc,tdnuc)
c Scheme of K42 decay (B.Singh et al., NDS 92(2001)1
c with additional information from ToI-1978 and ToI-1998).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 31.03.2006; 29.10.2006 (change from allowed to forbidden beta shapes);
c 7.08.2012 (addition of new experimental correction factors).  
	thnuc=44496.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
        pbeta=100.*rnd1(d)
        if(pbeta.le. 0.07) go to 3446
        if(pbeta.le. 0.12) go to 2424
        if(pbeta.le. 0.46) go to 1837
        if(pbeta.le.18.10) go to 1525
                           go to 10000
c-----------------------------------------------------------------------
3446    call beta(0.080,20.,0.,0.,t)
34460   thlev=250.e-15 ! ToI-1998
	p=100.*rnd1(d)
        if(p.le.63.66) go to 34461
        if(p.le.94.88) go to 34462
                       go to 34463
34461   call nucltransK(1.921,0.004,1.2e-5,5.8e-4,tclev,thlev,tdlev)
        go to 15250
34462   call nucltransK(1.021,0.004,3.9e-5,0.,tclev,thlev,tdlev)
        go to 24240
34463   call nucltransK(0.692,0.004,8.7e-5,0.,tclev,thlev,tdlev)
        go to 27530
c-----------------------------------------------------------------------
27530   thlev=3.0e-12 ! ToI-1998
27531   call nucltransK(1.228,0.004,5.6e-5,1.4e-5,tclev,thlev,tdlev)
        go to 15250
c-----------------------------------------------------------------------
2424    call beta(1.101,20.,0.,0.,t)
24240   thlev=140.e-15 ! ToI-1998
	p=100.*rnd1(d)
        if(p.le.27.78) go to 24241
                       go to 24242
24241   call nucltransK(2.424,0.004,1.5e-5,5.2e-4,tclev,thlev,tdlev)
        return
24242   call nucltransK(0.900,0.004,8.3e-5,0.,tclev,thlev,tdlev)
        go to 15250
c-----------------------------------------------------------------------
c1837    call beta(1.688,20.,0.,0.,t)
c change to the 1st forbidden unique
1837	call beta_1fu(1.688,20.,0.,0.,t,0.,0.,0.,0.)
18370   thlev=0.33e-9      
	p=100.*rnd1(d)
        if(p.le.2.1) go to 18371 ! ToI-1978
                     go to 18372
18371   p=100.*rnd1(d)
	if(p.le.90.) then
	   call pair(0.815,tclev,thlev,tdlev)
	else
	   call electron(1.833,tclev,thlev,tdlev)
	   call gamma(0.004,0.,0.,tdlev)
	endif
        return
18372   call nucltransK(0.313,0.004,3.4e-3,0.,tclev,thlev,tdlev)
        go to 15250
c-----------------------------------------------------------------------
c below only 1 line with call to beta or beta1 should be uncommented
c allowed spectrum
c1525    call beta(2.000,20.,0.,0.,t)
c change to forbidden spectrum with experimental corrections from
c H.Daniel, RMP 49(1968)659
1525    call beta1(2.000,20.,0.,0.,t,0.81,0.15,-0.02,0.)
c or from S.Andre et al., Compt. Rend. 259(1964)1102
c1525    call beta1(2.000,20.,0.,0.,t,0.67,-0.12,0.013,0.)
c or from M.Rao et al., Curr. Sci. 45(1976)319
c1525    call beta1(2.000,20.,0.,0.,t,0.70,-0.11,0.012,0.)
15250   thlev=0.82e-12 ! ToI-1998
	call nucltransK(1.525,0.004,3.6e-5,9.8e-5,tclev,thlev,tdlev)
        return
c-----------------------------------------------------------------------
c below only 1 line with call to beta or beta_1fu should be uncommented
c allowed spectrum
c10000	call beta(3.525,20.,0.,0.,t)
c 1st forbidden unique with experimental corrections from 
c H.Daniel et al., PRB 136(1964)1240 and RMP 40(1968)659
10000	call beta_1fu(3.525,20.,0.,0.,t,0.,-0.01,0.,0.)
c or from J. van Klinken et al., NPA 112(1968)372
c10000	call beta_1fu(3.525,20.,0.,0.,t,0.,-0.005,0.,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Kr81(tcnuc,tdnuc)
c Scheme of Kr81 decay (NDS 79(1996)447 and ENSDF at NNDC site on 9.12.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 9.12.2007.
	thnuc=7.226493e12
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.0.30) go to   276
	                   go to 10000
c-----------------------------------------------------------------------
276	call gamma(0.013,0.,0.,t) ! capture from only K shell is supposed
	thlev=9.7e-12
	call nucltransKLM(0.276,0.013,7.3e-3,0.002,7.8e-4,0.000,2.6e-4,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	pklm=100.*rnd1(d)
	if(                    pklm.le.84.73) call gamma(0.013,0.,0.,t)
	if(pklm.gt.84.73 .and. pklm.le.97.44) call gamma(0.002,0.,0.,t)
	if(pklm.gt.97.44                    ) call gamma(0.000,0.,0.,t)
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Kr85(tcnuc,tdnuc)
c Scheme of Kr85 decay (NDS 62(1991)271 and ENSDF at NNDC site on 9.12.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 9.12.2007.
	thnuc=3.394243e8
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.0.434) go to   514
	                    go to 10000
c-----------------------------------------------------------------------
514	call beta(0.173,37.,0.,0.,t)
514000	thlev=1.015e-6
	p=100.*rnd1(d)
	if(p.le.99.99947) go to 51401
	                  go to 51402
51401	call nucltransKLM(0.514,0.014,6.3e-3,0.002,7.1e-4,0.000,2.3e-4,
     +                    0.,tclev,thlev,tdlev)
	return
51402	call nucltransKLM(0.363,0.014,2.9e-2,0.002,3.9e-3,0.000,1.3e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 15100
c-----------------------------------------------------------------------
15100	thlev=0.71e-9
	call nucltransKLM(0.151,0.014,4.3e-2,0.002,4.8e-3,0.000,3.4e-4,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c 1st forbidden unique beta decay
10000	call beta2(0.687,37.,0.,0.,t,1,1.,0.,0.,0.)
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Mn54(tcnuc,tdnuc)
c Scheme of Mn54 decay ("Table of Isotopes", 8th ed., 1996 + NDS 50(1987)255).
c Accuracy in description of: decay branches       - 0.001%,
c                           : deexcitation process - 0.001%.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 16.04.1998.
c VIT, 1.04.2007, updated to NDS 107(2006)1393.
	thnuc=2.696717E+07
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
c 100% EC to Cr54
	call gamma(0.006,0.,0.,t)
	thlev=7.9e-12
	call nucltransK(0.835,0.006,2.4e-4,0.,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

	subroutine Na22(tcnuc,tdnuc)
c Scheme of Na22 decay ("Table of Isotopes", 7th ed., 1978).
c Accuracy in description of: decay branches       - 0.001%,
c                           : deexcitation process - 0.001%.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 26.07.1993, 22.10.1995.
c VIT, 12.11.2006 (updated to NDS 106(2005)1 and change to beta spectra with
c experimental corrections).
c VIT, 26.08.2007 (corrected beta shapes).
	thnuc=8.2132717e+7
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.99.944) go to  1275
	                     go to 10000
c-----------------------------------------------------------------------
1275	thlev=3.63e-12
	if(pdecay.le.9.618) call gamma(0.001,0.,0.,t)
c	if(pdecay.gt.9.618) call beta(0.545,-10.,0.,0.,t)
c experimental correction to the shape of the beta spectrum from:
c H.Daniel, RMP 40(1968)659 and H.Wenninger et al., NPA 109(1968)561
	if(pdecay.gt.9.618) 
     +     call beta1(0.545,-10.,0.,0.,t,1.e-3,0.,0.,0.)
	call nucltransK(1.275,0.001,6.8e-6,2.1e-5,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c10000	call beta(1.820,-10.,0.,0.,t)
c change to 2nd unique shape in accordance with H.Daniel, RMP 40(1968)659
10000	call beta2(1.820,-10.,0.,0.,t,2,3.333333,1.,0.,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Nb96(tcnuc,tdnuc)
c Scheme of Nb96 decay (NDS 68(1993)165 and ENSDF at NNDC site on 13.11.2007).
c Three-figured labels correspond to energies of 96Mo excited
c levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 7.05.1998; update 13.11.2007.
	thnuc=8.406e4
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.024) go to 2975
	if(pbeta.le. 0.524) go to 2876
	if(pbeta.le. 1.014) go to 2755
	if(pbeta.le. 3.314) go to 2441
	                    go to 2439
c-----------------------------------------------------------------------
2975	call beta(0.212,42.,0.,0.,t)
29750	thlev=0.
	call nucltransK(1.347,0.020,4.3e-4,0.3e-4,tclev,thlev,tdlev)
	go to 16280
c-----------------------------------------------------------------------
2876	call beta(0.311,42.,0.,0.,t)
28760	thlev=0.
	p=100.*rnd1(d)
	if(p.le.93.26) go to 28761
	               go to 28762
28761	call nucltransK(0.435,0.020,5.4e-3,0.,tclev,thlev,tdlev)
	go to 24410
28762	call nucltransK(0.120,0.020,1.5e-1,0.,tclev,thlev,tdlev)
	go to 27550
c-----------------------------------------------------------------------
2755	call beta(0.432,42.,0.,0.,t)
27550	thlev=0.
	p=100.*rnd1(d)
	if(p.le.75.63) go to 27551
	if(p.le.86.64) go to 27552
	               go to 27553
27551	call nucltransK(1.127,0.020,5.2e-4,0.1e-5,tclev,thlev,tdlev)
	go to 16280
27552	call nucltransK(0.316,0.020,1.2e-2,0.,tclev,thlev,tdlev)
	go to 24390
27553	call nucltransKLM(0.314,0.020,1.1e-2,0.003,1.3e-3,0.001,4.2e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 24410
c-----------------------------------------------------------------------
2441	call beta(0.746,42.,0.,0.,t)
24410	thlev=0.
	call nucltransK(0.813,0.020,1.3e-3,0.,tclev,thlev,tdlev)
	go to 16280
c-----------------------------------------------------------------------
2439	call beta(0.748,42.,0.,0.,t)
24390	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.20) go to 24391
	if(p.le.69.87) go to 24392
	if(p.le.96.89) go to 24393
	               go to 24394
24391	call nucltransKLM(0.811,0.020,1.1e-3,0.003,1.3e-4,0.001,2.2e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 16280
24392	call nucltransKLM(0.569,0.020,2.6e-3,0.003,2.8e-4,0.001,5.8e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 18700
24393	call nucltransKLM(0.460,0.020,5.3e-3,0.003,6.4e-4,0.001,1.3e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 19780
24394	call nucltransKLM(0.219,0.020,3.2e-2,0.003,4.0e-3,0.001,1.4e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 22190
c-----------------------------------------------------------------------
22190	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.19) go to 22191
	if(p.le.36.94) go to 22192
	if(p.le.44.75) go to 22193
	if(p.le.68.44) go to 22194
	if(p.le.80.66) go to 22195
	               go to 22196
22191	call nucltransK(1.441,0.020,4.3e-4,0.5e-4,tclev,thlev,tdlev)
	go to 77800
22192	call nucltransKLM(0.722,0.020,1.5e-3,0.003,1.7e-4,0.001,3.6e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 14980
22193	call nucltransKLM(0.593,0.020,2.3e-3,0.003,2.6e-4,0.001,5.2e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 16260
22194	call nucltransKLM(0.591,0.020,2.4e-3,0.003,2.8e-4,0.001,4.9e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 16280
22195	call nucltransKLM(0.350,0.020,1.0e-2,0.003,1.2e-3,0.001,5.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 18700
22196	call nucltransKLM(0.241,0.020,2.1e-2,0.003,2.4e-3,0.001,4.9e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 19780
c-----------------------------------------------------------------------
19780	thlev=0.
	p=100.*rnd1(d)
	if(p.le.71.90) go to 19781
	if(p.le.92.93) go to 19782
	if(p.le.95.95) go to 19783
	if(p.le.99.81) go to 19784
	               go to 19785
19781	call nucltransK(1.200,0.020,4.6e-4,7.7e-6,tclev,thlev,tdlev)
	go to 77800
19782	call nucltransK(0.481,0.020,4.5e-3,0.,tclev,thlev,tdlev)
	go to 14980
19783	call nucltransKLM(0.353,0.020,1.0e-2,0.003,1.2e-3,0.001,7.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 16260
19784	call nucltransKLM(0.350,0.020,1.0e-2,0.003,1.2e-3,0.001,5.0e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 16280
19785	call nucltransKLM(0.109,0.020,1.7e-1,0.003,2.0e-2,0.001,4.2e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 18700
c-----------------------------------------------------------------------
18700	thlev=6.4e-12
	p=100.*rnd1(d)
	if(p.le.88.61) go to 18701
	if(p.le.93.45) go to 18702
	               go to 18703
18701	call nucltransK(1.091,0.020,5.6e-4,0.,tclev,thlev,tdlev)
	go to 77800
18702	call nucltransKLM(0.372,0.020,1.0e-2,0.003,1.3e-3,0.001,4.3e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 14980
18703	call nucltransKLM(0.241,0.020,2.1e-2,0.003,2.4e-3,0.001,7.8e-4,
     +                    0.,tclev,thlev,tdlev)
	go to 16280
c-----------------------------------------------------------------------
16280	thlev=1.2e-12
	call nucltransKLM(0.850,0.020,1.0e-3,0.003,1.1e-4,0.001,2.3e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 77800
c-----------------------------------------------------------------------
16260	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.72) go to 16261
	if(p.le.98.63) go to 16262
	               go to 16263
16261	call nucltransK(1.626,0.020,2.8e-4,1.3e-4,tclev,thlev,tdlev)
	return
16262	call nucltransKLM(0.848,0.020,1.0e-3,0.003,1.1e-4,0.001,2.3e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 77800
16263	call nucltransKLM(0.128,0.020,1.1e-1,0.003,1.3e-2,0.001,2.7e-3,
     +                    0.,tclev,thlev,tdlev)
	go to 14980
c-----------------------------------------------------------------------
14980	thlev=0.78e-12
	p=100.*rnd1(d)
	if(p.le.32.43) go to 14981
	               go to 14982
14981	call nucltransK(1.498,0.020,3.3e-4,0.8e-4,tclev,thlev,tdlev)
	return
14982	call nucltransKLM(0.720,0.020,1.5e-3,0.003,1.7e-4,0.001,3.5e-5,
     +                    0.,tclev,thlev,tdlev)
	go to 77800
c-----------------------------------------------------------------------
77800	thlev=3.67e-12
	call nucltransKLM(0.778,0.020,1.2e-3,0.003,1.4e-3,0.001,2.9e-5,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine P32(tcnuc,tdnuc)
c Scheme of P32 beta decay, ToI'1998 and ENSDF'2004.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 5.11.2006.
	thnuc=1.2323232e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
c experimental corrections to the allowed beta shape from
c H.Daniel, RMP 40(1968)659 and M.J.Canty et al., NP 85(1966)317
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1
	call beta1(1.710,16.,0.,0.,t,0.,0.003,0.,0.)
	return
	end

c***********************************************************************

	subroutine Pa234m(tcnuc,tdnuc)
c Model (not the exact) scheme of Pa234m decay ("Table of Isotopes",
c 7th ed., 1978):
c decays of Pa234m to excited levels of U234 with energies
c greater than 1.045 MeV are not considered (p=0.20%).
c Three- and four-figured labels correspond to energies of
c U234 excited levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 18.08.1992, 22.10.1995;
c VIT, 3.11.2006 (update to NDS 71(1994)181 - however, levels with E_exc>1.045 
c MeV are still not considered; change of beta shape of the gs-to-gs beta decay 
c to the 1st forbidden with exp. corr.).
c VIT, 1.03.2017 - update to NDS 108(2007)681; levels with E_exc>1.045 
c MeV are still not considered.
	thnuc=69.54
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
c-----------------------------------------------------------------------
c IT to Pa234
	if(pdecay.le.0.16) then
	   call nucltransK(0.074,0.021,1.1e+1,0.,tclev,thlev,tdlev)
	   return ! subsequent b- decay of Pa234 (T1/2=6.70 h) should be described independently
	endif
c-----------------------------------------------------------------------
c beta decay to U234
	pbeta=100.*rnd1(d)
	if(pbeta.le.1.006) go to  1045   !  1.006%
	if(pbeta.le.1.015) go to   989   !  0.009%
	if(pbeta.le.1.967) go to   810   !  0.952%
	if(pbeta.le.2.026) go to   786   !  0.059%
	                   go to 10000   ! 97.974%
c-----------------------------------------------------------------------
1045	call beta(1.224,92.,0.,0.,t)
10450	thlev=0.
	p=100.*rnd1(d)
	if(p.le.83.766) go to 10451   ! 83.766%
	if(p.le.91.281) go to 10452   !  7.515%
	if(p.le.99.897) go to 10453   !  8.616%
	                go to 10454   !  0.103%
10451	call nucltransK(1.001,0.116,1.1e-2,0.,tclev,thlev,tdlev)
	go to 43000
10452	call nucltransK(0.258,0.116,5.5e-2,0.,tclev,thlev,tdlev)
	go to 78600
10453	call electron(0.119,tclev,thlev,tdlev)      ! only ec
	call gamma(0.116,0.,0.,tdlev)
	go to 81000
10454	call nucltransK(0.193,0.116,8.5e-1,0.,tclev,thlev,tdlev)
	go to 85200
c-----------------------------------------------------------------------
989	call beta(1.280,92.,0.,0.,t)
98900	thlev=0.76e-9
	p=100.*rnd1(d)
	if(p.le.42.437) go to 98901   ! 42.437%
	if(p.le.59.244) go to 98902   ! 16.807%
	if(p.le.92.857) go to 98903   ! 33.613%
	                go to 98904   !  7.143%
98901	call nucltransK(0.946,0.116,4.1e-3,0.,tclev,thlev,tdlev)
	go to 43000
98902	call nucltransK(0.203,0.116,1.4e0,0.,tclev,thlev,tdlev)
	go to 78600
98903	call nucltransK(0.140,0.116,5.3e0,0.,tclev,thlev,tdlev)
	go to 84900
98904	call nucltransK(0.063,0.022,4.3e-1,0.,tclev,thlev,tdlev)
	go to 92700
c-----------------------------------------------------------------------
92700	thlev=1.38e-12
	p=100.*rnd1(d)
	if(p.le.25.714) go to 92701   ! 25.714%
	if(p.le.99.184) go to 92702   ! 73.470%
	                go to 92703   !  0.816%
92701	call nucltransK(0.927,0.116,1.3e-2,0.,tclev,thlev,tdlev)
	return
92702	call nucltransK(0.883,0.116,1.4e-2,0.,tclev,thlev,tdlev)
	go to 43000
92703	call nucltransK(0.783,0.116,1.8e-2,0.,tclev,thlev,tdlev)
	go to 14300
c-----------------------------------------------------------------------
85200	thlev=1.74e-12
	p=100.*rnd1(d)
	if(p.le.15.556) go to 85201   ! 15.556%
	if(p.le.63.368) go to 85202   ! 47.812%
	if(p.le.68.223) go to 85203   !  4.855%
	                go to 85204   ! 31.777%
85201	call nucltransK(0.852,0.116,1.5e-2,0.,tclev,thlev,tdlev)
	return
85202	call nucltransK(0.808,0.116,4.2e0,0.,tclev,thlev,tdlev)
	go to 43000
85203	call nucltransK(0.708,0.116,2.2e-2,0.,tclev,thlev,tdlev)
	go to 14300
85204	call nucltransK(0.042,0.022,8.6e+2,0.,tclev,thlev,tdlev)
	go to 81000
c-----------------------------------------------------------------------
84900	thlev=0.
	p=100.*rnd1(d)
	if(p.le.51.304) go to 84901   ! 51.304%
	                go to 84902   ! 48.696%
84901	call nucltransK(0.806,0.116,5.5e-3,0.,tclev,thlev,tdlev)
	go to 43000
84902	call nucltransK(0.706,0.116,7.0e-3,0.,tclev,thlev,tdlev)
	go to 14300
c-----------------------------------------------------------------------
810	call beta(1.459,92.,0.,0.,t)
81000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.72.606) go to 81001   ! 72.606%
	                go to 81002   ! 27.394%
81001	call electron(0.694,tclev,thlev,tdlev)      ! only ec
	call gamma(0.116,0.,0.,tdlev)
	return
81002	call nucltransK(0.766,0.116,1.9e-2,0.,tclev,thlev,tdlev)
	go to 43000
c-----------------------------------------------------------------------
786	call beta(1.483,92.,0.,0.,t)
78600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.33.786) go to 78601   ! 33.786%
	                go to 78602   ! 66.214%
78601	call nucltransK(0.786,0.116,5.7e-3,0.,tclev,thlev,tdlev)
	return
78602	call nucltransK(0.743,0.116,6.4e-3,0.,tclev,thlev,tdlev)
	go to 43000
c-----------------------------------------------------------------------
14300	thlev=0.
	call nucltransK(0.100,0.022,1.3e+1,0.,tclev,thlev,tdlev)
	go to 43000
c-----------------------------------------------------------------------
43000	thlev=0.252e-9
	call nucltransK(0.043,0.022,7.1e+2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c10000	call beta(2.269,92.,0.,0.,t)
c change to 1st forbidden shape with experimental shape factor from 
c A.G.Carles et al., NIMA 369(1996)431
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1.
10000	call beta1(2.269,92.,0.,0.,t,0.,-0.09,0.,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Pb210(tcnuc,tdnuc)
c Scheme of Pb210 decay in accordance with NDS 99(2003)649 and ENSDF at
c the NNDC site on 6.08.2007.
c Labels correspond to energies of Bi210 excited levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c Beta decays are 1st forbidden (dJ^(dPi)=0^-,1^-); thus allowed shape
c is supposen.
c VIT, 6.08.2007.
	thnuc=7.0056e8
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.84.) go to    47
	                 go to 10000
c-----------------------------------------------------------------------
47	call beta(0.0170,83.,0.,0.,t)
47000	thlev=0.
	call nucltransKLM(0.0465,0.016,14.2,0.004,3.36,0.001,1.14,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call beta(0.0635,83.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Pb211(tcnuc,tdnuc)
c Scheme of Pb211 decay ("Table of Isotopes", 7th ed., 1978).
c Three- and four-figured labels correspond to energies of Bi211
c excited levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 14.08.1992, 22.10.1995;
c VIT, 31.10.2006 (updated to NDS 103(2004)183). 
c Main beta decays are 1st forbidden (dJ^(dPi)=0^-,1^-); thus allowed shape
c is supposen.
	thnuc=2166.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.0.0186) go to  1271  !  0.0186%
	if(pbeta.le.0.0199) go to  1234  !  0.0013%
	if(pbeta.le.0.0369) go to  1196  !  0.0170%
	if(pbeta.le.0.8660) go to  1109  !  0.8291%
	if(pbeta.le.0.8706) go to  1104  !  0.0046%
	if(pbeta.le.0.9265) go to  1081  !  0.0559%
	if(pbeta.le.0.9485) go to   951  !  0.0220%
	if(pbeta.le.7.2616) go to   832  !  6.3131%
	if(pbeta.le.8.7999) go to   405  !  1.5383%
	                    go to 10000  ! 91.2001%
c-----------------------------------------------------------------------
1271	call beta(0.096,83.,0.,0.,t)
12710	thlev=0.
	p=100.*rnd1(d)
	if(p.le.36.76) go to 12711   ! 36.76%
	if(p.le.68.65) go to 12712   ! 31.89%
	               go to 12713   ! 31.35%
12711	call nucltransK(1.271,0.091,1.0e-2,0.2e-4,tclev,thlev,tdlev)
	return
12712	call nucltransK(0.866,0.091,2.8e-2,0.,tclev,thlev,tdlev)
	go to 40500
12713	call nucltransK(0.504,0.091,1.1e-1,0.,tclev,thlev,tdlev)
	go to 76700
c-----------------------------------------------------------------------
1234	call beta(0.133,83.,0.,0.,t)
	call nucltransK(1.234,0.091,1.1e-2,0.1e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1196	call beta(0.171,83.,0.,0.,t)
11960	thlev=0.
	p=100.*rnd1(d)
	if(p.le.62.96) go to 11961   ! 62.96%
	               go to 11962   ! 37.04%
11961	call nucltransK(1.196,0.091,1.2e-2,0.1e-4,tclev,thlev,tdlev)
	return
11962	call nucltransK(0.430,0.091,1.8e-1,0.,tclev,thlev,tdlev)
	go to 76700
c-----------------------------------------------------------------------
1109	call beta(0.258,83.,0.,0.,t)
11090	thlev=0.
	p=100.*rnd1(d)
	if(p.le.13.9) go to 11091   ! 13.9%
	if(p.le.72.8) go to 11092   ! 58.9%
	if(p.le.77.0) go to 11093   !  4.2%
	              go to 11094   ! 23.0%
11091	call nucltransK(1.109,0.091,1.5e-2,0.4e-6,tclev,thlev,tdlev)
	return
11092	call nucltransK(0.705,0.091,5.0e-2,0.,tclev,thlev,tdlev)
	go to 40500
11093	call nucltransK(0.343,0.091,3.2e-1,0.,tclev,thlev,tdlev)
	go to 76700
11094	call nucltransK(0.095,0.016,9.6e+0,0.,tclev,thlev,tdlev)
	go to 10140
c-----------------------------------------------------------------------
1104	call beta(0.263,83.,0.,0.,t)
11040	call nucltransK(1.104,0.091,1.5e-2,0.3e-6,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1081	call beta(0.286,83.,0.,0.,t)
10810	thlev=0.
	p=100.*rnd1(d)
	if(p.le.21.8) go to 10811   ! 21.8%
	if(p.le.44.9) go to 10812   ! 23.1%
	              go to 10813   ! 55.1%
10811	call nucltransK(1.081,0.091,1.6e-2,0.1e-4,tclev,thlev,tdlev)
	return
10812	call nucltransK(0.677,0.091,5.3e-2,0.,tclev,thlev,tdlev)
	go to 40500
10813	call nucltransK(0.314,0.091,4.1e-1,0.,tclev,thlev,tdlev)
	go to 76700
c-----------------------------------------------------------------------
10140	thlev=0.
	p=100.*rnd1(d)
	if(p.le.28.7) go to 10141   ! 28.7%
	              go to 10142   ! 71.3%
10141	call nucltransK(1.014,0.091,1.9e-2,0.,tclev,thlev,tdlev)
	return
10142	call nucltransK(0.609,0.091,7.0e-2,0.,tclev,thlev,tdlev)
	go to 40500
c-----------------------------------------------------------------------
951	call beta(0.416,83.,0.,0.,t)
95100	thlev=0.
	call nucltransK(0.951,0.091,2.2e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
832	call beta(0.535,83.,0.,0.,t)
83200	thlev=0.
	p=100.*rnd1(d)
	if(p.le.57.4) go to 83201   ! 57.4%
	if(p.le.90.3) go to 83202   ! 32.9%
	              go to 83203   !  9.7%
83201	call nucltransK(0.832,0.091,2.9e-2,0.,tclev,thlev,tdlev)
	return
83202	call nucltransK(0.427,0.091,1.9e-1,0.,tclev,thlev,tdlev)
	go to 40500
83203	call nucltransK(0.065,0.016,6.9e+0,0.,tclev,thlev,tdlev)
	go to 76700
c-----------------------------------------------------------------------
76700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.57.4) go to 76701   ! 93.7%
	              go to 76702   !  6.3%
76701	call nucltransK(0.767,0.091,4.0e-2,0.,tclev,thlev,tdlev)
	return
76702	call nucltransK(0.362,0.091,2.8e-1,0.,tclev,thlev,tdlev)
	go to 40500
c-----------------------------------------------------------------------
405	call beta(0.962,83.,0.,0.,t)
40500	thlev=0.317e-9
	call nucltransK(0.405,0.091,1.3e-1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call beta(1.367,83.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Pb212(tcnuc,tdnuc)
c Scheme of Pb212 decay ("Table of Isotopes", 7th ed., 1978).
c Three-figured labels correspond to energies of 212Bi excited
c levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 5.08.1992, 22.10.1995.
	thnuc=38304.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 5.) go to   415         !  5%
	if(pbeta.le.88.) go to   239         ! 83%
	                 go to 10000         ! 12%
c-----------------------------------------------------------------------
415	call beta(0.158,83.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.5) go to 41501          !  0.5%
	if(p.le.98.5) go to 41502          ! 98.0%
	              go to 41503          !  1.5%
41501	call nucltransK(0.415,0.091,0.24,0.,tclev,thlev,tdlev)
	return
41502	call nucltransK(0.300,0.091,0.55,0.,tclev,thlev,tdlev)
	go to 115
41503	call nucltransK(0.177,0.091,2.4,0.,tclev,thlev,tdlev)
	go to 23900
c-----------------------------------------------------------------------
239	call beta(0.334,83.,0.,0.,t)
23900	thlev=1.e-12
	call nucltransK(0.239,0.091,1.1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
115	thlev=8.e-12
	call nucltransK(0.115,0.091,8.0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call beta(0.573,83.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Pb214(tcnuc,tdnuc)
c Scheme of 214Pb decay ("Table of Isotopes", 7th ed., 1978).
c Three-figured labels correspond to energies of 214Bi
c excited levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 11.08.1992, 22.10.1995.
c VIT, 4.01.2007: updated to NDS 76(1995)127, and conversion from K, L, M shells
c is introduced.
	thnuc=1608.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.034) go to   888   !  0.034%
	if(pbeta.le. 2.766) go to   839   !  2.732%
	if(pbeta.le. 2.787) go to   797   !  0.021%
	if(pbeta.le. 3.951) go to   534   !  1.164%
	if(pbeta.le.52.172) go to   352   ! 48.221%
	if(pbeta.le.93.787) go to   295   ! 41.615%
	                    go to 10000   !  6.213%
c-----------------------------------------------------------------------
888	call beta(0.135,83.,0.,0.,t)
	thlev=0.
	call nucltransK(0.511,0.091,6.0e-2,0.,tclev,thlev,tdlev)
	go to 37700
c-----------------------------------------------------------------------
839	call beta(0.184,83.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.21.3) go to 83901   ! 21.3%
	if(p.le.60.1) go to 83902   ! 38.8%
	if(p.le.72.9) go to 83903   ! 12.8%
	if(p.le.75.4) go to 83904   !  2.5%
	if(p.le.90.8) go to 83905   ! 15.4%
	if(p.le.98.8) go to 83906   !  8.0%
	              go to 83907   !  1.2%
83901	call nucltransKLM(0.839,0.091,2.99e-3,0.016,4.7e-4,
     +                    0.004,1.5e-4,0.,tclev,thlev,tdlev)
	return
83902	call nucltransKLM(0.786,0.091,3.38e-3,0.016,5.3e-4,
     +                    0.004,1.7e-4,0.,tclev,thlev,tdlev)
	go to 53000
83903	call nucltransKLM(0.580,0.091,6.06e-3,0.016,9.7e-4,
     +                    0.004,3.2e-4,0.,tclev,thlev,tdlev)
	go to 25900
83904	call nucltransKLM(0.544,0.091,6.90e-3,0.016,1.11e-3,
     +                    0.004,3.7e-4,0.,tclev,thlev,tdlev)
	go to 29500
83905	call nucltransKLM(0.487,0.091,8.65e-3,0.016,1.41e-3,
     +                    0.004,4.4e-4,0.,tclev,thlev,tdlev)
	go to 35200
83906	call nucltransKLM(0.462,0.091,9.64e-3,0.016,1.58e-3,
     +                    0.004,4.8e-4,0.,tclev,thlev,tdlev)
	go to 37700
83907	call nucltransKLM(0.305,0.091,2.40e-2,0.016,4.1e-3,
     +                    0.004,1.3e-3,0.,tclev,thlev,tdlev)
	go to 53400
c-----------------------------------------------------------------------
797	call beta(0.226,83.,0.,0.,t)
	thlev=0.
	call nucltransK(0.538,0.091,8.5e-3,0.,tclev,thlev,tdlev)
	go to 25900
c-----------------------------------------------------------------------
534	call beta(0.489,83.,0.,0.,t)
53400	thlev=0.
	p=100.*rnd1(d)
	if(p.le.16.3) go to 53401   ! 16.3%
	if(p.le.46.0) go to 53402   ! 29.7%
	              go to 53403   ! 54.0%
53401	call nucltransKL(0.534,0.091,5.0e-2,0.016,1.0e-2,
     +                   0.,tclev,thlev,tdlev)
	return
53402	call nucltransKLM(0.480,0.091,1.22e-1,0.016,1.9e-2,
     +                    0.004,6.0e-3,0.,tclev,thlev,tdlev)
	go to 53000
53403	call nucltransKLM(0.275,0.091,2.9e-1,0.016,7.3e-2,
     +                    0.004,2.4e-2,0.,tclev,thlev,tdlev)
	go to 25900
c-----------------------------------------------------------------------
37700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.26.2) go to 37701   ! 26.2%
	              go to 37702   ! 73.8%
37701	call nucltransK(0.324,0.091,2.1e-1,0.,tclev,thlev,tdlev)
	go to 53000
37702	call nucltransK(0.314,0.091,2.3e-1,0.,tclev,thlev,tdlev)
	go to 63000
c-----------------------------------------------------------------------
352	call beta(0.671,83.,0.,0.,t)
35200	thlev=0.
	call nucltransKLM(0.352,0.091,2.55e-1,0.016,4.41e-2,
     +                    0.004,1.38e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
295	call beta(0.728,83.,0.,0.,t)
29500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.67.10) go to 29501   ! 67.1%
	               go to 29502   ! 32.9%
29501	call nucltransKLM(0.295,0.091,3.8e-1,0.016,6.9e-2,
     +                    0.004,2.2e-2,0.,tclev,thlev,tdlev)
	return
29502	call nucltransKLM(0.242,0.091,7.13e-1,0.016,1.23e-1,
     +                    0.004,3.88e-2,0.,tclev,thlev,tdlev)
	go to 53000
c-----------------------------------------------------------------------
25900	thlev=0.
	p=100.*rnd1(d)
	if(p.le.81.4) go to 25901   ! 81.4%
	if(p.le.83.8) go to 25902   !  2.4%
	              go to 25903   ! 16.2%
25901	call nucltransKLM(0.259,0.091,5.92e-1,0.016,1.03e-1,
     +                    0.004,3.2e-2,0.,tclev,thlev,tdlev)
	return
25902	call nucltransKLM(0.206,0.091,1.12e+0,0.016,1.95e-1,
     +                    0.004,6.1e-2,0.,tclev,thlev,tdlev)
	go to 53000
25903	call nucltransKLM(0.196,0.091,1.28e+0,0.016,2.23e-1,
     +                    0.004,7.0e-2,0.,tclev,thlev,tdlev)
	go to 63000
c-----------------------------------------------------------------------
63000	thlev=0.
	call nucltransK(0.063,0.016,1.0e+1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
53000	thlev=0.
	call nucltransKL(0.053,0.016,9.69e+0,0.004,3.05e+0,
     +                   0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call beta(1.023,83.,0.,0.,t)
	return
	end

c***********************************************************************

	subroutine PbAtShell(KLMenergy,tclev,thlev,tdlev)
c Subroutine describes in some approximation the deexcitation process in
c atomic shell of Pb after creation of electron vacation in K, L or M shell.
c Call  : call PbAtShell(KLMenergy,tclev,thlev,tdlev)
c Input : KLMenergy - binding energy of electron on atomic shell [integer
c                     in keV] where the hole was created;
c         tclev     - time of hole creation (sec);
c         thlev     - hole halflife (sec).
c Output: tdlev     - time of decay of hole (sec).
c It is supposed electron binding energy on Pb K-shell = 88 keV, on L-shell =
c 15 keV, on M-shell = 3 keV. So, following values of KLMenergy are allowed:
c 88 (hole in K-shell), 15 (in L-shell) and 3 (in M-shell).
c VIT, 7.07.1995, 22.10.1995.
	Lhole=0
	Mhole=0
	if(KLMenergy.eq.88) go to 88
	if(KLMenergy.eq.15) then
	   Lhole=1
	   go to 15
	endif
	if(KLMenergy.eq.3) then
	   Mhole=1
	   go to 3
	endif
	go to 20000
c-----------------------------------------------------------------------
c K-shell
88	p=100.*rnd1(d)
	if(p.le.22.) go to 88001
	             go to 88002
88001	call gamma(0.085,tclev,thlev,tdlev)          ! X ray K-M
	Mhole=Mhole+1
	go to 3
88002	p=100.*rnd1(d)
	if(p.le.96.) then
	   call gamma(0.073,tclev,thlev,tdlev)       ! X ray K-L
	else
	   call electron(0.058,tclev,thlev,tdlev)    ! Auger electron K-LL
	   Lhole=Lhole+1
	end if
	Lhole=Lhole+1
c-----------------------------------------------------------------------
c L-shell
15	do i=1,Lhole
	   p=100.*rnd1(d)
	   if(p.le.40.) then
	      call gamma(0.012,tclev,thlev,tdlev)    ! X ray L-M
	   else
	      call electron(0.009,tclev,thlev,tdlev) ! Auger electron L-MM
	      Mhole=Mhole+1
	   end if
	   Mhole=Mhole+1
	enddo
c-----------------------------------------------------------------------
c M-shell
3	do i=1,Mhole
	   call gamma(0.003,tclev,thlev,tdlev)       ! X ray M-inf
	enddo
	return
c-----------------------------------------------------------------------
20000	print *,'Pb_At_Shell: wrong hole level [keV] ',KLMenergy
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Po212(tcnuc,tdnuc)
c Scheme of Po212 decay (Nucl. Data Sheets 66(1992)171).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 14.07.1995, 22.10.1995.
	thnuc=0.299e-6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	call alpha(8.785,0.,0.,t)
	return
	end

c***********************************************************************

	subroutine Po214(tcnuc,tdnuc)
c Scheme of Po214 decay (Nucl. Data Sheets 55(1988)665).
c Alpha decay to excited level 1097.7 keV of Pb210 is neglected (6e-5%).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 14.07.1995, 22.10.1995.
c VIT, 11.05.2005, updated to NDS 99(2003)649.
	thnuc=164.3e-6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	palpha=100.*rnd1(d)
	if(palpha.le.0.0104) go to   800 !  0.0104%
	                     go to 10000 ! 99.9896%
c-----------------------------------------------------------------------
800	call alpha(6.902,0.,0.,t)
	call nucltransK(0.800,0.088,1.1e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call alpha(7.687,0.,0.,t)
	return
	end

c***********************************************************************

	subroutine Ra222(tcnuc,tdnuc)
c Model for scheme of Ra222 decay (NDS 107(2006)1027 and ENSDF at NNDC site 
c on 9.12.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 9.12.2007.
	thnuc=36.17
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	palpha=100.*rnd1(d)
	if(palpha.le.0.0042) go to   840
	if(palpha.le.0.0083) go to   797
	if(palpha.le.0.0124) go to   653
	if(palpha.le.3.0635) go to   324
	                     go to 10000
c-----------------------------------------------------------------------
840	call alpha(5.734,0.,0.,t)
84000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.66.35) go to 84001         
	               go to 84002  
84001	call nucltransK(0.840,0.098,2.9e-2,0.,tclev,thlev,tdlev)
	return
84002	call nucltransK(0.516,0.098,2.5e-2,0.,tclev,thlev,tdlev)
	go to 32400
c-----------------------------------------------------------------------
797	call alpha(5.776,0.,0.,t)
79700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.96.75) go to 79701         
	               go to 79702  
79701	call nucltransK(0.473,0.098,1.0e-2,0.,tclev,thlev,tdlev)
	go to 32400
79702	call nucltransK(0.144,0.098,1.9e-1,0.,tclev,thlev,tdlev)
	go to 65300
c-----------------------------------------------------------------------
653	call alpha(5.917,0.,0.,t)
65300	thlev=0.
	call nucltransK(0.329,0.098,1.1e-1,0.,tclev,thlev,tdlev)
	go to 32400
c-----------------------------------------------------------------------
324	call alpha(6.240,0.,0.,t)
32400	thlev=0.
	call nucltransK(0.324,0.098,1.1e-1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call alpha(6.559,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end
c***********************************************************************

	subroutine Ra228(tcnuc,tdnuc)
c Scheme of Ra228 decay in accordance with NDS 80(1997)723 and
C ENSDF database at NNDC site on 8.08.2007.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 8.08.2007.
	thnuc=1.814512e8
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.30.) go to 331         ! 30%
	if(pbeta.le.50.) go to 202         ! 20%
	if(pbeta.le.90.) go to  67         ! 40%
	                 go to  63         ! 10%
c-----------------------------------------------------------------------
331	call beta(0.0128,89.,0.,0.,t)
33100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.50.) go to 33101          !  50%
	             go to 33102          !  50%
33101	call nucltransK(0.0264,0.0198,2.1e2,0.,tclev,thlev,tdlev)
	go to 67000
33102	call nucltransK(0.0128,0.0050,8.7e0,0.,tclev,thlev,tdlev)
	go to 20200
c-----------------------------------------------------------------------
202	call beta(0.0257,89.,0.,0.,t)
20200	thlev=0.
	call nucltransK(0.0135,0.0050,6.1e0,0.,tclev,thlev,tdlev)
	go to 67000
c-----------------------------------------------------------------------
67	call beta(0.0392,89.,0.,0.,t)
67000	thlev=0.
	call nucltransK(0.0067,0.0050,1.6e6,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
63	call beta(0.0396,89.,0.,0.,t)
63000	thlev=0.
	call nucltransK(0.0063,0.0050,7.1e6,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Rb87(tcnuc,tdnuc)
c Scheme of Rb87 decay in accordance with NDS 95(2002)543 and ENSDF
c at NNDC site on 6.08.2007.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 6.08.2007.
	thnuc=1.518e18
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
c Shape of the 3-rd forbidden non-unique beta decay in accordance with
c measurements of: A.G.Carles et al., NPA 767(2006)248.
	call beta2(0.283,38.,0.,0.,t,2,27.72,90.91,0.,0.)
	return
	end

c***********************************************************************

	subroutine Rh106(tcnuc,tdnuc)
c Approximate scheme of 106Rh decay ("Table of Isotopes", 7th ed., 1978)
c (beta decays to excited levels of 106Pd not higher 2.002 MeV,
c 99.32% of decay).
c Three-figured labels correspond to energies of 106Pd excited levels
c in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 17.12.1995.
	thnuc=29.80
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.45) go to  2002
	if(pbeta.le. 0.52) go to  1707
	if(pbeta.le. 2.32) go to  1562
	if(pbeta.le.12.32) go to  1134
	if(pbeta.le.19.32) go to   512
	                   go to 10000
c-----------------------------------------------------------------------
2002	call beta(1.539,46.,0.,0.,t)
20020	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.4) go to 20021
	if(p.le.98.6) go to 20022
	              go to 20023
20021	call nucltransK(1.490,0.024,4.0e-4,0.3e-4,tclev,thlev,tdlev)
	go to 51200
20022	call nucltransK(0.874,0.024,1.3e-3,0.,tclev,thlev,tdlev)
	go to 11280
20023	call nucltransK(0.440,0.024,8.5e-3,0.,tclev,thlev,tdlev)
	go to 15620
c-----------------------------------------------------------------------
1707	call beta(1.834,46.,0.,0.,t)
17070	thlev=0.
	p=100.*rnd1(d)
	if(p.le.89.0) go to 17071
	              go to 17072
17071	call nucltransK(1.195,0.024,7.5e-4,0.,tclev,thlev,tdlev)
	go to 51200
17072	call nucltransK(0.578,0.024,3.7e-3,0.,tclev,thlev,tdlev)
	go to 11280
c-----------------------------------------------------------------------
1562	call beta(1.979,46.,0.,0.,t)
15620	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 9.1) go to 15621
	if(p.le.95.6) go to 15622
	if(p.le.96.8) go to 15623
	              go to 15624
15621	call nucltransK(1.562,0.024,3.5e-4,0.4e-4,tclev,thlev,tdlev)
	return
15622	call nucltransK(1.051,0.024,8.5e-4,0.,tclev,thlev,tdlev)
	go to 51200
15623	call nucltransK(0.434,0.024,8.5e-3,0.,tclev,thlev,tdlev)
	go to 11280
15624	call nucltransK(0.428,0.024,8.5e-3,0.,tclev,thlev,tdlev)
	go to 11340
c-----------------------------------------------------------------------
1134	call beta(2.407,46.,0.,0.,t)
11340	thlev=7.0e-12
	call nucltransK(0.622,0.024,3.3e-3,0.,tclev,thlev,tdlev)
	go to 51200
c-----------------------------------------------------------------------
11280	thlev=3.2e-12
	p=100.*rnd1(d)
	if(p.le.34.) go to 11281
	             go to 11282
11281	call nucltransK(1.128,0.024,7.0e-4,0.,tclev,thlev,tdlev)
	return
11282	call nucltransK(0.616,0.024,3.0e-3,0.,tclev,thlev,tdlev)
	go to 51200
c-----------------------------------------------------------------------
512	call beta(3.029,46.,0.,0.,t)
51200	thlev=11.0e-12
	call nucltransK(0.512,0.024,5.5e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call beta(3.541,46.,0.,0.,t)
	return
	end

c***********************************************************************

	subroutine Rn218(tcnuc,tdnuc)
c Model for scheme of Rn218 decay (NDS 76(1995)127 and ENSDF at NNDC site 
c on 9.12.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 9.12.2007.
	thnuc=35.e-3
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	palpha=100.*rnd1(d)
	if(palpha.le.0.127) go to   609
	                    go to 10000
c-----------------------------------------------------------------------
609	call alpha(6.532,0.,0.,t)
	thlev=0.
	call nucltransK(0.609,0.093,2.1e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call alpha(7.130,0.,0.,t)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

        subroutine Sb125(tcnuc,tdnuc)
c Scheme of 125Sb decay (NDS 86(1999)955 + NNDC on 7.02.2010).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.02.2010.
	thnuc=8.705115e7
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.13.446) go to 671
	if(pbeta.le.13.502) go to 653
	if(pbeta.le.19.265) go to 642
	if(pbeta.le.37.180) go to 636
	if(pbeta.le.38.791) go to 525
	if(pbeta.le.79.199) go to 463
	if(pbeta.le.79.247) go to 444
	if(pbeta.le.79.268) go to 402
	if(pbeta.le.86.464) go to 321
	                    go to 145
c-----------------------------------------------------------------------
671	call beta(0.096,52.,0.,0.,t)
6710	thlev=1.26e-12
	p=100.*rnd1(d)
	if(p.le.13.347) go to 6711
	if(p.le.96.921) go to 6712
	if(p.le.97.980) go to 6713
	if(p.le.99.993) go to 6714
	                go to 6715
6711	call nucltransK(0.671,0.032,3.8e-3,0.,tclev,thlev,tdlev)
	return
6712	call nucltransK(0.636,0.032,5.3e-3,0.,tclev,thlev,tdlev)
	go to 3500
6713	call nucltransK(0.228,0.032,8.4e-2,0.,tclev,thlev,tdlev)
	go to 4440
6714	call nucltransK(0.208,0.032,9.1e-2,0.,tclev,thlev,tdlev)
	go to 4630
6715	call nucltransK(0.133,0.032,3.1e-1,0.,tclev,thlev,tdlev)
	go to 5390
c-----------------------------------------------------------------------
653	call beta(0.114,52.,0.,0.,t)
6530	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.85) go to 6531
	if(p.le.14.56) go to 6532
	if(p.le.19.11) go to 6533
	               go to 6534
6531	call nucltransK(0.653,0.032,4.0e-3,0.,tclev,thlev,tdlev)
	return
6532	call nucltransK(0.617,0.032,5.6e-3,0.,tclev,thlev,tdlev)
	go to 3500
6533	call nucltransK(0.332,0.032,2.8e-2,0.,tclev,thlev,tdlev)
	go to 3210
6534	call nucltransK(0.209,0.032,8.9e-2,0.,tclev,thlev,tdlev)
	go to 4440
c-----------------------------------------------------------------------
642	call beta(0.125,52.,0.,0.,t)
6420	thlev=70e-12
	p=100.*rnd1(d)
	if(p.le.86.63) go to 6421
	if(p.le.86.70) go to 6422
	if(p.le.93.91) go to 6423
	if(p.le.94.17) go to 6424
	if(p.le.94.86) go to 6425
	               go to 6426
6421	call nucltransK(0.607,0.032,4.9e-3,0.,tclev,thlev,tdlev)
	go to 3500
6422	call nucltransK(0.497,0.032,3.2e-2,0.,tclev,thlev,tdlev)
	go to 1450
6423	call nucltransK(0.321,0.032,7.9e-3,0.,tclev,thlev,tdlev)
	go to 3210
6424	call nucltransK(0.199,0.032,1.5e-1,0.,tclev,thlev,tdlev)
	go to 4440
6425	call nucltransK(0.179,0.032,1.8e-1,0.,tclev,thlev,tdlev)
	go to 4630
6426	call nucltransK(0.117,0.032,1.3e-1,0.,tclev,thlev,tdlev)
	go to 5250
c-----------------------------------------------------------------------
636	call beta(0.131,52.,0.,0.,t)
6360	thlev=40e-12
	p=100.*rnd1(d)
	if(p.le.98.716) go to 6361
	if(p.le.98.743) go to 6362
	if(p.le.98.766) go to 6363
	if(p.le.99.994) go to 6364
	                go to 6365
6361	call nucltransK(0.601,0.032,5.0e-3,0.,tclev,thlev,tdlev)
	go to 3500
6362	call nucltransK(0.491,0.032,3.2e-2,0.,tclev,thlev,tdlev)
	go to 1450
6363	call nucltransK(0.315,0.032,8.3e-3,0.,tclev,thlev,tdlev)
	go to 3210
6364	call nucltransK(0.173,0.032,1.5e-1,0.,tclev,thlev,tdlev)
	go to 4630
6365	call nucltransK(0.111,0.032,1.5e-1,0.,tclev,thlev,tdlev)
	go to 5250
c-----------------------------------------------------------------------
5390	thlev=0.
	p=100.*rnd1(d)
	if(p.le.26.42) go to 5391
	               go to 5392
5391	call nucltransK(0.539,0.032,7.8e-3,0.,tclev,thlev,tdlev)
	return
5392	call nucltransK(0.503,0.032,9.3e-3,0.,tclev,thlev,tdlev)
	go to 3500
c-----------------------------------------------------------------------
525	call beta(0.242,52.,0.,0.,t)
5250	thlev=160e-12
	p=100.*rnd1(d)
	if(p.le. 0.07) go to 5251
	if(p.le.81.12) go to 5252
	if(p.le.99.89) go to 5253
	               go to 5254
5251	call nucltransK(0.490,0.032,3.3e-2,0.,tclev,thlev,tdlev)
	go to 3500
5252	call nucltransK(0.380,0.032,1.8e-2,0.,tclev,thlev,tdlev)
	go to 1450
5253	call nucltransK(0.204,0.032,1.3e-1,0.,tclev,thlev,tdlev)
	go to 3210
5254	call nucltransK(0.062,0.032,7.4e-1,0.,tclev,thlev,tdlev)
	go to 4630
c-----------------------------------------------------------------------
463	call beta(0.304,52.,0.,0.,t)
4630	thlev=13.2e-12
	p=100.*rnd1(d)
	if(p.le.26.08) go to 4631
	if(p.le.99.39) go to 4632
	               go to 4633
4631	call nucltransK(0.463,0.032,1.0e-2,0.,tclev,thlev,tdlev)
	return
4632	call nucltransK(0.428,0.032,1.4e-2,0.,tclev,thlev,tdlev)
	go to 3500
4633	call nucltransK(0.020,0.005,11.1,0.,tclev,thlev,tdlev)
	go to 4440
c-----------------------------------------------------------------------
444	call beta(0.323,52.,0.,0.,t)
4440	thlev=19.1e-12
	p=100.*rnd1(d)
	if(p.le.62.40) go to 4441
	               go to 4442
4441	call nucltransK(0.444,0.032,1.2e-2,0.,tclev,thlev,tdlev)
	return
4442	call nucltransK(0.408,0.032,1.5e-2,0.,tclev,thlev,tdlev)
	go to 3500
c-----------------------------------------------------------------------
402	call beta(0.365,52.,0.,0.,t)
4020	thlev=0.
	p=100.*rnd1(d)
	if(p.le.29.72) go to 4021
	if(p.le.67.45) go to 4022
	               go to 4023
4021	call nucltransK(0.402,0.032,1.9e-1,0.,tclev,thlev,tdlev)
	return
4022	call nucltransK(0.367,0.032,2.0e-2,0.,tclev,thlev,tdlev)
	go to 3500
4023	call nucltransK(0.081,0.032,3.6e-1,0.,tclev,thlev,tdlev)
	go to 3210
c-----------------------------------------------------------------------
321	call beta(0.446,52.,0.,0.,t)
3210	thlev=0.673e-9
	call nucltransK(0.176,0.032,1.7e-1,0.,tclev,thlev,tdlev)
	go to 1450
c-----------------------------------------------------------------------
145	call beta(0.622,52.,0.,0.,t)
1450	thlev=4.959e6
	call nucltransK(0.109,0.032,355.,0.,tclev,thlev,tdlev)
	go to 3500
c-----------------------------------------------------------------------
3500	thlev=1.48e-9
	call nucltransK(0.035,0.032,14.,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

        subroutine Sb126(tcnuc,tdnuc)
c Scheme of 126Sb decay (J.Katakura et al., NDS 97(2002)765).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 27.11.2003. Corrected 2.12.2003, thanks F.Capella.
	thnuc=1.0670e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.48) go to 3473
	if(pbeta.le. 2.48) go to 3450
	if(pbeta.le.30.28) go to 3194
	if(pbeta.le.35.94) go to 3171
	if(pbeta.le.43.99) go to 3071
	if(pbeta.le.48.02) go to 2989
	if(pbeta.le.48.50) go to 2974
	if(pbeta.le.49.27) go to 2840
	if(pbeta.le.57.04) go to 2812
	if(pbeta.le.61.74) go to 2766
	if(pbeta.le.77.08) go to 2497
	if(pbeta.le.77.94) go to 2396
	if(pbeta.le.80.82) go to 2218
	                   go to 1776
c-----------------------------------------------------------------------
3473	call beta(0.200,52.,0.,0.,t)
34730	thlev=0.
	call nucltransK(0.958,0.032,1.5e-3,0.,tclev,thlev,tdlev)
	go to 25150
c-----------------------------------------------------------------------
3450	call beta(0.223,52.,0.,0.,t)
34500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.57.14) go to 34501
	               go to 34502
34501	call nucltransK(0.954,0.032,1.5e-3,0.,tclev,thlev,tdlev)
	go to 24970
34502	call nucltransK(0.639,0.032,3.6e-3,0.,tclev,thlev,tdlev)
	go to 28120
c-----------------------------------------------------------------------
3194	call beta(0.479,52.,0.,0.,t)
31940	thlev=0.
	call nucltransK(0.697,0.032,3.0e-3,0.,tclev,thlev,tdlev)
	go to 24970
c-----------------------------------------------------------------------
3171	call beta(0.502,52.,0.,0.,t)
31710	thlev=0.
	p=100.*rnd1(d)
	if(p.le.62.82) go to 31711
	               go to 31712
31711	call nucltransK(0.675,0.032,3.2e-3,0.,tclev,thlev,tdlev)
	go to 24970
31712	call nucltransK(0.656,0.032,3.4e-3,0.,tclev,thlev,tdlev)
	go to 25150
c-----------------------------------------------------------------------
3071	call beta(0.602,52.,0.,0.,t)
30710	thlev=0.
	p=100.*rnd1(d)
	if(p.le.79.86) go to 30711
	               go to 30712
30711	call nucltransK(0.574,0.032,5.0e-3,0.,tclev,thlev,tdlev)
	go to 24970
30712	call nucltransK(0.556,0.032,5.0e-3,0.,tclev,thlev,tdlev)
	go to 25150
c-----------------------------------------------------------------------
2989	call beta(0.684,52.,0.,0.,t)
29890	thlev=0.
	p=100.*rnd1(d)
	if(p.le.57.18) go to 29891
	if(p.le.90.43) go to 29892
	               go to 29893
29891	call nucltransK(1.213,0.032,1.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 17760
29892	call nucltransK(0.224,0.032,9.0e-2,0.,tclev,thlev,tdlev)
	go to 27660
29893	call nucltransK(0.149,0.032,4.0e-1,0.,tclev,thlev,tdlev)
	go to 28400
c-----------------------------------------------------------------------
2974	call beta(0.699,52.,0.,0.,t)
29740	thlev=0.
	call nucltransK(0.209,0.032,1.3e-1,0.,tclev,thlev,tdlev)
	go to 27660
c-----------------------------------------------------------------------
2840	call beta(0.833,52.,0.,0.,t)
28400	thlev=0.
	p=100.*rnd1(d)
	if(p.le.23.73) go to 28401
	               go to 28402
28401	call nucltransK(1.477,0.032,4.0e-4,0.3e-4,tclev,thlev,tdlev)
	go to 13620
28402	call nucltransK(1.064,0.032,1.2e-3,0.,tclev,thlev,tdlev)
	go to 17760
c-----------------------------------------------------------------------
2812	call beta(0.861,52.,0.,0.,t)
28120	thlev=0.
	p=100.*rnd1(d)
	if(p.le.83.33) go to 28121
	if(p.le.94.44) go to 28122
	               go to 28123
28121	call nucltransK(0.593,0.032,5.0e-3,0.,tclev,thlev,tdlev)
	go to 22180
28122	call nucltransK(0.415,0.032,1.2e-2,0.,tclev,thlev,tdlev)
	go to 23960
28123	call nucltransK(0.297,0.032,3.0e-2,0.,tclev,thlev,tdlev)
	go to 25150
c-----------------------------------------------------------------------
2766	call beta(0.907,52.,0.,0.,t)
27660	thlev=0.
	call nucltransK(0.990,0.032,1.5e-3,0.,tclev,thlev,tdlev)
	go to 17760
c-----------------------------------------------------------------------
25150	thlev=0.
	call nucltransK(0.297,0.032,4.0e-2,0.,tclev,thlev,tdlev)
	go to 22180
c-----------------------------------------------------------------------
2497	call beta(1.176,52.,0.,0.,t)
24970	thlev=0.152e-9
	p=100.*rnd1(d)
	if(p.le.95.56) go to 24971
	               go to 24972
24971	call nucltransK(0.721,0.032,1.0e-2,0.,tclev,thlev,tdlev)
	go to 17760
24972	call nucltransK(0.278,0.032,4.9e-2,0.,tclev,thlev,tdlev)
	go to 22180
c-----------------------------------------------------------------------
2396	call beta(1.277,52.,0.,0.,t)
23960	thlev=0.
	p=100.*rnd1(d)
	if(p.le.52.63) go to 23961
	               go to 23962
23961	call nucltransK(1.036,0.032,1.3e-3,0.,tclev,thlev,tdlev)
	go to 13620
23962	call nucltransK(0.620,0.032,5.0e-3,0.,tclev,thlev,tdlev)
	go to 17760
c-----------------------------------------------------------------------
2218	call beta(1.455,52.,0.,0.,t)
22180	thlev=0.
	call nucltransK(0.857,0.032,8.4e-4,0.,tclev,thlev,tdlev)
	go to 13620
c-----------------------------------------------------------------------
1776	call beta(1.897,52.,0.,0.,t)
17760	thlev=68.e-12
	call nucltransK(0.415,0.032,1.4e-2,0.,tclev,thlev,tdlev)
	go to 13620
c-----------------------------------------------------------------------
13620	thlev=0.
	call nucltransK(0.695,0.032,3.4e-3,0.,tclev,thlev,tdlev)
	go to 66700
c-----------------------------------------------------------------------
66700	thlev=0.
	call nucltransK(0.667,0.032,3.8e-3,0.,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

        subroutine Sb133(tcnuc,tdnuc)
c Scheme of 133Sb decay (S.Rab, NDS 75(1995)491).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 11.12.2003. 
	thnuc=150
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.27.84) go to 2756
	if(pbeta.le.53.70) go to 2750
	if(pbeta.le.58.28) go to 2211
	if(pbeta.le.58.58) go to 2024
	if(pbeta.le.59.58) go to 1976
	if(pbeta.le.68.54) go to 1913
	if(pbeta.le.75.31) go to 1729
	if(pbeta.le.76.31) go to 1706
	if(pbeta.le.80.19) go to 1642
	if(pbeta.le.83.97) go to 1640
	if(pbeta.le.88.15) go to 1552
	if(pbeta.le.88.95) go to 1501
	if(pbeta.le.91.14) go to 1421
	if(pbeta.le.94.03) go to 1265
	                   go to 1096
c-----------------------------------------------------------------------
2756	call beta(1.247,52.,0.,0.,t)
27560	thlev=0.
	p=100.*rnd1(d)
	if(p.le.45.15) go to 27561
	if(p.le.49.81) go to 27562
	if(p.le.57.90) go to 27563
	if(p.le.67.22) go to 27564
	if(p.le.87.10) go to 27565
	               go to 27566
27561	call nucltransK(2.755,0.032,1.5e-4,5.7e-4,tclev,thlev,tdlev)
	return
27562	call nucltransK(2.447,0.032,1.5e-4,5.2e-4,tclev,thlev,tdlev)
	go to 30800
27563	call nucltransK(1.659,0.032,4.0e-4,1.3e-4,tclev,thlev,tdlev)
	go to 10960
27564	call nucltransK(1.490,0.032,5.0e-4,0.9e-4,tclev,thlev,tdlev)
	go to 12650
27565	call nucltransK(1.026,0.032,1.5e-3,0.,tclev,thlev,tdlev)
	go to 17290
27566	call nucltransK(0.423,0.032,1.2e-2,0.,tclev,thlev,tdlev)
	go to 23320
c-----------------------------------------------------------------------
2750	call beta(1.253,52.,0.,0.,t)
27500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.32.79) go to 27501
	if(p.le.39.00) go to 27502
	if(p.le.42.36) go to 27503
	if(p.le.49.24) go to 27504
	if(p.le.92.58) go to 27505
	               go to 27506
27501	call nucltransK(2.416,0.032,8.0e-5,5.0e-4,tclev,thlev,tdlev)
	go to 33400
27502	call nucltransK(1.654,0.032,4.0e-4,1.3e-4,tclev,thlev,tdlev)
	go to 10960
27503	call nucltransK(1.250,0.032,1.0e-3,0.4e-4,tclev,thlev,tdlev)
	go to 15010
27504	call nucltransK(1.111,0.032,1.5e-3,0.1e-4,tclev,thlev,tdlev)
	go to 16400
27505	call nucltransK(0.837,0.032,8.0e-4,0.,tclev,thlev,tdlev)
	go to 19130
27506	call nucltransK(0.539,0.032,7.0e-3,0.,tclev,thlev,tdlev)
	go to 22110
c-----------------------------------------------------------------------
23320	thlev=0.
	p=100.*rnd1(d)
	if(p.le.65.82) go to 23321
	               go to 23322
23321	call nucltransK(1.236,0.032,1.0e-3,0.4e-4,tclev,thlev,tdlev)
	go to 10960
23322	call nucltransK(0.308,0.032,2.5e-2,0.,tclev,thlev,tdlev)
	go to 20240
c-----------------------------------------------------------------------
2211	call beta(1.792,52.,0.,0.,t)
22110	thlev=0.
	p=100.*rnd1(d)
	if(p.le.23.75) go to 22111
	if(p.le.97.38) go to 22112
	               go to 22113
22111	call nucltransK(1.877,0.032,3.5e-4,1.9e-4,tclev,thlev,tdlev)
	go to 33400
22112	call nucltransK(1.115,0.032,1.5e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10960
22113	call nucltransK(0.572,0.032,5.5e-3,0.,tclev,thlev,tdlev)
	go to 16400
c-----------------------------------------------------------------------
2024	call beta(1.979,52.,0.,0.,t)
20240	thlev=0.
	p=100.*rnd1(d)
	if(p.le.81.61) go to 20241
	               go to 20242
20241	call nucltransK(0.928,0.032,1.8e-3,0.,tclev,thlev,tdlev)
	go to 10960
20242	call nucltransK(0.523,0.032,7.0e-3,0.,tclev,thlev,tdlev)
	go to 15010
c-----------------------------------------------------------------------
1976	call beta(2.027,52.,0.,0.,t)
19760	thlev=0.
	call nucltransK(1.976,0.032,3.0e-4,3.2e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1913	call beta(2.090,52.,0.,0.,t)
19130	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 7.81) go to 19131
	if(p.le.98.08) go to 19132
	               go to 19133
19131	call nucltransK(1.579,0.032,4.5e-4,0.4e-4,tclev,thlev,tdlev)
	go to 33400
19132	call nucltransK(0.818,0.032,8.0e-4,0.,tclev,thlev,tdlev)
	go to 10960
19133	call nucltransK(0.413,0.032,1.2e-2,0.,tclev,thlev,tdlev)
	go to 15010
c-----------------------------------------------------------------------
1729	call beta(2.274,52.,0.,0.,t)
17290	thlev=0.
	p=100.*rnd1(d)
	if(p.le.68.47) go to 17291
	               go to 17292
17291	call nucltransK(1.729,0.032,4.5e-4,1.5e-4,tclev,thlev,tdlev)
	return
17292	call nucltransK(0.632,0.032,4.5e-3,0.,tclev,thlev,tdlev)
	go to 10960
c-----------------------------------------------------------------------
1706	call beta(2.297,52.,0.,0.,t)
17060	thlev=0.
	call nucltransK(1.706,0.032,4.5e-4,1.5e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1642	call beta(2.361,52.,0.,0.,t)
16420	thlev=0.
	call nucltransK(1.642,0.032,5.0e-4,1.2e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1640	call beta(2.363,52.,0.,0.,t)
16400	thlev=0.
	call nucltransK(1.305,0.032,9.0e-4,0.5e-4,tclev,thlev,tdlev)
	go to 33400
c-----------------------------------------------------------------------
1552	call beta(2.451,52.,0.,0.,t)
15520	thlev=0.
	call nucltransK(1.552,0.032,5.0e-4,1.0e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1501	call beta(2.502,52.,0.,0.,t)
15010	thlev=0.
	call nucltransK(0.404,0.032,1.3e-2,0.,tclev,thlev,tdlev)
	go to 10960
c-----------------------------------------------------------------------
1421	call beta(2.582,52.,0.,0.,t)
14210	thlev=0.
	p=100.*rnd1(d)
	if(p.le.13.44) go to 14211
	               go to 14212
14211	call nucltransK(1.421,0.032,6.5e-4,0.7e-4,tclev,thlev,tdlev)
	return
14212	call nucltransK(1.113,0.032,1.3e-3,0.,tclev,thlev,tdlev)
	go to 30800
c-----------------------------------------------------------------------
1265	call beta(2.738,52.,0.,0.,t)
12650	thlev=0.
	call nucltransK(1.265,0.032,9.0e-4,0.5e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1096	call beta(2.907,52.,0.,0.,t)
10960	thlev=0.
	call nucltransK(1.096,0.032,1.1e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
33400	return ! creation of isomeric 133mTe with E_exc=334 keV and T1/2=55.4 m
c-----------------------------------------------------------------------
30800	thlev=0.
	call nucltransK(0.308,0.032,2.5e-2,0.,tclev,thlev,tdlev)
	return ! creation of 133Te in g.s. (T1/2=12.5 m)
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Sc48(tcnuc,tdnuc)
c Scheme of Sc48 decay ("Table of Isotopes", 8 ed., 1996 + NDS 68(1993)1).
c Three-figured labels correspond to energies of 48Ti excited
c levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 7.05.1998; 13.08.2007 update to NDS 107(2006)1747.
	thnuc=1.57212e5
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.10.02) go to 3509
	                   go to 3333
c-----------------------------------------------------------------------
3509	call beta(0.483,22.,0.,0.,t)
35090	thlev=1.4e-12
	p=100.*rnd1(d)
	if(p.le.24.14) go to 35091
	               go to 35092
35091	call nucltransK(1.213,0.005,8.8e-5,0.1e-4,tclev,thlev,tdlev)
	go to 22960
35092	call nucltransK(0.175,0.005,4.5e-3,0.,tclev,thlev,tdlev)
	go to 33330
c-----------------------------------------------------------------------
3333	call beta(0.659,22.,0.,0.,t)
33330	thlev=221.e-15
	call nucltransK(1.038,0.005,1.1e-4,0.,tclev,thlev,tdlev)
	go to 22960
c-----------------------------------------------------------------------
22960	thlev=0.762e-12
	call nucltransK(1.312,0.005,9.7e-5,0.1e-4,tclev,thlev,tdlev)
	go to 98400
c-----------------------------------------------------------------------
98400	thlev=4.04e-12
	call nucltransK(0.984,0.005,1.3e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Sr90(tcnuc,tdnuc)
c Scheme of Sr90 decay ("Table of Isotopes", 7th ed., 1978).
c Accuracy in description of: decay branches       - 0.001%,
c                           : deexcitation process - 0.001%.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c Slight update to NDS 82(1997)379.
c VIT, 9.08.1993, 22.10.1995, 26.10.2006.
	thnuc=0.9085184E+09
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
c	call beta(0.546,39.,0.,0.,t)
c Change from the allowed shape to the 1st forbidden unique with empirical
c correction from: H.H.Hansen, Appl. Rad. Isot. 34(1983)1241
	call beta_1fu(0.546,39.,0.,0.,t,0.,-0.032,0.,0.)
	return
	end

c***********************************************************************

	subroutine Ta182(tcnuc,tdnuc)
c Scheme of 182Ta decay ("Table of Isotopes", 7th ed., 1978).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 6.03.1996.
	thnuc=9.936e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.28.586) go to 1553
	if(pbeta.le.28.716) go to 1510
	if(pbeta.le.31.416) go to 1488
	if(pbeta.le.32.076) go to 1443
	if(pbeta.le.52.066) go to 1374
	if(pbeta.le.54.366) go to 1331
	if(pbeta.le.94.346) go to 1289
	if(pbeta.le.94.846) go to 1257
	if(pbeta.le.99.846) go to 1221
	if(pbeta.le.99.942) go to  329
	                    go to  100
c-----------------------------------------------------------------------
1553	call beta(0.258,74.,0.,0.,t)
15530	thlev=1.23e-9
	p=100.*rnd1(d)
	if(p.le. 0.25) go to 15531
	if(p.le. 1.45) go to 15532
	if(p.le.22.47) go to 15533
	if(p.le.65.50) go to 15534
	if(p.le.83.50) go to 15535
	if(p.le.84.00) go to 15536
	               go to 15537
15531	call nucltransK(1.453,0.070,4.5e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
15532	call nucltransK(1.223,0.070,2.5e-3,0.1e-4,tclev,thlev,tdlev)
	go to 32900
15533	call nucltransK(0.264,0.070,1.4e-1,0.,tclev,thlev,tdlev)
	go to 12890
15534	call nucltransK(0.222,0.070,5.0e-2,0.,tclev,thlev,tdlev)
	go to 13310
15535	call nucltransK(0.179,0.070,7.5e-1,0.,tclev,thlev,tdlev)
	go to 13740
15536	call nucltransK(0.110,0.070,3.0e-1,0.,tclev,thlev,tdlev)
	go to 14430
15537	call nucltransK(0.066,0.012,3.0e-0,0.,tclev,thlev,tdlev)
	go to 14880
c-----------------------------------------------------------------------
1510	call beta(0.301,74.,0.,0.,t)
15100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.34.) go to 15101
	             go to 15102
15101	call nucltransK(1.410,0.070,2.4e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
15102	call nucltransK(1.181,0.070,1.4e-3,0.1e-4,tclev,thlev,tdlev)
	go to 32900
c-----------------------------------------------------------------------
1488	call beta(0.323,74.,0.,0.,t)
14880	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.1) go to 14881
	if(p.le. 6.1) go to 14882
	if(p.le.29.3) go to 14883
	if(p.le.70.8) go to 14884
	              go to 14885
14881	call nucltransK(1.387,0.070,5.0e-3,0.5e-5,tclev,thlev,tdlev)
	go to 10000
14882	call nucltransK(1.158,0.070,1.5e-3,0.5e-5,tclev,thlev,tdlev)
	go to 32900
14883	call nucltransK(0.198,0.070,3.2e-1,0.,tclev,thlev,tdlev)
	go to 12890
14884	call nucltransK(0.156,0.070,1.2e-1,0.,tclev,thlev,tdlev)
	go to 13310
14885	call nucltransK(0.114,0.070,3.8e-0,0.,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
1443	call beta(0.368,74.,0.,0.,t)
14430	thlev=0.
	p=100.*rnd1(d)
	if(p.le.40.) go to 14431
	             go to 14432
14431	call nucltransK(1.343,0.070,2.8e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
14432	call nucltransK(1.113,0.070,6.0e-3,0.,tclev,thlev,tdlev)
	go to 32900
c-----------------------------------------------------------------------
1374	call beta(0.437,74.,0.,0.,t)
13740	thlev=0.08e-9
	p=100.*rnd1(d)
	if(p.le. 2.0) go to 13741
	if(p.le. 7.7) go to 13742
	if(p.le. 9.8) go to 13743
	if(p.le.71.3) go to 13744
	if(p.le.75.1) go to 13745
	if(p.le.97.9) go to 13746
	              go to 13747
13741	call nucltransK(1.374,0.070,5.5e-3,0.5e-5,tclev,thlev,tdlev)
	return
13742	call nucltransK(1.274,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
13743	call nucltransK(1.044,0.070,6.6e-3,0.,tclev,thlev,tdlev)
	go to 32900
13744	call nucltransK(0.152,0.070,1.2e-1,0.,tclev,thlev,tdlev)
	go to 12210
13745	call nucltransK(0.116,0.070,2.6e-1,0.,tclev,thlev,tdlev)
	go to 12570
13746	call nucltransK(0.085,0.070,8.5e-0,0.,tclev,thlev,tdlev)
	go to 12890
13747	call nucltransK(0.043,0.012,7.0e-1,0.,tclev,thlev,tdlev)
	go to 13310
c-----------------------------------------------------------------------
1331	call beta(0.480,74.,0.,0.,t)
13310	thlev=0.
	p=100.*rnd1(d)
	if(p.le.85.) go to 13311
	             go to 13312
13311	call nucltransK(1.231,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
13312	call nucltransK(1.002,0.070,4.7e-3,0.,tclev,thlev,tdlev)
	go to 32900
c-----------------------------------------------------------------------
1289	call beta(0.522,74.,0.,0.,t)
12890	thlev=1.12e-9
	p=100.*rnd1(d)
	if(p.le. 2.35) go to 12891
	if(p.le.29.75) go to 12892
	if(p.le.30.34) go to 12893
	if(p.le.99.00) go to 12894
	               go to 12895
12891	call nucltransK(1.289,0.070,1.3e-2,0.3e-4,tclev,thlev,tdlev)
	return
12892	call nucltransK(1.189,0.070,5.3e-3,0.1e-4,tclev,thlev,tdlev)
	go to 10000
12893	call nucltransK(0.960,0.070,1.3e-2,0.,tclev,thlev,tdlev)
	go to 32900
12894	call nucltransK(0.068,0.012,2.0e-1,0.,tclev,thlev,tdlev)
	go to 12210
12895	call nucltransK(0.032,0.012,1.6e-0,0.,tclev,thlev,tdlev)
	go to 12570
c-----------------------------------------------------------------------
1257	call beta(0.554,74.,0.,0.,t)
12570	thlev=1.7e-12
	p=100.*rnd1(d)
	if(p.le.54.5) go to 12571
	if(p.le.77.8) go to 12572
	              go to 12573
12571	call nucltransK(1.257,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev)
	return
12572	call nucltransK(1.157,0.070,5.3e-3,0.,tclev,thlev,tdlev)
	go to 10000
12573	call nucltransK(0.928,0.070,5.5e-3,0.,tclev,thlev,tdlev)
	go to 32900
c-----------------------------------------------------------------------
1221	call beta(0.590,74.,0.,0.,t)
12210	thlev=0.37e-12
	p=100.*rnd1(d)
	if(p.le.44.00) go to 12211
	if(p.le.99.92) go to 12212
	               go to 12213
12211	call nucltransK(1.221,0.070,3.0e-3,0.1e-4,tclev,thlev,tdlev)
	return
12212	call nucltransK(1.121,0.070,3.5e-3,0.1e-5,tclev,thlev,tdlev)
	go to 10000
12213	call nucltransK(0.892,0.070,6.0e-3,0.,tclev,thlev,tdlev)
	go to 32900
c-----------------------------------------------------------------------
329	call beta(1.482,74.,0.,0.,t)
32900	thlev=64.e-12
	call nucltransK(0.229,0.070,2.4e-1,0.,tclev,thlev,tdlev)
	go to 10000
c-----------------------------------------------------------------------
100	call beta(1.711,74.,0.,0.,t)
10000	thlev=1.38e-9
	call nucltransK(0.100,0.012,4.0e-0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

        subroutine Te133(tcnuc,tdnuc)
c Model for scheme of Te133 decay (S.Rab, Nucl. Data Sheets 
c 75(1995)491).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 14.12.2003.
	thnuc=750.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.13) go to 2936
	if(pbeta.le. 0.60) go to 2866
	if(pbeta.le. 0.86) go to 2825
	if(pbeta.le. 1.29) go to 2808
	if(pbeta.le. 2.34) go to 2768
	if(pbeta.le. 2.52) go to 2661
	if(pbeta.le. 2.70) go to 2597
	if(pbeta.le. 4.86) go to 2542
	if(pbeta.le. 5.24) go to 2526
	if(pbeta.le. 5.60) go to 2493
	if(pbeta.le. 6.20) go to 2467
	if(pbeta.le. 6.75) go to 2417
	if(pbeta.le. 6.86) go to 2393
	if(pbeta.le. 7.00) go to 2364
	if(pbeta.le. 7.26) go to 2284
	if(pbeta.le. 7.72) go to 2266
	if(pbeta.le. 8.96) go to 2255
	if(pbeta.le. 9.95) go to 2225
	if(pbeta.le.11.27) go to 2210
	if(pbeta.le.13.53) go to 2194
	if(pbeta.le.15.90) go to 2136
	if(pbeta.le.16.97) go to 2054
	if(pbeta.le.17.31) go to 2040
	if(pbeta.le.18.70) go to 2025
	if(pbeta.le.28.99) go to 1718
	if(pbeta.le.30.31) go to 1671
	if(pbeta.le.33.78) go to 1564
	if(pbeta.le.34.97) go to 1374
	if(pbeta.le.47.93) go to 1333
	if(pbeta.le.51.20) go to 1313
	if(pbeta.le.51.40) go to 1240
	if(pbeta.le.79.41) go to  720
	                   go to  312
c-----------------------------------------------------------------------
2936	call beta(0.001,53.,0.,0.,t)
29360	thlev=0.
	p=100.*rnd1(d)
	if(p.le.72.87) go to 29361 
	if(p.le.92.25) go to 29362 
	               go to 29363
29361	call nucltransK(2.624,0.033,1.5e-4,5.1e-4,tclev,thlev,tdlev)
	go to 31200
29362	call nucltransK(2.148,0.033,3.0e-4,2.9e-4,tclev,thlev,tdlev)
	go to 78700
29363	call nucltransK(1.372,0.033,1.0e-3,0.7e-4,tclev,thlev,tdlev)
	go to 15640
c-----------------------------------------------------------------------
2866	call beta(0.054,53.,0.,0.,t)
28660	thlev=0.
	p=100.*rnd1(d)
	if(p.le.74.63) go to 28661 
	if(p.le.94.67) go to 28662 
	               go to 28663
28661	call nucltransK(2.554,0.033,1.8e-4,4.9e-4,tclev,thlev,tdlev)
	go to 31200
28662	call nucltransK(2.079,0.033,3.2e-4,2.7e-4,tclev,thlev,tdlev)
	go to 78700
28663	call nucltransK(1.493,0.033,7.5e-4,0.9e-4,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
2825	call beta(0.095,53.,0.,0.,t)
28250	thlev=0.
	p=100.*rnd1(d)
	if(p.le.60.94) go to 28251 
	               go to 28252
28251	call nucltransK(2.825,0.033,1.3e-4,5.9e-4,tclev,thlev,tdlev)
	return
28252	call nucltransK(2.106,0.033,3.2e-4,2.7e-4,tclev,thlev,tdlev)
	go to 72000
c-----------------------------------------------------------------------
2808	call beta(0.112,53.,0.,0.,t)
28080	thlev=0.
	p=100.*rnd1(d)
	if(p.le.46.23) go to 28081 
	if(p.le.63.26) go to 28082 
	if(p.le.92.46) go to 28083 
	               go to 28084
28081	call nucltransK(2.496,0.033,2.0e-4,4.7e-4,tclev,thlev,tdlev)
	go to 31200
28082	call nucltransK(1.244,0.033,1.1e-3,0.4e-4,tclev,thlev,tdlev)
	go to 15640
28083	call nucltransK(1.137,0.033,1.5e-3,0.2e-4,tclev,thlev,tdlev)
	go to 16710
28084	call nucltransK(0.341,0.033,3.0e-2,0.,tclev,thlev,tdlev)
	go to 24670
c-----------------------------------------------------------------------
2768	call beta(0.152,53.,0.,0.,t)
27680	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.57) go to 27681 
	if(p.le.28.07) go to 27682 
	if(p.le.42.25) go to 27683 
	if(p.le.71.55) go to 27684 
	if(p.le.82.89) go to 27685 
	if(p.le.88.56) go to 27686 
	if(p.le.91.49) go to 27687 
	               go to 27688
27681	call nucltransK(2.456,0.033,2.0e-4,4.4e-4,tclev,thlev,tdlev)
	go to 31200
27682	call nucltransK(2.049,0.033,1.2e-3,2.5e-4,tclev,thlev,tdlev)
	go to 72000
27683	call nucltransK(1.455,0.033,1.0e-3,0.8e-4,tclev,thlev,tdlev)
	go to 13130
27684	call nucltransK(0.743,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 20250
27685	call nucltransK(0.544,0.033,2.0e-4,0.,tclev,thlev,tdlev)
	go to 22250
27686	call nucltransK(0.485,0.033,1.0e-2,0.,tclev,thlev,tdlev)
	go to 22840
27687	call nucltransK(0.302,0.033,4.5e-2,0.,tclev,thlev,tdlev)
	go to 24670
27688	call nucltransK(0.171,0.033,2.0e-1,0.,tclev,thlev,tdlev)
	go to 25970
c-----------------------------------------------------------------------
2661	call beta(0.259,53.,0.,0.,t)
26610	thlev=0.
	p=100.*rnd1(d)
	if(p.le.43.10) go to 26611 
	if(p.le.47.70) go to 26612 
	if(p.le.82.18) go to 26613 
	               go to 26614
26611	call nucltransK(2.661,0.033,1.5e-4,5.2e-4,tclev,thlev,tdlev)
	return
26612	call nucltransK(2.349,0.033,2.2e-4,3.9e-4,tclev,thlev,tdlev)
	go to 31200
26613	call nucltransK(0.943,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 17180
26614	call nucltransK(0.620,0.033,6.5e-3,0.,tclev,thlev,tdlev)
	go to 20400
c-----------------------------------------------------------------------
2597	call beta(0.323,53.,0.,0.,t)
25970	thlev=0.
	p=100.*rnd1(d)
	if(p.le.20.00) go to 25971 
	if(p.le.23.21) go to 25972 
	if(p.le.73.21) go to 25973 
	if(p.le.80.00) go to 25974 
	if(p.le.88.93) go to 25975 
	if(p.le.91.07) go to 25976 
	               go to 25977
25971	call nucltransK(2.597,0.033,1.6e-4,5.1e-4,tclev,thlev,tdlev)
	return
25972	call nucltransK(2.286,0.033,2.3e-4,3.5e-4,tclev,thlev,tdlev)
	go to 31200
25973	call nucltransK(1.683,0.033,5.0e-4,0.6e-4,tclev,thlev,tdlev)
	go to 91500
25974	call nucltransK(1.290,0.033,1.0e-3,0.5e-4,tclev,thlev,tdlev)
	go to 13070
25975	call nucltransK(1.285,0.033,1.0e-3,0.5e-4,tclev,thlev,tdlev)
	go to 13130
25976	call nucltransK(1.224,0.033,1.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 13740
25977	call nucltransK(0.572,0.033,9.0e-3,0.,tclev,thlev,tdlev)
	go to 20250
c-----------------------------------------------------------------------
2542	call beta(0.378,53.,0.,0.,t)
25420	thlev=0.
	p=100.*rnd1(d)
	if(p.le.23.06) go to 25421 
	if(p.le.63.19) go to 25422 
	if(p.le.73.34) go to 25423 
	if(p.le.75.37) go to 25424 
	if(p.le.77.40) go to 25425 
	if(p.le.84.78) go to 25426 
	if(p.le.90.32) go to 25427 
	if(p.le.94.47) go to 25428 
	               go to 25429
25421	call nucltransK(2.542,0.033,1.6e-4,4.8e-4,tclev,thlev,tdlev)
	return
25422	call nucltransK(2.230,0.033,2.5e-4,3.2e-4,tclev,thlev,tdlev)
	go to 31200
25423	call nucltransK(1.822,0.033,5.0e-4,1.8e-4,tclev,thlev,tdlev)
	go to 72000
25424	call nucltransK(1.755,0.033,5.5e-4,1.6e-4,tclev,thlev,tdlev)
	go to 78700
25425	call nucltransK(1.302,0.033,1.0e-3,0.5e-4,tclev,thlev,tdlev)
	go to 12400
25426	call nucltransK(1.209,0.033,1.4e-3,0.3e-4,tclev,thlev,tdlev)
	go to 13330
25427	call nucltransK(0.978,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 15640
25428	call nucltransK(0.488,0.033,1.2e-2,0.,tclev,thlev,tdlev)
	go to 20540
25429	call nucltransK(0.332,0.033,3.5e-2,0.,tclev,thlev,tdlev)
	go to 22100
c-----------------------------------------------------------------------
2526	call beta(0.394,53.,0.,0.,t)
25260	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.97) go to 25261 
	if(p.le.37.30) go to 25262 
	if(p.le.78.57) go to 25263 
	if(p.le.86.51) go to 25264 
	if(p.le.90.48) go to 25265 
	               go to 25266
25261	call nucltransK(2.526,0.033,1.7e-4,5.7e-4,tclev,thlev,tdlev)
	return
25262	call nucltransK(2.214,0.033,2.5e-4,3.1e-4,tclev,thlev,tdlev)
	go to 31200
25263	call nucltransK(1.807,0.033,5.0e-4,1.8e-4,tclev,thlev,tdlev)
	go to 72000
25264	call nucltransK(1.738,0.033,5.5e-4,1.5e-4,tclev,thlev,tdlev)
	go to 78700
25265	call nucltransK(1.286,0.033,1.0e-3,0.5e-4,tclev,thlev,tdlev)
	go to 12400
25266	call nucltransK(0.854,0.033,3.5e-3,0.,tclev,thlev,tdlev)
	go to 16710
c-----------------------------------------------------------------------
2493	call beta(0.427,53.,0.,0.,t)
24930	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 8.93) go to 24931 
	if(p.le.48.72) go to 24932 
	if(p.le.65.81) go to 24933 
	               go to 24934
24931	call nucltransK(2.181,0.033,2.5e-4,3.4e-4,tclev,thlev,tdlev)
	go to 31200
24932	call nucltransK(1.773,0.033,5.0e-4,0.9e-4,tclev,thlev,tdlev)
	go to 72000
24933	call nucltransK(1.706,0.033,6.0e-4,1.3e-4,tclev,thlev,tdlev)
	go to 78700
24934	call nucltransK(0.928,0.033,2.8e-3,0.,tclev,thlev,tdlev)
	go to 15640
c-----------------------------------------------------------------------
2467	call beta(0.453,53.,0.,0.,t)
24670	thlev=0.
	p=100.*rnd1(d)
	if(p.le.61.38) go to 24671 
	if(p.le.65.12) go to 24672 
	if(p.le.78.59) go to 24673 
	if(p.le.95.36) go to 24674 
	               go to 24675
24671	call nucltransK(2.467,0.033,1.8e-4,5.2e-4,tclev,thlev,tdlev)
	return
24672	call nucltransK(2.155,0.033,3.0e-4,3.0e-4,tclev,thlev,tdlev)
	go to 31200
24673	call nucltransK(1.680,0.033,5.0e-4,1.3e-4,tclev,thlev,tdlev)
	go to 78700
24674	call nucltransK(1.228,0.033,1.2e-3,0.4e-4,tclev,thlev,tdlev)
	go to 12400
24675	call nucltransK(0.242,0.033,8.0e-2,0.,tclev,thlev,tdlev)
	go to 22250
c-----------------------------------------------------------------------
2417	call beta(0.503,53.,0.,0.,t)
24170	thlev=0.
	p=100.*rnd1(d)
	if(p.le.34.48) go to 24171 
	if(p.le.52.63) go to 24172 
	if(p.le.63.52) go to 24173 
	if(p.le.68.06) go to 24174 
	if(p.le.73.69) go to 24175 
	if(p.le.95.46) go to 24176 
	               go to 24177
24171	call nucltransK(2.417,0.033,2.0e-4,4.2e-4,tclev,thlev,tdlev)
	return
24172	call nucltransK(2.106,0.033,3.0e-4,2.7e-4,tclev,thlev,tdlev)
	go to 31200
24173	call nucltransK(1.697,0.033,5.0e-4,1.3e-4,tclev,thlev,tdlev)
	go to 72000
24174	call nucltransK(1.630,0.033,5.2e-4,1.2e-4,tclev,thlev,tdlev)
	go to 78700
24175	call nucltransK(1.503,0.033,7.0e-4,0.3e-4,tclev,thlev,tdlev)
	go to 91500
24176	call nucltransK(1.110,0.033,1.8e-3,0.1e-4,tclev,thlev,tdlev)
	go to 13070
24177	call nucltransK(0.207,0.033,1.2e-1,0.,tclev,thlev,tdlev)
	go to 22100
c-----------------------------------------------------------------------
2393	call beta(0.527,53.,0.,0.,t)
23930	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.32) go to 23931 
	if(p.le.64.16) go to 23932 
	if(p.le.82.08) go to 23933 
	               go to 23934
23931	call nucltransK(2.393,0.033,2.0e-4,4.1e-4,tclev,thlev,tdlev)
	return
23932	call nucltransK(2.081,0.033,3.0e-4,2.6e-4,tclev,thlev,tdlev)
	go to 31200
23933	call nucltransK(0.722,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 16710
23934	call nucltransK(0.183,0.033,1.7e-1,0.,tclev,thlev,tdlev)
	go to 22100
c-----------------------------------------------------------------------
2364	call beta(0.556,53.,0.,0.,t)
23640	thlev=0.
	p=100.*rnd1(d)
	if(p.le.18.52) go to 23641 
	if(p.le.62.96) go to 23642 
	               go to 23643
23641	call nucltransK(2.363,0.033,2.0e-4,4.0e-4,tclev,thlev,tdlev)
	return
23642	call nucltransK(1.124,0.033,1.8e-3,0.3e-4,tclev,thlev,tdlev)
	go to 12400
23643	call nucltransK(1.051,0.033,2.0e-3,0.,tclev,thlev,tdlev)
	go to 13130
c-----------------------------------------------------------------------
2284	call beta(0.636,53.,0.,0.,t)
22840	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 5.77) go to 22841 
	if(p.le.34.62) go to 22842 
	if(p.le.53.85) go to 22843 
	               go to 22844
22841	call nucltransK(1.972,0.033,3.5e-4,1.7e-4,tclev,thlev,tdlev)
	go to 31200
22842	call nucltransK(1.564,0.033,6.0e-4,0.4e-4,tclev,thlev,tdlev)
	go to 72000
22843	call nucltransK(0.971,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 13130
22844	call nucltransK(0.910,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
2266	call beta(0.654,53.,0.,0.,t)
22660	thlev=0.
	p=100.*rnd1(d)
	if(p.le.52.17) go to 22661 
	if(p.le.64.34) go to 22662 
	if(p.le.90.43) go to 22663 
	               go to 22664
22661	call nucltransK(2.266,0.033,2.5e-4,3.5e-4,tclev,thlev,tdlev)
	return
22662	call nucltransK(1.027,0.033,2.2e-3,0.,tclev,thlev,tdlev)
	go to 12400
22663	call nucltransK(0.934,0.033,2.8e-3,0.,tclev,thlev,tdlev)
	go to 13330
22664	call nucltransK(0.702,0.033,5.5e-3,0.,tclev,thlev,tdlev)
	go to 15640
c-----------------------------------------------------------------------
2255	call beta(0.665,53.,0.,0.,t)
22550	thlev=0.
	p=100.*rnd1(d)
	if(p.le.16.92) go to 22551 
	if(p.le.23.45) go to 22552 
	if(p.le.40.37) go to 22553 
	if(p.le.44.40) go to 22554 
	if(p.le.54.07) go to 22555 
	if(p.le.79.05) go to 22556 
	if(p.le.88.72) go to 22557 
	               go to 22558
22551	call nucltransK(2.255,0.033,3.0e-4,3.8e-4,tclev,thlev,tdlev)
	return
22552	call nucltransK(1.944,0.033,3.5e-4,2.1e-4,tclev,thlev,tdlev)
	go to 31200
22553	call nucltransK(1.535,0.033,6.0e-4,1.0e-4,tclev,thlev,tdlev)
	go to 72000
22554	call nucltransK(1.468,0.033,6.5e-4,0.9e-4,tclev,thlev,tdlev)
	go to 78700
22555	call nucltransK(1.015,0.033,2.3e-3,0.,tclev,thlev,tdlev)
	go to 12400
22556	call nucltransK(0.942,0.033,2.7e-3,0.,tclev,thlev,tdlev)
	go to 13130
22557	call nucltransK(0.922,0.033,2.8e-3,0.,tclev,thlev,tdlev)
	go to 13330
22558	call nucltransK(0.691,0.033,5.5e-3,0.,tclev,thlev,tdlev)
	go to 15640
c-----------------------------------------------------------------------
2225	call beta(0.695,53.,0.,0.,t)
22250	thlev=0.
	p=100.*rnd1(d)
	if(p.le.19.00) go to 22251 
	if(p.le.29.28) go to 22252 
	if(p.le.35.32) go to 22253 
	if(p.le.35.84) go to 22254 
	if(p.le.47.67) go to 22255 
	if(p.le.53.02) go to 22256 
	if(p.le.79.79) go to 22257 
	if(p.le.84.97) go to 22258 
	if(p.le.96.80) go to 22259 
	               go to 22260
22251	call nucltransK(2.225,0.033,3.0e-4,3.2e-4,tclev,thlev,tdlev)
	return
22252	call nucltransK(1.913,0.033,4.5e-4,2.0e-4,tclev,thlev,tdlev)
	go to 31200
22253	call nucltransK(1.505,0.033,7.5e-4,0.9e-4,tclev,thlev,tdlev)
	go to 72000
22254	call nucltransK(1.438,0.033,8.5e-4,0.8e-4,tclev,thlev,tdlev)
	go to 78700
22255	call nucltransK(1.310,0.033,9.0e-4,0.1e-4,tclev,thlev,tdlev)
	go to 91500
22256	call nucltransK(0.912,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 13130
22257	call nucltransK(0.852,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 13740
22258	call nucltransK(0.554,0.033,9.5e-3,0.,tclev,thlev,tdlev)
	go to 16710
22259	call nucltransK(0.507,0.033,1.2e-2,0.,tclev,thlev,tdlev)
	go to 17180
22260	call nucltransK(0.200,0.033,1.4e-1,0.,tclev,thlev,tdlev)
	go to 20250
c-----------------------------------------------------------------------
2210	call beta(0.710,53.,0.,0.,t)
22100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.46.12) go to 22101 
	if(p.le.53.21) go to 22102 
	if(p.le.61.23) go to 22103 
	if(p.le.73.93) go to 22104 
	               go to 22105
22101	call nucltransK(2.210,0.033,2.9e-4,3.6e-4,tclev,thlev,tdlev)
	return
22102	call nucltransK(1.898,0.033,4.5e-4,2.0e-4,tclev,thlev,tdlev)
	go to 31200
22103	call nucltransK(1.490,0.033,7.5e-4,0.9e-4,tclev,thlev,tdlev)
	go to 72000
22104	call nucltransK(0.903,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 13070
22105	call nucltransK(0.646,0.033,6.5e-3,0.,tclev,thlev,tdlev)
	go to 15640
c-----------------------------------------------------------------------
2194	call beta(0.726,53.,0.,0.,t)
21940	thlev=0.
	p=100.*rnd1(d)
	if(p.le.25.07) go to 21941 
	if(p.le.78.72) go to 21942 
	if(p.le.92.79) go to 21943 
	if(p.le.94.72) go to 21944 
	if(p.le.97.36) go to 21945 
	               go to 21946
21941	call nucltransK(2.194,0.033,3.0e-4,3.1e-4,tclev,thlev,tdlev)
	return
21942	call nucltransK(1.882,0.033,4.5e-4,1.9e-4,tclev,thlev,tdlev)
	go to 31200
21943	call nucltransK(1.474,0.033,7.5e-4,0.9e-4,tclev,thlev,tdlev)
	go to 72000
21944	call nucltransK(0.886,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 13070
21945	call nucltransK(0.881,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 13130
21946	call nucltransK(0.860,0.033,3.4e-3,0.,tclev,thlev,tdlev)
	go to 13330
c-----------------------------------------------------------------------
2136	call beta(0.784,53.,0.,0.,t)
21360	thlev=0.
	p=100.*rnd1(d)
	if(p.le.57.73) go to 21361 
	if(p.le.69.61) go to 21362 
	if(p.le.75.10) go to 21363 
	if(p.le.79.32) go to 21364 
	if(p.le.80.12) go to 21365 
	if(p.le.82.23) go to 21366 
	if(p.le.86.03) go to 21367 
	if(p.le.89.41) go to 21368 
	if(p.le.94.94) go to 21369 
	               go to 21370
21361	call nucltransK(2.136,0.033,3.0e-4,2.9e-4,tclev,thlev,tdlev)
	return
21362	call nucltransK(1.824,0.033,5.0e-4,1.7e-4,tclev,thlev,tdlev)
	go to 31200
21363	call nucltransK(1.417,0.033,1.0e-3,0.8e-4,tclev,thlev,tdlev)
	go to 72000
21364	call nucltransK(1.350,0.033,1.2e-3,0.7e-4,tclev,thlev,tdlev)
	go to 78700
21365	call nucltransK(1.222,0.033,1.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 91500
21366	call nucltransK(0.897,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 12400
21367	call nucltransK(0.829,0.033,3.7e-3,0.,tclev,thlev,tdlev)
	go to 13070
21368	call nucltransK(0.824,0.033,3.7e-3,0.,tclev,thlev,tdlev)
	go to 13130
21369	call nucltransK(0.803,0.033,4.0e-3,0.,tclev,thlev,tdlev)
	go to 13330
21370	call nucltransK(0.763,0.033,3.2e-3,0.,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
2054	call beta(0.866,53.,0.,0.,t)
20540	thlev=0.
	p=100.*rnd1(d)
	if(p.le.12.21) go to 20541 
	if(p.le.24.15) go to 20542 
	if(p.le.31.12) go to 20543 
	if(p.le.47.69) go to 20544 
	if(p.le.58.15) go to 20545 
	if(p.le.67.74) go to 20546 
	if(p.le.84.31) go to 20547 
	if(p.le.94.77) go to 20548 
	               go to 20549
20541	call nucltransK(2.054,0.033,4.0e-4,2.5e-4,tclev,thlev,tdlev)
	return
20542	call nucltransK(1.742,0.033,5.0e-4,1.5e-4,tclev,thlev,tdlev)
	go to 31200
20543	call nucltransK(1.334,0.033,1.2e-3,0.6e-4,tclev,thlev,tdlev)
	go to 72000
20544	call nucltransK(1.267,0.033,1.3e-3,0.5e-4,tclev,thlev,tdlev)
	go to 78700
20545	call nucltransK(0.813,0.033,3.8e-3,0.,tclev,thlev,tdlev)
	go to 12400
20546	call nucltransK(0.746,0.033,4.5e-3,0.,tclev,thlev,tdlev)
	go to 13070
20547	call nucltransK(0.741,0.033,4.5e-3,0.,tclev,thlev,tdlev)
	go to 13130
20548	call nucltransK(0.720,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 13330
20549	call nucltransK(0.680,0.033,4.0e-3,0.,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
2040	call beta(0.880,53.,0.,0.,t)
20400	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.87) go to 20401 
	if(p.le.12.09) go to 20402 
	if(p.le.23.08) go to 20403 
	if(p.le.75.28) go to 20404 
	               go to 20405
20401	call nucltransK(1.320,0.033,9.5e-4,0.1e-4,tclev,thlev,tdlev)
	go to 72000
20402	call nucltransK(1.254,0.033,1.2e-3,0.5e-4,tclev,thlev,tdlev)
	go to 78700
20403	call nucltransK(0.727,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 13130
20404	call nucltransK(0.667,0.033,6.0e-3,0.,tclev,thlev,tdlev)
	go to 13740
20405	call nucltransK(0.369,0.033,2.5e-2,0.,tclev,thlev,tdlev)
	go to 16710
c-----------------------------------------------------------------------
2025	call beta(0.895,53.,0.,0.,t)
20250	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.60) go to 20251 
	if(p.le.25.61) go to 20252 
	if(p.le.40.94) go to 20253 
	if(p.le.47.75) go to 20254 
	if(p.le.54.00) go to 20255 
	if(p.le.64.79) go to 20256 
	               go to 20257
20251	call nucltransK(2.025,0.033,3.5e-4,2.2e-4,tclev,thlev,tdlev)
	return
20252	call nucltransK(1.713,0.033,5.0e-4,1.4e-4,tclev,thlev,tdlev)
	go to 31200
20253	call nucltransK(1.306,0.033,1.2e-3,0.6e-4,tclev,thlev,tdlev)
	go to 72000
20254	call nucltransK(1.239,0.033,1.3e-3,0.5e-4,tclev,thlev,tdlev)
	go to 78700
20255	call nucltransK(0.718,0.033,1.4e-3,0.,tclev,thlev,tdlev)
	go to 13070
20256	call nucltransK(0.713,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 13130
20257	call nucltransK(0.461,0.033,1.5e-2,0.,tclev,thlev,tdlev)
	go to 15640
c-----------------------------------------------------------------------
1718	call beta(1.202,53.,0.,0.,t)
17180	thlev=0.
	p=100.*rnd1(d)
	if(p.le.30.02) go to 17181 
	if(p.le.35.59) go to 17182 
	if(p.le.45.41) go to 17183 
	if(p.le.81.39) go to 17184 
	if(p.le.81.97) go to 17185 
	if(p.le.85.56) go to 17186 
	if(p.le.94.43) go to 17187 
	if(p.le.96.88) go to 17188 
	if(p.le.99.43) go to 17189 
	               go to 17190
17181	call nucltransK(1.718,0.033,6.0e-4,1.4e-4,tclev,thlev,tdlev)
	return
17182	call nucltransK(1.406,0.033,1.2e-3,0.7e-4,tclev,thlev,tdlev)
	go to 31200
17183	call nucltransK(0.998,0.033,2.4e-3,0.,tclev,thlev,tdlev)
	go to 72000
17184	call nucltransK(0.931,0.033,2.7e-3,0.,tclev,thlev,tdlev)
	go to 78700
17185	call nucltransK(0.803,0.033,1.1e-3,0.,tclev,thlev,tdlev)
	go to 91500
17186	call nucltransK(0.478,0.033,1.3e-2,0.,tclev,thlev,tdlev)
	go to 12400
17187	call nucltransK(0.410,0.033,2.0e-2,0.,tclev,thlev,tdlev)
	go to 13070
17188	call nucltransK(0.405,0.033,2.0e-2,0.,tclev,thlev,tdlev)
	go to 13130
17189	call nucltransK(0.384,0.033,2.5e-2,0.,tclev,thlev,tdlev)
	go to 13330
17190	call nucltransK(0.344,0.033,3.0e-2,0.,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
1671	call beta(1.249,53.,0.,0.,t)
16710	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 9.59) go to 16711 
	if(p.le.15.22) go to 16712 
	if(p.le.28.40) go to 16713 
	if(p.le.71.54) go to 16714 
	if(p.le.78.73) go to 16715 
	if(p.le.83.94) go to 16716 
	               go to 16717
16711	call nucltransK(1.671,0.033,5.0e-4,0.7e-4,tclev,thlev,tdlev)
	return
16712	call nucltransK(1.359,0.033,1.2e-3,0.7e-4,tclev,thlev,tdlev)
	go to 31200
16713	call nucltransK(0.952,0.033,2.6e-3,0.,tclev,thlev,tdlev)
	go to 72000
16714	call nucltransK(0.884,0.033,3.2e-3,0.,tclev,thlev,tdlev)
	go to 78700
16715	call nucltransK(0.432,0.033,1.8e-2,0.,tclev,thlev,tdlev)
	go to 12400
16716	call nucltransK(0.359,0.033,3.0e-2,0.,tclev,thlev,tdlev)
	go to 13130
16717	call nucltransK(0.338,0.033,3.5e-2,0.,tclev,thlev,tdlev)
	go to 13330
c-----------------------------------------------------------------------
1564	call beta(1.356,53.,0.,0.,t)
15640	thlev=0.
	p=100.*rnd1(d)
	if(p.le.28.18) go to 15641 
	if(p.le.92.95) go to 15642 
	if(p.le.96.86) go to 15643 
	if(p.le.97.85) go to 15644 
	if(p.le.98.46) go to 15645 
	if(p.le.98.83) go to 15646 
	               go to 15647
15641	call nucltransK(1.252,0.033,1.3e-3,0.5e-4,tclev,thlev,tdlev)
	go to 31200
15642	call nucltransK(0.844,0.033,3.5e-3,0.,tclev,thlev,tdlev)
	go to 72000
15643	call nucltransK(0.778,0.033,4.2e-3,0.,tclev,thlev,tdlev)
	go to 78700
15644	call nucltransK(0.324,0.033,3.7e-2,0.,tclev,thlev,tdlev)
	go to 12400
15645	call nucltransK(0.251,0.033,7.5e-2,0.,tclev,thlev,tdlev)
	go to 13130
15646	call nucltransK(0.231,0.033,8.5e-2,0.,tclev,thlev,tdlev)
	go to 13330
15647	call nucltransK(0.191,0.033,1.5e-1,0.,tclev,thlev,tdlev)
	go to 13740
c-----------------------------------------------------------------------
1374	call beta(1.546,53.,0.,0.,t)
13740	thlev=0.
	p=100.*rnd1(d)
	if(p.le.56.13) go to 13741 
	if(p.le.14.62) go to 13742 
	               go to 13743
13741	call nucltransK(1.062,0.033,1.5e-3,0.,tclev,thlev,tdlev)
	go to 31200
13742	call nucltransK(0.654,0.033,4.5e-3,0.,tclev,thlev,tdlev)
	go to 72000
13743	call nucltransK(0.587,0.033,8.5e-3,0.,tclev,thlev,tdlev)
	go to 78700
c-----------------------------------------------------------------------
1333	call beta(1.587,53.,0.,0.,t)
13330	thlev=0.
	p=100.*rnd1(d)
	if(p.le.74.49) go to 13331 
	if(p.le.94.05) go to 13332 
	if(p.le.96.28) go to 13333 
	if(p.le.99.83) go to 13334 
	               go to 13335
13331	call nucltransK(1.333,0.033,1.2e-3,0.6e-4,tclev,thlev,tdlev)
	return
13332	call nucltransK(1.021,0.033,2.3e-3,0.,tclev,thlev,tdlev)
	go to 31200
13333	call nucltransK(0.614,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 72000
13334	call nucltransK(0.546,0.033,9.5e-3,0.,tclev,thlev,tdlev)
	go to 78700
13335	call nucltransK(0.418,0.033,1.5e-2,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
1313	call beta(1.607,53.,0.,0.,t)
13130	thlev=0.
	p=100.*rnd1(d)
	if(p.le.17.45) go to 13131 
	if(p.le.91.78) go to 13132 
	if(p.le.95.27) go to 13133 
	               go to 13134
13131	call nucltransK(1.313,0.033,9.0e-4,0.,tclev,thlev,tdlev)
	return
13132	call nucltransK(1.001,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 31200
13133	call nucltransK(0.593,0.033,8.5e-3,0.,tclev,thlev,tdlev)
	go to 72000
13134	call nucltransK(0.526,0.033,1.2e-2,0.,tclev,thlev,tdlev)
	go to 78700
c-----------------------------------------------------------------------
13070	thlev=0.
	p=100.*rnd1(d)
	if(p.le.33.13) go to 13071 
	if(p.le.75.46) go to 13072 
	if(p.le.81.59) go to 13073 
	if(p.le.82.76) go to 13074 
	if(p.le.84.66) go to 13075 
	               go to 13076 
13071	call nucltransK(1.307,0.033,1.2e-3,0.5e-4,tclev,thlev,tdlev)
	return
13072	call nucltransK(0.995,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 31200
13073	call nucltransK(0.588,0.033,8.5e-3,0.,tclev,thlev,tdlev)
	go to 72000
13074	call nucltransK(0.520,0.033,8.5e-3,0.,tclev,thlev,tdlev)
	go to 78700
13075	call nucltransK(0.394,0.033,2.0e-2,0.,tclev,thlev,tdlev)
	go to 91300
13076	call nucltransK(0.392,0.033,2.2e-2,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
1240	call beta(1.680,53.,0.,0.,t)
12400	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.03) go to 12401 
	if(p.le.81.24) go to 12402 
	if(p.le.86.27) go to 12403 
	               go to 12404
12401	call nucltransK(1.240,0.033,1.2e-3,0.,tclev,thlev,tdlev)
	return
12402	call nucltransK(0.928,0.033,2.7e-3,0.,tclev,thlev,tdlev)
	go to 31200
12403	call nucltransK(0.520,0.033,1.2e-2,0.,tclev,thlev,tdlev)
	go to 72000
12404	call nucltransK(0.453,0.033,1.5e-2,0.,tclev,thlev,tdlev)
	go to 78700
c-----------------------------------------------------------------------
91500	thlev=0.
	call nucltransK(0.915,0.033,2.8e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
91300	thlev=0.
	call nucltransK(0.913,0.033,2.0e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
78700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.78.49) go to 78701 
	if(p.le.91.28) go to 78702 
	               go to 78703
78701	call nucltransK(0.787,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	return
78702	call nucltransK(0.475,0.033,1.2e-2,0.,tclev,thlev,tdlev)
	go to 31200
78703	call nucltransK(0.067,0.033,4.9,0.,tclev,thlev,tdlev)
	go to 72000
c-----------------------------------------------------------------------
720	call beta(2.200,53.,0.,0.,t)
72000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.72) go to 72001 
	               go to 72002
72001	call nucltransK(0.720,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	return
72002	call nucltransK(0.408,0.033,2.0e-2,0.,tclev,thlev,tdlev)
	go to 31200
c-----------------------------------------------------------------------
312	call beta(2.608,53.,0.,0.,t)
31200	thlev=0.
	call nucltransK(0.312,0.033,3.5e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

        subroutine Te133m(tcnuc,tdnuc)
c Model for scheme of Te133m decay (S.Rab, Nucl. Data Sheets 
c 75(1995)491; E_exc=334 keV).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 18.12.2003.
	thnuc=3324.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
c 17.5% IT to 133Te(g.s.)
	if(pdecay.le.17.5) then
	   call nucltransK(0.334,0.033,1.431,0.,tclev,thlev,tdlev)
	   return
	endif
c 82.5% beta decay to 133I
	pbeta=100.*rnd1(d)
	if(pbeta.le. 1.77) go to  3051
	if(pbeta.le. 2.70) go to  3029
	if(pbeta.le. 3.03) go to  2975
	if(pbeta.le. 3.16) go to  2968
	if(pbeta.le. 4.25) go to  2881
	if(pbeta.le. 5.22) go to  2826
	if(pbeta.le. 6.02) go to  2808
	if(pbeta.le. 7.59) go to  2784
	if(pbeta.le.10.97) go to  2686
	if(pbeta.le.31.35) go to  2596
	if(pbeta.le.36.78) go to  2556
	if(pbeta.le.37.87) go to  2516
	if(pbeta.le.39.00) go to  2506
	if(pbeta.le.41.05) go to  2500
	if(pbeta.le.41.77) go to  2483
	if(pbeta.le.45.63) go to  2467
	if(pbeta.le.46.96) go to  2445
	if(pbeta.le.47.36) go to  2427
	if(pbeta.le.48.10) go to  2419
	if(pbeta.le.55.22) go to  2372
	if(pbeta.le.56.31) go to  2262
	if(pbeta.le.57.64) go to  2249
	if(pbeta.le.59.21) go to  2212
	if(pbeta.le.61.14) go to  2142
	if(pbeta.le.63.07) go to  2049
	if(pbeta.le.66.21) go to  2005
	if(pbeta.le.72.72) go to  1991
	if(pbeta.le.73.32) go to  1975
	if(pbeta.le.74.41) go to  1943
	if(pbeta.le.78.03) go to  1886
	if(pbeta.le.86.59) go to  1777
	if(pbeta.le.88.28) go to  1647
	if(pbeta.le.91.06) go to  1560
	if(pbeta.le.91.66) go to  1516
	if(pbeta.le.92.87) go to  1455
	if(pbeta.le.93.96) go to   915
	if(pbeta.le.95.17) go to   913
	                   go to 10000
c-----------------------------------------------------------------------
3051	call beta(0.203,53.,0.,0.,t)
30510	thlev=0.
	p=100.*rnd1(d)
	if(p.le.21.62) go to 30511 
	if(p.le.29.05) go to 30512 
	               go to 30513
30511	call nucltransK(3.051,0.033,2.0e-5,18.1e-4,tclev,thlev,tdlev)
	return
30512	call nucltransK(1.405,0.033,3.5e-4,0.3e-4,tclev,thlev,tdlev)
	go to 16470
30513	call nucltransK(0.535,0.033,8.0e-3,0.,tclev,thlev,tdlev)
	go to 25160
c-----------------------------------------------------------------------
3029	call beta(0.225,53.,0.,0.,t)
30290	thlev=0.
	p=100.*rnd1(d)
	if(p.le.35.90) go to 30291 
	if(p.le.78.21) go to 30292 
	               go to 30293
30291	call nucltransK(1.574,0.033,2.6e-4,0.7e-4,tclev,thlev,tdlev)
	go to 14550
30292	call nucltransK(1.252,0.033,4.0e-4,0.2e-4,tclev,thlev,tdlev)
	go to 17770
30293	call nucltransK(1.054,0.033,7.0e-4,0.,tclev,thlev,tdlev)
	go to 19750
c-----------------------------------------------------------------------
2975	call beta(0.279,53.,0.,0.,t)
29750	thlev=0.
	p=100.*rnd1(d)
	if(p.le.31.25) go to 29751 
	               go to 29752
29751	call nucltransK(2.062,0.033,1.4e-4,4.8e-4,tclev,thlev,tdlev)
	go to 91300
29752	call nucltransK(1.198,0.033,5.0e-4,0.1e-4,tclev,thlev,tdlev)
	go to 17770
c-----------------------------------------------------------------------
2968	call beta(0.286,53.,0.,0.,t)
29680	thlev=0.
	call nucltransK(2.968,0.033,8.0e-5,15.1e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
2881	call beta(0.373,53.,0.,0.,t)
28810	thlev=0.
	p=100.*rnd1(d)
	if(p.le.17.89) go to 28811 
	if(p.le.47.36) go to 28812 
	if(p.le.76.83) go to 28813 
	               go to 28814
28811	call nucltransK(1.968,0.033,1.7e-4,3.2e-4,tclev,thlev,tdlev)
	go to 91300
28812	call nucltransK(0.890,0.033,3.1e-3,0.,tclev,thlev,tdlev)
	go to 19910
28813	call nucltransK(0.632,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 22490
28814	call nucltransK(0.285,0.033,5.0e-2,0.,tclev,thlev,tdlev)
	go to 25960
c-----------------------------------------------------------------------
2826	call beta(0.428,53.,0.,0.,t)
28260	thlev=0.
	p=100.*rnd1(d)
	if(p.le.16.10) go to 28261 
	if(p.le.23.00) go to 28262 
	if(p.le.55.18) go to 28263 
	if(p.le.67.82) go to 28264 
	               go to 28265
28261	call nucltransK(2.826,0.033,9.0e-5,13.7e-4,tclev,thlev,tdlev)
	return
28262	call nucltransK(1.914,0.033,1.8e-4,2.7e-4,tclev,thlev,tdlev)
	go to 91300
28263	call nucltransK(1.372,0.033,3.5e-4,0.3e-4,tclev,thlev,tdlev)
	go to 14550
28264	call nucltransK(0.852,0.033,1.0e-3,0.,tclev,thlev,tdlev)
	go to 19750
28265	call nucltransK(0.326,0.033,3.6e-2,0.,tclev,thlev,tdlev)
	go to 25000
c-----------------------------------------------------------------------
2808	call beta(0.446,53.,0.,0.,t)
28080	thlev=0.
	p=100.*rnd1(d)
	if(p.le.16.42) go to 28081 
	if(p.le.58.21) go to 28082 
	               go to 28083
28081	call nucltransK(1.104,0.033,6.0e-4,0.,tclev,thlev,tdlev)
	go to 17040
28082	call nucltransK(0.308,0.033,1.0e-2,0.,tclev,thlev,tdlev)
	go to 25000
28083	call nucltransK(0.251,0.033,7.5e-2,0.,tclev,thlev,tdlev)
	go to 25560
c-----------------------------------------------------------------------
2784	call beta(0.470,53.,0.,0.,t)
27840	thlev=0.
	p=100.*rnd1(d)
	if(p.le.42.97) go to 27841 
	if(p.le.94.53) go to 27842 
	               go to 27843
27841	call nucltransK(1.871,0.033,1.8e-4,2.2e-4,tclev,thlev,tdlev)
	go to 91300
27842	call nucltransK(1.008,0.033,7.0e-4,0.,tclev,thlev,tdlev)
	go to 17770
27843	call nucltransK(0.734,0.033,1.4e-3,0.,tclev,thlev,tdlev)
	go to 20490
c-----------------------------------------------------------------------
2686	call beta(0.568,53.,0.,0.,t)
26860	thlev=0.
	p=100.*rnd1(d)
	if(p.le.23.49) go to 26861 
	if(p.le.62.64) go to 26862 
	if(p.le.70.47) go to 26863 
	if(p.le.74.38) go to 26864 
	if(p.le.88.26) go to 26865 
	               go to 26866
26861	call nucltransK(1.773,0.033,1.9e-4,1.4e-4,tclev,thlev,tdlev)
	go to 91300
26862	call nucltransK(0.801,0.033,1.1e-3,0.,tclev,thlev,tdlev)
	go to 18860
26863	call nucltransK(0.637,0.033,1.7e-3,0.,tclev,thlev,tdlev)
	go to 20490
26864	call nucltransK(0.475,0.033,3.5e-3,0.,tclev,thlev,tdlev)
	go to 22120
26865	call nucltransK(0.314,0.033,1.0e-2,0.,tclev,thlev,tdlev)
	go to 23720
26866	call nucltransK(0.241,0.033,2.0e-2,0.,tclev,thlev,tdlev)
	go to 24450
c-----------------------------------------------------------------------
2596	call beta(0.658,53.,0.,0.,t)
25960	thlev=0.
	p=100.*rnd1(d)
	if(p.le.24.04) go to 25961 
	if(p.le.27.23) go to 25962 
	if(p.le.31.05) go to 25963 
	if(p.le.37.13) go to 25964 
	if(p.le.41.94) go to 25965 
	if(p.le.42.92) go to 25966 
	if(p.le.47.09) go to 25967 
	if(p.le.61.18) go to 25968 
	if(p.le.64.71) go to 25969 
	if(p.le.67.61) go to 25970 
	if(p.le.74.97) go to 25971 
	if(p.le.75.95) go to 25972 
	if(p.le.79.77) go to 25973
	if(p.le.99.02) go to 25974
	               go to 25975
25961	call nucltransK(1.683,0.033,2.5e-4,1.0e-4,tclev,thlev,tdlev)
	go to 91300
25962	call nucltransK(1.080,0.033,6.0e-4,0.,tclev,thlev,tdlev)
	go to 15160
25963	call nucltransK(0.949,0.033,8.0e-4,0.,tclev,thlev,tdlev)
	go to 16470
25964	call nucltransK(0.891,0.033,9.0e-4,0.,tclev,thlev,tdlev)
	go to 17040
25965	call nucltransK(0.889,0.033,9.0e-4,0.,tclev,thlev,tdlev)
	go to 17070
25966	call nucltransK(0.819,0.033,3.7e-3,0.,tclev,thlev,tdlev)
	go to 17770
25967	call nucltransK(0.710,0.033,1.4e-3,0.,tclev,thlev,tdlev)
	go to 18860
25968	call nucltransK(0.703,0.033,1.4e-3,0.,tclev,thlev,tdlev)
	go to 18930
25969	call nucltransK(0.653,0.033,1.7e-3,0.,tclev,thlev,tdlev)
	go to 19430
25970	call nucltransK(0.621,0.033,1.8e-3,0.,tclev,thlev,tdlev)
	go to 19750
25971	call nucltransK(0.605,0.033,7.7e-3,0.,tclev,thlev,tdlev)
	go to 19910
25972	call nucltransK(0.384,0.033,2.5e-2,0.,tclev,thlev,tdlev)
	go to 22120
25973	call nucltransK(0.347,0.033,3.0e-2,0.,tclev,thlev,tdlev)
	go to 22490
25974	call nucltransK(0.334,0.033,3.4e-2,0.,tclev,thlev,tdlev)
	go to 22620
25975	call nucltransK(0.224,0.033,1.0e-1,0.,tclev,thlev,tdlev)
	go to 23720
c-----------------------------------------------------------------------
2556	call beta(0.698,53.,0.,0.,t)
25560	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.82) go to 25561 
	if(p.le.15.08) go to 25562 
	if(p.le.26.44) go to 25563 
	if(p.le.63.01) go to 25564 
	if(p.le.65.28) go to 25565 
	if(p.le.75.61) go to 25566 
	if(p.le.77.06) go to 25567 
	if(p.le.91.94) go to 25568 
	if(p.le.96.49) go to 25569 
	               go to 25570
25561	call nucltransK(1.644,0.033,2.6e-4,0.9e-4,tclev,thlev,tdlev)
	go to 91300
25562	call nucltransK(0.996,0.033,7.0e-4,0.,tclev,thlev,tdlev)
	go to 15600
25563	call nucltransK(0.827,0.033,3.7e-3,0.,tclev,thlev,tdlev)
	go to 17290
25564	call nucltransK(0.780,0.033,4.2e-3,0.,tclev,thlev,tdlev)
	go to 17770
25565	call nucltransK(0.663,0.033,6.0e-3,0.,tclev,thlev,tdlev)
	go to 18930
25566	call nucltransK(0.581,0.033,8.2e-3,0.,tclev,thlev,tdlev)
	go to 19750
25567	call nucltransK(0.565,0.033,8.3e-3,0.,tclev,thlev,tdlev)
	go to 19910
25568	call nucltransK(0.344,0.033,3.2e-2,0.,tclev,thlev,tdlev)
	go to 22120
25569	call nucltransK(0.295,0.033,4.8e-2,0.,tclev,thlev,tdlev)
	go to 22620
25570	call nucltransK(0.185,0.033,1.6e-1,0.,tclev,thlev,tdlev)
	go to 23720
c-----------------------------------------------------------------------
2516	call beta(0.738,53.,0.,0.,t)
25160	thlev=0.
	p=100.*rnd1(d)
	if(p.le.30.50) go to 25161 
	if(p.le.72.00) go to 25162 
	if(p.le.86.00) go to 25163 
	               go to 25164
25161	call nucltransK(0.740,0.033,4.8e-3,0.,tclev,thlev,tdlev)
	go to 17770
25162	call nucltransK(0.719,0.033,4.9e-3,0.,tclev,thlev,tdlev)
	go to 17970
25163	call nucltransK(0.623,0.033,6.0e-3,0.,tclev,thlev,tdlev)
	go to 18930
25164	call nucltransK(0.526,0.033,1.1e-2,0.,tclev,thlev,tdlev)
	go to 19910
c-----------------------------------------------------------------------
2506	call beta(0.748,53.,0.,0.,t)
25060	thlev=0.
	p=100.*rnd1(d)
	if(p.le.64.89) go to 25061 
	               go to 25062
25061	call nucltransK(0.945,0.033,2.6e-3,0.,tclev,thlev,tdlev)
	go to 15600
25062	call nucltransK(0.244,0.033,7.5e-2,0.,tclev,thlev,tdlev)
	go to 22620
c-----------------------------------------------------------------------
2500	call beta(0.754,53.,0.,0.,t)
25000	thlev=0.
	p=100.*rnd1(d)
	if(p.le.62.53) go to 25001 
	if(p.le.67.31) go to 25002 
	if(p.le.72.09) go to 25003 
	if(p.le.84.25) go to 25004 
	if(p.le.91.63) go to 25005 
	               go to 25006
25001	call nucltransK(1.588,0.033,7.0e-4,1.1e-4,tclev,thlev,tdlev)
	go to 91300
25002	call nucltransK(0.796,0.033,1.1e-3,0.,tclev,thlev,tdlev)
	go to 17040
25003	call nucltransK(0.793,0.033,1.1e-3,0.,tclev,thlev,tdlev)
	go to 17070
25004	call nucltransK(0.724,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 17770
25005	call nucltransK(0.607,0.033,2.0e-3,0.,tclev,thlev,tdlev)
	go to 18930
25006	call nucltransK(0.495,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 20050
c-----------------------------------------------------------------------
2483	call beta(0.771,53.,0.,0.,t)
24830	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.66) go to 24831 
	if(p.le.31.09) go to 24832 
	               go to 24833
24831	call nucltransK(2.483,0.033,2.2e-4,4.5e-4,tclev,thlev,tdlev)
	return
24832	call nucltransK(1.570,0.033,7.0e-4,1.1e-4,tclev,thlev,tdlev)
	go to 91300
24833	call nucltransK(1.174,0.033,1.5e-3,0.3e-4,tclev,thlev,tdlev)
	go to 13070
c-----------------------------------------------------------------------
2467	call beta(0.787,53.,0.,0.,t)
24670	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 5.30) go to 24671 
	if(p.le.27.73) go to 24672 
	if(p.le.51.72) go to 24673 
	               go to 24674
24671	call nucltransK(1.552,0.033,7.0e-4,1.1e-4,tclev,thlev,tdlev)
	go to 91500
24672	call nucltransK(0.574,0.033,8.5e-3,0.,tclev,thlev,tdlev)
	go to 18930
24673	call nucltransK(0.493,0.033,1.2e-2,0.,tclev,thlev,tdlev)
	go to 19750
24674	call nucltransK(0.462,0.033,1.4e-2,0.,tclev,thlev,tdlev)
	go to 20050
c-----------------------------------------------------------------------
2445	call beta(0.809,53.,0.,0.,t)
24450	thlev=0.
	p=100.*rnd1(d)
	if(p.le.75.00) go to 24451 
	               go to 24452
24451	call nucltransK(0.885,0.033,9.5e-4,0.,tclev,thlev,tdlev)
	go to 15600
24452	call nucltransK(0.629,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 18170
c-----------------------------------------------------------------------
2427	call beta(0.827,53.,0.,0.,t)
24270	thlev=0.
	call nucltransK(0.178,0.033,1.7e-1,0.,tclev,thlev,tdlev)
	go to 22490
c-----------------------------------------------------------------------
2419	call beta(0.835,53.,0.,0.,t)
24190	thlev=0.
	p=100.*rnd1(d)
	if(p.le.45.91) go to 24191 
	if(p.le.63.94) go to 24192 
	if(p.le.81.97) go to 24193 
	               go to 24194
24191	call nucltransK(1.506,0.033,9.0e-4,0.9e-4,tclev,thlev,tdlev)
	go to 91300
24192	call nucltransK(0.859,0.033,2.9e-3,0.,tclev,thlev,tdlev)
	go to 15600
24193	call nucltransK(0.415,0.033,2.0e-2,0.,tclev,thlev,tdlev)
	go to 20050
24194	call nucltransK(0.158,0.033,2.5e-1,0.,tclev,thlev,tdlev)
	go to 22620
c-----------------------------------------------------------------------
2372	call beta(0.882,53.,0.,0.,t)
23720	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.55) go to 23721 
	if(p.le. 4.20) go to 23722 
	if(p.le. 5.85) go to 23723 
	if(p.le.19.06) go to 23724 
	if(p.le.37.37) go to 23725 
	if(p.le.39.02) go to 23726 
	if(p.le.53.13) go to 23727 
	if(p.le.86.29) go to 23728 
	if(p.le.97.10) go to 23729 
	if(p.le.98.75) go to 23730 
	               go to 23731
23721	call nucltransK(1.459,0.033,2.5e-4,0.5e-4,tclev,thlev,tdlev)
	go to 91300
23722	call nucltransK(1.456,0.033,2.5e-4,0.5e-4,tclev,thlev,tdlev)
	go to 91500
23723	call nucltransK(0.724,0.033,1.3e-2,0.,tclev,thlev,tdlev)
	go to 16470
23724	call nucltransK(0.642,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 17290
23725	call nucltransK(0.574,0.033,9.0e-3,0.,tclev,thlev,tdlev)
	go to 17970
23726	call nucltransK(0.555,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 18170
23727	call nucltransK(0.479,0.033,3.5e-3,0.,tclev,thlev,tdlev)
	go to 18930
23728	call nucltransK(0.429,0.033,4.5e-3,0.,tclev,thlev,tdlev)
	go to 19430
23729	call nucltransK(0.397,0.033,5.2e-3,0.,tclev,thlev,tdlev)
	go to 19750
23730	call nucltransK(0.322,0.033,9.0e-3,0.,tclev,thlev,tdlev)
	go to 20490
23731	call nucltransK(0.110,0.033,1.6e-1,0.,tclev,thlev,tdlev)
	go to 22620
c-----------------------------------------------------------------------
2262	call beta(0.992,53.,0.,0.,t)
22620	thlev=0.
	p=100.*rnd1(d)
	if(p.le.29.62) go to 22621 
	if(p.le.47.12) go to 22622 
	if(p.le.52.69) go to 22623 
	if(p.le.93.44) go to 22624 
	if(p.le.95.63) go to 22625 
	               go to 22626
22621	call nucltransK(1.349,0.033,5.0e-4,0.3e-4,tclev,thlev,tdlev)
	go to 91300
22622	call nucltransK(0.532,0.033,1.1e-2,0.,tclev,thlev,tdlev)
	go to 17290
22623	call nucltransK(0.464,0.033,3.5e-3,0.,tclev,thlev,tdlev)
	go to 17970
22624	call nucltransK(0.445,0.033,1.6e-2,0.,tclev,thlev,tdlev)
	go to 18170
22625	call nucltransK(0.369,0.033,6.0e-3,0.,tclev,thlev,tdlev)
	go to 18930
22626	call nucltransK(0.319,0.033,4.0e-2,0.,tclev,thlev,tdlev)
	go to 19430
c-----------------------------------------------------------------------
2249	call beta(1.005,53.,0.,0.,t)
22490	thlev=0.
	p=100.*rnd1(d)
	if(p.le.34.30) go to 22491 
	if(p.le.54.96) go to 22492 
	if(p.le.81.82) go to 22493 
	               go to 22494
22491	call nucltransK(0.472,0.033,1.3e-2,0.,tclev,thlev,tdlev)
	go to 17770
22492	call nucltransK(0.363,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 18860
22493	call nucltransK(0.355,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 18930
22494	call nucltransK(0.258,0.033,6.5e-2,0.,tclev,thlev,tdlev)
	go to 19910
c-----------------------------------------------------------------------
2212	call beta(1.042,53.,0.,0.,t)
22120	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 7.42) go to 22121 
	if(p.le.60.70) go to 22122 
	if(p.le.89.52) go to 22123 
	               go to 22124
22121	call nucltransK(1.299,0.033,4.0e-4,0.3e-4,tclev,thlev,tdlev)
	go to 91300
22122	call nucltransK(0.435,0.033,1.7e-2,0.,tclev,thlev,tdlev)
	go to 17770
22123	call nucltransK(0.413,0.033,1.6e-2,0.,tclev,thlev,tdlev)
	go to 17990
22124	call nucltransK(0.221,0.033,1.0e-1,0.,tclev,thlev,tdlev)
	go to 19910
c-----------------------------------------------------------------------
2142	call beta(1.112,53.,0.,0.,t)
21420	thlev=0.
	p=100.*rnd1(d)
	if(p.le.12.99) go to 21421 
	if(p.le.23.03) go to 21422 
	if(p.le.24.98) go to 21423 
	if(p.le.63.96) go to 21424 
	if(p.le.72.82) go to 21425 
	               go to 21426
21421	call nucltransK(1.230,0.033,1.5e-3,0.4e-4,tclev,thlev,tdlev)
	go to 91300
21422	call nucltransK(1.228,0.033,1.5e-3,0.4e-4,tclev,thlev,tdlev)
	go to 91500
21423	call nucltransK(0.249,0.033,7.5e-2,0.,tclev,thlev,tdlev)
	go to 18930
21424	call nucltransK(0.151,0.033,1.8e-2,0.,tclev,thlev,tdlev)
	go to 19910
21425	call nucltransK(0.137,0.033,4.0e-1,0.,tclev,thlev,tdlev)
	go to 20050
21426	call nucltransK(0.092,0.033,1.3,0.,tclev,thlev,tdlev)
	go to 20490
c-----------------------------------------------------------------------
2049	call beta(1.205,53.,0.,0.,t)
20490	thlev=0.
	p=100.*rnd1(d)
	if(p.le.50.00) go to 20491 
	if(p.le.61.48) go to 20492 
	if(p.le.75.00) go to 20493 
	if(p.le.90.98) go to 20494 
	               go to 20495
20491	call nucltransK(2.049,0.033,1.5e-4,2.2e-4,tclev,thlev,tdlev)
	return
20492	call nucltransK(1.137,0.033,1.7e-3,0.3e-4,tclev,thlev,tdlev)
	go to 91300
20493	call nucltransK(1.135,0.033,1.7e-3,0.3e-4,tclev,thlev,tdlev)
	go to 91500
20494	call nucltransK(0.743,0.033,3.5e-3,0.,tclev,thlev,tdlev)
	go to 13070
20495	call nucltransK(0.346,0.033,3.0e-2,0.,tclev,thlev,tdlev)
	go to 17040
c-----------------------------------------------------------------------
2005	call beta(1.249,53.,0.,0.,t)
20050	thlev=0.
	p=100.*rnd1(d)
	if(p.le.72.63) go to 20051 
	if(p.le.72.86) go to 20052 
	if(p.le.75.21) go to 20053 
	if(p.le.95.30) go to 20054 
	if(p.le.97.65) go to 20055 
	               go to 20056
20051	call nucltransK(2.005,0.033,8.0e-4,2.3e-4,tclev,thlev,tdlev)
	return
20052	call nucltransK(1.693,0.033,4.5e-4,0.7e-4,tclev,thlev,tdlev)
	go to 31200
20053	call nucltransK(1.091,0.033,2.0e-3,0.,tclev,thlev,tdlev)
	go to 91500
20054	call nucltransK(0.698,0.033,5.5e-3,0.,tclev,thlev,tdlev)
	go to 13070
20055	call nucltransK(0.119,0.033,5.0e-1,0.,tclev,thlev,tdlev)
	go to 18860
20056	call nucltransK(0.112,0.033,5.5e-1,0.,tclev,thlev,tdlev)
	go to 18930
c-----------------------------------------------------------------------
1991	call beta(1.263,53.,0.,0.,t)
19910	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.96) go to 19911 
	if(p.le.91.68) go to 19912 
	if(p.le.98.47) go to 19913 
	               go to 19914
19911	call nucltransK(1.078,0.033,6.0e-4,0.,tclev,thlev,tdlev)
	go to 91300
19912	call nucltransK(0.262,0.033,6.5e-2,0.,tclev,thlev,tdlev)
	go to 17290
19913	call nucltransK(0.193,0.033,3.5e-2,0.,tclev,thlev,tdlev)
	go to 17970
19914	call nucltransK(0.098,0.033,2.2e-1,0.,tclev,thlev,tdlev)
	go to 18930
c-----------------------------------------------------------------------
1975	call beta(1.279,53.,0.,0.,t)
19750	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.13) go to 19751 
	if(p.le.49.41) go to 19752 
	if(p.le.51.15) go to 19753 
	if(p.le.59.29) go to 19754 
	if(p.le.62.49) go to 19755 
	if(p.le.67.43) go to 19756 
	if(p.le.73.83) go to 19757 
	               go to 19758
19751	call nucltransK(1.975,0.033,4.0e-4,1.9e-4,tclev,thlev,tdlev)
	return
19752	call nucltransK(1.062,0.033,2.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 91300
19753	call nucltransK(1.060,0.033,2.0e-3,0.1e-4,tclev,thlev,tdlev)
	go to 91500
19754	call nucltransK(0.520,0.033,8.0e-3,0.,tclev,thlev,tdlev)
	go to 14550
19755	call nucltransK(0.458,0.033,1.5e-2,0.,tclev,thlev,tdlev)
	go to 15160
19756	call nucltransK(0.198,0.033,3.2e-2,0.,tclev,thlev,tdlev)
	go to 17770
19757	call nucltransK(0.177,0.033,1.9e-1,0.,tclev,thlev,tdlev)
	go to 17970
19758	call nucltransK(0.082,0.033,1.8,0.,tclev,thlev,tdlev)
	go to 18930
c-----------------------------------------------------------------------
1943	call beta(1.311,53.,0.,0.,t)
19430	thlev=0.
	p=100.*rnd1(d)
	if(p.le.35.36) go to 19431 
	if(p.le.97.97) go to 19432 
	               go to 19433
19431	call nucltransK(1.030,0.033,2.1e-3,0.,tclev,thlev,tdlev)
	go to 91300
19432	call nucltransK(0.213,0.033,2.6e-2,0.,tclev,thlev,tdlev)
	go to 17290
19433	call nucltransK(0.050,0.033,1.4e+1,0.,tclev,thlev,tdlev)
	go to 18930
c-----------------------------------------------------------------------
18930	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.13) go to 18931 
	if(p.le.23.29) go to 18932 
	if(p.le.92.90) go to 18933 
	if(p.le.96.02) go to 18934 
	               go to 18935
18931	call nucltransK(1.893,0.033,4.0e-4,1.4e-4,tclev,thlev,tdlev)
	return
18932	call nucltransK(0.980,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 91300
18933	call nucltransK(0.978,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 91500
18934	call nucltransK(0.377,0.033,2.5e-2,0.,tclev,thlev,tdlev)
	go to 15160
18935	call nucltransK(0.116,0.033,1.5e-1,0.,tclev,thlev,tdlev)
	go to 17770
c-----------------------------------------------------------------------
1886	call beta(1.368,53.,0.,0.,t)
18860	thlev=0.
	p=100.*rnd1(d)
	if(p.le.18.33) go to 18861 
	if(p.le.28.52) go to 18862 
	if(p.le.34.63) go to 18863 
	if(p.le.36.67) go to 18864 
	if(p.le.40.74) go to 18865 
	               go to 18866
18861	call nucltransK(1.886,0.033,2.0e-4,1.2e-4,tclev,thlev,tdlev)
	return
18862	call nucltransK(0.973,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 91300
18863	call nucltransK(0.971,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 91500
18864	call nucltransK(0.369,0.033,2.6e-2,0.,tclev,thlev,tdlev)
	go to 15160
18865	call nucltransK(0.177,0.033,2.0e-1,0.,tclev,thlev,tdlev)
	go to 17070
18866	call nucltransK(0.088,0.033,1.4,0.,tclev,thlev,tdlev)
	go to 17970
c-----------------------------------------------------------------------
18170	thlev=0.
	p=100.*rnd1(d)
	if(p.le.52.17) go to 18171 
	               go to 18172
18171	call nucltransK(0.040,0.033,3.2e+1,0.,tclev,thlev,tdlev)
	go to 17770
18172	call nucltransK(0.018,0.005,2.0e+1,0.,tclev,thlev,tdlev)
	go to 17990
c-----------------------------------------------------------------------
17990	thlev=0.
	call nucltransK(0.164,0.033,2.5e-1,0.,tclev,thlev,tdlev)
	go to 16340
c-----------------------------------------------------------------------
17970	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.06) go to 17971 
	if(p.le.19.90) go to 17972 
	if(p.le.57.49) go to 17973 
	if(p.le.65.99) go to 17974 
	if(p.le.67.86) go to 17975 
	if(p.le.75.34) go to 17976 
	               go to 17977
17971	call nucltransK(1.797,0.033,4.5e-4,0.9e-4,tclev,thlev,tdlev)
	return
17972	call nucltransK(0.885,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 91300
17973	call nucltransK(0.883,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 91500
17974	call nucltransK(0.343,0.033,3.0e-2,0.,tclev,thlev,tdlev)
	go to 14550
17975	call nucltransK(0.281,0.033,5.5e-2,0.,tclev,thlev,tdlev)
	go to 15160
17976	call nucltransK(0.151,0.033,3.3e-1,0.,tclev,thlev,tdlev)
	go to 16470
17977	call nucltransK(0.021,0.005,2.6,0.,tclev,thlev,tdlev)
	go to 17770
c-----------------------------------------------------------------------
1777	call beta(1.477,53.,0.,0.,t)
17770	thlev=0.
	p=100.*rnd1(d)
	if(p.le.98.61) go to 17771 
	               go to 17772
17771	call nucltransK(0.864,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 91300
17772	call nucltransK(0.047,0.033,1.7e+1,0.,tclev,thlev,tdlev)
	go to 17290
c-----------------------------------------------------------------------
17290	thlev=170.e-9
	p=100.*rnd1(d)
	if(p.le.37.93) go to 17291 
	               go to 17292
17291	call nucltransK(0.169,0.033,4.7e-2,0.,tclev,thlev,tdlev)
	go to 15600
17292	call nucltransK(0.095,0.033,2.1,0.,tclev,thlev,tdlev)
	go to 16340
c-----------------------------------------------------------------------
17070	thlev=0.
	p=100.*rnd1(d)
	if(p.le.90.91) go to 17071 
	               go to 17072
17071	call nucltransK(0.795,0.033,4.0e-3,0.,tclev,thlev,tdlev)
	go to 91300
17072	call nucltransK(0.793,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
17040	thlev=0.
	p=100.*rnd1(d)
	if(p.le.52.17) go to 17041 
	if(p.le.60.14) go to 17042 
	if(p.le.68.11) go to 17043 
	               go to 17044
17041	call nucltransK(1.704,0.033,6.0e-4,1.4e-4,tclev,thlev,tdlev)
	return
17042	call nucltransK(1.392,0.033,8.5e-4,0.2e-4,tclev,thlev,tdlev)
	go to 31200
17043	call nucltransK(0.792,0.033,4.0e-3,0.,tclev,thlev,tdlev)
	go to 91300
17044	call nucltransK(0.790,0.033,4.0e-3,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
1647	call beta(1.607,53.,0.,0.,t)
16470	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 9.88) go to 16471 
	if(p.le.72.34) go to 16472 
	if(p.le.93.86) go to 16473 
	               go to 16474
16471	call nucltransK(1.646,0.033,5.0e-4,0.6e-4,tclev,thlev,tdlev)
	return
16472	call nucltransK(0.734,0.033,4.6e-3,0.,tclev,thlev,tdlev)
	go to 91300
16473	call nucltransK(0.732,0.033,4.6e-3,0.,tclev,thlev,tdlev)
	go to 91500
16474	call nucltransK(0.087,0.033,2.9,0.,tclev,thlev,tdlev)
	go to 15600
c-----------------------------------------------------------------------
16340	thlev=9.
	call nucltransK(0.074,0.033,2.4e+1,0.,tclev,thlev,tdlev)
	go to 15600
c-----------------------------------------------------------------------
1560	call beta(1.694,53.,0.,0.,t)
15600	thlev=0.
	call nucltransK(0.648,0.033,4.6e-3,0.,tclev,thlev,tdlev)
	go to 91300
c-----------------------------------------------------------------------
1516	call beta(1.738,53.,0.,0.,t)
15160	thlev=0.
	p=100.*rnd1(d)
	if(p.le.78.54) go to 15161 
	if(p.le.92.15) go to 15162 
	               go to 15163
15161	call nucltransK(1.516,0.033,8.0e-4,0.9e-4,tclev,thlev,tdlev)
	return
15162	call nucltransK(1.204,0.033,1.1e-3,0.1e-4,tclev,thlev,tdlev)
	go to 31200
15163	call nucltransK(0.602,0.033,8.0e-3,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
1455	call beta(1.799,53.,0.,0.,t)
14550	thlev=0.
	p=100.*rnd1(d)
	if(p.le.30.90) go to 14551 
	if(p.le.87.98) go to 14552 
	               go to 14553
14551	call nucltransK(1.455,0.033,1.0e-3,0.9e-4,tclev,thlev,tdlev)
	return
14552	call nucltransK(1.143,0.033,1.8e-3,0.3e-4,tclev,thlev,tdlev)
	go to 31200
14553	call nucltransK(0.540,0.033,1.0e-2,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
13070	thlev=0.
	p=100.*rnd1(d)
	if(p.le.39.00) go to 13071 
	if(p.le.89.00) go to 13072 
	               go to 13073
13071	call nucltransK(1.307,0.033,1.2e-3,0.5e-4,tclev,thlev,tdlev)
	return
13072	call nucltransK(0.995,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 31200
13073	call nucltransK(0.392,0.033,2.1e-2,0.,tclev,thlev,tdlev)
	go to 91500
c-----------------------------------------------------------------------
915	call beta(2.339,53.,0.,0.,t)
91500	thlev=0.
	p=100.*rnd1(d)
	if(p.le.99.84) go to 91501 
	               go to 91502
91501	call nucltransK(0.915,0.033,2.7e-3,0.,tclev,thlev,tdlev)
	return
91502	call nucltransK(0.602,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 31200
c-----------------------------------------------------------------------
913	call beta(2.341,53.,0.,0.,t)
91300	thlev=0.
	call nucltransK(0.913,0.033,2.1e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
31200	thlev=0.
	call nucltransK(0.312,0.033,4.0e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	call beta(3.254,53.,0.,0.,t)
	return
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Te134(tcnuc,tdnuc)
c Model for scheme of Te134 decay (Yu.V.Sergeenkov, Nucl. Data Sheets 
c 71(1994)557).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 7.10.2002.
	thnuc=2508.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.14.) go to 1106 ! 14%
	if(pbeta.le.58.) go to  923 ! 44%
	                 go to  847 ! 42%
c-----------------------------------------------------------------------
1106	call beta(0.454,53.,0.,0.,t)
11060	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.33) go to 11061   !  3.33%
	if(p.le.14.45) go to 11062   ! 11.12%
	if(p.le.17.78) go to 11063   !  3.33%
	if(p.le.91.15) go to 11064   ! 73.37%
	if(p.le.94.70) go to 11065   !  3.55%
	               go to 11066   !  5.30%
11061	call nucltransK(1.027,0.033,1.5e-3,0.,tclev,thlev,tdlev)
	go to 79000
11062	call nucltransK(0.926,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 18100
11063	call nucltransK(0.896,0.033,3.0e-3,0.,tclev,thlev,tdlev)
	go to 21000
11064	call nucltransK(0.461,0.033,1.5e-2,0.,tclev,thlev,tdlev)
	go to 64500
11065	call nucltransK(0.260,0.033,6.0e-2,0.,tclev,thlev,tdlev)
	go to 84700
11066	call nucltransK(0.183,0.033,1.8e-1,0.,tclev,thlev,tdlev)
	go to 92300
c-----------------------------------------------------------------------
923	call beta(0.637,53.,0.,0.,t)
92300	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.71) go to 92301   !  2.71%
	if(p.le.37.31) go to 92302   ! 34.60%
	if(p.le.47.94) go to 92303   ! 10.63%
	if(p.le.98.37) go to 92304   ! 50.43%
	               go to 92305   !  1.63%
92301	call nucltransK(0.844,0.033,2.5e-3,0.,tclev,thlev,tdlev)
	go to 79000
92302	call nucltransK(0.743,0.033,4.5e-3,0.,tclev,thlev,tdlev)
	go to 18100
92303	call nucltransK(0.713,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	go to 21000
92304	call nucltransK(0.278,0.033,4.9e-2,0.,tclev,thlev,tdlev)
	go to 64500
92305	call nucltransK(0.077,0.033,1.61,0.,tclev,thlev,tdlev)
	go to 84700
c----------------------------------------------------------------------
847	call beta(0.713,53.,0.,0.,t)
84700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.69.71) go to 84701   ! 69.71%
	if(p.le.72.49) go to 84702   !  2.78%
	if(p.le.76.45) go to 84703   !  3.96%
	               go to 84704   ! 23.55%
84701	call nucltransK(0.767,0.033,3.3e-3,0.,tclev,thlev,tdlev)
	go to 79000
84702	call nucltransK(0.666,0.033,6.0e-3,0.,tclev,thlev,tdlev)
	go to 18100
84703	call nucltransK(0.636,0.033,7.0e-3,0.,tclev,thlev,tdlev)
	go to 21000
84704	call nucltransK(0.201,0.033,1.3e-1,0.,tclev,thlev,tdlev)
	go to 64500
c----------------------------------------------------------------------
64500	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 2.03) go to 64501   !  2.03%
	if(p.le.45.01) go to 64502   ! 42.98%
	if(p.le.55.87) go to 64503   ! 10.86%
	               go to 64504   ! 44.13%
64501	call nucltransK(0.645,0.033,5.0e-3,0.,tclev,thlev,tdlev)
	return
64502	call nucltransK(0.566,0.033,9.0e-3,0.,tclev,thlev,tdlev)
	go to 79000
64503	call nucltransK(0.465,0.033,1.5e-2,0.,tclev,thlev,tdlev)
	go to 18100
64504	call nucltransK(0.435,0.033,1.4e-2,0.,tclev,thlev,tdlev)
	go to 21000
c----------------------------------------------------------------------
21000	thlev=0.15e-9
	p=100.*rnd1(d)
	if(p.le.98.94) go to 21001   ! 98.94%
	               go to 21002   !  1.06%
21001	call nucltransK(0.210,0.033,1.1e-1,0.,tclev,thlev,tdlev)
	return
21002	call nucltransK(0.131,0.033,5.2e-1,0.,tclev,thlev,tdlev)
	go to 79000
c----------------------------------------------------------------------
18100	thlev=0.1e-9
	p=100.*rnd1(d)
	if(p.le.95.83) go to 18101   ! 95.83%
	if(p.le.96.45) go to 18102   !  0.62%
	               go to 18103   !  3.55%
18101	call nucltransK(0.181,0.033,1.8e-1,0.,tclev,thlev,tdlev)
	return
18102	call nucltransK(0.137,0.033,5.8e-1,0.,tclev,thlev,tdlev)
	go to 44000
18103	call nucltransK(0.101,0.033,1.2,0.,tclev,thlev,tdlev)
	go to 79000
c----------------------------------------------------------------------
79000	thlev=1.62e-9
	call nucltransK(0.079,0.033,1.50,0.,tclev,thlev,tdlev)
	return
c----------------------------------------------------------------------
44000	thlev=0.
	call nucltransK(0.044,0.033,7.97,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Th234(tcnuc,tdnuc)
c Scheme of Th234 decay to Pa234m (not Pa234!) in accordance with NDS 
c 108(2007)681 and ENSDF database at NNDC site on 8.08.2007.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 8.08.2007.
	thnuc=2.08224e6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 1.501) go to 187         !  1.501%
	if(pbeta.le. 1.516) go to 177         !  0.015%
	if(pbeta.le. 7.921) go to 167         !  6.405%
	if(pbeta.le.21.933) go to 166         ! 14.012%
	                    go to  74         ! 78.067%
c-----------------------------------------------------------------------
187	call beta(0.086,91.,0.,0.,t)
18700	thlev=0.
	p=100.*rnd1(d)
	if(p.le.17.0) go to 18701          !  17.0%
	if(p.le.21.7) go to 18702          !   4.7%
	              go to 18703          !  78.3%
18701	call nucltransK(0.113,0.021,2.3e-1,0.,tclev,thlev,tdlev)
	go to 74000
18702	call nucltransK(0.083,0.021,2.0e-1,0.,tclev,thlev,tdlev)
	go to 10300
18703	call nucltransK(0.020,0.005,2.4e2,0.,tclev,thlev,tdlev)
	go to 16700
c-----------------------------------------------------------------------
177	call beta(0.096,91.,0.,0.,t)
17700	thlev=0.
	call nucltransK(0.103,0.021,3.8e0,0.,tclev,thlev,tdlev)
	go to 74000
c-----------------------------------------------------------------------
167	call beta(0.106,91.,0.,0.,t)
16700	thlev=0.55e-9
	p=100.*rnd1(d)
	if(p.le.32.1) go to 16701          !  32.1%
	              go to 16702          !  67.9%
16701	call nucltransK(0.093,0.021,1.5e-1,0.,tclev,thlev,tdlev)
	go to 74000
16702	call nucltransK(0.063,0.021,4.1e-1,0.,tclev,thlev,tdlev)
	go to 10300
c-----------------------------------------------------------------------
166	call beta(0.106,91.,0.,0.,t)
16600	thlev=0.
	p=100.*rnd1(d)
	if(p.le.97.0) go to 16601          !  97.0%
	              go to 16602          !   3.0%
16601	call nucltransK(0.092,0.021,5.3e0,0.,tclev,thlev,tdlev)
	go to 74000
16602	call nucltransK(0.062,0.021,2.5e1,0.,tclev,thlev,tdlev)
	go to 10300
c-----------------------------------------------------------------------
10300	thlev=0.
	call nucltransK(0.029,0.021,4.4e3,0.,tclev,thlev,tdlev)
	go to 74000
c-----------------------------------------------------------------------
74	call beta(0.199,91.,0.,0.,t)
c below is creation of Pa234m with T1/2=1.159 m which mainly beta^- decays
C to U234 (IT to Pa234 is only 0.16%); decay of Pa234m should be generated 
c independently
74000	return 
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Tl207(tcnuc,tdnuc)
c Scheme of Tl207 decay ("Table of Isotopes", 7th ed., 1978).
c Three-figured labels correspond to energies of Pb207
c excited levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 14.08.1992, 22.10.1995; 
c VIT, 30.10.2006 (update to NDS 70(1993)315 and correction to the beta shape).
	thnuc=286.2
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.0.268) go to   898  !  0.268%
	                   go to 10000  ! 99.732%
c-----------------------------------------------------------------------
898	call beta(0.529,82.,0.,0.,t)
	thlev=0.115e-12
	p=100.*rnd1(d)
	if(p.le.99.29) go to 89801   ! 99.29%
	               go to 89802   !  0.71%
89801	call nucltransK(0.898,0.088,2.5e-2,0.,tclev,thlev,tdlev)
	return
89802	call nucltransK(0.328,0.088,3.5e-1,0.,tclev,thlev,tdlev)
	go to 57000
c-----------------------------------------------------------------------
57000	thlev=130.5e-12
	call nucltransK(0.570,0.088,2.2e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
c10000	call beta(1.427,82.,0.,0.,t)
c change to forbidden spectrum with experimental correction from
c J.M.Trischuk et al., NPA 90(1967)33 and H.Daniel, RMP 40(1968)659
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1.
10000	call beta1(1.427,82.,0.,0.,t,0.,0.024,0.,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Tl208(tcnuc,tdnuc)
c Scheme of Tl208 decay ("Table of Isotopes", 7th ed., 1978).
c Four-figured labels correspond to energies of 208Pb excited
c levels in keV.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 27.07.1992, 22.10.1995.
c VIT, 11.05.2005, updated to NDS 47(1986)797 (last NDS issue for A=208).
c VIT, 4.02.2009, updated to NDS 108(2007)1583; also were added:
c LM conversion electrons; more complex emission of X rays emitted in K conversion.
	thnuc=183.18
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.052) go to 4481   !  0.052%
	if(pbeta.le. 0.069) go to 4383   !  0.017%
	if(pbeta.le. 0.113) go to 4358   !  0.044%
	if(pbeta.le. 0.118) go to 4323   !  0.005%
	if(pbeta.le. 0.219) go to 4296   !  0.101%
	if(pbeta.le. 0.221) go to 4262   !  0.002%
	if(pbeta.le. 0.448) go to 4180   !  0.227%
	if(pbeta.le. 0.623) go to 4125   !  0.175%
	if(pbeta.le. 0.630) go to 3996   !  0.007%
	if(pbeta.le. 3.810) go to 3961   !  3.180%
	if(pbeta.le. 3.856) go to 3946   !  0.046%
	if(pbeta.le. 4.486) go to 3920   !  0.630%
	if(pbeta.le.28.686) go to 3708   ! 24.200%
	if(pbeta.le.50.886) go to 3475   ! 22.200%
	                    go to 3198   ! 49.114%
c-----------------------------------------------------------------------
4481	call beta(0.518,82.,0.,0.,t)
	thlev=0.
	call nucltransKLM_Pb(1.283,0.088,7.75e-3,0.015,1.27e-3,
     +                       0.004,0.41e-3,2.3e-5,tclev,thlev,tdlev)
	go to 31980
c-----------------------------------------------------------------------
4383	call beta(0.616,82.,0.,0.,t)
	thlev=0.
c	call nucltransK(1.185,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
	call nucltransKLM_Pb(1.185,0.088,9.49e-3,0.015,1.56e-3,
     +                       0.004,0.47e-3,4.9e-6,tclev,thlev,tdlev)
	go to 31980
c-----------------------------------------------------------------------
4358	call beta(0.641,82.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.55) go to 43581   !  4.55%
	if(p.le.29.55) go to 43582   ! 25.00%
	               go to 43583   ! 70.45%
c43581	call nucltransK(1.744,0.088,4.0e-3,1.5e-4,tclev,thlev,tdlev)
43581	call nucltransKLM_Pb(1.744,0.088,3.56e-3,0.015,0.58e-3,
     +                       0.004,0.17e-3,2.6e-4,tclev,thlev,tdlev)
	go to 26150
c43582	call nucltransK(1.161,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
43582	call nucltransKLM_Pb(1.161,0.088,9.99e-3,0.015,1.64e-3,
     +                       0.004,0.51e-3,2.6e-6,tclev,thlev,tdlev)
	go to 31980
c43583	call nucltransK(0.883,0.088,2.2e-2,0.,tclev,thlev,tdlev)
43583	call nucltransKLM_Pb(0.883,0.088,20.13e-3,0.015,3.33e-3,
     +                       0.004,1.02e-3,0.,tclev,thlev,tdlev)
	go to 34750
c-----------------------------------------------------------------------
4323	call beta(0.676,82.,0.,0.,t)
	thlev=0.
c	call nucltransK(1.126,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
	call nucltransKLM_Pb(1.126,0.088,1.69e-3,0.015,0.26e-3,
     +                       0.004,0.08e-3,2.1e-6,tclev,thlev,tdlev)
	go to 31980
c-----------------------------------------------------------------------
4296	call beta(0.703,82.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.87.23) go to 42961   ! 87.23%
	               go to 42962   ! 12.77%
c42961	call nucltransK(0.821,0.088,2.6e-2,0.,tclev,thlev,tdlev)
42961	call nucltransKLM_Pb(0.821,0.088,2.43e-2,0.015,0.40e-2,
     +                       0.004,0.12e-2,0.,tclev,thlev,tdlev)
	go to 34750
c42962	call nucltransK(0.588,0.088,6.5e-2,0.,tclev,thlev,tdlev)
42962	call nucltransKLM_Pb(0.588,0.088,5.78e-2,0.015,0.97e-2,
     +                       0.004,0.29e-2,0.,tclev,thlev,tdlev)
	go to 37080
c-----------------------------------------------------------------------
4262	call beta(0.737,82.,0.,0.,t)
	thlev=0.
c	call nucltransK(1.648,0.088,1.1e-2,0.3e-4,tclev,thlev,tdlev)
	call nucltransKLM_Pb(1.648,0.088,4.11e-3,0.015,0.67e-3,
     +                       0.004,0.20e-3,0.19e-3,tclev,thlev,tdlev)
	go to 26150
c-----------------------------------------------------------------------
4180	call beta(0.819,82.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.90.31) go to 41801   ! 90.31%
                       go to 41802   !  9.69%
c41801	call nucltransK(0.983,0.088,1.7e-2,0.,tclev,thlev,tdlev)
41801	call nucltransKLM_Pb(0.983,0.088,1.53e-2,0.015,0.25e-2,
     +                       0.004,0.08e-2,0.,tclev,thlev,tdlev)
	go to 31980
c41802	call nucltransK(0.705,0.088,4.0e-2,0.,tclev,thlev,tdlev)
41802	call nucltransKLM_Pb(0.705,0.088,3.60e-2,0.015,0.60e-2,
     +                       0.004,0.18e-2,0.,tclev,thlev,tdlev)
	go to 34750
c-----------------------------------------------------------------------
4125	call beta(0.874,82.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.96.15) go to 41251   ! 96.15%
	               go to 41252   !  3.85%
c41251	call nucltransK(0.928,0.088,1.9e-2,0.,tclev,thlev,tdlev)
41251	call nucltransKLM_Pb(0.928,0.088,1.77e-2,0.015,0.29e-2,
     +                       0.004,0.10e-2,0.,tclev,thlev,tdlev)
	go to 31980
c41252	call nucltransK(0.650,0.088,5.0e-2,0.,tclev,thlev,tdlev)
41252	call nucltransKLM_Pb(0.650,0.088,4.45e-2,0.015,0.75e-2,
     +                       0.004,0.22e-2,0.,tclev,thlev,tdlev)
	go to 34750
c-----------------------------------------------------------------------
3996	call beta(1.003,82.,0.,0.,t)
	thlev=0.
c	call nucltransK(1.381,0.088,8.0e-3,0.6e-4,tclev,thlev,tdlev)
	call nucltransKLM_Pb(1.381,0.088,6.43e-3,0.015,1.05e-3,
     +                       0.004,0.32e-3,0.05e-3,tclev,thlev,tdlev)
	go to 26150
c-----------------------------------------------------------------------
3961	call beta(1.038,82.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.51.25) go to 39611   ! 51.25%
	if(p.le.64.82) go to 39612   ! 13.57%
                       go to 39613   ! 35.18%
c39611	call nucltransK(0.763,0.088,3.8e-2,0.,tclev,thlev,tdlev)
39611	call nucltransKLM_Pb(0.763,0.088,2.93e-2,0.015,0.49e-2,
     +                       0.004,0.14e-2,0.,tclev,thlev,tdlev)
	go to 31980
c39612	call nucltransK(0.486,0.088,0.21,0.,tclev,thlev,tdlev)
39612	call nucltransKLM_Pb(0.486,0.088,9.54e-2,0.015,1.61e-2,
     +                       0.004,0.49e-2,0.,tclev,thlev,tdlev)
	go to 34750
c39613	call nucltransK(0.253,0.088,0.71,0.,tclev,thlev,tdlev)
39613	call nucltransKLM_Pb(0.253,0.088,51.60e-2,0.015,8.83e-2,
     +                       0.004,2.57e-2,0.,tclev,thlev,tdlev)
	go to 37080
c-----------------------------------------------------------------------
3946	call beta(1.053,82.,0.,0.,t)
	thlev=0.
c	call nucltransK(0.749,0.088,3.5e-2,0.,tclev,thlev,tdlev)
	call nucltransKLM_Pb(0.749,0.088,3.08e-2,0.015,0.51e-2,
     +                       0.004,0.16e-2,0.,tclev,thlev,tdlev)
	go to 31980
c-----------------------------------------------------------------------
3920	call beta(1.079,82.,0.,0.,t)
	thlev=0.
	p=100.*rnd1(d)
	if(p.le.39.49) go to 39201   ! 39.49%
                       go to 39202   ! 60.51%
c39201	call nucltransK(0.722,0.088,4.1e-2,0.,tclev,thlev,tdlev)
39201	call nucltransKLM_Pb(0.722,0.088,3.20e-2,0.015,0.54e-2,
     +                       0.004,0.16e-2,0.,tclev,thlev,tdlev)
	go to 31980
c39202	call nucltransK(0.211,0.088,1.17,0.,tclev,thlev,tdlev)
39202	call nucltransKLM_Pb(0.211,0.088,9.22e-1,0.015,1.59e-1,
     +                       0.004,0.45e-1,0.,tclev,thlev,tdlev)
	go to 37080
c-----------------------------------------------------------------------
3708	call beta(1.291,82.,0.,0.,t)
37080	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.66) go to 37081   !  1.66%
	if(p.le.97.95) go to 37082   ! 96.29%
	               go to 37083   !  2.05%
c37081	call nucltransK(1.094,0.088,0.6e-2,0.,tclev,thlev,tdlev)
37081	call nucltransKLM_Pb(1.094,0.088,4.49e-3,0.015,0.84e-3,
     +                       0.004,0.27e-3,0.,tclev,thlev,tdlev)
	go to 26150
c37082	call nucltransK(0.511,0.088,0.107,0.,tclev,thlev,tdlev)
37082	call nucltransKLM_Pb(0.511,0.088,8.42e-2,0.015,1.42e-2,
     +                       0.004,0.43e-2,0.,tclev,thlev,tdlev)
	go to 31980
c37083	call nucltransK(0.233,0.088,0.888,0.,tclev,thlev,tdlev)
37083	call nucltransKLM_Pb(0.233,0.088,5.47e-1,0.015,1.16e-1,
     +                       0.004,0.37e-1,0.,tclev,thlev,tdlev)
	go to 34750
c-----------------------------------------------------------------------
3475	call beta(1.524,82.,0.,0.,t)
34750	thlev=4.e-12
	p=100.*rnd1(d)
	if(p.le.55.95) go to 34751   ! 55.95%
	               go to 34752   ! 44.05%
c34751	call nucltransK(0.861,0.088,2.8e-2,0.,tclev,thlev,tdlev)
34751	call nucltransKLM_Pb(0.861,0.088,2.17e-2,0.015,0.36e-2,
     +                       0.004,0.11e-2,0.,tclev,thlev,tdlev)
	go to 26150
c34752	call nucltransK(0.277,0.088,0.551,0.,tclev,thlev,tdlev)
34752	call nucltransKLM_Pb(0.277,0.088,4.36e-1,0.015,0.75e-1,
     +                       0.004,0.22e-1,0.,tclev,thlev,tdlev)
	go to 31980
c-----------------------------------------------------------------------
3198	call beta(1.801,82.,0.,0.,t)
31980	thlev=294.e-12
c	call nucltransK(0.583,0.088,2.1e-2,0.,tclev,thlev,tdlev)
	call nucltransKLM_Pb(0.583,0.088,1.51e-2,0.015,0.41e-2,
     +                       0.004,0.13e-2,0.,tclev,thlev,tdlev)
	go to 26150
c-----------------------------------------------------------------------
26150	thlev=16.7e-12
c	call nucltransK(2.615,0.088,8.5e-3,4.3e-4,tclev,thlev,tdlev)
c change in accordance with NNDC-ENSDF on 19.12.2006; confirmed on 23.01.2009
c	call nucltransK(2.615,0.088,2.47e-3,4.3e-4,tclev,thlev,tdlev)
	call nucltransKLM_Pb(2.615,0.088,1.71e-3,0.015,0.29e-3,
     +                       0.004,0.10e-3,0.37e-3,tclev,thlev,tdlev)
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Xe129m(tcnuc,tdnuc)
c Scheme of Xe129m decay (NDS 77(1996)631 and ENSDF at NNDC site on 
c 13.11.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.11.2007.
	thnuc=767232.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
c-----------------------------------------------------------------------
23600	thlev=0.
	call nucltransKLM(0.197,0.035,13.94,0.005,5.34,0.001,1.52,
     +                    0.,tclev,thlev,tdlev)
	go to 40000
c-----------------------------------------------------------------------
40000	thlev=0.97e-9
	call nucltransKLM(0.040,0.035,10.49,0.005,1.43,0.001,0.39,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Xe131m(tcnuc,tdnuc)
c Scheme of Xe129m decay (NDS 107(2006)2715 and ENSDF at NNDC site on 
c 13.11.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.11.2007.
	thnuc=1.022976e+6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
c-----------------------------------------------------------------------
16400	thlev=0.
	call nucltransKLM(0.164,0.035,31.60,0.005,14.75,0.001,4.15,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Xe133(tcnuc,tdnuc)
c Scheme of Xe133 decay ("Table of Isotopes", 8th ed., 1996).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 18.08.1997. Updated 5.12.2003 in accordance with NDS 75(1995)491.
	thnuc=452995.2
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le. 0.008) go to 384
	if(pbeta.le. 0.818) go to 161
	                    go to  81
c-----------------------------------------------------------------------
384	call beta(0.044,55.,0.,0.,t)
38400	thlev=21.e-12
	p=100.*rnd1(d)
	if(p.le.32.313) go to 38401
	if(p.le.98.259) go to 38402
	                go to 38403
38401	call nucltransK(0.384,0.036,2.0e-2,0.,tclev,thlev,tdlev)
	return
38402	call nucltransK(0.303,0.036,4.4e-2,0.,tclev,thlev,tdlev)
	go to 81000
38403	call nucltransK(0.223,0.036,9.8e-2,0.,tclev,thlev,tdlev)
	go to 16100
c-----------------------------------------------------------------------
161	call beta(0.267,55.,0.,0.,t)
16100	thlev=172.e-12
	p=100.*rnd1(d)
	if(p.le.10.287) go to 16101
	                go to 16102
16101	call nucltransK(0.161,0.036,3.0e-1,0.,tclev,thlev,tdlev)
	return
16102	call nucltransK(0.080,0.036,1.8e+0,0.,tclev,thlev,tdlev)
	go to 81000
c-----------------------------------------------------------------------
81	call beta(0.346,55.,0.,0.,t)
81000	thlev=6.28e-9
	call nucltransK(0.081,0.036,1.7e+0,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Xe135(tcnuc,tdnuc)
c Model of Xe135 decay (Yu.V.Sergeenkov et al., Nucl. Data Sheets 
c 84(1998)115).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 9.10.2002.
	thnuc=32904.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.0.123) go to 1062 !  0.123%%
	if(pbeta.le.0.198) go to  981 !  0.075%
	if(pbeta.le.3.311) go to  608 !  3.113%
	if(pbeta.le.3.902) go to  408 !  0.591%
	                   go to  250 ! 96.098%
c-----------------------------------------------------------------------
1062	call beta(0.089,55.,0.,0.,t)
10620	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 3.34) go to 10621   !  3.34%
	if(p.le.60.40) go to 10622   ! 57.06%
	if(p.le.97.07) go to 10623   ! 36.67%
	               go to 10624   !  2.93%
10621	call nucltransK(1.062,0.036,2.0e-3,0.,tclev,thlev,tdlev)
	return
10622	call nucltransK(0.813,0.036,3.8e-3,0.,tclev,thlev,tdlev)
	go to 25000
10623	call nucltransK(0.654,0.036,6.5e-3,0.,tclev,thlev,tdlev)
	go to 40800
10624	call nucltransK(0.454,0.036,1.5e-2,0.,tclev,thlev,tdlev)
	go to 60800
c-----------------------------------------------------------------------
981	call beta(0.170,55.,0.,0.,t)
98100	thlev=0.
	p=100.*rnd1(d)
	if(p.le.73.53) go to 98101   ! 73.53%
	if(p.le.79.95) go to 98102   !  6.42%
	               go to 98103   ! 20.05%
98101	call nucltransK(0.732,0.036,5.0e-3,0.,tclev,thlev,tdlev)
	go to 25000
98102	call nucltransK(0.573,0.036,9.0e-3,0.,tclev,thlev,tdlev)
	go to 40800
98103	call nucltransK(0.373,0.036,2.5e-2,0.,tclev,thlev,tdlev)
	go to 60800
c-----------------------------------------------------------------------
608	call beta(0.543,55.,0.,0.,t)
60800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.92.42) go to 60801   ! 92.42%
	if(p.le.99.62) go to 60802   !  7.20%
	               go to 60803   !  0.38%
60801	call nucltransK(0.608,0.036,7.5e-3,0.,tclev,thlev,tdlev)
	return
60802	call nucltransK(0.358,0.036,2.7e-2,0.,tclev,thlev,tdlev)
	go to 25000
60803	call nucltransK(0.200,0.036,1.4e-1,0.,tclev,thlev,tdlev)
	go to 40800
c-----------------------------------------------------------------------
408	call beta(0.743,55.,0.,0.,t)
40800	thlev=0.
	p=100.*rnd1(d)
	if(p.le.55.33) go to 40801   ! 55.33%
	               go to 40802   ! 44.67%
40801	call nucltransK(0.408,0.036,2.0e-2,0.,tclev,thlev,tdlev)
	return
40802	call nucltransK(0.158,0.036,2.5e-1,0.,tclev,thlev,tdlev)
	go to 25000
c-----------------------------------------------------------------------
250	call beta(0.901,55.,0.,0.,t)
25000	thlev=0.28e-9
	call nucltransK(0.250,0.036,7.6e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Y88(tcnuc,tdnuc)
c Scheme of Y88 decay ("Table of Isotopes", 7th ed., 1978).
c Accuracy in description of: decay branches       - 0.001%,
c                           : deexcitation process - 0.001%.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 20.07.1993, 22.10.1995.
c VIT, 12.11.2006 (update to NDS 105(2005)419 and change of beta+ spectrum 
c shape)
	thnuc=9.2124864e+6
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pdecay=100.*rnd1(d)
	if(pdecay.le.99.79) go to 1
	                    go to 2
c-----------------------------------------------------------------------
c EC to Sr88
1	call gamma(0.016,0.,0.,t)
	pec=pdecay
	if(pec.le. 0.065) go to 35850
	if(pec.le. 0.093) go to 32190
	if(pec.le.94.490) go to 27340
	                  go to 18360
c-----------------------------------------------------------------------
c b+ to Sr88
c2	call beta(0.765,-38.,0.,0.,t)
c change to the approximation to the 1st forbidden unique shape 
2	call beta2(0.765,-38.,0.,0.,t,1,1.,0.,0.,0.)
	go to 18360
c-----------------------------------------------------------------------
35850	thlev=0.14e-9
	call nucltransK(0.851,0.016,8.5e-4,0.,tclev,thlev,tdlev)
	go to 27340
c-----------------------------------------------------------------------
32190	thlev=0.13e-12
	p=100.*rnd1(d)
	if(p.le.25.) go to 32191
	             go to 32192
32191	call nucltransK(3.219,0.016,6.0e-5,8.7e-4,tclev,thlev,tdlev)
	return
32192	call nucltransK(1.382,0.016,2.6e-4,4.8e-5,tclev,thlev,tdlev)
	go to 18360
c-----------------------------------------------------------------------
27340	thlev=0.78e-12
	p=100.*rnd1(d)
	if(p.le.0.75) go to 27341
	              go to 27342
27341	call nucltransK(2.734,0.016,1.2e-4,3.3e-4,tclev,thlev,tdlev)
	return
27342	call nucltransK(0.898,0.016,3.1e-4,0.,tclev,thlev,tdlev)
	go to 18360
c-----------------------------------------------------------------------
18360	thlev=0.148e-12
	call nucltransK(1.836,0.016,1.4e-4,2.3e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Y90(tcnuc,tdnuc)
c Scheme of Y90 decay ("Table of Isotopes", 7th ed., 1978).
c Accuracy in description of: decay branches       - 0.001%,
c                           : deexcitation process - 0.001%.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c Slight update to NDS 82(1997)379.
c VIT, 9.08.1993, 22.10.1995, 26.10.2006; 27.02.2007.
	thnuc=230400.
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbeta=100.*rnd1(d)
	if(pbeta.le.0.0115) go to  1761
	                    go to 10000
c-----------------------------------------------------------------------
c1761	call beta(0.523,40.,0.,0.,t)
1761	call beta_1fu(0.519,40.,0.,0.,t,0.,0.,0.,0.)
17610	thlev=61.3e-9
	p=100.*rnd1(d)
c to reproduce 31.86e-6 branching ratio for e+e- pair, 
c R.G.Selwyn et al., Appl. Rad. Isot. 65(2007)318
	if(p.le.27.7) go to 17611
	              go to 17612
17611	call pair(0.739,tclev,thlev,tdlev)
	return
17612	call electron(1.743,tclev,thlev,tdlev)
	call gamma(0.018,0.,0.,tdlev)
	return
c-----------------------------------------------------------------------
c10000	call beta(2.284,40.,0.,0.,t)
c Change from the allowed shape to the 1st forbidden unique with empirical
c correction from: H.H.Hansen, Appl. Rad. Isot. 34(1983)1241
10000	call beta_1fu(2.280,40.,0.,0.,t,0.,-0.0078,0.,0.)
	return
c-----------------------------------------------------------------------
	end

c***********************************************************************

	subroutine Zn65(tcnuc,tdnuc)
c Scheme of Zn65 decay (NDS 69(1993)209 and NNDC online corrections on 28.03.2007).
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.03.2007.
	thnuc=2.1086784E+07
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	tclev=0.
	pbec=100.*rnd1(d)
	if(pbec.le.1.42) go to 1
	                 go to 2
c beta+ decay to g.s. of 65-Cu
1	call pair(0.329,0.,0.,tdlev)
	return
c X ray after EC to 65-Cu
2	call gamma(0.009,0.,0.,t)
	if(pbec.le.52.03) go to 11160
	                  go to 10000
c-----------------------------------------------------------------------
11160	thlev=0.285e-12
	p=100.*rnd1(d)
	if(p.le.99.994) go to 11161
	                go to 11162
11161	call nucltransK(1.116,0.009,1.9e-4,1.0e-6,tclev,thlev,tdlev)
	return
11162	call nucltransK(0.345,0.009,6.8e-3,0.,tclev,thlev,tdlev)
	go to 77100
c-----------------------------------------------------------------------
77100	thlev=99.e-15
	call nucltransK(0.771,0.009,3.8e-4,0.,tclev,thlev,tdlev)
c-----------------------------------------------------------------------
10000	return
	end

c***********************************************************************

	subroutine Zr96(tcnuc,tdnuc)
c Scheme of Zr96 beta decay.
c It is supposed that decay goes to the first excited level (5+) of Nb96
c (E_exc=44 keV) with T1/2=2.4e20 y in accordance with: H.Heiskanen et al.,
C JPG 34(2007)837. Transition to the ground state (6+) is suppressed by 
c factor of ~1e-9, to the excited 4+ (E_exc=146 keV) - by 1e-2.
c Input : tcnuc - time of creation of nucleus (sec);
c Output: tdnuc - time of decay of nucleus (sec);
c         common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 07.05.1998.
c VIT, 18.08.2007: update to NDS 68(1993)165 and ENSDF at NNDC site.
	thnuc=7.574e27
	tdnuc=tcnuc-thnuc/alog(2.)*alog(rnd1(d))
	call beta(0.117,41.,0.,0.,t)
	tclev=0.
	thlev=0.
	call nucltransK(0.044,0.019,2.4e0,0.,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

c***********************************************************************
c***************** Section of daughter 2b isotopes *********************
c***********************************************************************

c***********************************************************************

	subroutine Ar40low(levelkeV)
c Subroutine describes the deexcitation process in Ar40 nucleus
c after 2e-decay of Ca40 to ground 0+ level
c of Ar40 (ENSDF on 21.10.2013).
c Call  : call Ar40low(levelkeV)
c Input : levelkeV - energy of Ar40 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 22.10.2013.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ar40: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ti46low(levelkeV)
c Subroutine describes the deexcitation process in Ti46 nucleus
c after 2b-decay of Ca46 to ground 0+ and excited 2+ levels
c of Ti46 (ENSDF on 21.10.2013).
c Call  : call Ti46low(levelkeV)
c Input : levelkeV - energy of Ti46 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -   0 keV,
c                    2+(1)  - 889 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 22.10.2013.
	tclev=0.
	if(levelkev.eq.889) go to   889
	if(levelkev.eq.  0) go to 10000
	                    go to 20000
c-----------------------------------------------------------------------
889	thlev=5.32e-12
	call nucltransK(0.889,0.005,1.7e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ti46: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ti48low(levelkeV)
c Subroutine describes the deexcitation process in Ti48 nucleus
c after 2b-decay of Ca48 to ground and excited 0+ and 2+ levels
c of Ti48 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ti48low(levelkeV)
c Input : levelkeV - energy of Ti48 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  984 keV,
c                    2+(2)  - 2421 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 19.07.1993, 22.10.1995.
	tclev=0.
	if(levelkev.eq.2421) go to  2421
	if(levelkev.eq. 984) go to   984
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2421	thlev=24.e-15
	p=100.*rnd1(d)
	if(p.le.8.) go to 24211
	            go to 24212
24211	call nucltransK(2.421,0.005,1.5e-5,5.0e-4,tclev,thlev,tdlev)
	return
24212	call nucltransK(1.437,0.005,3.1e-5,1.8e-4,tclev,thlev,tdlev)
	go to 984
c-----------------------------------------------------------------------
984	thlev=4.3e-12
	call nucltransK(0.984,0.005,1.2e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ti48: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Fe58low(levelkeV)
c Subroutine describes the deexcitation process in Fe58 nucleus
c after 2b-decay of Ni58 to ground and excited 0+ and 2+ levels
c of Fe58 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Fe58low(levelkeV)
c Input : levelkeV - energy of Fe58 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  811 keV,
c                    2+(2)  - 1675 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995.
	tclev=0.
	if(levelkev.eq.1675) go to  1675
	if(levelkev.eq. 811) go to   811
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1675	thlev=0.
	p=100.*rnd1(d)
	if(p.le.43.) go to 16751
	             go to 16752
16751	call nucltransK(1.675,0.007,1.0e-4,0.6e-4,tclev,thlev,tdlev)
	return
16752	call nucltransK(0.864,0.007,3.0e-4,0.,tclev,thlev,tdlev)
	go to 811
c-----------------------------------------------------------------------
811	thlev=9.0e-12
	call nucltransK(0.811,0.007,5.0e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Fe58: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ni64low(levelkeV)
c Subroutine describes the deexcitation process in Ni64 nucleus
c after 2b-decay of Zn64 to ground and excited 0+ and 2+ levels
c of Ni64 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ni64low(levelkeV)
c Input : levelkeV - energy of Ni64 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.02.2004.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ni64: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ge70low(levelkeV)
c Subroutine describes the deexcitation process in Ge70 nucleus
c after 2b-decay of Zn70 to ground and excited 0+ and 2+ levels
c of Ge70 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ge70low(levelkeV)
c Input : levelkeV - energy of Ge70 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.02.2004.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ge70: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Se76low(levelkeV)
c Subroutine describes the deexcitation process in Se76 nucleus
c after 2b-decay of Ge76 to ground and excited 0+ and 2+ levels
c of Se76 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Se76low(levelkeV)
c Input : levelkeV - energy of Se76 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  559 keV,
c                    0+(1)  - 1122 keV,
c                    2+(2)  - 1216 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 19.07.1993, 22.10.1995.
c Luciano Pandola, 25.10.2006: angular correlation of 563 and 559 keV gamma
c quanta if 1122 keV level is populated.
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	npg563=0
	npg559=0
	tclev=0.
	if(levelkev.eq.1216) go to  1216
	if(levelkev.eq.1122) go to  1122
	if(levelkev.eq. 559) go to   559
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1216	thlev=3.4e-12
	p=100.*rnd1(d)
	if(p.le.36.) go to 12161
	             go to 12162
12161	call nucltransK(1.216,0.013,4.3e-4,0.1e-4,tclev,thlev,tdlev)
	return
12162	call nucltransK(0.657,0.013,2.1e-3,0.,tclev,thlev,tdlev)
	go to 559
c-----------------------------------------------------------------------
1122	thlev=11.e-12
c	call nucltransK(0.563,0.013,2.0e-3,0.,tclev,thlev,tdlev)
	Egamma=0.563
	EbindK=0.013
	cg=1.
	cK=2.0e-3
	p=rndm(d)*(cg+cK)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg563=npfull
	else 
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call gamma(EbindK,0.,0.,tdlev)
	end if
	go to 559
c-----------------------------------------------------------------------
559	thlev=12.3e-12
c	call nucltransK(0.559,0.013,2.0e-3,0.,tclev,thlev,tdlev)
	Egamma=0.559
	EbindK=0.013
	cg=1.
	cK=2.0e-3
	p=rndm(d)*(cg+cK)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg559=npfull
	else 
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call gamma(EbindK,0.,0.,tdlev)
	end if
c Angular correlation between gammas 559 and 563 keV, L.Pandola + VIT
	if(npg559.ne.0.and.npg563.ne.0) then 
	   p559=sqrt(pmoment(1,npg559)**2+pmoment(2,npg559)**2+
     +               pmoment(3,npg559)**2)
	   p563=sqrt(pmoment(1,npg563)**2+pmoment(2,npg563)**2+
     +               pmoment(3,npg563)**2)
c Coefficients in formula 1+a2*ctet**2+a4*ctet**4 are from:
c R.D.Evans, "The Atomic Nucleus", Krieger Publ. Comp., 1985, p. 240, 
c 0(2)2(2)0 cascade.
	   a2=-3.0
	   a4=4.0
	   twopi=6.2831853
1	   phi1=twopi*rndm(d)
	   ctet1=1.-2.*rndm(d)
	   stet1=sqrt(1.-ctet1*ctet1)
	   phi2=twopi*rndm(d)
	   ctet2=1.-2.*rndm(d)
	   stet2=sqrt(1.-ctet2*ctet2)
	   ctet=ctet1*ctet2+stet1*stet2*cos(phi1-phi2)
	   if(rndm(d)*(1.+abs(a2)+abs(a4)).gt.1.+a2*ctet**2+a4*ctet**4) 
     +        go to 1 
	   pmoment(1,npg559)=p559*stet1*cos(phi1)
	   pmoment(2,npg559)=p559*stet1*sin(phi1)
	   pmoment(3,npg559)=p559*ctet1
	   pmoment(1,npg563)=p563*stet2*cos(phi2)
	   pmoment(2,npg563)=p563*stet2*sin(phi2)
	   pmoment(3,npg563)=p563*ctet2
	endif
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Se76: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ge74low(levelkeV)
c Subroutine describes the deexcitation process in Ge74 nucleus
c after 2b-decay of Se74 to ground and excited 0+ and 2+ levels
c of Ge74 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ge74low(levelkeV)
c Input : levelkeV - energy of Ge74 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  596 keV,
c                    2+(2)  - 1204 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995.
	tclev=0.
	if(levelkev.eq.1204) go to  1204
	if(levelkev.eq. 596) go to   596
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1204	thlev=6.0e-12
	p=100.*rnd1(d)
	if(p.le.34.) go to 12041
	             go to 12042
12041	call nucltransK(1.204,0.011,1.9e-4,0.1e-4,tclev,thlev,tdlev)
	return
12042	call nucltransK(0.608,0.011,1.1e-3,0.,tclev,thlev,tdlev)
	go to 596
c-----------------------------------------------------------------------
596	thlev=12.0e-12
	call nucltransK(0.596,0.011,1.1e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ge74: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Kr82low(levelkeV)
c Subroutine describes the deexcitation process in Kr82 nucleus
c after 2b-decay of Se82 to ground and excited 0+ and 2+ levels
c of Kr82 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Kr82low(levelkeV)
c Input : levelkeV - energy of Kr82 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  776 keV,
c                    2+(2)  - 1475 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.1993, 22.10.1995.
	tclev=0.
	if(levelkev.eq.1475) go to  1475
	if(levelkev.eq. 776) go to   776
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1475	thlev=0.
	p=100.*rnd1(d)
	if(p.le.36.7) go to 14751
	              go to 14752
14751	call nucltransK(1.475,0.014,2.0e-4,0.5e-4,tclev,thlev,tdlev)
	return
14752	call nucltransK(0.698,0.014,1.3e-3,0.,tclev,thlev,tdlev)
	go to 776
c-----------------------------------------------------------------------
776	thlev=5.e-12
	call nucltransK(0.776,0.014,9.3e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Kr82: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Kr84low(levelkeV)
c Subroutine describes the deexcitation process in Kr84 nucleus
c after 2b-decay of Sr84 to ground and excited 0+ and 2+ levels
c of Kr84 ("Table of Isotopes", 8th ed., 1998 and NNDC site on 22.12.2008).
c Call  : call Kr84low(levelkeV)
c Input : levelkeV - energy of Kr84 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  882 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 22.12.2008.
	tclev=0.
	if(levelkev.eq.882) go to   882
	if(levelkev.eq.  0) go to 10000
	                    go to 20000
c-----------------------------------------------------------------------
882	thlev=4.35e-12
	call nucltransK(0.882,0.014,6.8e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Kr84: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Mo94low(levelkeV)
c Subroutine describes the deexcitation process in Mo94 nucleus
c after 2b-decay of Zr94 to ground and excited 0+ and 2+ levels
c of Mo94 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Mo94low(levelkeV)
c Input : levelkeV - energy of Mo94 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  871 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995.
	tclev=0.
	if(levelkev.eq. 871) go to   871
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
871	thlev=2.9e-12
	call nucltransK(0.871,0.020,9.5e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Mo94: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Mo96low(levelkeV)
c Subroutine describes the deexcitation process in Mo96 nucleus
c after 2b- decay of Zr96 and 2b+/eb+/2e decay of Ru96 to ground and 
c excited 0+ and 2+ levels c of Mo96 ("Table of Isotopes", 7th ed., 1978).
c VIT, 20.05.2009: four levels (2096, 2426, 2623 and 2700 keV) are added 
c and information is updated in accordance with NNDC site on 19.05.2009 and 
c NDS 109(2008)2501.
c Call  : call Mo96low(levelkeV)
c Input : levelkeV - energy of Mo96 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  778 keV,
c                    0+(1)  - 1148 keV,
c                    2+(2)  - 1498 keV,
c                    2+(3)  - 1626 keV,
c                    2+(4)  - 2096 keV,
c                    2+(5)  - 2426 keV,
c                    0+(2)  - 2623 keV,
c                    2+(6)  - 2700 keV,
c                    2+(7)  - 2713 keV (in fact spin and parity of this level
c                             are unknown).
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.1993, 22.10.1995, 20.05.2009.
	tclev=0.
	if(levelkev.eq.2713) go to  2713
	if(levelkev.eq.2700) go to  2700
	if(levelkev.eq.2623) go to  2623
	if(levelkev.eq.2426) go to  2426
	if(levelkev.eq.2096) go to  2096
	if(levelkev.eq.1626) go to  1626
	if(levelkev.eq.1498) go to  1498
	if(levelkev.eq.1148) go to  1148
	if(levelkev.eq. 778) go to   778
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2713	thlev=0.
c 2+ to 6+ E4 transition is supposed
27131	call nucltransK(0.272,0.020,5.9e-1,0.,tclev,thlev,tdlev)
	go to 2441
c-----------------------------------------------------------------------
2700	thlev=0.103e-12
	p=100.*rnd1(d)
	if(p.le. 3.04) go to 27001
	if(p.le.12.12) go to 27002
	if(p.le.53.40) go to 27003
	if(p.le.86.67) go to 27004
	               go to 27005
27001	call nucltransK(0.160,0.020,6.9e-2,0.,tclev,thlev,tdlev)
	go to 2540
27002	call nucltransK(1.074,0.020,6.7e-4,0.,tclev,thlev,tdlev)
	go to 1626
27003	call nucltransK(1.202,0.020,5.5e-4,0.,tclev,thlev,tdlev)
	go to 1498
27004	call nucltransK(1.922,0.020,2.1e-4,2.5e-4,tclev,thlev,tdlev)
	go to 778
27005	call nucltransK(2.701,0.020,1.1e-4,6.4e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
2623	thlev=0.6e-12
26231	call nucltransK(1.844,0.020,2.2e-4,2.3e-4,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
2540	thlev=0.069e-12
	p=100.*rnd1(d)
	if(p.le. 8.17) go to 25401
	if(p.le.28.31) go to 25402
	               go to 25403
25401	call nucltransK(0.915,0.020,9.7e-4,0.,tclev,thlev,tdlev)
	go to 1626
25402	call nucltransK(1.043,0.020,7.3e-4,0.,tclev,thlev,tdlev)
	go to 1498
25403	call nucltransK(1.762,0.020,2.5e-4,1.7e-4,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
2441	thlev=0.208e-12
24411	call nucltransK(0.813,0.020,1.3e-3,0.,tclev,thlev,tdlev)
	go to 1628
c-----------------------------------------------------------------------
2426	thlev=0.19e-12
	p=100.*rnd1(d)
	if(p.le. 2.50) go to 24261
	if(p.le.38.16) go to 24262
	if(p.le.42.07) go to 24263
	if(p.le.95.22) go to 24264
	               go to 24265
24261	call nucltransK(0.448,0.020,6.4e-3,0.,tclev,thlev,tdlev)
	go to 1978
24262	call nucltransK(0.800,0.020,1.3e-3,0.,tclev,thlev,tdlev)
	go to 1626
24263	call nucltransK(0.928,0.020,9.2e-4,0.,tclev,thlev,tdlev)
	go to 1498
24264	call nucltransK(1.648,0.020,2.9e-4,1.2e-4,tclev,thlev,tdlev)
	go to 778
24265	call nucltransK(2.426,0.020,1.4e-4,5.1e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
2096	thlev=0.097e-12
	p=100.*rnd1(d)
	if(p.le. 3.06) go to 20961
	if(p.le.98.55) go to 20962
	               go to 20963
20961	call nucltransK(0.948,0.020,8.7e-4,0.,tclev,thlev,tdlev)
	go to 1148
20962	call nucltransK(1.317,0.020,4.4e-4,2.5e-5,tclev,thlev,tdlev)
	go to 778
20963	call nucltransK(2.096,0.020,1.8e-4,3.5e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1978	thlev=2.29e-12
	p=100.*rnd1(d)
	if(p.le. 0.18) go to 19781
	if(p.le. 5.96) go to 19782
	if(p.le. 9.27) go to 19783
	if(p.le.30.34) go to 19784
	               go to 19785
19781	call nucltransK(0.109,0.020,2.0e-1,0.,tclev,thlev,tdlev)
	go to 1870
19782	call nucltransK(0.350,0.020,1.2e-2,0.,tclev,thlev,tdlev)
	go to 1628
19783	call nucltransK(0.353,0.020,1.2e-2,0.,tclev,thlev,tdlev)
	go to 1626
19784	call nucltransK(0.481,0.020,4.3e-3,0.,tclev,thlev,tdlev)
	go to 1498
19785	call nucltransK(1.200,0.020,5.4e-4,6.1e-6,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
1870	thlev=6.4e-12
	p=100.*rnd1(d)
	if(p.le. 7.52) go to 18701
	if(p.le.12.22) go to 18702
	               go to 18703
18701	call nucltransK(0.241,0.020,2.4e-2,0.,tclev,thlev,tdlev)
	go to 1628
18702	call nucltransK(0.372,0.020,1.2e-2,0.,tclev,thlev,tdlev)
	go to 1498
18703	call nucltransK(1.091,0.020,6.4e-4,0.,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
1628	thlev=1.2e-12
16281	call nucltransK(0.850,0.020,1.1e-3,0.,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
1626	thlev=1.4e-12
	p=100.*rnd1(d)
	if(p.le. 8.47) go to 16261
	if(p.le.98.58) go to 16262
	               go to 16263
16261	call nucltransK(1.626,0.020,2.8e-4,1.3e-4,tclev,thlev,tdlev)
	return
16262	call nucltransK(0.848,0.020,1.2e-3,0.,tclev,thlev,tdlev)
	go to 778
16263	call nucltransK(0.128,0.020,1.3e-1,0.,tclev,thlev,tdlev)
	go to 1498
c-----------------------------------------------------------------------
1498	thlev=0.78e-12
	p=100.*rnd1(d)
	if(p.le.29.73) go to 14981
	               go to 14982
14981	call nucltransK(1.498,0.020,3.3e-4,8.3e-5,tclev,thlev,tdlev)
	return
14982	call nucltransK(0.720,0.020,1.7e-3,0.,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
1148	thlev=61.e-12
11481	call nucltransK(0.370,0.020,1.2e-2,0.,tclev,thlev,tdlev)
	go to 778
c-----------------------------------------------------------------------
778	thlev=3.67e-12
	call nucltransK(0.778,0.020,1.4e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Mo96: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Zr92low(levelkeV)
c Subroutine describes the deexcitation process in Zr92 nucleus
c after 2b-decay of Mo92 to ground and excited 0+ and 2+ levels
c of Zr92 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Zr92low(levelkeV)
c Input : levelkeV - energy of Zr92 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  934 keV,
c                    2+(2)  - 1383 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995.
	tclev=0.
	if(levelkev.eq.1383) go to  1383
	if(levelkev.eq. 934) go to   934
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1383	thlev=0.17e-9
	call nucltransK(0.449,0.018,5.5e-3,0.,tclev,thlev,tdlev)
	go to 934
c-----------------------------------------------------------------------
934	thlev=5.0e-12
	call nucltransK(0.934,0.018,8.0e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Zr92: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ru100low(levelkeV)
c Subroutine describes the deexcitation process in Ru100 nucleus
c after 2b-decay of Mo100 to ground and excited 0+ and 2+ levels
c of Ru100 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ru100low(levelkeV)
c Input : levelkeV - energy of Ru100 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  540 keV,
c                    0+(1)  - 1130 keV,
c                    2+(2)  - 1362 keV,
c                    0+(2)  - 1741 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.1993, 22.10.1995.
c VIT, 19.05.2009: angular correlation of 591 and 540 keV gamma quanta
c if 1130 keV level is populated.
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	npg591=0
	npg540=0
	tclev=0.
	if(levelkev.eq.1741) go to  1741
	if(levelkev.eq.1362) go to  1362
	if(levelkev.eq.1130) go to  1130
	if(levelkev.eq. 540) go to   540
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1741	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.05) go to 17411
	if(p.le.59.00) go to 17412
	if(p.le.59.03) go to 17413
	               go to 17414
17411	call electron(1.741-0.022,tclev,thlev,tdlev)    ! only ec
	call gamma(0.022,0.,0.,tdlev)
	return
17412	call nucltransK(1.201,0.022,6.2e-4,0.1e-4,tclev,thlev,tdlev)
	go to 540
17413	call electron(0.611-0.022,tclev,thlev,tdlev)    ! only ec
	call gamma(0.022,0.,0.,tdlev)
	go to 1130
17414	call nucltransK(0.379,0.022,1.3e-2,0.,tclev,thlev,tdlev)
	go to 1362
c-----------------------------------------------------------------------
1362	thlev=1.2e-12
	p=100.*rnd1(d)
	if(p.le.43.) go to 13621
	             go to 13622
13621	call nucltransK(1.362,0.022,4.2e-4,0.2e-4,tclev,thlev,tdlev)
	return
13622	call nucltransK(0.822,0.022,1.7e-3,0.,tclev,thlev,tdlev)
	go to 540
c-----------------------------------------------------------------------
1130	thlev=0.
	p=100.*rnd1(d)
	if(p.le.0.02) go to 11301
	              go to 11302
11301	call electron(1.130-0.022,tclev,thlev,tdlev) ! only ec
	call gamma(0.022,0.,0.,tdlev)
	return
c11302	call nucltransK(0.591,0.022,3.3e-3,0.,tclev,thlev,tdlev)
11302	Egamma=0.591
	EbindK=0.022
	cg=1.
	cK=3.3e-3
	p=rndm(d)*(cg+cK)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg591=npfull
	else 
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call gamma(EbindK,0.,0.,tdlev)
	end if
	go to 540
c-----------------------------------------------------------------------
540	thlev=11.e-12
c	call nucltransK(0.540,0.022,4.4e-3,0.,tclev,thlev,tdlev)
	Egamma=0.540
	EbindK=0.022
	cg=1.
	cK=4.4e-3
	p=rndm(d)*(cg+cK)
	if(p.le.cg) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	   npg540=npfull
	else 
	   call electron(Egamma-EbindK,tclev,thlev,tdlev)
	   call gamma(EbindK,0.,0.,tdlev)
	end if
c Angular correlation between gammas 591 and 540 keV
	if(npg591.ne.0.and.npg540.ne.0) then 
	   p591=sqrt(pmoment(1,npg591)**2+pmoment(2,npg591)**2+
     +               pmoment(3,npg591)**2)
	   p540=sqrt(pmoment(1,npg540)**2+pmoment(2,npg540)**2+
     +               pmoment(3,npg540)**2)
c Coefficients in formula 1+a2*ctet**2+a4*ctet**4 are from:
c R.D.Evans, "The Atomic Nucleus", Krieger Publ. Comp., 1985, p. 240, 
c 0(2)2(2)0 cascade.
	   a2=-3.0
	   a4=4.0
	   twopi=6.2831853
1	   phi1=twopi*rndm(d)
	   ctet1=1.-2.*rndm(d)
	   stet1=sqrt(1.-ctet1*ctet1)
	   phi2=twopi*rndm(d)
	   ctet2=1.-2.*rndm(d)
	   stet2=sqrt(1.-ctet2*ctet2)
	   ctet=ctet1*ctet2+stet1*stet2*cos(phi1-phi2)
	   if(rndm(d)*(1.+abs(a2)+abs(a4)).gt.1.+a2*ctet**2+a4*ctet**4) 
     +        go to 1 
	   pmoment(1,npg591)=p591*stet1*cos(phi1)
	   pmoment(2,npg591)=p591*stet1*sin(phi1)
	   pmoment(3,npg591)=p591*ctet1
	   pmoment(1,npg540)=p540*stet2*cos(phi2)
	   pmoment(2,npg540)=p540*stet2*sin(phi2)
	   pmoment(3,npg540)=p540*ctet2
	endif
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ru100: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Pd104low(levelkeV)
c Subroutine describes the deexcitation process in Pd104 nucleus
c after 2b-decay of Ru104 to ground and excited 0+ and 2+ levels
c of Pd104 (NNDC site on 19.05.2009).
c Call  : call Pd104low(levelkeV)
c Input : levelkeV - energy of Pd104 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  556 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 19.05.2009.
	tclev=0.
	if(levelkev.eq.556) go to   556
	if(levelkev.eq.  0) go to 10000
	                    go to 20000
c-----------------------------------------------------------------------
556	thlev=9.9e-12
	call nucltransK(0.556,0.024,4.5e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Pd104: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Pd106low(levelkeV)
c Subroutine describes the deexcitation process in Pd106 nucleus
c after 2b-decay of Cd106 to ground and excited 0+ and 2+ levels
c of Pd106 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Pd106low(levelkeV)
c Input : levelkeV - energy of Pd106 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  512 keV,
c                    2+(2)  - 1128 keV,
c                    0+(1)  - 1134 keV,
c                    2+(3)  - 1562 keV,
c                    0+(2)  - 1706 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995; 3.04.2006; 14.11.2006.
	tclev=0.
c	if(levelkev.eq.2741) go to  2741
	if(levelkev.eq.1706) go to  1706
	if(levelkev.eq.1562) go to  1562
	if(levelkev.eq.1134) go to  1134
	if(levelkev.eq.1128) go to  1128
	if(levelkev.eq. 512) go to   512
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2741	thlev=0.
	p=100.*rnd1(d)
	if(p.le.66.2) go to 27411
	              go to 27412
27411	call nucltransK(2.741,0.024,1.4e-4,6.6e-4,tclev,thlev,tdlev)
	return
27412	call nucltransK(2.230,0.024,2.1e-4,3.9e-4,tclev,thlev,tdlev)
	go to 512
c-----------------------------------------------------------------------
1706	thlev=0.
	p=100.*rnd1(d)
	if(p.le.87.2) go to 17061
	              go to 17062
17061	call nucltransK(1.195,0.024,6.9e-4,6.7e-6,tclev,thlev,tdlev)
	go to 512
17062	call nucltransK(0.578,0.024,4.0e-3,0.,tclev,thlev,tdlev)
	go to 1128
c-----------------------------------------------------------------------
1562	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 9.0) go to 15621
	if(p.le.95.0) go to 15622
	if(p.le.96.1) go to 15623
	              go to 15624
15621	call nucltransK(1.562,0.024,3.9e-4,1.1e-4,tclev,thlev,tdlev)
	return
15622	call nucltransK(1.050,0.024,1.0e-3,0.,tclev,thlev,tdlev)
	go to 512
15623	call nucltransK(0.434,0.024,7.7e-3,0.,tclev,thlev,tdlev)
	go to 1128
15624	call nucltransK(0.428,0.024,9.5e-3,0.,tclev,thlev,tdlev)
	go to 1134
c-----------------------------------------------------------------------
1134	thlev=6.8e-12
	p=100.*rnd1(d)
	if(p.le.5.7e-2) go to 11341
	                go to 11342
11341	call electron(1.110,tclev,thlev,tdlev) ! E0 transition
	call gamma(0.024,0.,0.,tdlev)
	return
11342	call nucltransK(0.622,0.024,3.2e-3,0.,tclev,thlev,tdlev)
	go to 512
c-----------------------------------------------------------------------
1128	thlev=3.12e-12
	p=100.*rnd1(d)
	if(p.le.35.0) go to 11281
	              go to 11282
11281	call nucltransK(1.128,0.024,7.7e-4,0.,tclev,thlev,tdlev)
	return
11282	call nucltransK(0.616,0.024,3.4e-3,0.,tclev,thlev,tdlev)
	go to 512
c-----------------------------------------------------------------------
512	thlev=12.1e-12
	call nucltransK(0.512,0.024,5.6e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Pd106: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Pd108low(levelkeV)
c Subroutine describes the deexcitation process in Pd108 nucleus
c after 2b-decay of Cd108 to ground and excited 0+ and 2+ levels
c of Pd108 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Pd108low(levelkeV)
c Input : levelkeV - energy of Pd108 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.02.2004.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Pd108: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Sn114low(levelkeV)
c Subroutine describes the deexcitation process in Sn114 nucleus
c after 2b-decay of Cd114 to ground and excited 0+ and 2+ levels
c of Sn114 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Sn114low(levelkeV)
c Input : levelkeV - energy of Sn114 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Sn114: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Sn116low(levelkeV)
c Subroutine describes the deexcitation process in Sn116 nucleus
c after 2b-decay of Cd116 to ground and excited 0+ and 2+ levels
c of Sn116 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Sn116low(levelkeV)
c Input : levelkeV - energy of Sn116 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  - 1294 keV,
c                    0+(1)  - 1757 keV,
c                    0+(2)  - 2027 keV,
c                    2+(2)  - 2112 keV,
c                    2+(3)  - 2225 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.1993, 22.10.1995.
	tclev=0.
	if(levelkev.eq.2225) go to  2225
	if(levelkev.eq.2112) go to  2112
	if(levelkev.eq.2027) go to  2027
	if(levelkev.eq.1757) go to  1757
	if(levelkev.eq.1294) go to  1294
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2225	thlev=0.
	p=100.*rnd1(d)
	if(p.le.37.) go to 22251
	             go to 22252
22251	call nucltransK(2.225,0.029,2.7e-4,3.4e-4,tclev,thlev,tdlev)
	return
22252	call nucltransK(0.932,0.029,1.5e-3,0.,tclev,thlev,tdlev)
	go to 1294
c-----------------------------------------------------------------------
2112	thlev=0.
	p=100.*rnd1(d)
	if(p.le.54.9) go to 21121
	if(p.le.96.9) go to 21122
	              go to 21123
21121	call nucltransK(2.112,0.029,3.1e-4,2.7e-4,tclev,thlev,tdlev)
	return
21122	call nucltransK(0.819,0.029,2.6e-3,0.,tclev,thlev,tdlev)
	go to 1294
21123	call nucltransK(0.355,0.029,1.8e-2,0.,tclev,thlev,tdlev)
	go to 1757
c-----------------------------------------------------------------------
2027	thlev=0.
	call nucltransK(0.733,0.029,2.7e-3,0.,tclev,thlev,tdlev)
	go to 1294
c-----------------------------------------------------------------------
1757	thlev=0.
	p=100.*rnd1(d)
	if(p.le.0.29) go to 17571
	              go to 17572
17571	call electron(1.757-0.029,tclev,thlev,tdlev) ! only ec
	call gamma(0.029,0.,0.,tdlev)
	return
17572	call nucltransK(0.463,0.029,9.0e-3,0.,tclev,thlev,tdlev)
	go to 1294
c-----------------------------------------------------------------------
1294	thlev=0.36e-12
	call nucltransK(1.294,0.029,7.5e-4,0.5e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Sn116: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Cd112low(levelkeV)
c Subroutine describes the deexcitation process in Cd112 nucleus
c after 2b-decay of Sn112 to ground 0+ and excited 2+ levels
c of Cd112 (NNDC site on 22.12.2008 and NDS 79(1996)639).
c Call  : call Cd112low(levelkeV)
c Input : levelkeV - energy of Cd112 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  618 keV,
c                    0+(1)  - 1224 keV,
c                    2+(2)  - 1312 keV,
c                    0+(2)  - 1433 keV,
c                    2+(3)  - 1469 keV,
c                    0+(3)  - 1871 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 23.12.2008.
	tclev=0.
	if(levelkev.eq.1871) go to  1871
	if(levelkev.eq.1469) go to  1469
	if(levelkev.eq.1433) go to  1433
	if(levelkev.eq.1312) go to  1312
	if(levelkev.eq.1224) go to  1224
	if(levelkev.eq. 618) go to   618
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1871	thlev=0.
	p=100.*rnd1(d)
	if(p.le.86.91) go to 18711
	if(p.le.89.88) go to 18712
	               go to 18713
18711	call nucltransK(1.253,0.027,7.2e-4,1.5e-5,tclev,thlev,tdlev)
	go to 618
18712	call nucltransK(0.559,0.027,4.9e-3,0.,tclev,thlev,tdlev)
	go to 1312
18713	call nucltransK(0.402,0.027,1.3e-2,0.,tclev,thlev,tdlev)
	go to 1469
c-----------------------------------------------------------------------
1469	thlev=2.7e-12
	p=100.*rnd1(d)
	if(p.le.36.98) go to 14691
	if(p.le.99.14) go to 14692
	               go to 14693
14691	call nucltransK(1.469,0.027,5.8e-4,7.1e-5,tclev,thlev,tdlev)
	return
14692	call nucltransK(0.851,0.027,1.8e-3,0.,tclev,thlev,tdlev)
	go to 618
14693	call nucltransK(0.245,0.027,6.4e-2,0.,tclev,thlev,tdlev)
	go to 1224
c-----------------------------------------------------------------------
1433	thlev=1.9e-9
	p=100.*rnd1(d)
	if(p.le. 0.66) go to 14331
	if(p.le.39.36) go to 14332
	if(p.le.60.61) go to 14333
	               go to 14334
14331	p=100.*rnd1(d)
	if(p.le.3.8) then                         ! e0.exe
	   call pair(0.411,tclev,thlev,tdlev)     ! conversion to pair
	else
	   call electron(1.406,tclev,thlev,tdlev) ! conversion to electron
	   call gamma(0.027,0.,0.,tdlev)
	endif
        return
14332	call nucltransK(0.816,0.027,1.8e-3,0.,tclev,thlev,tdlev)
	go to 618
14333	call electron(0.182,tclev,thlev,tdlev)    ! E0 conversion to electron
	call gamma(0.027,0.,0.,tdlev)
	go to 1224
14334	call nucltransK(0.121,0.027,7.6e-1,0.,tclev,thlev,tdlev)
	go to 1312
c-----------------------------------------------------------------------
1312	thlev=2.0e-12
	p=100.*rnd1(d)
	if(p.le.26.59) go to 13121
	               go to 13122
13121	call nucltransK(1.312,0.027,6.6e-4,2.6e-5,tclev,thlev,tdlev)
	return
13122	call nucltransK(0.695,0.027,2.8e-3,0.,tclev,thlev,tdlev)
	go to 618
c-----------------------------------------------------------------------
1224	thlev=4.2e-12
	p=100.*rnd1(d)
	if(p.le. 0.12) go to 12241
	               go to 12242
12241	p=100.*rnd1(d)
	if(p.le.0.4) then                         ! e0.exe
	   call pair(0.202,tclev,thlev,tdlev)     ! conversion to pair
	else
	   call electron(1.197,tclev,thlev,tdlev) ! conversion to electron
	   call gamma(0.027,0.,0.,tdlev)
	endif
        return
12242	call nucltransK(0.607,0.027,3.9e-3,0.,tclev,thlev,tdlev)
	go to 618
c-----------------------------------------------------------------------
618	thlev=6.51e-12
	call nucltransK(0.618,0.027,3.7e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Cd112: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Te122low(levelkeV)
c Subroutine describes the deexcitation process in Te122 nucleus
c after 2b-decay of Sn122 to ground and excited 0+ and 2+ levels
c of Te122.
c Call  : call Te122low(levelkeV)
c Input : levelkeV - energy of Te122 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 23.12.2008
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Te122: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Te124low(levelkeV)
c Subroutine describes the deexcitation process in Te124 nucleus
c after 2b-decay of Sn124 to ground 0+ and excited 2+ levels
c of Te124 (NNDC site on 22.12.2008 and NDS 109(2008)1655).
c Call  : call Te124low(levelkeV)
c Input : levelkeV - energy of Te124 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  603 keV,
c                    2+(2)  - 1326 keV,
c                    0+(1)  - 1657 keV,
c                    0+(2)  - 1883 keV,
c                    2+(3)  - 2039 keV,
c                    2+(4)  - 2092 keV,
c                    0+(3)  - 2153 keV,
c                    2+(5)  - 2182 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 23.12.2008.
	tclev=0.
	if(levelkev.eq.2182) go to  2182
	if(levelkev.eq.2153) go to  2153
	if(levelkev.eq.2092) go to  2092
	if(levelkev.eq.2039) go to  2039
	if(levelkev.eq.1883) go to  1883
	if(levelkev.eq.1657) go to  1657
	if(levelkev.eq.1326) go to  1326
	if(levelkev.eq. 603) go to   603
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2182	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 9.53) go to 21821
	if(p.le.92.38) go to 21822
	               go to 21823
21821	call nucltransK(2.182,0.032,7.0e-4,3.9e-4,tclev,thlev,tdlev)
	return
21822	call nucltransK(1.580,0.032,7.7e-4,1.0e-4,tclev,thlev,tdlev)
	go to 603
21823	call nucltransK(0.857,0.032,2.3e-3,0.,tclev,thlev,tdlev)
	go to 1326
c-----------------------------------------------------------------------
2153	thlev=0.
	p=100.*rnd1(d)
	if(p.le.19.29) go to 21531
	               go to 21532
21531	call nucltransK(1.550,0.032,6.8e-4,1.0e-4,tclev,thlev,tdlev)
	go to 603
21532	call nucltransK(0.828,0.032,2.2e-3,0.,tclev,thlev,tdlev)
	go to 1326
c-----------------------------------------------------------------------
2092	thlev=0.28e-12
	p=100.*rnd1(d)
	if(p.le.97.97) go to 20921
	if(p.le.98.24) go to 20922
	               go to 20923
20921	call nucltransK(1.488,0.032,8.3e-4,7.1e-5,tclev,thlev,tdlev)
	go to 603
20922	call nucltransK(0.844,0.032,2.1e-3,0.,tclev,thlev,tdlev)
	go to 1248
20923	call nucltransK(0.766,0.032,3.0e-3,0.,tclev,thlev,tdlev)
	go to 1326
c-----------------------------------------------------------------------
2039	thlev=0.49e-12
	p=100.*rnd1(d)
	if(p.le.34.26) go to 20391
	if(p.le.94.57) go to 20392
	if(p.le.96.80) go to 20393
	if(p.le.99.04) go to 20394
	               go to 20395
20391	call nucltransK(2.039,0.032,6.7e-4,3.2e-4,tclev,thlev,tdlev)
	return
20392	call nucltransK(1.437,0.032,8.7e-4,5.5e-5,tclev,thlev,tdlev)
	go to 603
20393	call nucltransK(0.791,0.032,2.5e-3,0.,tclev,thlev,tdlev)
	go to 1248
20394	call nucltransK(0.714,0.032,4.0e-3,0.,tclev,thlev,tdlev)
	go to 1326
20395	call nucltransK(0.382,0.032,1.8e-2,0.,tclev,thlev,tdlev)
	go to 1657
c-----------------------------------------------------------------------
1883	thlev=0.76e-12
	p=100.*rnd1(d)
	if(p.le. 0.31) go to 18831
	if(p.le.99.93) go to 18832
	               go to 18833
18831	p=100.*rnd1(d)
	if(p.le.21.89) then                         ! e0.exe
	   call pair(0.861,tclev,thlev,tdlev)       ! conversion to pair
	else
	   call electron(1.851,tclev,thlev,tdlev)   ! conversion to electron
	   call gamma(0.032,0.,0.,tdlev)
	endif
        return
18832	call nucltransK(0.557,0.032,6.0e-3,0.,tclev,thlev,tdlev)
	go to 1326
18833	call electron(0.194,tclev,thlev,tdlev)      ! E0 conversion to electron
	call gamma(0.032,0.,0.,tdlev)
	go to 1657
c-----------------------------------------------------------------------
1657	thlev=0.55-12
	p=100.*rnd1(d)
	if(p.le. 0.02) go to 16571
	               go to 16572
16571	p=100.*rnd1(d)
	if(p.le.10.68) then                         ! e0.exe
	   call pair(0.636,tclev,thlev,tdlev)       ! conversion to pair
	else
	   call electron(1.626,tclev,thlev,tdlev)   ! conversion to electron
	   call gamma(0.032,0.,0.,tdlev)
	endif
        return
16572	call nucltransK(1.055,0.032,1.3e-3,0.,tclev,thlev,tdlev)
	go to 603
c-----------------------------------------------------------------------
1326	thlev=1.04e-12
	p=100.*rnd1(d)
	if(p.le.13.84) go to 13261
	               go to 13262
13261	call nucltransK(1.326,0.032,8.3e-4,2.8e-5,tclev,thlev,tdlev)
	return
13262	call nucltransK(0.723,0.032,3.1e-3,0.,tclev,thlev,tdlev)
	go to 603
c-----------------------------------------------------------------------
1248	thlev=1.4e-12
	call nucltransK(0.646,0.032,4.1e-3,0.,tclev,thlev,tdlev)
	go to 603
c-----------------------------------------------------------------------
603	thlev=6.2e-12
	call nucltransK(0.603,0.032,4.9e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Te124: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Sn120low(levelkeV)
c Subroutine describes the deexcitation process in Sn120 nucleus
c after 2b-decay of Te120 to ground 0+ and excited 2+ levels
c of Sn120 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Sn120low(levelkeV)
c Input : levelkeV - energy of Sn120 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  - 1171 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.02.2004.
	tclev=0.
	if(levelkev.eq.1171) go to  1171
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1171	thlev=0.642e-12
	call nucltransK(1.171,0.029,8.0e-4,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Sn120: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Xe128low(levelkeV)
c Subroutine describes the deexcitation process in Xe128 nucleus
c after 2b-decay of Te128 to ground 0+ and excited 2+ levels
c of Xe128 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Xe128low(levelkeV)
c Input : levelkeV - energy of Xe128 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  443 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 13.02.2004.
	tclev=0.
	if(levelkev.eq. 443) go to   443
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
443	thlev=23.8e-12
	call nucltransK(0.443,0.035,8.0e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Xe128: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Xe130low(levelkeV)
c Subroutine describes the deexcitation process in Xe130 nucleus
c after 2b-decay of Te130 to ground 0+ and excited 2+ levels
c of Xe130 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Xe130low(levelkeV)
c Input : levelkeV - energy of Xe130 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  536 keV,
c                    2+(2)  - 1122 keV,
c                    0+(1)  - 1794 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 20.06.1996; 3.04.2006.
	tclev=0.
	if(levelkev.eq.1794) go to  1794
	if(levelkev.eq.1122) go to  1122
	if(levelkev.eq. 536) go to   536
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1794	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 1.0) go to 17941 ! E0 to gs; ToI-1978
	if(p.le.86.3) go to 17942
	              go to 17943
17941	p=100.*rnd1(d)
	if(p.le.12.7) then                        ! e0.exe
	   call pair(0.772,tclev,thlev,tdlev)     ! conversion to pair
	else
	   call electron(1.759,tclev,thlev,tdlev) ! conversion to electron
	   call gamma(0.035,0.,0.,tdlev)
	endif
        return
17942	call nucltransK(1.258,0.035,1.0e-3,1.5e-5,tclev,thlev,tdlev)
	go to 536
17943	call nucltransK(0.672,0.035,4.1e-3,0.,tclev,thlev,tdlev)
	go to 1122
c-----------------------------------------------------------------------
1122	thlev=0.
	p=100.*rnd1(d)
	if(p.le.13.3) go to 11221 
	              go to 11222
11221	call nucltransK(1.122,0.035,1.3e-3,9.0e-7,tclev,thlev,tdlev)
	return
11222	call nucltransK(0.586,0.035,7.5e-3,0.,tclev,thlev,tdlev)
	go to 536
c-----------------------------------------------------------------------
536	thlev=7.0e-12
	call nucltransK(0.536,0.035,7.4e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Xe130: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ba136low(levelkeV)
c Subroutine describes the deexcitation process in Ba136 nucleus
c after 2b-decay of Xe136 or Ce136 to ground and excited 0+ and 2+ levels
c of Ba136 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ba136low(levelkeV)
c Input : levelkeV - energy of Ba136 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  819 keV,
c                    2+(2)  - 1551 keV,
c                    0+(1)  - 1579 keV,
c                    2+(3)  - 2080 keV,
c                    2+(4)  - 2129 keV,
c                    0+(2)  - 2141 keV,
c                    2+(5)  - 2223 keV,
c                    0+(3)  - 2315 keV,
c                    2+(6)  - 2400 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.1993, 22.10.1995.
c VIT, 10.12.2008: updated to NDS 95(2002)837 
c (E0 transitions from 2141 and 1579 keV levels are neglected); 
c levels 2080, 2129, 2141, 2223, 2315 and 2400 keV were added.
	tclev=0.
	if(levelkev.eq.2400) go to  2400
	if(levelkev.eq.2315) go to  2315
	if(levelkev.eq.2223) go to  2223
	if(levelkev.eq.2141) go to  2141
	if(levelkev.eq.2129) go to  2129
	if(levelkev.eq.2080) go to  2080
	if(levelkev.eq.1579) go to  1579
	if(levelkev.eq.1551) go to  1551
	if(levelkev.eq. 819) go to   819
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2400	thlev=0.
	call nucltransK(1.581,0.037,1.0e-3,1.1e-4,tclev,thlev,tdlev)
	go to 819
c-----------------------------------------------------------------------
2315	thlev=0.
	call nucltransK(1.497,0.037,8.7e-4,7.7e-5,tclev,thlev,tdlev)
	go to 819
c-----------------------------------------------------------------------
2223	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 4.3) go to 22231
	if(p.le.51.9) go to 22232
	              go to 22233
22231	call nucltransK(2.223,0.037,7.8e-4,4.0e-4,tclev,thlev,tdlev)
	return
22232	call nucltransK(1.404,0.037,9.6e-4,4.8e-5,tclev,thlev,tdlev)
	go to 819
22233	call nucltransK(0.672,0.037,6.5e-3,0.,tclev,thlev,tdlev)
	go to 1551
c-----------------------------------------------------------------------
2141	thlev=0.
	call nucltransK(1.323,0.037,1.0e-3,2.6e-5,tclev,thlev,tdlev)
	go to 819
c-----------------------------------------------------------------------
2129	thlev=0.051e-12
	p=100.*rnd1(d)
	if(p.le.33.3) go to 21291
	              go to 21292
21291	call nucltransK(2.129,0.037,7.7e-4,3.6e-4,tclev,thlev,tdlev)
	return
21292	call nucltransK(1.310,0.037,1.4e-3,2.3e-5,tclev,thlev,tdlev)
	go to 819
c-----------------------------------------------------------------------
2080	thlev=0.6e-12
	p=100.*rnd1(d)
	if(p.le.35.4) go to 20801
	if(p.le.93.8) go to 20802
	              go to 20803
20801	call nucltransK(2.080,0.037,7.6e-4,3.3e-4,tclev,thlev,tdlev)
	return
20802	call nucltransK(1.262,0.037,1.3e-3,1.4e-5,tclev,thlev,tdlev)
	go to 819
20803	call nucltransK(0.529,0.037,1.0e-2,0.,tclev,thlev,tdlev)
	go to 1551
c-----------------------------------------------------------------------
1579	thlev=0.
	call nucltransK(0.761,0.037,3.4e-3,0.,tclev,thlev,tdlev)
	go to 819
c-----------------------------------------------------------------------
1551	thlev=1.01e-12
	p=100.*rnd1(d)
	if(p.le.52.1) go to 15511
	              go to 15512
15511	call nucltransK(1.551,0.037,8.4e-4,9.7e-5,tclev,thlev,tdlev)
	return
15512	call nucltransK(0.733,0.037,4.5e-3,0.,tclev,thlev,tdlev)
	go to 819
c-----------------------------------------------------------------------
819	thlev=1.93e-12
	call nucltransK(0.819,0.037,2.9e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ba136: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ba138low(levelkeV)
c Subroutine describes the deexcitation process in Ba138 nucleus
c after 2b-decay of Ce138 to ground and excited 0+ and 2+ levels
c of Ba138 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Ba138low(levelkeV)
c Input : levelkeV - energy of Ba138 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 11.12.2008.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ba138: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Nd142low(levelkeV)
c Subroutine describes the deexcitation process in Nd142 nucleus
c after 2b-decay of Ce142 to ground and excited 0+ and 2+ levels
c of Nd142 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Nd142low(levelkeV)
c Input : levelkeV - energy of Nd142 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 11.12.2008.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Nd142: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Sm148low(levelkeV)
c Subroutine describes the deexcitation process in Sm148 nucleus
c after 2b-decay of Nd148 to ground and excited 0+ and 2+ levels
c of Sm148 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Sm148low(levelkeV)
c Input : levelkeV - energy of Sm148 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  550 keV,
c                    2+(2)  - 1455 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.11.1995.
	tclev=0.
	if(levelkev.eq.1455) go to  1455
	if(levelkev.eq. 550) go to   550
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1455	thlev=0.6e-12
	p=100.*rnd1(d)
	if(p.le.42.) go to 14551
	             go to 14552
14551	call nucltransK(1.455,0.047,1.1e-3,0.3e-4,tclev,thlev,tdlev)
	return
14552	call nucltransK(0.904,0.047,2.8e-3,0.,tclev,thlev,tdlev)
	go to 550
c-----------------------------------------------------------------------
550	thlev=7.3e-12
	call nucltransK(0.550,0.047,9.0e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Sm148: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Sm150low(levelkeV)
c Subroutine describes the deexcitation process in Sm150 nucleus
c after 2b-decay of Nd150 to ground and excited 0+ and 2+ levels
c of Sm150 ("Table of Isotopes", 7th ed., 1978).
c Call  : call Sm150low(levelkeV)
c Input : levelkeV - energy of Sm150 level (integer in keV) occupied
c	             initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  334 keV,
c                    0+(1)  -  740 keV,
c                    2+(2)  - 1046 keV,
c                    2+(3)  - 1194 keV,
c                    0+(2)  - 1256 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.1993, 22.10.1995; 23.09.2008.
	tclev=0.
	if(levelkev.eq.1256) go to  1256
	if(levelkev.eq.1194) go to  1194
	if(levelkev.eq.1046) go to  1046
	if(levelkev.eq. 740) go to   740
	if(levelkev.eq. 334) go to   334
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1256	thlev=0.
	p=100.*rnd1(d)
	if(p.le.93.) go to 12561
	             go to 12562
12561	call nucltransK(0.922,0.047,2.6e-3,0.,tclev,thlev,tdlev)
	go to 334
12562	call nucltransK(0.210,0.047,1.7e-1,0.,tclev,thlev,tdlev)
	go to 1046
c-----------------------------------------------------------------------
1194	thlev=1.3e-12
	p=100.*rnd1(d)
	if(p.le.55.9) go to 11941
	if(p.le.96.9) go to 11942
	if(p.le.98.7) go to 11943
	              go to 11944
11941	call nucltransK(1.194,0.047,1.6e-3,0.1e-4,tclev,thlev,tdlev)
	return
11942	call nucltransK(0.860,0.047,3.2e-3,0.,tclev,thlev,tdlev)
	go to 334
11943	call nucltransK(0.453,0.047,1.5e-2,0.,tclev,thlev,tdlev)
	go to 740
11944	call nucltransK(0.420,0.047,1.9e-2,0.,tclev,thlev,tdlev)
	go to 773
c-----------------------------------------------------------------------
1046	thlev=0.7e-12
	p=100.*rnd1(d)
	if(p.le. 7.0) go to 10461
	if(p.le.94.3) go to 10462
	if(p.le.97.0) go to 10463
	              go to 10464
10461	call nucltransK(1.046,0.047,2.0e-3,0.,tclev,thlev,tdlev)
	return
10462	call nucltransK(0.712,0.047,7.6e-3,0.,tclev,thlev,tdlev)
	go to 334
10463	call nucltransK(0.306,0.047,4.9e-2,0.,tclev,thlev,tdlev)
	go to 740
10464	call nucltransK(0.273,0.047,7.0e-2,0.,tclev,thlev,tdlev)
	go to 773
c-----------------------------------------------------------------------
773	thlev=6.6e-12
	call nucltransK(0.439,0.047,1.7e-2,0.,tclev,thlev,tdlev)
	go to 334
c-----------------------------------------------------------------------
740	thlev=20.e-12
	p=100.*rnd1(d)
c the following line is corrected in accordance with ToI'1998 and Nucl.
c Data Sheets 75(1995)827 (real page is 856)
c VIT, 23.09.2008
c	if(p.le.92.) go to 74001
	if(p.le.1.33) go to 74001
	              go to 74002
74001	call electron(0.740-0.047,tclev,thlev,tdlev) ! only ec
	call gamma(0.047,0.,0.,tdlev)
	return
74002	call nucltransK(0.407,0.047,2.0e-2,0.,tclev,thlev,tdlev)
	go to 334
c-----------------------------------------------------------------------
334	thlev=48.5e-12
	call nucltransK(0.334,0.047,3.7e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Sm150: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Gd156low(levelkeV)
c Subroutine describes the deexcitation process in Gd156 nucleus
c after 2b-decay of Dy156 to ground and excited 0+ and 2+ levels
c of Gd156 (NNDC site on 21.12.2010; NDS 99(2003)753).
c Call  : call Gd156low(levelkeV)
c Input : levelkeV - energy of Gd156 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -   89 keV,
c                    0+(1)  - 1050 keV,
c                    2+(2)  - 1129 keV,
c                    2+(3)  - 1154 keV,
c                    0+(2)  - 1168 keV,
c                    2+(4)  - 1258 keV,
c                    0+(3)  - 1715 keV,
c                    2+(5)  - 1771 keV,
c                    2+(6)  - 1828 keV,
c                    0+(4)  - 1851 keV,
c                    2+(7)  - 1915 keV,
c                    1-()   - 1946 keV,
c                    0-()   - 1952 keV,
c                    0+(5)  - 1989 keV,
c                    2+(8)  - 2004 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 23.12.2010.
	tclev=0.
	if(levelkev.eq.2004) go to  2004
	if(levelkev.eq.1989) go to  1989
	if(levelkev.eq.1952) go to  1952
	if(levelkev.eq.1946) go to  1946
	if(levelkev.eq.1915) go to  1915
	if(levelkev.eq.1851) go to  1851
	if(levelkev.eq.1828) go to  1828
	if(levelkev.eq.1771) go to  1771
	if(levelkev.eq.1715) go to  1715
	if(levelkev.eq.1258) go to  1258
	if(levelkev.eq.1168) go to  1168
	if(levelkev.eq.1154) go to  1154
	if(levelkev.eq.1129) go to  1129
	if(levelkev.eq.1050) go to  1050
	if(levelkev.eq.  89) go to    89
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
2004	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 6.1) go to 20041
	if(p.le.39.5) go to 20042
	if(p.le.53.8) go to 20043
	if(p.le.81.5) go to 20044
	if(p.le.94.1) go to 20045
	if(p.le.97.0) go to 20046
	              go to 20047
20041	call nucltransK(0.684,0.050,2.4e-3,0.,tclev,thlev,tdlev)
	go to 1320
20042	call nucltransK(0.728,0.050,2.1e-3,0.,tclev,thlev,tdlev)
	go to 1276
20043	call nucltransK(0.756,0.050,7.2e-3,0.,tclev,thlev,tdlev)
	go to 1248
20044	call nucltransK(0.761,0.050,1.9e-3,0.,tclev,thlev,tdlev)
	go to 1243
20045	call nucltransK(0.850,0.050,5.4e-3,0.,tclev,thlev,tdlev)
	go to 1154
20046	call nucltransK(0.874,0.050,6.5e-3,0.,tclev,thlev,tdlev)
	go to 1129
20047	call nucltransK(1.715,0.050,1.1e-3,0.,tclev,thlev,tdlev)
	go to 288
c-----------------------------------------------------------------------
1989	thlev=0.
	call nucltransK(1.900,0.050,7.9e-4,2.4e-4,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1952	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 5.5) go to 19521
	if(p.le. 9.3) go to 19522
	              go to 19523
19521	call nucltransK(0.586,0.050,1.7e-2,0.,tclev,thlev,tdlev)
	go to 1367
19522	call nucltransK(0.633,0.050,7.8e-3,0.,tclev,thlev,tdlev)
	go to 1320
19523	call nucltransK(0.710,0.050,1.1e-2,0.,tclev,thlev,tdlev)
	go to 1243
c-----------------------------------------------------------------------
1946	thlev=30.e-15
	p=100.*rnd1(d)
	if(p.le. 2.8) go to 19461
	if(p.le.60.7) go to 19462
	              go to 19463
19461	call nucltransK(0.688,0.050,2.4e-3,0.,tclev,thlev,tdlev)
	go to 1258
19462	call nucltransK(1.857,0.050,3.9e-4,4.7e-4,tclev,thlev,tdlev)
	go to 89
19463	call nucltransK(1.946,0.050,3.6e-4,5.4e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1915	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.64) go to 19151
	if(p.le. 4.06) go to 19152
	if(p.le.13.31) go to 19153
	if(p.le.17.90) go to 19154
	if(p.le.22.04) go to 19155
	if(p.le.26.03) go to 19156
	               go to 19157
19151	call nucltransK(0.376,0.050,9.2e-3,0.,tclev,thlev,tdlev)
	go to 1539
19152	call nucltransK(0.548,0.050,3.9e-3,0.,tclev,thlev,tdlev)
	go to 1367
19153	call nucltransK(0.639,0.050,2.8e-3,0.,tclev,thlev,tdlev)
	go to 1276
19154	call nucltransK(0.657,0.050,1.8e-2,0.,tclev,thlev,tdlev)
	go to 1258
19155	call nucltransK(0.667,0.050,1.0e-2,0.,tclev,thlev,tdlev)
	go to 1248
19156	call nucltransK(0.672,0.050,2.5e-3,0.,tclev,thlev,tdlev)
	go to 1243
19157	call nucltransK(1.826,0.050,1.1e-3,2.4e-4,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1851	thlev=0.
	p=100.*rnd1(d)
	if(p.le.13.2) go to 18511
	if(p.le.25.7) go to 18512
	if(p.le.34.6) go to 18513
	if(p.le.40.0) go to 18514
	if(p.le.99.7) go to 18515
	              go to 18516
18511	call nucltransK(0.485,0.050,5.1e-3,0.,tclev,thlev,tdlev)
	go to 1367
18512	call nucltransK(0.609,0.050,3.1e-3,0.,tclev,thlev,tdlev)
	go to 1243
18513	call nucltransK(0.697,0.050,6.2e-3,0.,tclev,thlev,tdlev)
	go to 1154
18514	call nucltransK(0.722,0.050,5.7e-3,0.,tclev,thlev,tdlev)
	go to 1129
18515	call nucltransK(1.763,0.050,9.0e-4,1.8e-4,tclev,thlev,tdlev)
	go to 89
18516	p=100.*rnd1(d)
	if(p.le.91.7) then                        ! e0.exe
	   call electron(1.801,tclev,thlev,tdlev) ! conversion to electron
	   call gamma(0.050,0.,0.,tdlev)
	else
	   call pair(0.829,tclev,thlev,tdlev)     ! conversion to pair
	endif
	return
c-----------------------------------------------------------------------
1828	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.28) go to 18281
	if(p.le. 3.37) go to 18282
	if(p.le.14.51) go to 18283
	if(p.le.28.57) go to 18284
	if(p.le.48.82) go to 18285
	if(p.le.71.88) go to 18286
	               go to 18287
18281	call nucltransK(0.366,0.050,3.3e-2,0.,tclev,thlev,tdlev)
	go to 1462
18282	call nucltransK(0.570,0.050,1.4e-2,0.,tclev,thlev,tdlev)
	go to 1258
18283	call nucltransK(0.580,0.050,1.4e-2,0.,tclev,thlev,tdlev)
	go to 1248
18284	call nucltransK(0.674,0.050,6.6e-3,0.,tclev,thlev,tdlev)
	go to 1154
18285	call nucltransK(0.698,0.050,9.0e-3,0.,tclev,thlev,tdlev)
	go to 1129
18286	call nucltransK(0.778,0.050,4.8e-3,0.,tclev,thlev,tdlev)
	go to 1050
18287	call nucltransK(1.739,0.050,1.3e-3,1.9e-4,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1771	thlev=0.42e-12
	p=100.*rnd1(d)
	if(p.le. 0.10) go to 17711
	if(p.le. 1.08) go to 17712
	if(p.le. 7.61) go to 17713
	if(p.le. 9.76) go to 17714
	if(p.le.10.50) go to 17715
	               go to 17716
17711	call nucltransK(0.232,0.050,3.1e-2,0.,tclev,thlev,tdlev)
	go to 1539
17712	call nucltransK(0.405,0.050,7.7e-3,0.,tclev,thlev,tdlev)
	go to 1367
17713	call nucltransK(0.495,0.050,4.8e-3,0.,tclev,thlev,tdlev)
	go to 1276
17714	call nucltransK(0.513,0.050,2.4e-2,0.,tclev,thlev,tdlev)
	go to 1258
17715	call nucltransK(0.529,0.050,4.2e-3,0.,tclev,thlev,tdlev)
	go to 1243
17716	call nucltransK(1.682,0.050,1.4e-3,1.6e-4,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1715	thlev=2.6e-12
	p=100.*rnd1(d)
	if(p.le. 6.97) go to 17151
	if(p.le.74.65) go to 17152
	if(p.le.74.72) go to 17153
	if(p.le.77.43) go to 17154
	if(p.le.77.54) go to 17155
	if(p.le.99.88) go to 17156
	               go to 17157
17151	call nucltransK(0.349,0.050,1.1e-2,0.,tclev,thlev,tdlev)
	go to 1367
17152	call nucltransK(0.473,0.050,5.4e-3,0.,tclev,thlev,tdlev)
	go to 1243
17153	call electron(0.497,tclev,thlev,tdlev) ! only conversion to electron
	call gamma(0.050,0.,0.,tdlev)
	go to 1168
17154	call nucltransK(0.586,0.050,9.4e-3,0.,tclev,thlev,tdlev)
	go to 1129
17155	call electron(0.616,tclev,thlev,tdlev) ! only conversion to electron
	call gamma(0.050,0.,0.,tdlev)
	go to 1050
17156	call nucltransK(1.625,0.050,1.1e-3,1.2e-4,tclev,thlev,tdlev)
	go to 89
17157	call electron(1.665,tclev,thlev,tdlev) ! only conversion to electron
	call gamma(0.050,0.,0.,tdlev)
	return
c-----------------------------------------------------------------------
1539	thlev=20.e-15
	p=100.*rnd1(d)
	if(p.le. 0.2) go to 15391
	if(p.le.51.6) go to 15392
	              go to 15393
15391	call nucltransK(0.385,0.050,8.6e-3,0.,tclev,thlev,tdlev)
	go to 1154
15392	call nucltransK(1.251,0.050,7.6e-4,0.5e-4,tclev,thlev,tdlev)
	go to 288
15393	call nucltransK(1.450,0.050,5.9e-4,1.7e-4,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1462	thlev=0.
	p=100.*rnd1(d)
	if(p.le. 0.16) go to 14621
	if(p.le. 0.76) go to 14622
	if(p.le. 1.00) go to 14623
	if(p.le.27.32) go to 14624
	if(p.le.89.98) go to 14625
	               go to 14626
14621	call nucltransK(0.165,0.050,4.9e-1,0.,tclev,thlev,tdlev)
	go to 1298
14622	call nucltransK(0.204,0.050,2.1e-1,0.,tclev,thlev,tdlev)
	go to 1258
14623	call nucltransK(0.333,0.050,3.4e-2,0.,tclev,thlev,tdlev)
	go to 1129
14624	call nucltransK(0.878,0.050,3.7e-3,0.,tclev,thlev,tdlev)
	go to 585
14625	call nucltransK(1.174,0.050,3.2e-3,0.,tclev,thlev,tdlev)
	go to 288
14626	call nucltransK(1.373,0.050,1.5e-3,0.,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1367	thlev=17.e-15
	p=100.*rnd1(d)
	if(p.le. 0.05) go to 13671
	if(p.le.64.74) go to 13672
	               go to 13673
13671	call nucltransK(0.237,0.050,2.9e-2,0.,tclev,thlev,tdlev)
	go to 1129
13672	call nucltransK(1.278,0.050,7.3e-4,0.6e-4,tclev,thlev,tdlev)
	go to 89
13673	call nucltransK(1.367,0.050,6.5e-4,1.1e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1320	thlev=3.9e-12
	p=100.*rnd1(d)
	if(p.le. 0.22) go to 13201
	               go to 13202
13201	call nucltransK(0.190,0.050,5.2e-2,0.,tclev,thlev,tdlev)
	go to 1129
13202	call nucltransK(1.231,0.050,7.8e-4,0.,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1298	thlev=1.6e-12
	p=100.*rnd1(d)
	if(p.le. 0.07) go to 12981
	if(p.le. 0.84) go to 12982
	if(p.le. 6.41) go to 12983
	if(p.le.50.74) go to 12984
	               go to 12985
12981	call nucltransK(0.144,0.050,6.8e-1,0.,tclev,thlev,tdlev)
	go to 1154
12982	call nucltransK(0.168,0.050,4.0e-1,0.,tclev,thlev,tdlev)
	go to 1129
12983	call nucltransK(0.713,0.050,5.8e-3,0.,tclev,thlev,tdlev)
	go to 585
12984	call nucltransK(1.010,0.050,1.7e-2,0.,tclev,thlev,tdlev)
	go to 288
12985	call nucltransK(1.209,0.050,1.9e-3,0.,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1276	thlev=0.098e-12
	p=100.*rnd1(d)
	if(p.le.31.0) go to 12761
	              go to 12762
12761	call nucltransK(0.988,0.050,1.2e-3,0.,tclev,thlev,tdlev)
	go to 288
12762	call nucltransK(1.187,0.050,8.3e-4,0.,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1258	thlev=1.54e-12
	p=100.*rnd1(d)
	if(p.le.50.8) go to 12581
	if(p.le.86.8) go to 12582
	              go to 12583
12581	call nucltransK(0.970,0.050,3.0e-3,0.,tclev,thlev,tdlev)
	go to 288
12582	call nucltransK(1.169,0.050,3.1e-3,0.,tclev,thlev,tdlev)
	go to 89
12583	call nucltransK(1.258,0.050,1.7e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1248	thlev=0.58e-12
	p=100.*rnd1(d)
	if(p.le.21.3) go to 12481
	              go to 12482
12481	call nucltransK(0.960,0.050,3.0e-3,0.,tclev,thlev,tdlev)
	go to 288
12482	call nucltransK(1.159,0.050,2.1e-3,0.,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
1243	thlev=31.e-15
	p=100.*rnd1(d)
	if(p.le.50.7) go to 12431
	              go to 12432
12431	call nucltransK(1.154,0.050,8.8e-4,0.,tclev,thlev,tdlev)
	go to 89
12432	call nucltransK(1.243,0.050,7.7e-4,0.4e-4,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1168	thlev=5.e-12
	p=100.*rnd1(d)
	if(p.le. 0.18) go to 11681
	if(p.le.99.95) go to 11682
	               go to 11683
11681	call electron(0.069,tclev,thlev,tdlev) ! only conversion to electron
	call gamma(0.050,0.,0.,tdlev)
	go to 1050
11682	call nucltransK(1.079,0.050,2.4e-3,0.,tclev,thlev,tdlev)
	go to 89
11683	call electron(1.118,tclev,thlev,tdlev) ! only conversion to electron
	call gamma(0.050,0.,0.,tdlev)
	return
c-----------------------------------------------------------------------
1154	thlev=0.568e-12
	p=100.*rnd1(d)
	if(p.le. 1.89) go to 11541
	if(p.le.51.90) go to 11542
	               go to 11543
11541	call nucltransK(0.866,0.050,3.8e-3,0.,tclev,thlev,tdlev)
	go to 288
11542	call nucltransK(1.065,0.050,2.4e-3,0.,tclev,thlev,tdlev)
	go to 89
11543	call nucltransK(1.154,0.050,2.1e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1129	thlev=1.59e-12
	p=100.*rnd1(d)
	if(p.le.24.3) go to 11291
	if(p.le.83.8) go to 11292
	              go to 11293
11291	call nucltransK(0.841,0.050,4.0e-3,0.,tclev,thlev,tdlev)
	go to 288
11292	call nucltransK(1.041,0.050,1.4e-2,0.,tclev,thlev,tdlev)
	go to 89
11293	call nucltransK(1.129,0.050,2.2e-3,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
1050	thlev=1.8e-12
	p=100.*rnd1(d)
	if(p.le.99.4) go to 10501
	              go to 10502
10501	call nucltransK(0.961,0.050,3.0e-3,0.,tclev,thlev,tdlev)
	go to 89
10502	call electron(1.000,tclev,thlev,tdlev) ! only conversion to electron
	call gamma(0.050,0.,0.,tdlev)
	return
c-----------------------------------------------------------------------
585	thlev=15.8e-12
	call nucltransK(0.297,0.050,6.3e-2,0.,tclev,thlev,tdlev)
	go to 288
c-----------------------------------------------------------------------
288	thlev=111.9e-12
	call nucltransK(0.199,0.050,2.3e-1,0.,tclev,thlev,tdlev)
	go to 89
c-----------------------------------------------------------------------
89	thlev=2.21e-9
	call nucltransK(0.089,0.050,3.93,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Gd156: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Gd158low(levelkeV)
c Subroutine describes the deexcitation process in Gd158 nucleus
c after 2b-decay of Dy158 to ground and excited 0+ and 2+ levels
c of Gd158 (NNDC site on 10.10.2010, NDS 101(2004)325).
c Call  : call Gd158low(levelkeV)
c Input : levelkeV - energy of Gd158 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -   80 keV,
c                    4+(1)  -  261 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 10.10.2010.
	tclev=0.
	if(levelkev.eq.261) go to   261
	if(levelkev.eq. 80) go to    80
	if(levelkev.eq.  0) go to 10000
	                    go to 20000
c-----------------------------------------------------------------------
261	thlev=0.148e-9
	call nucltransK(0.182,0.050,0.308,0.,tclev,thlev,tdlev)
	go to 80
c-----------------------------------------------------------------------
80	thlev=2.52e-9
	call nucltransK(0.080,0.050,6.02,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Gd158: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Hf180low(levelkeV)
c Subroutine describes the deexcitation process in Hf180 nucleus
c after 2e-decay of W180 to ground 0+ level
c of Hf180 ("Table of Isotopes", 8th ed., 1998).
c Call  : call Hf180low(levelkeV)
c Input : levelkeV - energy of Hf18o level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 24.06.2008.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Hf180: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine W184low(levelkeV)
c Subroutine describes the deexcitation process in W184 nucleus
c after eb+/2e decay of Os184 to ground and excited 0+ and 2+ levels
c of W184 (in accordance with NDS 111(2010)275 and NNDC on 22.06.2012).
c Call  : call W184low(levelkeV)
c Input : levelkeV - energy of W184 level (integer in keV) occupied
c	             initially; the following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  111 keV,
c                    2+(2)  -  903 keV,
c                    0+(1)  - 1002 keV,
c                    2+(3)  - 1121 keV,
c                    0+(2)  - 1322 keV,
c                    2+(4)  - 1386 keV,
c                    2+(5)  - 1431 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 28.06.2012.
	tclev=0.
	if(levelkev.eq.1431) go to  1431
	if(levelkev.eq.1386) go to  1386
	if(levelkev.eq.1322) go to  1322
	if(levelkev.eq.1121) go to  1121
	if(levelkev.eq.1002) go to  1002
	if(levelkev.eq. 903) go to   903
	if(levelkev.eq. 111) go to   111
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1431	thlev=5.0e-12
	p=100.*rnd1(d)
	if(p.le. 4.43) go to 14311
	if(p.le.57.82) go to 14312
	               go to 14313
14311	call nucltransK(0.424,0.070,8.7e-2,0.,tclev,thlev,tdlev)
	go to 1006
14312	call nucltransK(1.320,0.070,2.6e-3,2.1e-5,tclev,thlev,tdlev)
	go to 111
14313	call nucltransK(1.431,0.070,2.3e-3,4.8e-5,tclev,thlev,tdlev)
	go to 10000
c-----------------------------------------------------------------------
1386	thlev=1.08e-12
	p=100.*rnd1(d)
	if(p.le. 1.94) go to 13861
	if(p.le. 9.81) go to 13862
	if(p.le.59.64) go to 13863
	               go to 13864
13861	call nucltransK(0.380,0.070,7.0e-2,0.,tclev,thlev,tdlev)
	go to 1006
13862	call nucltransK(0.483,0.070,4.2e-2,0.,tclev,thlev,tdlev)
	go to 903
13863	call nucltransK(1.275,0.070,4.0e-3,1.6e-5,tclev,thlev,tdlev)
	go to 111
13864	call nucltransK(1.386,0.070,2.4e-3,3.6e-5,tclev,thlev,tdlev)
	go to 10000
c-----------------------------------------------------------------------
1322	thlev=0.
	call nucltransK(0.419,0.070,3.3e-2,0.,tclev,thlev,tdlev)
	go to 903
c-----------------------------------------------------------------------
1121	thlev=4.5e-12
	p=100.*rnd1(d)
	if(p.le.33.65) go to 11211
	if(p.le.81.73) go to 11212
	               go to 11213
11211	call nucltransK(0.757,0.070,8.0e-3,0.,tclev,thlev,tdlev)
	go to 364
11212	call nucltransK(1.010,0.070,1.4e-2,0.,tclev,thlev,tdlev)
	go to 111
11213	call nucltransK(1.121,0.070,3.6e-3,0.,tclev,thlev,tdlev)
	go to 10000
c-----------------------------------------------------------------------
1006	thlev=0.
	p=100.*rnd1(d)
	if(p.le.11.03) go to 10061
	               go to 10062
10061	call nucltransK(0.642,0.070,1.2e-2,0.,tclev,thlev,tdlev)
	go to 364
10062	call nucltransK(0.895,0.070,5.7e-3,0.,tclev,thlev,tdlev)
	go to 111
c-----------------------------------------------------------------------
1002	thlev=0.
	call nucltransK(0.891,0.070,5.8e-3,0.,tclev,thlev,tdlev)
	go to 111
c-----------------------------------------------------------------------
903	thlev=1.71e-12
	p=100.*rnd1(d)
	if(p.le. 0.42) go to 90301
	if(p.le.49.84) go to 90302
	               go to 90303
90301	call nucltransK(0.539,0.070,1.7e-2,0.,tclev,thlev,tdlev)
	go to 364
90302	call nucltransK(0.792,0.070,7.3e-3,0.,tclev,thlev,tdlev)
	go to 111
90303	call nucltransK(0.903,0.070,5.5e-3,0.,tclev,thlev,tdlev)
	go to 10000
c-----------------------------------------------------------------------
364	thlev=48.0e-12
	call nucltransK(0.253,0.070,0.144,0.,tclev,thlev,tdlev)
	go to 111
c-----------------------------------------------------------------------
111	thlev=1.251e-9
	call nucltransK(0.111,0.070,2.57,0.,tclev,thlev,tdlev)
	go to 10000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'W184: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine pt192low(levelkeV)
c Subroutine describes the deexcitation process in Pt192 nucleus
c after 2b-decay of Os192 to ground and excited 0+ and 2+ levels
c of Pt192 (NNDC site on 21.06.2012).
c Call  : call Pt192low(levelkeV)
c Input : levelkeV - energy of Pt192 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  317 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 22.06.2012.
	tclev=0.
	if(levelkev.eq.317) go to   317
	if(levelkev.eq.  0) go to 10000
	                    go to 20000
c-----------------------------------------------------------------------
317	thlev=43.7e-12
	call nucltransK(0.317,0.078,8.5e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Pt192: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Os186low(levelkeV)
c Subroutine describes the deexcitation process in Os186 nucleus
c after 2b-decay of W186 to ground 0+ and excited 2+ levels
c of Os186 (NDS 99(200301).
c Call  : call Os186low(levelkeV)
c Input : levelkeV - energy of Os186 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -   0 keV,
c                    2+(1)  - 137 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 24.06.2008.
	tclev=0.
	if(levelkev.eq.137) go to   137
	if(levelkev.eq.  0) go to 10000
	                    go to 20000
c-----------------------------------------------------------------------
137	thlev=875.e-12
c KLM ratios in accordance with BrIcc calculation
	call nucltransKLM(0.137,0.074,0.44,0.012,0.64,0.003,0.20,
     +                    0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Os186: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Os190low(levelkeV)
c Subroutine describes the deexcitation process in Os190 nucleus
c after eb+/2e decay of Pt190 to ground and excited 0+ and 2+ levels
c of Os190 (in accordance with NDS 99(2003)275 and NNDC on 22.07.2010).
c Level (0,1,2)+ at 1382 keV is supposed to be 0+.
c Call  : call Os190low(levelkeV)
c Input : levelkeV - energy of Os190 level (integer in keV) occupied
c	             initially; the following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  187 keV,
c                    2+(2)  -  558 keV,
c                    0+(1)  -  912 keV,
c                    2+(3)  - 1115 keV,
c                    0+(2)  - 1382 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.07.2010.
	tclev=0.
	if(levelkev.eq.1382) go to  1382
	if(levelkev.eq.1115) go to  1115
	if(levelkev.eq. 912) go to   912
	if(levelkev.eq. 558) go to   558
	if(levelkev.eq. 187) go to   187
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
1382	thlev=0.
	call nucltransK(1.196,0.074,3.5e-3,4.0e-6,tclev,thlev,tdlev)
	go to 187
c-----------------------------------------------------------------------
1115	thlev=0.
	p=100.*rnd1(d)
	if(p.le.28.8) go to 11151
	if(p.le.79.3) go to 11152
	if(p.le.97.0) go to 11153
	              go to 11154
11151	call nucltransK(1.115,0.074,4.0e-3,3.5e-7,tclev,thlev,tdlev)
	return
11152	call nucltransK(0.928,0.074,5.8e-3,0.,tclev,thlev,tdlev)
	go to 187
11153	call nucltransK(0.359,0.074,5.4e-2,0.,tclev,thlev,tdlev)
	go to 756
11154	call nucltransK(0.203,0.074,3.2e-1,0.,tclev,thlev,tdlev)
	go to 912
c-----------------------------------------------------------------------
912	thlev=15e-12
	p=100.*rnd1(d)
	if(p.le.77.3) go to 91201
	              go to 91202
91201	call nucltransK(0.725,0.074,9.7e-3,0.,tclev,thlev,tdlev)
	go to 187
91202	call nucltransK(0.354,0.074,6.0e-2,0.,tclev,thlev,tdlev)
	go to 558
c-----------------------------------------------------------------------
756	thlev=0.
	p=100.*rnd1(d)
	if(p.le.87.1) go to 75601
	if(p.le.91.7) go to 75602
	              go to 75603
75601	call nucltransK(0.569,0.074,1.7e-2,0.,tclev,thlev,tdlev)
	go to 187
75602	call nucltransK(0.208,0.074,3.0e-1,0.,tclev,thlev,tdlev)
	go to 548
75603	call nucltransK(0.198,0.074,3.5e-1,0.,tclev,thlev,tdlev)
	go to 558
c-----------------------------------------------------------------------
558	thlev=15.2e-12
	p=100.*rnd1(d)
	if(p.le.56.7) go to 55801
	              go to 55802
55801	call nucltransK(0.558,0.074,1.8e-2,0.,tclev,thlev,tdlev)
	return
55802	call nucltransK(0.371,0.074,5.1e-2,0.,tclev,thlev,tdlev)
	go to 187
c-----------------------------------------------------------------------
548	thlev=12.8e-12
	call nucltransK(0.361,0.074,5.4e-2,0.,tclev,thlev,tdlev)
	go to 187
c-----------------------------------------------------------------------
187	thlev=375e-12
	call nucltransK(0.187,0.074,4.25e-1,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Os190: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Hg198low(levelkeV)
c Subroutine describes the deexcitation process in Hg198 nucleus
c after 2b- decay of Pt198 to ground and excited 0+ and 2+ levels
c of Hg198 (in accordance with NDS 110(2009)2533 and NNDC on 30.07.2010).
c Call  : call Hg198low(levelkeV)
c Input : levelkeV - energy of Hg198 level (integer in keV) occupied
c	             initially; the following levels can be occupied:
c                    0+(gs) -    0 keV,
c                    2+(1)  -  412 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 30.07.2010.
	tclev=0.
	if(levelkev.eq. 412) go to   412
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
412	thlev=33.4e-12
	call nucltransK(0.412,0.083,4.4e-2,0.,tclev,thlev,tdlev)
	return
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Hg198: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine At214low(levelkeV)
c Subroutine describes the deexcitation process in At214 nucleus
c after 2b-decay of Bi214 to ground and excited levels
c of At214.
c Call  : call At214low(levelkeV)
c Input : levelkeV - energy of At214 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 10.12.2007.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'At214: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Po214low(levelkeV)
c Subroutine describes the deexcitation process in Po214 nucleus
c after 2b-decay of Pb214 to ground and excited 0+ and 2+ levels
c of Po214.
c Call  : call Po214low(levelkeV)
c Input : levelkeV - energy of Po214 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 19.11.2007.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Po214: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Rn218low(levelkeV)
c Subroutine describes the deexcitation process in Rn218 nucleus
c after 2b-decay of Po218 to ground and excited 0+ and 2+ levels
c of Rn218.
c Call  : call Rn218low(levelkeV)
c Input : levelkeV - energy of Rn218 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 10.12.2007.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Rn218: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************

	subroutine Ra222low(levelkeV)
c Subroutine describes the deexcitation process in Rn218 nucleus
c after 2b-decay of Po218 to ground and excited 0+ and 2+ levels
c of Rn218.
c Call  : call Ra222low(levelkeV)
c Input : levelkeV - energy of Ra222 level (integer in keV) occupied
c                    initially; following levels can be occupied:
c                    0+(gs) -    0 keV.
c Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
c VIT, 10.12.2007.
	tclev=0.
	if(levelkev.eq.   0) go to 10000
	                     go to 20000
c-----------------------------------------------------------------------
10000	return
c-----------------------------------------------------------------------
20000	print *,'Ra222: wrong level [keV] ',levelkev
c-----------------------------------------------------------------------
	return
	end

c***********************************************************************
c***************** Section of working subroutines **********************
c***********************************************************************

c***********************************************************************

	block data
	common/const/pi,emass,datamass(50)
	common/bj69plog/plog69(48)

	data pi/3.1415927/
	data emass/0.51099906/

c Particle masses (MeV) - in accordance with GEANT 3.21 manual of October,
c 1994:
c        1 - gamma         2 - positron     3 - electron
c        4 - neutrino      5 - muon+        6 - muon-
c        7 - pion0         8 - pion+        9 - pion-
c       10 - kaon0 long   11 - kaon+       12 - kaon-
c       13 - neutron      14 - proton      15 - antiproton
c       16 - kaon0 short  17 - eta         18 - lambda
c       19 - sigma+       20 - sigma0      21 - sigma-
c       22 - xi0          23 - xi-         24 - omega
c       25 - antineutron  26 - antilambda  27 - antisigma-
c       28 - antisigma0   29 - antisigma+  30 - antixi0
c       31 - antixi+      32 - antiomega+  45 - deuteron
c       46 - tritium      47 - alpha       48 - geantino
c       49 - He3          50 - Cerenkov
	data datamass/
     +     0.,         0.51099906,   0.51099906, 0.,      105.658389, !  1 -  5
     +   105.658389, 134.9764,     139.5700,   139.5700,  497.672,    !  6 - 10
     +   493.677,    493.677,      939.56563,  938.27231, 938.27231,  ! 11 - 15
     +   497.672,    547.45,      1115.684,   1189.37,   1192.55,     ! 16 - 20
     +  1197.436,   1314.9,       1321.32,    1672.45,    939.56563,  ! 21 - 25
     +  1115.684,   1189.37,      1192.55,    1197.436,  1314.9,      ! 26 - 30
     +  1321.32,    1672.45,         0.,         0.,        0.,       ! 31 - 35
     +     0.,         0.,           0.,         0.,        0.,       ! 35 - 40
     +     0.,         0.,           0.,         0.,     1875.613,    ! 41 - 45
     +  2809.25,    3727.417,        0.,      2809.23,      0./       ! 46 - 50

c Values of natural logarithm of the standard values of momentum 
c (in units m_e*c) from: 
c H.Behrens, J.Janecke, "Numerical tables for beta-decay and 
c electron capture", Berlin, Springer-Verlag, 1969.
c Range of momenta correspond to kinetic energy range from 2.55 keV to 25.0 MeV.
	data plog69/
c p      0.1         0.2         0.3         0.4         0.5
     +  -2.302585,  -1.609438,  -1.203973,  -0.9162907, -0.6931472,
c p      0.6         0.7         0.8         0.9         1.0
     +  -0.5108256, -0.3566750, -0.2231435, -0.1053605,  0.0000000,
c p      1.2         1.4         1.6         1.8         2.0
     +   0.1823216,  0.3364722,  0.4700036,  0.5877866,  0.6931472,
c p      2.2         2.4         2.6         2.8         3.0
     +   0.7884574,  0.8754688,  0.9555114,  1.029619,   1.098612,
c p      3.2         3.4         3.6         3.8         4.0
     +   1.163151,   1.223776,   1.280934,   1.335001,   1.386294,
c p      4.5         5.0         5.5         6.0         6.5
     +   1.504077,   1.609438,   1.704748,   1.791759,   1.871802,
c p      7.0         7.5         8.0         9.0        10.0
     +   1.945910,   2.014903,   2.079442,   2.197225,   2.302585,
c       11.0        12.0        13.0        14.0        16.0
     +   2.397895,   2.484907,   2.564949,   2.639057,   2.772589,
c       18.0        20.0        25.0        30.0        35.0
     +   2.890372,   2.995732,   3.218876,   3.401197,  3.555348,
c       40.0        45.0        50.0
     +   3.688879,   3.806663,   3.912023/

	end

c***********************************************************************

	subroutine gamma(E,tclev,thlev,tdlev)
c Generation of emission of gamma quantum with fixed energy
c isotropically in the whole space.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call gamma(E,tclev,thlev,tdlev)
c Input : E     - kinetic energy of particle (MeV);
c         tclev - time of creation of level from which particle will be
c                 emitted (sec);
c         thlev - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification (=1);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 15.10.1995.
	common/const/pi,emass,datamass(50)
	call particle(1,E,E,0.,pi,0.,2.*pi,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

	subroutine positron(E,tclev,thlev,tdlev)
c Generation of emission of positron with fixed energy
c isotropically in the whole space.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call positron(E,tclev,thlev,tdlev)
c Input : E     - kinetic energy of particle (MeV);
c         tclev - time of creation of level from which particle will be
c                 emitted (sec);
c         thlev - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification (=2);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 15.10.1995.
	common/const/pi,emass,datamass(50)
	call particle(2,E,E,0.,pi,0.,2.*pi,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

	subroutine electron(E,tclev,thlev,tdlev)
c Generation of emission of electron with fixed energy
c isotropically in the whole space.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call electron(E,tclev,thlev,tdlev)
c Input : E     - kinetic energy of particle (MeV);
c         tclev - time of creation of level from which particle will be
c                 emitted (sec);
c         thlev - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification (=3);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 15.10.1995.
	common/const/pi,emass,datamass(50)
	call particle(3,E,E,0.,pi,0.,2.*pi,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

	subroutine alpha(E,tclev,thlev,tdlev)
c Generation of emission of alpha particle with fixed energy
c isotropically in the whole space.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call alpha(E,tclev,thlev,tdlev)
c Input : E     - kinetic energy of particle (MeV);
c         tclev - time of creation of level from which particle will be
c                 emitted (sec);
c         thlev - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification (=47);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 15.10.1995.
	common/const/pi,emass,datamass(50)
	call particle(47,E,E,0.,pi,0.,2.*pi,tclev,thlev,tdlev)
	return
	end

c***********************************************************************

	subroutine particle(np,E1,E2,teta1,teta2,phi1,phi2,tclev,
     +                      thlev,tdlev)
c Generation of isotropical emission of particle in the range of
c energies and angles.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call particle(np,E1,E2,teta1,teta2,phi1,phi2,tclev,thlev,tdlev)
c Input : np          - GEANT number for particle identification:
c                        1 - gamma         2 - positron     3 - electron
c                        4 - neutrino      5 - muon+        6 - muon-
c                        7 - pion0         8 - pion+        9 - pion-
c                       10 - kaon0 long   11 - kaon+       12 - kaon-
c                       13 - neutron      14 - proton      15 - antiproton
c                       16 - kaon0 short  17 - eta         18 - lambda
c                       19 - sigma+       20 - sigma0      21 - sigma-
c                       22 - xi0          23 - xi-         24 - omega
c                       25 - antineutron  26 - antilambda  27 - antisigma-
c                       28 - antisigma0   29 - antisigma+  30 - antixi0
c                       31 - antixi+      32 - antiomega+  45 - deuteron
c                       46 - tritium      47 - alpha       48 - geantino
c                       49 - He3          50 - Cerenkov;
c         E1,E2       - range of kinetic energy of particle (MeV);
c         teta1,teta2 - range of teta angle (radians);
c         phi1,phi2   - range of phi  angle (radians);
c         tclev       - time of creation of level from which particle will be
c                       emitted (sec);
c         thlev       - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (=np of input);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 15.10.1995.
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	common/const/pi,emass,datamass(50)
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +    'PARTICLE: in event more than 100 particles ',npfull
d	if(np.lt.1.or.np.gt.50.or.(np.gt.32.and.np.lt.45)) print *,
d    1     'PARTICLE: unknown particle number ',np
	npgeant(npfull)=np
	pmass=datamass(np)
	phi=phi1+(phi2-phi1)*rnd1(d)
	ctet1=1.
	if(teta1.ne.0.) ctet1=cos(teta1)
	ctet2=-1.
	if(teta2.ne.pi) ctet2=cos(teta2)
	ctet=ctet1+(ctet2-ctet1)*rnd1(d)
	stet=sqrt(1.-ctet*ctet)
	E=E1
	if(E1.ne.E2) E=E1+(E2-E1)*rnd1(d)
	p=sqrt(E*(E+2.*pmass))
	pmoment(1,npfull)=p*stet*cos(phi)
	pmoment(2,npfull)=p*stet*sin(phi)
	pmoment(3,npfull)=p*ctet
	tdlev=tclev
	if(thlev.gt.0.) tdlev=tclev-thlev/alog(2.)*alog(rnd1(d))
	ptime(npfull)=tdlev
	return
	end

c***********************************************************************

	subroutine beta(Qbeta,Zdtr,tcnuc,thnuc,tdnuc)
c Subroutine beta simulates the angles and energy of beta particles
c emitted in beta decay of nucleus. The decay is considered as allowed.
c Only Coulomb correction to the shape of energy spectrum is taken
c into consideration.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call beta(Qbeta,Zdtr,tcnuc,thnuc,tdnuc)
c Input : Qbeta    - beta energy endpoint (MeV; Qbeta>50 eV);
c         Zdtr     - atomic number of daughter nucleus (Zdtr>0 for e- and
c                    Zdtr<0 for e+ particles);
c         tcnuc - time of creation of nucleus (sec);
c         thnuc - nucleus halflife (sec).
c Output: tdnuc               - time of decay of nucleus (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (2 for beta+ and 3 for beta- decay);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 30.07.1992; 15.10.1995.
	external funbeta
	common/const/pi,emass,datamass(50)
	common/parbeta/z,q
	z=Zdtr
	q=Qbeta
	call tgold(50.e-6,Qbeta,funbeta,0.001*Qbeta,2,em,fm)
1	E=50.e-6+(Qbeta-50.e-6)*rnd1(d)
	fe=funbeta(E)
	f=fm*rnd1(d)
	if(f.gt.fe) go to 1
	if(Zdtr.ge.0.) np=3
	if(Zdtr.lt.0.) np=2
c isotropical emission of beta particle is supposed
	call particle(np,E,E,0.,pi,0.,2.*pi,tcnuc,thnuc,tdnuc)
	return
	end

c***********************************************************************

	function funbeta(E)
c Function to search the maximum of beta spectrum curve by tgold
c subroutine.
c VIT, 30.07.1992; 15.10.1995.
	common/const/pi,emass,datamass(50)
	common/parbeta/Zdtr,Qbeta
	funbeta=0.
	if(E.gt.0.) funbeta=sqrt(E*(E+2.*emass))*(E+emass)*(Qbeta-E)**2
     +                   *fermi(Zdtr,E)
	return
	end

c***********************************************************************

	subroutine beta1(Qbeta,Zdtr,tcnuc,thnuc,tdnuc,c1,c2,c3,c4)
c Subroutine beta1 simulates the angles and energy of beta particles
c emitted in beta decay of nucleus. The decay is considered as forbidden;
c correction factor to the allowed spectrum shape has a form
c typical for empirical corrections:
c cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), w=e/emass+1.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call beta1(Qbeta,Zdtr,tcnuc,thnuc,tdnuc,c1,c2,c3,c4)
c Input : Qbeta       - beta energy endpoint (MeV; Qbeta>50 eV);
c         Zdtr        - atomic number of daughter nucleus (Zdtr>0 for e- and
c                       Zdtr<0 for e+ particles);
c         tcnuc       - time of creation of nucleus (sec);
c         thnuc       - nucleus halflife (sec);
c         c1,c2,c3,c4 - coefficients in correction factor to the allowed spectrum
c                       shape cf(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), 
c                       where w=e/emass+1, e - kinetic energy of electron.                        .
c Output: tdnuc               - time of decay of nucleus (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (2 for beta+ and 3 for beta- decay);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 30.07.1992; 15.10.1995; 31.03.2006.
	external funbeta1
	common/const/pi,emass,datamass(50)
	common/parbeta/z,q
	common/parbeta1/c1h,c2h,c3h,c4h
	z=Zdtr
	q=Qbeta
	c1h=c1
	c2h=c2
	c3h=c3
	c4h=c4
	call tgold(50.e-6,Qbeta,funbeta1,0.001*Qbeta,2,em,fm)
1	E=50.e-6+(Qbeta-50.e-6)*rnd1(d)
	fe=funbeta1(E)
	f=fm*rnd1(d)
	if(f.gt.fe) go to 1
	if(Zdtr.ge.0.) np=3
	if(Zdtr.lt.0.) np=2
c isotropical emission of beta particle is supposed
	call particle(np,E,E,0.,pi,0.,2.*pi,tcnuc,thnuc,tdnuc)
	return
	end

c***********************************************************************

	function funbeta1(E)
c Function to search the maximum of beta spectrum curve by tgold
c subroutine.
c VIT, 30.07.1992; 15.10.1995; 31.03.2006.
	common/const/pi,emass,datamass(50)
	common/parbeta/Zdtr,Qbeta
	common/parbeta1/c1,c2,c3,c4
	funbeta1=0.
	if(E.gt.0.) then
c allowed spectrum
	   all=sqrt(E*(E+2.*emass))*(E+emass)*(Qbeta-E)**2*fermi(Zdtr,E)
c correction factor
	   w=E/emass+1.
	   cf=1.+c1/w+c2*w+c3*w**2+c4*w**3
c spectrum with correction
	   funbeta1=all*cf
	endif
	return
	end

c***********************************************************************

	subroutine beta2(Qbeta,Zdtr,tcnuc,thnuc,tdnuc,kf,c1,c2,c3,c4)
c Subroutine beta2 simulates the angles and energy of beta particles
c emitted in beta decay of nucleus. The decay is considered as forbidden;
c correction factor to the allowed spectrum shape has one of a form,
c typical for unique k-forbidden spectra:
c k=1: cf(e)=pel**2+c1*       pnu**2,
c k=2: cf(e)=pel**4+c1*pel**2*pnu**2+c2*       pnu**4,
c k=3: cf(e)=pel**6+c1*pel**4*pnu**2+c2*pel**2*pnu**4+c3*       pnu**6,
c k=4: cf(e)=pel**8+c1*pel**6*pnu**2+c2*pel**4*pnu**4+c3*pel**2*pnu**6+c4*pnu**8,
c where pel and pnu are impulses of electron and neutrino:
c pel=sqrt(w**2-1), pnu=(Qbeta-e)/emass , w=e/emass+1.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call beta2(Qbeta,Zdtr,tcnuc,thnuc,tdnuc,kf,c1,c2,c3,c4)
c Input : Qbeta       - beta energy endpoint (MeV; Qbeta>50 eV);
c         Zdtr        - atomic number of daughter nucleus (Zdtr>0 for e- and
c                       Zdtr<0 for e+ particles);
c         tcnuc       - time of creation of nucleus (sec);
c         thnuc       - nucleus halflife (sec);
c         kf          - degree of forbiddeness for unique spectra;
c         c1,c2,c3,c4 - coefficients in correction factor to the allowed spectrum
c                       shape - see above.
c Output: tdnuc               - time of decay of nucleus (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (2 for beta+ and 3 for beta- decay);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 30.07.1992; 15.10.1995; 31.03.2006.
	external funbeta2
	common/const/pi,emass,datamass(50)
	common/parbeta/z,q
	common/parbeta2/kfh,c1h,c2h,c3h,c4h
	z=Zdtr
	q=Qbeta
	kfh=kf
	c1h=c1
	c2h=c2
	c3h=c3
	c4h=c4
	call tgold(50.e-6,Qbeta,funbeta2,0.001*Qbeta,2,em,fm)
1	E=50.e-6+(Qbeta-50.e-6)*rnd1(d)
	fe=funbeta2(E)
	f=fm*rnd1(d)
	if(f.gt.fe) go to 1
	if(Zdtr.ge.0.) np=3
	if(Zdtr.lt.0.) np=2
c isotropical emission of beta particle is supposed
	call particle(np,E,E,0.,pi,0.,2.*pi,tcnuc,thnuc,tdnuc)
	return
	end

c***********************************************************************

	function funbeta2(E)
c Function to search the maximum of beta spectrum curve by tgold
c subroutine.
c VIT, 30.07.1992; 15.10.1995; 31.03.2006.
	common/const/pi,emass,datamass(50)
	common/parbeta/Zdtr,Qbeta
	common/parbeta2/kf,c1,c2,c3,c4
	funbeta2=0.
	if(E.gt.0.) then
c allowed spectrum
	   all=sqrt(E*(E+2.*emass))*(E+emass)*(Qbeta-E)**2*fermi(Zdtr,E)
c correction factor
	   w=E/emass+1.
	   pel=sqrt(w**2-1.)
	   pnu=(Qbeta-E)/emass
	   cf=1.
	   if(kf.eq.1) cf=pel**2+c1*pnu**2
	   if(kf.eq.2) cf=pel**4+c1*pel**2*pnu**2+c2*pnu**4
	   if(kf.eq.3) cf=pel**6+c1*pel**4*pnu**2+c2*pel**2*pnu**4+
     +                  c3*pnu**6
	   if(kf.eq.4) cf=pel**8+c1*pel**6*pnu**2+c2*pel**4*pnu**4+
     +                  c3*pel**2*pnu**6+c4*pnu**8
c spectrum with correction
	   funbeta2=all*cf
	endif
	return
	end

c***********************************************************************

	subroutine beta_1fu(Qbeta,Zdtr,tcnuc,thnuc,tdnuc,c1,c2,c3,c4)
c Subroutine beta_1fu simulates the angles and energy of beta particles
c emitted in beta decay of nucleus. The decay is considered as 1st-forbidden
c unique. Its shape is product of theoretical spectrum shape for allowed 
c decay and two correction factors:
c 1. theoretical of BJ'1969 
c       cf1(e)=pnu**2+lamda2*pel**2,
c       where lambda2 is the Coulomb function calculated in BJ'1969,
c       and pel and pnu are impulses of electron and neutrino:
c       pel=sqrt(w**2-1), pnu=(Qbeta-e)/emass , w=e/emass+1;
c 2. empirical correction 
c       cf2(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3).
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call beta_1fu(Qbeta,Zdtr,tcnuc,thnuc,tdnuc,c1,c2,c3,c4)
c Input : Qbeta       - beta energy endpoint (MeV; Qbeta>50 eV);
c         Zdtr        - atomic number of daughter nucleus (Zdtr>0 for e- and
c                       Zdtr<0 for e+ particles);
c         tcnuc       - time of creation of nucleus (sec);
c         thnuc       - nucleus halflife (sec);
c         c1,c2,c3,c4 - coefficients in correction factor to the spectrum
c                       shape cf2(e)=(1+c1/w+c2*w+c3*w**2+c4*w**3), 
c                       where w=e/emass+1, e - kinetic energy of electron.                        .
c Output: tdnuc               - time of decay of nucleus (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (2 for beta+ and 3 for beta- decay);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 24.10.2006.
	external funbeta_1fu
	common/const/pi,emass,datamass(50)
	common/parbeta/z,q
	common/parbeta1/c1h,c2h,c3h,c4h
	common/bj69plog/plog69(48)
	common/bj69sl2/sl2(48)
	z=Zdtr
	q=Qbeta
	c1h=c1
	c2h=c2
	c3h=c3
	c4h=c4
c Values of the "lambda2" Coulomb function for some Zdtr values from:
c H.Behrens, J.Janecke, "Numerical tables for beta-decay and electron 
c capture", Berlin, Springer-Verlag, 1969.
c Values are calculated as product between unscreened lambda2 (Table II of BJ'1969)
c and screened corrections (Table III), and are given for "standard" values of 
c momentum (0.1-50.0 in units of m_e*c). (Log values of these momenta are in array
c plog69.) 
	do i=1,48
	   sl2(i)=1.
	enddo
	if    (int(Zdtr).eq.19) then    ! 39-Ar, Q_beta=0.565 
	   sl2( 1)=2.0929               ! p=0.1
	   sl2( 2)=1.2337               ! p=0.2
	   sl2( 3)=1.0747               ! p=0.3
	   sl2( 4)=1.0234               ! p=0.4
	   sl2( 5)=0.99977              ! p=0.5
	   sl2( 6)=0.98728              ! p=0.6
	   sl2( 7)=0.98024              ! p=0.7
	   sl2( 8)=0.97624              ! p=0.8
	   sl2( 9)=0.97445              ! p=0.9
	   sl2(10)=0.97377              ! p=1.0
	   sl2(11)=0.97406              ! p=1.2
	   sl2(12)=0.97549              ! p=1.4
	   sl2(13)=0.9757               ! p=1.6
	   sl2(14)=0.9754               ! p=1.8
	   sl2(15)=0.9754               ! p=2.0
    	   sl2(16)=0.9756               ! p=2.2
    	   sl2(17)=0.9760               ! p=2.4, E=0.818
	elseif(int(Zdtr).eq.20) then    ! 42-Ar, Q_beta=0.600 + 42-K, Q_beta=3.525 
	   sl2( 1)=2.2248               ! p=0.1
	   sl2( 2)=1.2634               ! p=0.2
	   sl2( 3)=1.0851               ! p=0.3
	   sl2( 4)=1.0275               ! p=0.4
	   sl2( 5)=1.0008               ! p=0.5
	   sl2( 6)=0.98693              ! p=0.6
	   sl2( 7)=0.97884              ! p=0.7
	   sl2( 8)=0.97426              ! p=0.8
	   sl2( 9)=0.97213              ! p=0.9
	   sl2(10)=0.97128              ! p=1.0
	   sl2(11)=0.97138              ! p=1.2
	   sl2(12)=0.97276              ! p=1.4
	   sl2(13)=0.9731               ! p=1.6
	   sl2(14)=0.9728               ! p=1.8
	   sl2(15)=0.9728               ! p=2.0
    	   sl2(16)=0.9731               ! p=2.2
    	   sl2(17)=0.9735               ! p=2.4
	   sl2(18)=0.9740               ! p=2.6
	   sl2(19)=0.9745               ! p=2.8
	   sl2(20)=0.9750               ! p=3.0
	   sl2(21)=0.9756               ! p=3.2
	   sl2(22)=0.9762               ! p=3.4
	   sl2(23)=0.9768               ! p=3.6
	   sl2(24)=0.9774               ! p=3.8
	   sl2(25)=0.9780               ! p=4.0
	   sl2(26)=0.9794               ! p=4.5
	   sl2(27)=0.9808               ! p=5.0
	   sl2(28)=0.9821               ! p=5.5
	   sl2(29)=0.9834               ! p=6.0
	   sl2(30)=0.9846               ! p=6.5
	   sl2(31)=0.9859               ! p=7.0
	   sl2(32)=0.9870               ! p=7.5
	   sl2(33)=0.9882               ! p=8.0
	   sl2(34)=0.9903               ! p=9.0
	   sl2(35)=0.9924               ! p=10.0, E=4.625
	elseif(int(Zdtr).eq.39) then    ! 90-Sr, Q_beta=0.546 
	   sl2( 1)=5.6836               ! p=0.1
	   sl2( 2)=2.0435               ! p=0.2
	   sl2( 3)=1.3704               ! p=0.3
	   sl2( 4)=1.1386               ! p=0.4
	   sl2( 5)=1.0327               ! p=0.5
	   sl2( 6)=0.97761              ! p=0.6
	   sl2( 7)=0.94571              ! p=0.7
	   sl2( 8)=0.92621              ! p=0.8
	   sl2( 9)=0.91383              ! p=0.9
	   sl2(10)=0.90577              ! p=1.0
	   sl2(11)=0.89708              ! p=1.2
	   sl2(12)=0.89379              ! p=1.4
	   sl2(13)=0.89354              ! p=1.6
	   sl2(14)=0.89479              ! p=1.8
	   sl2(15)=0.89695              ! p=2.0
    	   sl2(16)=0.89953              ! p=2.2
    	   sl2(17)=0.90229              ! p=2.4, E=0.818
	elseif(int(Zdtr).eq.40) then    ! 90-Y, Q_beta=2.228 
	   sl2( 1)=5.8992               ! p=0.1
	   sl2( 2)=2.0922               ! p=0.2
	   sl2( 3)=1.3883               ! p=0.3
	   sl2( 4)=1.1454               ! p=0.4
	   sl2( 5)=1.0345               ! p=0.5
	   sl2( 6)=0.97692              ! p=0.6
	   sl2( 7)=0.94344              ! p=0.7
	   sl2( 8)=0.92294              ! p=0.8
	   sl2( 9)=0.90998              ! p=0.9
	   sl2(10)=0.90153              ! p=1.0
	   sl2(11)=0.89243              ! p=1.2
	   sl2(12)=0.88892              ! p=1.4
	   sl2(13)=0.88848              ! p=1.6
	   sl2(14)=0.88970              ! p=1.8
	   sl2(15)=0.89186              ! p=2.0
    	   sl2(16)=0.89454              ! p=2.2
    	   sl2(17)=0.89739              ! p=2.4
	   sl2(18)=0.90037              ! p=2.6
	   sl2(19)=0.90330              ! p=2.8
	   sl2(20)=0.90631              ! p=3.0
	   sl2(21)=0.90931              ! p=3.2
	   sl2(22)=0.91223              ! p=3.4
	   sl2(23)=0.91507              ! p=3.6
	   sl2(24)=0.9174               ! p=3.8
	   sl2(25)=0.9195               ! p=4.0
	   sl2(26)=0.9246               ! p=4.5
	   sl2(27)=0.9295               ! p=5.0
	   sl2(28)=0.9343               ! p=5.5
	   sl2(29)=0.9388               ! p=6.0
	   sl2(30)=0.9432               ! p=6.5, E=2.850
	elseif(int(Zdtr).eq.56) then    ! 137-Cs, Q_beta=0.514 (to level 0.662)
	   sl2( 1)=9.3262               ! p=0.1
	   sl2( 2)=2.8592               ! p=0.2
	   sl2( 3)=1.6650               ! p=0.3
	   sl2( 4)=1.2481               ! p=0.4
	   sl2( 5)=1.0580               ! p=0.5
	   sl2( 6)=0.95794              ! p=0.6
	   sl2( 7)=0.89948              ! p=0.7
	   sl2( 8)=0.86350              ! p=0.8
	   sl2( 9)=0.84043              ! p=0.9
	   sl2(10)=0.82535              ! p=1.0
	   sl2(11)=0.80875              ! p=1.2
	   sl2(12)=0.80209              ! p=1.4
	   sl2(13)=0.80046              ! p=1.6
	   sl2(14)=0.80152              ! p=1.8
	   sl2(15)=0.80409              ! p=2.0
    	   sl2(16)=0.80752              ! p=2.2
    	   sl2(17)=0.81167              ! p=2.4, E=0.818
	endif
	call tgold(50.e-6,Qbeta,funbeta_1fu,0.001*Qbeta,2,em,fm)
1	E=50.e-6+(Qbeta-50.e-6)*rnd1(d)
	fe=funbeta_1fu(E)
	f=fm*rnd1(d)
	if(f.gt.fe) go to 1
	if(Zdtr.ge.0.) np=3
	if(Zdtr.lt.0.) np=2
c isotropical emission of beta particle is supposed
	call particle(np,E,E,0.,pi,0.,2.*pi,tcnuc,thnuc,tdnuc)
	return
	end

c***********************************************************************

	function funbeta_1fu(E)
c Function to search the maximum of beta spectrum curve by tgold
c subroutine.
c VIT, 26.10.2006.
	common/const/pi,emass,datamass(50)
	common/parbeta/Zdtr,Qbeta
	common/parbeta1/c1,c2,c3,c4
	common/bj69plog/plog69(48)
	common/bj69sl2/sl2(48)
	funbeta_1fu=0.
	if(E.gt.0.) then
c allowed spectrum
	   all=sqrt(E*(E+2.*emass))*(E+emass)*(Qbeta-E)**2*fermi(Zdtr,E)
c correction factor 1 (theoretical)
	   w=E/emass+1.
	   pel=sqrt(w**2-1.)
	   pnu=(Qbeta-E)/emass
c calculation of the screened lambda2 value by interpolation of the table 
c with the help of the divdif CERN function for logarithms of p
	   pellog=alog(pel) 
	   scrl2=divdif(sl2,plog69,48,pellog,2)
	   cf1=pnu**2+scrl2*pel**2
c correction factor 2 (empirical)
	   cf2=1.+c1/w+c2*w+c3*w**2+c4*w**3
c spectrum with correction
	   funbeta_1fu=all*cf1*cf2
	endif
	return
	end

c***********************************************************************

	function fermi(Z,E)
c Function fermi calculates the traditional function of Fermi in
c theory of beta decay to take into account the Coulomb correction
c to the shape of electron/positron energy spectrum.
c Call  : corr=fermi(Z,E)
c Input : Z - atomic number of daughter nuclei (>0 for e-, <0 for e+);
c         E - kinetic energy of particle (MeV; E>50 eV).
c Output: corr - value of correction factor (without normalization -
c                constant factors are removed - for MC simulation).
c V.I.Tretyak, 15.07.1992.
	complex carg,cgamma
	if(E.lt.50.e-6) E=50.e-6
	alfaz=Z/137.036
	w=E/0.511+1.
	p=sqrt(w*w-1.)
	y=alfaz*w/p
	g=sqrt(1.-alfaz**2)
	carg=cmplx(g,y)
	fermi=p**(2.*g-2.)*exp(3.1415927*y+2.*alog(cabs(cgamma(carg))))
	return
	end

c***********************************************************************

	subroutine tgold(a,b,f,eps,minmax,xextr,fextr)
c Subroutine tgold determines maximum or minimum of the function f(x) in
c the interval [a,b] by the gold section method.
c Call : 	external f
c		call tgold(a,b,f,eps,minmax,xextr,fextr)
c Input:	a,b    - beginning and the end of the interval [a,b];
c 		f      - name of the external function; should be as
c                        function f(x), and additional parameters have
c                        to be transmitted with help of common blocks;
c		eps    - desired uncertainty of xextr determination;
c		minmax - if minmax = 1 minimum of f(x) is searched,
c		                   = 2 maximum of f(x) is searched.
c Output:	xextr  - x-point of extremum;
c		fextr  - f(xextr).
c V.Tretyak, 25.09.1985.
	qc=0.61803395
	al=a
	bl=b
	xp=al+(bl-al)*qc
	xl=bl-(bl-al)*qc
	yp=f(xp)
	yl=f(xl)
3	goto (4,5) minmax
4	if(yp.lt.yl) goto 1
	goto 6
5	if(yp.gt.yl) goto 1
6	bl=xp
	xp=xl
	yp=yl
	xl=bl-(bl-al)*qc
	yl=f(xl)
	goto 2
1	al=xl
	xl=xp
	yl=yp
	xp=al+(bl-al)*qc
	yp=f(xp)
2	if((bl-al).gt.eps) goto 3
	xextr=0.5*(al+bl)
	fextr=f(xextr)
	return
	end

c***********************************************************************

	subroutine pair(Epair,tclev,thlev,tdlev)
c Generation of e+e- pair in zero-approximation to real subroutine for
c INTERNAL pair creation:
c    1) energy of e+ is equal to the energy of e-;
c    2) e+ and e- are emitted in the same direction.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call pair(Epair,tclev,thlev,tdlev)
c Input:  Epair - kinetic energy of e+e- pair (MeV);
c         tclev - time of creation of level from which pair will be
c                 emitted (sec);
c         thlev - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of last particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (2 for e+ and 3 for e-);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 3.08.1992; 15.10.1995.
	common/const/pi,emass,datamass(50)
	phi=2.*pi*rnd1(d)
	ctet=-1.+2.*rnd1(d)
	teta=acos(ctet)
	E=0.5*Epair
	call particle(2,E,E,teta,teta,phi,phi,tclev,thlev,tdlev)
c	call particle(3,E,E,teta,teta,phi,phi,tdlev,0.,tdlev)  ! for real time
	call particle(3,E,E,teta,teta,phi,phi,0.,0.,tdlev)     ! for time shift
	return
	end

c***********************************************************************

	subroutine nucltransK(Egamma,Ebinde,conve,convp,tclev,
     +                        thlev,tdlev)
c Subroutine nucltransK choise one of the three concurent processes
c by which the transition from one nuclear state to another is
c occured: gamma-ray emission, internal conversion and internal
c pair creation. Conversion electrons are emitted only with one fixed energy
c (usually with Egamma-E(K)_binding_energy).
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call nucltransK(Egamma,Ebinde,conve,convp,tclev,thlev,tdlev)
c Input : Egamma - gamma-ray energy (MeV) [=difference in state energies];
c         Ebinde - binding energy of electron (MeV);
c         conve  - internal electron conversion coefficient [=Nelectron/Ngamma];
c         convp  - pair conversion coefficient [=Npair/Ngamma];
c         tclev  - time of creation of level from which particle will be
c                  emitted (sec);
c         thlev  - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of last particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (1 for gamma, 2 for e+ and 3 for e-);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 27.07.1992; 15.10.1995.
	common/const/pi,emass,datamass(50)
	p=(1.+conve+convp)*rnd1(d)
	if(p.le.1.) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.1.+conve) then
	   call electron(Egamma-Ebinde,tclev,thlev,tdlev)
c	   call gamma(Ebinde,tdlev,0.,tdlev)                ! for real time
	   call gamma(Ebinde,0.,0.,tdlev)                   ! for time shift
	else
	   call pair(Egamma-2.*emass,tclev,thlev,tdlev)
	end if
	return
	end

c***********************************************************************

	subroutine nucltransKL(Egamma,EbindeK,conveK,EbindeL,conveL,
     +                         convp,tclev,thlev,tdlev)
c Subroutine nucltransKL choise one of the three concurent processes
c by which the transition from one nuclear state to another is
c occured: gamma-ray emission, internal conversion and internal
c pair creation. Conversion electrons are emitted with two fixed energies
c (Egamma-E(K)_binding_energy and Egamma-E(L)_binding_energy).
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call nucltransKL(Egamma,EbindeK,conveK,EbindeL,conveL,convp,
c                          tclev,thlev,tdlev)
c Input:  Egamma  - gamma-ray energy (MeV) [=difference in state energies];
c         EbindeK - binding energy of electron (MeV) on K-shell;
c         conveK  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   K-shell;
c         EbindeL - binding energy of electron (MeV) on L-shell;
c         conveL  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   L-shell;
c         convp   - pair conversion coefficient [=Npair/Ngamma];
c         tclev   - time of creation of level from which particle will be
c                   emitted (sec);
c         thlev   - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of last particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (1 for gamma, 2 for e+ and 3 for e-);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 5.07.1995.
	common/const/pi,emass,datamass(50)
	p=(1.+conveK+conveL+convp)*rnd1(d)
	if(p.le.1.) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.1.+conveK) then
	   call electron(Egamma-EbindeK,tclev,thlev,tdlev)
c	   call gamma(EbindeK,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeK,0.,0.,tdlev)                   ! for time shift
	else if(p.le.1.+conveK+conveL) then
	   call electron(Egamma-EbindeL,tclev,thlev,tdlev)
c	   call gamma(EbindeL,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeL,0.,0.,tdlev)                   ! for time shift
	else
	   call pair(Egamma-2.*emass,tclev,thlev,tdlev)
	end if
	return
	end

c***********************************************************************

	subroutine nucltransKLM(Egamma,EbindeK,conveK,EbindeL,conveL,
     +                          EbindeM,conveM,convp,tclev,thlev,tdlev)
c Subroutine nucltransKLM choises one of the three concurent processes
c by which the transition from one nuclear state to another is
c occured: gamma-ray emission, internal conversion and internal
c pair creation. Conversion electrons are emitted with three fixed energies:
c Egamma-E(K)_binding_energy, Egamma-E(L)_binding_energy and 
c Egamma-E(M)_binding_energy).
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call nucltransKLM(Egamma,EbindeK,conveK,EbindeL,conveL,
c                           EbindeM,conveM,convp,tclev,thlev,tdlev)
c Input:  Egamma  - gamma-ray energy (MeV) [=difference in state energies];
c         EbindeK - binding energy of electron (MeV) on K-shell;
c         conveK  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   K-shell;
c         EbindeL - binding energy of electron (MeV) on L-shell;
c         conveL  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   L-shell;
c         EbindeM - binding energy of electron (MeV) on M-shell;
c         convem  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   M-shell;
c         convp   - pair conversion coefficient [=Npair/Ngamma];
c         tclev   - time of creation of level from which particle will be
c                   emitted (sec);
c         thlev   - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of last particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (1 for gamma, 2 for e+ and 3 for e-);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 4.01.2007.
	common/const/pi,emass,datamass(50)
	p=(1.+conveK+conveL+conveM+convp)*rnd1(d)
	if(p.le.1.) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.1.+conveK) then
	   call electron(Egamma-EbindeK,tclev,thlev,tdlev)
c	   call gamma(EbindeK,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeK,0.,0.,tdlev)                   ! for time shift
	else if(p.le.1.+conveK+conveL) then
	   call electron(Egamma-EbindeL,tclev,thlev,tdlev)
c	   call gamma(EbindeL,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeL,0.,0.,tdlev)                   ! for time shift
	else if(p.le.1.+conveK+conveL+conveM) then
	   call electron(Egamma-EbindeM,tclev,thlev,tdlev)
c	   call gamma(EbindeM,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeM,0.,0.,tdlev)                   ! for time shift
	else
	   call pair(Egamma-2.*emass,tclev,thlev,tdlev)
	end if
	return
	end

c***********************************************************************

	subroutine nucltransKLM_Pb(Egamma,EbindeK,conveK,EbindeL,conveL,
     +                          EbindeM,conveM,convp,tclev,thlev,tdlev)
c
c The same as nucltransKLM but two X rays are emitted after K conversion
c in deexcitation of 208-Pb in decay 208Tl->208Pb. 
c VIT, 4.02.2009.
c
c Subroutine nucltransKLM choises one of the three concurent processes
c by which the transition from one nuclear state to another is
c occured: gamma-ray emission, internal conversion and internal
c pair creation. Conversion electrons are emitted with three fixed energies:
c Egamma-E(K)_binding_energy, Egamma-E(L)_binding_energy and 
c Egamma-E(M)_binding_energy).
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call nucltransKLM(Egamma,EbindeK,conveK,EbindeL,conveL,
c                           EbindeM,conveM,convp,tclev,thlev,tdlev)
c Input:  Egamma  - gamma-ray energy (MeV) [=difference in state energies];
c         EbindeK - binding energy of electron (MeV) on K-shell;
c         conveK  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   K-shell;
c         EbindeL - binding energy of electron (MeV) on L-shell;
c         conveL  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   L-shell;
c         EbindeM - binding energy of electron (MeV) on M-shell;
c         convem  - internal conversion coefficient [=Nelectron/Ngamma] from
c                   M-shell;
c         convp   - pair conversion coefficient [=Npair/Ngamma];
c         tclev   - time of creation of level from which particle will be
c                   emitted (sec);
c         thlev   - level halflife (sec).
c Output: tdlev               - time of decay of level (sec);
c         tevst               - time of event's start (sec);
c         npfull              - current number of last particle in event;
c         npgeant(npfull)     - GEANT number for particle identification
c                               (1 for gamma, 2 for e+ and 3 for e-);
c         pmoment(1-3,npfull) - x,y,z components of particle momentum (MeV);
c         ptime(npfull)       - time shift from previous time to calculate
c                               when particle was emitted (sec).
c VIT, 4.01.2007.
	common/const/pi,emass,datamass(50)
	p=(1.+conveK+conveL+conveM+convp)*rnd1(d)
	if(p.le.1.) then
	   call gamma(Egamma,tclev,thlev,tdlev)
	else if(p.le.1.+conveK) then
	   call electron(Egamma-EbindeK,tclev,thlev,tdlev)
c	   call gamma(EbindeK,tdlev,0.,tdlev)                ! for real time
c	   call gamma(EbindeK,0.,0.,tdlev)                   ! for time shift
c emission of two X rays with E(X1)+E(X2)=EbindeK instead of one 
c with E(X)=EbindeK; probabilities are from ToI'98, Appendix F.5.a (Table 7a).
c VIT, 4.02.2009.
	   p1=100.*rnd1(d)
c 73.9% - E(X1)=74 keV, 21.3% - E(X1)=85 keV
	   if(p1.le.73.9) then
	      call gamma(0.074,0.,0.,tdlev)                
	      call gamma(0.014,0.,0.,tdlev)                
	   else if(p1.le.95.2) then
	      call gamma(0.085,0.,0.,tdlev)                
	      call gamma(0.003,0.,0.,tdlev)                
c in 4.8% few low energy particles are emitted; they are neglected
	   end if                     
	else if(p.le.1.+conveK+conveL) then
	   call electron(Egamma-EbindeL,tclev,thlev,tdlev)
c	   call gamma(EbindeL,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeL,0.,0.,tdlev)                   ! for time shift
	else if(p.le.1.+conveK+conveL+conveM) then
	   call electron(Egamma-EbindeM,tclev,thlev,tdlev)
c	   call gamma(EbindeM,tdlev,0.,tdlev)                ! for real time
	   call gamma(EbindeM,0.,0.,tdlev)                   ! for time shift
	else
	   call pair(Egamma-2.*emass,tclev,thlev,tdlev)
	end if
	return
	end

c***********************************************************************

	function tsimpr(f,a,b,h)
c Function tsimpr calculates the value of integral of function f from a to b
c with step h using Simpson's formula.
c (b-a)/h must be equal 2*m where m is integer.
c Function f must be decribed as external in main program.
c VIT, DLP KINR, 20.11.1984.
	n=(b-a)/h-1
	fi=f(a)-f(b)
	x1=a
	x2=a
	ni=1
1	x1=x2+h
	x2=x1+h
	fi=fi+4.*f(x1)+2.*f(x2)
	ni=ni+2
	if(ni.lt.n) go to 1
	tsimpr=fi*h/3.
	return
	end

c***********************************************************************

	function rnd1(x)
c Function rnd1 gives random number from 0 to 1 by using the most 
c convenient or available to user random number generator (CERN, IMSL,
c internal FORTRAN, etc.). Please, choose what you want.
c VIT, 15.11.2006.
	dimension r(1)

c CERN rndm as random number generator
c	rnd1=rndm(d)

c CERN ranlux as random number generator
	call ranlux(r,1)
	rnd1=r(1)

	return
	end

c***********************************************************************

	subroutine compton(E1,E2,teta1,teta2,phi1,phi2)
c
c To sample the momentum of initial gamma quantum for COMPTON1 subroutine
c and store the momenta of scattered gamma and electron in common/genevent/.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call compton(E1,E2,teta1,teta2,phi1,phi2)
c Input : E1,E2       - range of kinetic energy of gamma (MeV);
c         teta1,teta2 - range of teta angle (radians);
c         phi1,phi2   - range of phi  angle (radians);
c Output: see description of common/genevent/. Times emission of scattered
c         gamma quantum and electron are supposed to be 0.
c VIT, 11.12.1995.
c
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	common/const/pi,emass,datamass(50)
	dimension pg0(3),pg1(3),pe1(3)
	phi=phi1+(phi2-phi1)*rnd1(d)
	ctet1=1.
	if(teta1.ne.0.) ctet1=cos(teta1)
	ctet2=-1.
	if(teta2.ne.pi) ctet2=cos(teta2)
	ctet=ctet1+(ctet2-ctet1)*rnd1(d)
	stet=sqrt(1.-ctet*ctet)
	E=E1
	if(E1.ne.E2) E=E1+(E2-E1)*rnd1(d)
	p=E
	pg0(1)=p*stet*cos(phi)
	pg0(2)=p*stet*sin(phi)
	pg0(3)=p*ctet
	call compton1(pg0,pg1,pe1)
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +     'COMPTON: in event more than 100 particles',npfull
	npgeant(npfull)=1
	pmoment(1,npfull)=pg1(1)
	pmoment(2,npfull)=pg1(2)
	pmoment(3,npfull)=pg1(3)
	ptime(npfull)=0.
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +     'COMPTON: in event more than 100 particles',npfull
	npgeant(npfull)=3
	pmoment(1,npfull)=pe1(1)
	pmoment(2,npfull)=pe1(2)
	pmoment(3,npfull)=pe1(3)
	ptime(npfull)=0.
	return
	end

c***********************************************************************

	subroutine moller(E1,E2,teta1,teta2,phi1,phi2,dcute)
c
c To sample the momentum of initial electron for MOLLER1 subroutine and
c store the momenta of scattered electron and delta ray in common/genevent/.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call moller(E1,E2,teta1,teta2,phi1,phi2,dcute)
c Input : E1,E2       - range of kinetic energy of gamma (MeV);
c         teta1,teta2 - range of teta angle (radians);
c         phi1,phi2   - range of phi  angle (radians);
c         dcute       - lower energy threshold for emitted delta ray (MeV);
c Output: see description of common/genevent/. Times emission of scattered
c         electron and delta ray are supposed to be 0.
c VIT, 11.12.1995.
c
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	common/const/pi,emass,datamass(50)
	dimension pe0(3),pe1(3),pe2(3)
	phi=phi1+(phi2-phi1)*rnd1(d)
	ctet1=1.
	if(teta1.ne.0.) ctet1=cos(teta1)
	ctet2=-1.
	if(teta2.ne.pi) ctet2=cos(teta2)
	ctet=ctet1+(ctet2-ctet1)*rnd1(d)
	stet=sqrt(1.-ctet*ctet)
	E=E1
	if(E1.ne.E2) E=E1+(E2-E1)*rnd1(d)
	p=sqrt(e*(e+2.*emass))
	pe0(1)=p*stet*cos(phi)
	pe0(2)=p*stet*sin(phi)
	pe0(3)=p*ctet
	call moller1(dcute,pe0,pe1,pe2)
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +     'MOLLER: in event more than 100 particles',npfull
	npgeant(npfull)=3
	pmoment(1,npfull)=pe1(1)
	pmoment(2,npfull)=pe1(2)
	pmoment(3,npfull)=pe1(3)
	ptime(npfull)=0.
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +     'MOLLER: in event more than 100 particles',npfull
	npgeant(npfull)=3
	pmoment(1,npfull)=pe2(1)
	pmoment(2,npfull)=pe2(2)
	pmoment(3,npfull)=pe2(3)
	ptime(npfull)=0.
	return
	end

c***********************************************************************

	subroutine pairext(E1,E2,teta1,teta2,phi1,phi2,Z)
c
c To sample the momentum of initial gamma quantum for PAIREXT1 subroutine
c and store the momenta of created positron and electron in common/genevent/.
c Call  : common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100)
c         call pairext(E1,E2,teta1,teta2,phi1,phi2,Z)
c Input : E1,E2       - range of kinetic energy of gamma (MeV);
c         teta1,teta2 - range of teta angle (radians);
c         phi1,phi2   - range of phi  angle (radians);
c         Z           - atomic number of target nuclei;
c Output: see description of common/genevent/. Times emission of scattered
c         e+ and e- are supposed to be 0.
c VIT, 12.03.1998.
c
	common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
     +                  ptime(100)
	common/const/pi,emass,datamass(50)
	dimension pg0(3),pe1(3),pe2(3)
	phi=phi1+(phi2-phi1)*rnd1(d)
	ctet1=1.
	if(teta1.ne.0.) ctet1=cos(teta1)
	ctet2=-1.
	if(teta2.ne.pi) ctet2=cos(teta2)
	ctet=ctet1+(ctet2-ctet1)*rnd1(d)
	stet=sqrt(1.-ctet*ctet)
	E=E1
	if(E1.ne.E2) E=E1+(E2-E1)*rnd1(d)
	p=E
	pg0(1)=p*stet*cos(phi)
	pg0(2)=p*stet*sin(phi)
	pg0(3)=p*ctet
	call pairext1(Z,pg0,pe1,pe2)
c to fix GEANT numbers of emitted particles but to select the momentum
c randomly
	if(rnd1(d).lt.0.5) then
	   x1=pe1(1)
	   x2=pe1(2)
	   x3=pe1(3)
	   pe1(1)=pe2(1)
	   pe1(2)=pe2(2)
	   pe1(3)=pe2(3)
	   pe2(1)=x1
	   pe2(2)=x2
	   pe2(3)=x3
	endif
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +     'PAIREXT: in event more than 100 particles',npfull
	npgeant(npfull)=2
	pmoment(1,npfull)=pe1(1)
	pmoment(2,npfull)=pe1(2)
	pmoment(3,npfull)=pe1(3)
	ptime(npfull)=0.
	npfull=npfull+1
	if(npfull.gt.100) print *,
     +     'PAIREXT: in event more than 100 particles',npfull
	npgeant(npfull)=3
	pmoment(1,npfull)=pe2(1)
	pmoment(2,npfull)=pe2(2)
	pmoment(3,npfull)=pe2(3)
	ptime(npfull)=0.
	return
	end

c***********************************************************************

c***********************************************************************
c Section of subroutines in GEANT style (for Compton and Moller effects)
c***********************************************************************

c***********************************************************************

	subroutine compton1(pg0,pg1,pe1)
c
c Simulates photon-electron Compton scattering.
c Call  : common/const/pi,emass
c         dimension pg0(3),pg1(3),pe1(3)
c         call compton1(pg0,pg1,pe1)
c Input : pg0 - momentum of initial gamma quantum (in MRS);
c Output: pg1 - momentum of scattered gamma quantum (in MRS);
c         pe1 - momentum of recoil electron (in MRS).
c
c VIT, 07.12.1995 from GEANT subroutine GCOMP by G.Patrick, L.Urban.
c
	dimension pg0(3),pg1(3),pe1(3)
	logical rotate
	common/const/pi,emass,datamass(50)
	egam0=sqrt(pg0(1)**2+pg0(2)**2+pg0(3)**2)
	ezero=egam0/emass
	emini=1.+2.*ezero
	emin=1./emini
	dsig1=log(emini)
	dsig2=0.5*(1.-emin*emin)
	dsigt=dsig1+dsig2
c Decide which part of f(e)=1/e+e to sample from
1	if(dsig1.lt.dsigt*rnd1(d)) then
c Sample from f2(e) distribution
	   brd=rnd1(d)
	   if(ezero.ge.(ezero+1.)*rnd1(d)) then
	      brd=max(brd,rnd1(d))
	   endif
	   br=emin+(1.-emin)*brd
	else
	   br=emin*exp(dsig1*rnd1(d))
	endif
c Scattered photon energy
	egam1=br*egam0
c Calculate rejection function g(e)
	t=emass*(1.-br)/egam1
	sinth=max(0.,t*(2.-t))
	rej=1.0-(br*sinth)/(1.+br*br)
	if(rnd1(d).gt.rej) go to 1
c Generate photon angles with respect to a Z-axis defined
c along the parent photon; phi is generated isotropically
	sinth=sqrt(sinth)
	costh=1.-t
	phi=2.*pi*rnd1(d)
	cosphi=cos(phi)
	sinphi=sin(phi)
c Polar co-ordinates to momentum components
	pg1(1)=egam1*sinth*cosphi
	pg1(2)=egam1*sinth*sinphi
	pg1(3)=egam1*costh
c Momentum vector of recoil electron
	pe1(1)=-pg1(1)
	pe1(2)=-pg1(2)
	pe1(3)=egam0-pg1(3)
c Rotate electron and scattered photon into MRS system
	call gfang(pg0,costh,sinth,cosph,sinph,rotate)
	if(rotate) then
	   call gdrot(pg1,costh,sinth,cosph,sinph)
	   call gdrot(pe1,costh,sinth,cosph,sinph)
	endif
	return
	end

c***********************************************************************

	subroutine moller1(dcute,pe0,pe1,pe2)
c
c Simulates electron-electron Moller scattering.
c Call  : common/const/pi,emass
c         dimension pe0(3),pe1(3),pe2(3)
c         call moller1(dcute,pe0,pe1,pe2)
c Input : pe0   - momentum of initial electron (in MRS);
c         dcute - minimal energy of delta ray to be borned;
c                 if energy of initial electron < dcute/2
c                 delta rays are not produced;
c Output: pe1   - momentum of 1 scattered electron (in MRS);
c         pe2   - momentum of 2 scattered electron (in MRS).
c
c VIT, 07.12.1995 from GEANT subroutine GDRAY by D.Ward, L.Urban.
c
	dimension pe0(3),pe1(3),pe2(3)
	logical rotate
	common/const/pi,emass,datamass(50)
	p=sqrt(pe0(1)**2+pe0(2)**2+pe0(3)**2)
	xe=sqrt(p**2+emass**2)
	te=xe-emass
	gam=xe/emass
	gam2=gam*gam
	t=gam-1.
	x=dcute/(t*emass)
	if(x.ge.0.5) then
	   do i=1,3
	      pe2(i)=pe0(i)
	      pe1(i)=0.
	   enddo
	   return
	endif
	cc=1.-2.*x
1	e=x/(1.-cc*rnd1(d))
	b1=4./(9.*gam2-10.*gam+5.)
	b2=t*t*b1
	b3=(2.*gam2+2.*gam-1.)*b1
	e1=1.-e
	screj=b2*e*e-b3*e/e1+b1*gam2/(e1*e1)
	if(rnd1(d).gt.screj) go to 1
	eel=(t*e+1.)*emass
	tel=eel-emass
	pel=sqrt(abs((eel+emass)*tel))
	costh=(xe*eel+emass*(tel-xe))/(p*pel)
	if(costh.ge.1.) then
	   costh=1.
	   sinth=0.
	elseif(costh.le.-1.) then
	   costh=-1.
	   sinth=0.
	else
	   sinth=sqrt((1.+costh)*(1.-costh))
	endif
	phi=2.*pi*rnd1(d)
	cosphi=cos(phi)
	sinphi=sin(phi)
c Polar co-ordinates to momentum components
	pe2(1)=pel*sinth*cosphi
	pe2(2)=pel*sinth*sinphi
	pe2(3)=pel*costh
	pe1(1)=-pe2(1)
	pe1(2)=-pe2(2)
	pe1(3)=p-pe2(3)
c Rotate to MRS
	call gfang(pe0,costh,sinth,cosph,sinph,rotate)
	if(rotate) then
	   call gdrot(pe1,costh,sinth,cosph,sinph)
	   call gdrot(pe2,costh,sinth,cosph,sinph)
	endif
	return
	end

c***********************************************************************

      subroutine pairext1(Z,pg0,pe1,pe2)
c
c Simulates e+e- pair production by photons in a target with atomic
c number Z.
c Call  : common/const/pi,emass
c         dimension pg0(3),pe1(3),pe2(3)
c         call pairext1(Z,pg0,pe1,pe2)
c Input : Z   - atomic number of the substance;
c         pg0 - momentum of initial gamma quantum (in MRS);
c Output: pe1 - momentum of 1 created electron (in MRS);
c         pe2 - momentum of 2 created electron (in MRS).
c Which particle is e+ and which e-, should be selected randomly.
c
c VIT, 11.03.1998 from GEANT subroutines GPAIRG of G.Patrick, L.Urban
c and GBTETH of L.Urban.
c
	common/const/pi,emass,datamass(50)
	dimension pg0(3),pe1(3),pe2(3)
	logical rotate
	Egam=sqrt(pg0(1)**2+pg0(2)**2+pg0(3)**2)
c If not enough energy, no pair production
	if(Egam.lt.2.*emass) go to 4
c For photons <2.1 MeV approximate the electron energy by sampling
c from a uniform distribution in the interval [emass,Egam/2]
	if(Egam.le.2.1) then
	   Eel1=emass+rnd1(r)*(0.5*Egam-emass)
	   x=Eel1/Egam
	   go to 2
	endif
c Calculate some constants
	z3=Z**(1./3.)
	f=8./3.*log(Z)
	if(Egam.gt.50.) then
	   aZ2=(Z/137.036)**2
	   fcoulomb=aZ2*(1./(1.+aZ2)+0.20206-0.0369*aZ2+
     +              0.0083*aZ2**2-0.002*aZ2**3)
	   f=f+8.*fcoulomb
	endif
	x0=emass/Egam
	dx=0.5-x0
	dmin=544.*x0/z3
	if(dmin.le.1.) then
	   f10=42.392-7.796*dmin+1.961*dmin**2-f
	   f20=41.405-5.828*dmin+0.8945*dmin**2-f
	else
	   f10=42.24-8.368*log(dmin+0.952)-f
	   f20=f10
	endif
c Calculate limit for screening variable, DELTA, to ensure
c that screening rejection functions always remain positive
	dmax=exp((42.24-f)/8.368)-0.952
	dsig1=dx*dx*f10/3.
	dsig2=0.5*f20
	bpar=dsig1/(dsig1+dsig2)
c Decide which screening rejection function to use and
c sample the electron/photon fractional energy
1	r1=rnd1(r)
	r2=rnd1(r)
	if(r1.lt.bpar) then
	   x=0.5-dx*r2**(1./3.)
	   irej=1
	else
	   x=x0+dx*r2
	   irej=2
	endif
c Calculate DELTA ensuring positivity
	d=0.25*dmin/(x*(1.-x))
	if(d.ge.dmax) goto 1
c Calculate F1 and F2 functions. F10 and F20 are the F1
c and F2 functions calculated for the DELTA=DELTA minimum.
	if(d.le.1.) then
	   f1=42.392-7.796*d+1.961*d**2-f
	   f2=41.405-5.828*d+0.8945*d**2-f
	else
	   f1=42.24-8.368*log(d+0.952)-f
	   f2=f1
	endif
	if(irej.eq.1) screj=f1/f10
	if(irej.eq.2) screj=f2/f20
c Accept or reject on basis of random variate
	if(rnd1(r).gt.screj) goto 1
	Eel1=x*Egam
c Generate electron decay angles with respect to a Z-axis defined
c along the parent photon. PHI is generated isotropically.
2	alfa=0.625
	d=0.13*(0.8+1.3/Z)*(100.+1./Eel1)*(1.+x)
	w1=9./(9.+d)
	umax=Eel1*pi/emass
3	beta=alfa
	if(rnd1(r).gt.w1) beta=3.*alfa
	r1=rnd1(r)
	u=-(log(rnd1(r)*r1))/beta
	if(u.ge.umax) goto 3
	theta=u*emass/Eel1
	sinth=sin(theta)
	costh=cos(theta)
	phi=2.*pi*rnd1(r)
	cosphi=cos(phi)
	sinphi=sin(phi)
c Momentum components of first electron
	pel1=sqrt((Eel1+emass)*(Eel1-emass))
	pe1(1)=pel1*sinth*cosphi
	pe1(2)=pel1*sinth*sinphi
	pe1(3)=pel1*costh
c Momentum vector of second electron. Recoil momentum of
c target nucleus/electron is ignored.
	Eel2=Egam-Eel1
	pel2=sqrt((Eel2+emass)*(Eel2-emass))
c correction for conservation of x and y components of momentum
	sinth=sinth*pel1/pel2
	costh=sqrt(max(0.,1.-sinth**2))
	pe2(1)=-pel2*sinth*cosphi
	pe2(2)=-pel2*sinth*sinphi
	pe2(3)=pel2*costh
c Rotate tracks to MRS
	call gfang(pg0,cosal,sinal,cosbt,sinbt,rotate)
	if(rotate) then
	   call gdrot(pe1,cosal,sinal,cosbt,sinbt)
	   call gdrot(pe2,cosal,sinal,cosbt,sinbt)
	endif
	return
4	print *,'e+e- pair is not created: Egamma < 1.022 MeV'
	return
	end

c***********************************************************************

	subroutine gfang(p,costh,sinth,cosph,sinph,rotate)
c
c Finds theta-phi angles for a particle with momentum P.
c The logical flag ROTATE indicates whether the director
c cosines are along the Z axis (.FALSE.) or not (.TRUE.).
c
c F.Carminati (GEANT).
c
	dimension p(3)
	logical rotate
	parameter (one=1)
c additional (as compared with original GFANG) normalization
	pfull=sqrt(p(1)**2+p(2)**2+p(3)**2)
	dux=p(1)/pfull
	duy=p(2)/pfull
	duz=p(3)/pfull
	rotate=.true.
	if(abs(duz).ge.0.85) then
	   dsith2=dux**2+duy**2
	   if(dsith2.gt.0.) then
	      costh=sign(one,duz)*sqrt(one-dsith2)
	      dsith=sqrt(dsith2)
	      sinth=dsith
	      cosph=dux/dsith
	      sinph=duy/dsith
	   elseif(duz.gt.0.) then
	      rotate=.false.
	      costh=1.
	      sinth=0.
	      cosph=1.
	      sinph=0.
	   else
	      costh=-1.
	      sinth=0.
	      cosph=1.
	      sinph=0.
	   endif
	else
	   costh=duz
	   dsith=sqrt((one+duz)*(one-duz))
	   sinth=dsith
	   dnorm=one/sqrt(dux**2+duy**2)
	   cosph=dux*dnorm
	   sinph=duy*dnorm
	endif
	return
	end

c***********************************************************************

	subroutine gdrot(p,costh,sinth,cosph,sinph)
c
c Rotates vector from one reference system into another.
c Theta and phi are anti-clockwise Eulerian angles between the
c two systems.
c
c M.Hansroul, G.Patrick (GEANT).
c
	dimension p(3)
	p1=p(1)
	p2=p(2)
	p3=p(3)
	p(1)= p1*costh*cosph - p2*sinph + p3*sinth*cosph
	p(2)= p1*costh*sinph + p2*cosph + p3*sinth*sinph
	p(3)=-p1*sinth                  + p3*costh
	return
	end

c***********************************************************************
