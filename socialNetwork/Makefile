CODEGEN = $(wildcard gen-cpp/*.cpp) $(wildcard gen-cpp/*.h)
SRC = $(wildcard src/**/*.cpp) $(wildcard src/**/*.h)
ALL_SRC = $(SRC) $(CODEGEN)

build: $(ALL_SRC)
	docker build -t social-network-benchmark .
	docker tag social-network-benchmark hilbertchen/social-network-benchmark:latest

init_graph:
	-python3 scripts/init_social_graph.py --graph=socfb-Reed98

gen_sample:
# -cd wrk2 && ./wrk -D exp -t 4 -c 5 -R 15 -d 30s -L -s ./scripts/social-network/compose-post.lua http://localhost:8080/wrk2-api/post/compose
	-cd wrk2 && ./wrk -D exp -t 1 -c 1 -R 1 -d 30s -L -s ./scripts/social-network/compose-post.lua http://localhost:8080/wrk2-api/post/compose
# -cd wrk2 && ./wrk -D exp -t 4 -c 5 -R 15 -d 30s -L -s ./scripts/social-network/read-home-timeline.lua http://localhost:8080/wrk2-api/home-timeline/read
# -cd wrk2 && ./wrk -D exp -t 4 -c 5 -R 15 -d 30s -L -s ./scripts/social-network/read-user-timeline.lua http://localhost:8080/wrk2-api/user-timeline/read

gen_lots:
	-cd wrk2 && ./wrk -D exp -t 8 -c 10 -R 50 -d 30m -L -s ./scripts/social-network/mixed-workload.lua http://localhost:8080/wrk2-api/post/compose

up:
	mkdir -p logs
	rm -rf logs/*
	docker-compose up

down:
	docker-compose down

.PHONY: clean_logs
clean_logs:
	rm -f logs/*