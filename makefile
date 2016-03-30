GCC = g++ -g -std=gnu++14

count:
	grep -r "src/" -e "Samuel Andrew Wisner" -l | xargs wc -l

docs:
	rm -r doc/
	doxygen etc/doxygen.config
	cd doc/latex; make pdf;
	git reset
	git add doc/.
	git commit -m "Updated documentation."
	git push


