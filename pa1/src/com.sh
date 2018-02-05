echo insert
./insert ../testcase/case0.dat ../output/case0.out
./insert ../testcase/case1.dat ../output/case1.out
./insert ../testcase/case2.dat ../output/case2.out
./insert ../testcase/case3.dat ../output/case3.out
./insert ../testcase/case4.dat ../output/case4.out
echo --------------------------------------

echo merge
./merge ../testcase/case0.dat ../output/case0.out
./merge ../testcase/case1.dat ../output/case1.out
./merge ../testcase/case2.dat ../output/case2.out
./merge ../testcase/case3.dat ../output/case3.out
./merge ../testcase/case4.dat ../output/case4.out
echo --------------------------------------

echo heap
./heap ../testcase/case0.dat ../output/case0.out
./heap ../testcase/case1.dat ../output/case1.out
./heap ../testcase/case2.dat ../output/case2.out
./heap ../testcase/case3.dat ../output/case3.out
./heap ../testcase/case4.dat ../output/case4.out
echo --------------------------------------

echo quick
./quick ../testcase/case0.dat ../output/case0.out
./quick ../testcase/case1.dat ../output/case1.out
./quick ../testcase/case2.dat ../output/case2.out
./quick ../testcase/case3.dat ../output/case3.out
./quick ../testcase/case4.dat ../output/case4.out
echo --------------------------------------
