rm mytsp.txt exampletsp.txt
(cd ~/cse13s/asgn4/ && make)
for f in ~/resources/asgn4/graphs/*
do
	~/cse13s/asgn4/tsp -v < $f >> mytsp.txt
	~/resources/asgn4/tsp -v < $f >> exampletsp.txt
	~/cse13s/asgn4/tsp < $f >> mytsp.txt
	~/resources/asgn4/tsp < $f >> exampletsp.txt
	~/cse13s/asgn4/tsp -u < $f >> mytsp.txt
	~/resources/asgn4/tsp -u < $f >> exampletsp.txt
	~/cse13s/asgn4/tsp -uv < $f >> mytsp.txt
	~/resources/asgn4/tsp -uv < $f >> exampletsp.txt
	echo "Finished ${f}"
done
diff mytsp.txt exampletsp.txt
(cd ~/cse13s/asgn4/&& make clean)
