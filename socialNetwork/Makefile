build:
	docker build -t social-network-benchmark .

init_graph:
	-python3 scripts/init_social_graph.py --graph=socfb-Reed98

gen_sample:
	-cd wrk2 && ./wrk -D exp -t 8 -c 10 -d 30m -L -s ./scripts/social-network/compose-post.lua http://localhost:8080/wrk2-api/post/compose -R 50

gen_lots:
	-cd wrk2 && ./wrk -D exp -t 8 -c 10 -d 30m -L -s ./scripts/social-network/mixed-workload.lua http://localhost:8080/wrk2-api/post/compose -R 50

up:
	docker-compose up

down:
	docker-compose down

.PHONY: clean_logs
clean_logs:
	rm -f logs/*