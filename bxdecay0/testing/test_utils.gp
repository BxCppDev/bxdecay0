

set size ratio -1
set grid
set view equal xyz
set xyplane at 0.0
set xrange [-1.5:1.5]
set yrange [-1.5:1.5]
set zrange [-1.5:1.5]
set xlabel "x"
set ylabel "y"
set zlabel "z"

splot "a.data" \
      index 0 using (0):(0):(0):($1):($2):($3) title "I"  with vectors , \
      ""  index 1 using (0):(0):(0):($1):($2):($3) title "R1z"  with vectors 
pause -1

splot "a.data" \
      index 0 using (0):(0):(0):($1):($2):($3)  title "I"  with vectors , \
      ""  index 1 using (0):(0):(0):($1):($2):($3) title "R1z" with vectors , \
      ""  index 2 using (0):(0):(0):($1):($2):($3) title "R2y" with vectors
pause -1


splot "a.data" \
      index 0 using (0):(0):(0):($1):($2):($3)  title "I"  with vectors , \
      ""  index 1 using (0):(0):(0):($1):($2):($3) title "R1z" with vectors , \
      ""  index 2 using (0):(0):(0):($1):($2):($3) title "R2y" with vectors , \
      ""  index 3 using (0):(0):(0):($1):($2):($3) title "R3z" with vectors
pause -1
