mm=1.0

dimView = 600*mm
set xlabel "z (mm)"
set ylabel "x (mm)"
set zlabel "y (mm)"
set xrange [-dimView:dimView]
set yrange [-dimView:dimView]
set zrange [-dimView:dimView]
set view equal xyz
set xyplane at -dimView
set view 65, 60

arrowDim = 200.0*mm

set label 1 "z" at arrowDim,0.0,0.0 center front textcolor rgb "blue"  offset 1,0
set label 2 "x" at 0.0,arrowDim,0.0 center front textcolor rgb "red"   offset 0,1
set label 3 "y" at 0.0,0.0,arrowDim+20.0*mm center front textcolor rgb "green" offset 0,0
set arrow 1 from 0,0,0 to arrowDim,0.0,0.0
set arrow 1 head lw 2 linecolor rgb "blue"
set arrow 2 from 0,0,0 to 0.0,arrowDim,0.0
set arrow 2 head lw 2 linecolor rgb "red"
set arrow 3 from 0,0,0 to 0.0,0.0,arrowDim
set arrow 3 head lw 2 linecolor rgb "green"

dimW = 500.0*mm

set arrow 10 from  dimW, dimW, dimW  to  dimW, dimW,-dimW nohead
set arrow 11 from  dimW,-dimW, dimW  to  dimW,-dimW,-dimW nohead
set arrow 12 from -dimW,-dimW, dimW  to -dimW,-dimW,-dimW nohead
set arrow 13 from -dimW, dimW, dimW  to -dimW, dimW,-dimW nohead

set arrow 20 from -dimW,-dimW, dimW  to  dimW,-dimW, dimW nohead
set arrow 21 from  dimW,-dimW, dimW  to  dimW, dimW, dimW nohead
set arrow 22 from  dimW, dimW, dimW  to -dimW, dimW, dimW nohead
set arrow 23 from -dimW, dimW, dimW  to -dimW,-dimW, dimW nohead

set arrow 30 from -dimW,-dimW,-dimW  to  dimW,-dimW,-dimW nohead
set arrow 31 from  dimW,-dimW,-dimW  to  dimW, dimW,-dimW nohead
set arrow 32 from  dimW, dimW,-dimW  to -dimW, dimW,-dimW nohead
set arrow 33 from -dimW, dimW,-dimW  to -dimW,-dimW,-dimW nohead

# set arrow 21 from  dimW, dimW, dimW  to  dimW,-dimW, dimW nohead
# set arrow 22 from  dimW,-dimW, dimW  to -dimW,-dimW, dimW nohead
# set arrow 23 from -dimW,-dimW, dimW  to -dimW, dimW, dimW nohead


splot 'source_bulk_vertexes-xyz-0bis.data' using 3:1:2 notitle with dots
pause -1 

set terminal push
set terminal pdfcairo
set output "source_bulk_vertexes-xyz.pdf"
replot
set output
set terminal pop

