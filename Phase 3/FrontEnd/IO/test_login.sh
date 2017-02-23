echo "--------------------------"
echo "Testing login function..."
echo "--------------------------"
for i in IO/Inputs/login/*.txt;
	do echo
	let counter++
	echo "Testing test input login$counter...."
	echo "-----------------------------------------"
	#Resets the daily transaction file
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt


	#Sets the input file to the program and outputs to a text file
	./frontend.o < IO/Inputs/login/login"$counter"_input.txt >> IO/Outputs/login/actual/login"$counter"_actout.txt
	
	#Copies the transction file from that test to a separate directory
	cp daily_transaction_file.txt IO/Outputs/login/actual/login"$counter"_actfile_output.txt
	
	#compares the console outputs
	diff -u --ignore-all-space IO/Outputs/login/login"$counter"_expout.txt IO/Outputs/login/actual/login"$counter"_actout.txt
	
	#compares the daily transaction file outputs
	diff -u --ignore-all-space IO/Outputs/login/login"$counter"_expfile_output.txt IO/Outputs/login/actual/login"$counter"_actfile_output.txt
	
done
