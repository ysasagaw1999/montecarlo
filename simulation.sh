g++ geo.cpp -o geo

num=10

for ((j=0; j<$num; j++))
do
    ./geo

    grep "trials_" output.txt > trials.txt
    sed -i.bak "s/trials__//g" trials.txt

    for ((i=0; i<16; i++))
    do
        grep "front_ch${i}_" output.txt > f_ch${i}.txt
        sed -i.bak "s/front_ch${i}__//g" f_ch${i}.txt
    done

    for ((i=0; i<8; i++))
    do
        grep "rear_ch${i}_" output.txt > r_ch${i}.txt
        sed -i.bak "s/rear_ch${i}__//g" r_ch${i}.txt
    done

    grep "all__" output.txt > all.txt
    sed -i.bak "s/all__//g" all.txt

    rm output.txt

    python3 -u app.py ${j}

done

rm *.txt
rm *.txt.bak

python3 sum.py $num

# for ((i=0; i<5; i++))
# do
#     rm count${i}.csv
# done
