

set grid
set size ratio -1
set xlabel "E1"
set ylabel "E2"

splot 'test_dbd_gA_1.data' using 1:2:3 with dots
pause -1 "Hit [Enter]..."

plot 'test_dbd_gA_2.data' using 1:2 with dots
pause -1 "Hit [Enter]..."

set size noratio 
set xlabel "E"
set ylabel "Counts/bin"

plot 'rand_e1.his' using (0.5*(column(1)+column(2))):3 title "E1" with histeps , \
     'rand_e2.his' using (0.5*(column(1)+column(2))):3 title "E2" with histeps 
pause -1 "Hit [Enter]..."

plot 'rand_e1.his' using (0.5*(column(1)+column(2))):3 title "E1" with histeps , \
     'rand_e2.his' using (0.5*(column(1)+column(2))):3 title "E2" with histeps , \
     'rand_esum.his' using (0.5*(column(1)+column(2))):3 title "E1+E2" with histeps  
pause -1 "Hit [Enter]..."

###############################
set grid
set size ratio -1
set xlabel "E1"
set ylabel "E2"

plot 'test2_dbd_gA_2.data' every 100 using 1:2 with dots
pause -1 "Hit [Enter]..."

set size noratio 
set xlabel "E"
set ylabel "Counts/bin"

plot 'rand2_e1.his' using (0.5*(column(1)+column(2))):3 title "E1" with histeps , \
     'rand2_e2.his' using (0.5*(column(1)+column(2))):3 title "E2" with histeps 
pause -1 "Hit [Enter]..."

plot 'rand2_e1.his' using (0.5*(column(1)+column(2))):3 title "E1" with histeps , \
     'rand2_e2.his' using (0.5*(column(1)+column(2))):3 title "E2" with histeps , \
     'rand2_esum.his' using (0.5*(column(1)+column(2))):3 title "E1+E2 (ITM)" with histeps  , \
     'rand_esum.his' using (0.5*(column(1)+column(2))):3 title "E1+E2 (VN)" with histeps  
pause -1 "Hit [Enter]..."

## end
