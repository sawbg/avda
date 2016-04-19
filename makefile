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

fileio-test:
	$(GCC) src/fileio_test.cpp -o bin/fileiotest

patient-name-test:
	$(GCC) src/patient_name_test.cpp -o bin/patnametest

process-test:
	$(GCC) src/process_test.cpp -o bin/proctest

sigmath-test:
	$(GCC) src/sigmath_test.cpp -o bin/sigmathtest

vaso:
	$(GCC) src/main.cpp -o bin/vaso

