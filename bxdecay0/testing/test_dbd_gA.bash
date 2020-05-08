#!/usr/bin/env bash

# test 1
cut -d' ' -f1  test_dbd_gA_2.data > rand_e1.data
cut -d' ' -f2  test_dbd_gA_2.data > rand_e2.data
gsl-histogram 0.0 3.0 300 < rand_e1.data > rand_e1.his
gsl-histogram 0.0 3.0 300 < rand_e2.data > rand_e2.his
# gsl-histogram 0.0 3.0 300 < test_dbd_gA_3.data > rand_esum.his

# test 2
cut -d' ' -f1  test2_dbd_gA_2.data > rand2_e1.data
cut -d' ' -f2  test2_dbd_gA_2.data > rand2_e2.data
gsl-histogram 0.0 3.0 3000 < rand2_e1.data > rand2_e1.his
gsl-histogram 0.0 3.0 3000 < rand2_e2.data > rand2_e2.his
# gsl-histogram 0.0 3.0 300 < test2_dbd_gA_3.data > rand2_esum.his





exit 0

