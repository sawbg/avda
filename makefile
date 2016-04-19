GCC = g++ -g -std=gnu++14

avda:
	$(GCC) src/main.cpp -o bin/avda

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

read-params-test:
	$(GCC) src/read_params_test.cpp -o bin/rptest

stdin-clear-test:
	$(GCC) src/stdin_clear_test.cpp -o bin/cleartest
