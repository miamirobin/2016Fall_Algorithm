all: insert merge quick heap
	@echo Compiling…
insert: parser.o insert.cpp 
	g++ insert.cpp parser.o -o insert
merge: parser.o merge.cpp 
	g++ merge.cpp parser.o -o merge
quick: parser.o quick.cpp
	g++ quick.cpp parser.o -o quick
heap: parser.o heap.cpp
	g++ heap.cpp parser.o -o heap

clean:
	rm -f insert merge quick heap