#!/bin/sh

start_time=$(date +%s)
for i in 1 2 3 4 5
do 
	rm ./Jinil_cJSON_seed_dir/seed*
	cp ../Jinil_cJSON_seed_dir/* ./Jinil_cJSON_seed_dir/ 
	./cJSON_test_driver
done
end_time=$(date +%s)

echo "It takes $(($end_time-$start_time)) second!"
