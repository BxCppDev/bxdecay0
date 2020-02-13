set title "BxDecay0 - Example ex05"

Qbb = 3.0
set grid
# set key out
set xlabel "E_1 (MeV)"
set ylabel "E_2 (MeV)"
set zlabel "p.d.f."
splot [0:Qbb][0:Qbb] 'bxdecay0_ex05_1.data' title "Tabulated p.d.f." with lines, \
      'bxdecay0_ex05_2.data' every 10 u 1:2:(0.0) title "Random points (10%)" with dots
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_2d-pdf_random.jpg"
replot
set output
set terminal pop

! cut -d' ' -f1 bxdecay0_ex05_2.data | gsl-histogram 0.0 4.0 80 > bxdecay0_ex05_e1.his
! cut -d' ' -f2 bxdecay0_ex05_2.data | gsl-histogram 0.0 4.0 80 > bxdecay0_ex05_e2.his
! gsl-histogram 0.0 4.0 80 < bxdecay0_ex05_3.data > bxdecay0_ex05_esum.his

set xlabel "E (MeV)"
set ylabel "Counts / 50 keV"
plot [0:4.0] \
     'bxdecay0_ex05_e1.his' using (0.5*($1+$2)):3 title "E_1" with histeps, \
     'bxdecay0_ex05_e2.his' using (0.5*($1+$2)):3 title "E_2" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_e1e2.jpg"
replot
set output
set terminal pop

set xlabel "E_{sum} (MeV)"
set ylabel "Counts / 50 keV"
plot [0:4.0][0:] 'bxdecay0_ex05_esum.his' using (0.5*($1+$2)):3 title "Random" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_esum.jpg"
replot
set output
set terminal pop

! gsl-histogram 0.0 1.0 50 < bxdecay0_ex05_4.data > bxdecay0_ex05_cos12.his
set xlabel "cos_{12}"
set ylabel "Counts / 0.02"
plot [0:1.2][0:] 'bxdecay0_ex05_cos12.his' using (0.5*($1+$2)):3 title "Random" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_cos12.jpg"
replot
set output
set terminal pop

# end

