./router ../testcase/gr4x4.in ../output/gr4x4.out
./router ../testcase/gr5x5.in ../output/gr5x5.out
./router ../testcase/gr10x10.in ../output/gr10x10.out
./router ../testcase/gr20x20.in ../output/gr20x20.out
./router ../testcase/gr60x60.in ../output/gr60x60.out
echo gr4x4
./verify ../testcase/gr4x4.in ../output/gr4x4.out
echo gr5x5
./verify ../testcase/gr5x5.in ../output/gr5x5.out
echo gr10x10
./verify ../testcase/gr10x10.in ../output/gr10x10.out
echo gr20x20
./verify ../testcase/gr20x20.in ../output/gr20x20.out
echo gr60x60
./verify ../testcase/gr60x60.in ../output/gr60x60.out
