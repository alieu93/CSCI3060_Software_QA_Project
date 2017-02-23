If using GNU GCC to compile, use -std=c++11 after g++ to compile it else there will be errors:
g++ -std=c++11 frontend.cpp

Initializing the tests for the frontend:
--------------------------------------------
Use the terminal and type the following:

chmod +x initialize.sh

Then type the following to execute the tests:

./initialize.sh

This will execute all the shell scripts for the test files, compares the executed output files to the actual output files. The text files for the actual outputs are stored in the sub-directory in the same directory as the expected file outputs under "actual".

The diff command is used to compare the actual and expected outputs, if there are no differences, then there will be no outputs from diff, therefore if all tests work out, then the only thing that will be printed are the lines indicating which test is being run. 

If there is a difference between the actual and expected outputs, then diff will output what the difference is (mainly the lines that are different in their respective text files).



These tests uses a lot of resetting for the three files, the daily transaction file is constantly resetted every transaction and the available tickets file and user accounts file are consistently replaced with a "master copy" in the IO directory. This is only used for the sake of testing.
