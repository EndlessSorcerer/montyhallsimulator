A basic Monty Hall problem simulator which calculates the simulated probability of winning for both strategies in the general case of n doors, 1 prize and k opened doors.

To build the program: clone the repository, open the folder in cmd and run the command "g++ -std=c++11 montyhall.cpp -o montyhall.exe"

To use the program: open the folder and run the command "./montyhall.exe --num_doors 5 --num_doors_opened_by_host 2 --num_simulations 1000". You can modify the values for the simulation you want to run.