set grid
set xlabel "cos((p, Ox))"
set ylabel "counts"
set xrange [-1.1:1.1]
set yrange [0:*]
set key out
set title "Cs137 decays (10000 events)\nForce momentum direction of the first ranked gamma\nin a 45°x18° rectangular cone aligned on the X-axis\nand rotate all other particles coherently"
plot "h1r.his" using (0.5*(column(1)+column(2))):3 title "target gamma" with histeps lw 2, \
     "h2r.his" using (0.5*(column(1)+column(2))):3 title "beta" with histeps lw 2
pause -1

set terminal push
set terminal pngcairo
set output "test_decay0_generator_mdlr.png"
replot
set output
set terminal pop

set terminal push
set terminal pdfcairo
set output "test_decay0_generator_mdlr.pdf"
replot
set output
set terminal pop

exit
###

set title "Cs137 decays (10000 events)\nForce momentum direction of all particles (gamma/e-)\nin a 45° cone aligned on the X-axis"
plot "h1rbis.his" using (0.5*(column(1)+column(2))):3 title "gamma" with histeps lw 2, \
     "h2rbis.his" using (0.5*(column(1)+column(2))):3 title "beta" with histeps lw 2
pause -1

set terminal push
set terminal pngcairo
set output "test_decay0_generator_mdlr_bis.png"
replot
set output
set terminal pop

set terminal push
set terminal pdfcairo
set output "test_decay0_generator_mdlr_bis.pdf"
replot
set output
set terminal pop


###

set title "Cs137 decays (10000 events)\nForce momentum direction of all electrons in the event\nin a 45° cone aligned on the X-axis\nand let gammas unchanged"
plot "h1ter.his" using (0.5*(column(1)+column(2))):3 title "gamma" with histeps lw 2, \
     "h2ter.his" using (0.5*(column(1)+column(2))):3 title "beta" with histeps lw 2
pause -1

set terminal push
set terminal pngcairo
set output "test_decay0_generator_mdlr_ter.png"
replot
set output
set terminal pop

set terminal push
set terminal pdfcairo
set output "test_decay0_generator_mdlr_ter.pdf"
replot
set output
set terminal pop


# end
