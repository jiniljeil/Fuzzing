#!/bin/sh

start_time=$(date +%s)
for i in 1 2 3 4 5
do 
	rm ./seed_cjson/seed*
	cp ../cjson_seed/* ./seed_cjson/ 
	./cJSON_test_driver
done
end_time=$(date +%s)

echo "It takes $(($end_time-$start_time)) second!"
