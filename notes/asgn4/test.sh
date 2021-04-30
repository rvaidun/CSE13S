rm mytsp.txt exampletsp.txt
(cd ~/cse13s/asgn4/ && make)
for f in ~/resources/asgn4/graphs/*
do
	~/cse13s/asgn4/tsp -v < $f >> mytsp.txt
	~/resources/asgn4/tsp -v < $f >> exampletsp.txt
done
diff mytsp.txt exampletsp.txt
(cd ~/cse13s/asgn4/&& make clean)
