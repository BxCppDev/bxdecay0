set grid
set xlabel "cos((p, Ox))"
set ylabel "counts"
set xrange [-1.1:1.1]
set yrange [0:*]
set key out
set title "Cs137 decays (10000 events)\nForce first ranked gamma momentum direction\nin a 45° cone aligned on the X-axis\nand rotate all other particles coherently"
plot "h1.his" using (0.5*(column(1)+column(2))):3 title "Rotated target gamma" with histeps lw 2, \
     "h2.his" using (0.5*(column(1)+column(2))):3 title "Rotated beta" with histeps lw 2
pause -1

set terminal push
set terminal pngcairo
set output "test_decay0_generator_mdl.png"
replot
set output
set terminal pop

set terminal push
set terminal pdfcairo
set output "test_decay0_generator_mdl.pdf"
replot
set output
set terminal pop


# end
