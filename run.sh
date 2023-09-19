# SEQUENTIAL
: << COMMENT
echo "100"
./aux 100 100 100 100
for run in {1..10}; do ./seq m1.txt m2.txt ; done

echo "200"
./aux 200 200 200 200
for run in {1..10}; do ./seq m1.txt m2.txt ; done

echo "400"
./aux 400 400 400 400
for run in {1..10}; do ./seq m1.txt m2.txt ; done


echo "800"
./aux 800 800 800 800
for run in {1..10}; do ./seq m1.txt m2.txt ; done

echo "1600"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./seq m1.txt m2.txt ; done
COMMENT



# MULTI PROCESS
: << COMMENT
echo "100"
./aux 100 100 100 100
for run in {1..10}; do ./proc m1.txt m2.txt 1250 && echo "########" ; done

echo "200"
./aux 200 200 200 200
for run in {1..10}; do ./proc m1.txt m2.txt 5000 && echo "########" ; done

echo "400"
./aux 400 400 400 400
for run in {1..10}; do ./proc m1.txt m2.txt 20000 && echo "########" ; done

echo "800"
./aux 800 800 800 800
for run in {1..10}; do ./proc m1.txt m2.txt 80000 && echo "########" ; done

echo "1600"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./proc m1.txt m2.txt 320000 && echo "########" ; done
COMMENT


# MULTI THREAD
: << COMMENT
echo "100"
./aux 100 100 100 100
for run in {1..10}; do ./a.out m1.txt m2.txt 1250 && echo "########" ; done

echo "200"
./aux 200 200 200 200
for run in {1..10}; do ./a.out m1.txt m2.txt 5000 && echo "########" ; done

echo "400"
./aux 400 400 400 400
for run in {1..10}; do ./a.out m1.txt m2.txt 20000 && echo "########" ; done

echo "800"
./aux 800 800 800 800
for run in {1..10}; do ./a.out m1.txt m2.txt 80000 && echo "########" ; done

echo "1600"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./a.out m1.txt m2.txt 320000 && echo "########" ; done
COMMENT

# 80000 160000 320000 640000 1280000



# P Process
: << COMMENT
echo "1600;80000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./proc m1.txt m2.txt 80000 && echo "########" ; done

echo "1600;160000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./proc m1.txt m2.txt 160000 && echo "########" ; done

echo "1600;320000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./proc m1.txt m2.txt 320000 && echo "########" ; done

echo "1600;640000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./proc m1.txt m2.txt 640000 && echo "########" ; done

echo "1600;1280000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./proc m1.txt m2.txt 1280000 && echo "########" ; done
COMMENT



# P Thread
: << COMMENT
echo "1600;80000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./a.out m1.txt m2.txt 80000 && echo "########" ; done

echo "1600;160000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./a.out m1.txt m2.txt 160000 && echo "########" ; done

echo "1600;320000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./a.out m1.txt m2.txt 320000 && echo "########" ; done

echo "1600;640000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./a.out m1.txt m2.txt 640000 && echo "########" ; done

echo "1600;1280000"
./aux 1600 1600 1600 1600
for run in {1..10}; do ./a.out m1.txt m2.txt 1280000 && echo "########" ; done
COMMENT


echo "1600;1280000"
./aux 1600 1600 1600 1600
for run in {1..1}; do ./proc m1.txt m2.txt 1280000 && echo "########" ; done
