#!/bin/bash
for i in {1..7}
do
   ./dyck $i > result-$i
   diff result-$i expected-$i
   ./dyck -s $i > result-$i
   diff result-$i expected-$i
done
