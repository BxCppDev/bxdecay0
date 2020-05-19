set title "BxDecay0 - Example ex05"

Qbb = 3.0
set grid
# set key out
set size ratio -1
set xlabel "E_1 (MeV)"
set ylabel "E_2 (MeV)"
set zlabel "p.d.f."
plot [0:Qbb][0:Qbb] \
      'bxdecay0_ex05.data' every 10 u 1:2:(0.0) title "Random points (10%)" with dots
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_2d-pdf_random.jpg"
replot
set output
set terminal pop

! cut -d' ' -f1 bxdecay0_ex05.data | gsl-histogram 0.0 3.0 3000 > bxdecay0_ex05_e1.his
! cut -d' ' -f2 bxdecay0_ex05.data | gsl-histogram 0.0 3.0 3000 > bxdecay0_ex05_e2.his

set size noratio

set xlabel "E (MeV)"
set ylabel "Counts / keV"
plot [0:Qbb][0:] \
     'bxdecay0_ex05_e1.his' using (0.5*($1+$2)):3 title "E_1" with histeps, \
     'bxdecay0_ex05_e2.his' using (0.5*($1+$2)):3 title "E_2" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_e1e2.jpg"
replot
set output
set terminal pop

plot [0:0.05][0:] \
     'bxdecay0_ex05_e1.his' using (0.5*($1+$2)):3 title "E_1" with histeps, \
     'bxdecay0_ex05_e2.his' using (0.5*($1+$2)):3 title "E_2" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_e1e2_zoom.jpg"
replot
set output
set terminal pop

! cut -d' ' -f3 bxdecay0_ex05.data | gsl-histogram 0.0 3.0 3000 > bxdecay0_ex05_esum.his

set xlabel "E_{sum} (MeV)"
set ylabel "Counts / keV"
plot [0:Qbb][0:] 'bxdecay0_ex05_esum.his' using (0.5*($1+$2)):3 title "Random" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_esum.jpg"
replot
set output
set terminal pop

plot [0:0.05][0:] 'bxdecay0_ex05_esum.his' using (0.5*($1+$2)):3 title "Random" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_esum_zoom.jpg"
replot
set output
set terminal pop

! cut -d' ' -f4 bxdecay0_ex05.data | gsl-histogram 0.0 2.0 100 > bxdecay0_ex05_cos12.his
set xlabel "cos_{12}"
set ylabel "Counts / 0.02"
plot [-1.1:1.1][0:] 'bxdecay0_ex05_cos12.his' using (0.5*($1+$2)-1.0):3 title "Random" with histeps
pause -1 "Hit [Enter]..."
set term push
set terminal jpeg
set output "bxdecay0_ex05_cos12.jpg"
replot
set output
set terminal pop

# ! rm -f bxdecay0_ex05_cos12.his
# ! rm -f bxdecay0_ex05_esum.his
# ! rm -f bxdecay0_ex05_e1.his
# ! rm -f bxdecay0_ex05_e2.his
## ! rm -f bxdecay0_ex05.data
pause -1 "End"

# end

