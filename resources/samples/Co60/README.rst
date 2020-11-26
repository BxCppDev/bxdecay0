===============================================
BxDecay0 - Decay event files generated for Co60
===============================================

Generation of 3 sample decay event ascii files:

.. code:: shell
   
   $ bxdecay0-run -s 314159 -n 10 -c background -N Co60 genCo60-1 
   $ bxdecay0-run -s 314160 -n 10 -c background -N Co60 genCo60-2 
   $ bxdecay0-run -s 314161 -n 10 -c background -N Co60 genCo60-3
..


List of files:

* ``genCo60-1.d0m`` : Run #1 metadata ascii file 
* ``genCo60-1.d0t`` : Run #1 decay event ascii file 
* ``genCo60-2.d0m`` : Run #2 metadata ascii file 
* ``genCo60-2.d0t`` : Run #2 decay event ascii file 
* ``genCo60-3.d0m`` : Run #3 metadata ascii file 
* ``genCo60-3.d0t`` : Run #3 decay event ascii file 

.. end


