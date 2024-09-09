all: cypher

cypher: cypher.c
	gcc cypher.c -o cypher

clean:
	rm -rf cypher