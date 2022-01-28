b:
	docker build -t social-network-benchmark .

c:
	-cd wrk2 && ./wrk -D exp -t 6 -c 10 -d 1m -L -s ./scripts/social-network/compose-post.lua http://localhost:8080/wrk2-api/post/compose -R 20

u:
	docker-compose up