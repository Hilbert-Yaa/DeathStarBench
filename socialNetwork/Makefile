b:
	docker build -t social-network-benchmark .

i:
	-cda proto && python3 scripts/init_social_graph.py --graph=socfb-Reed98

c:
	-cd wrk2 && ./wrk -D exp -t 8 -c 10 -d 15m -L -s ./scripts/social-network/compose-post.lua http://localhost:8080/wrk2-api/post/compose -R 50

u:
	docker-compose up

d:
	docker-compose down
