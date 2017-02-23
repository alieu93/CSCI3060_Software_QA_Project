echo "--------------------------"
echo "Testing buy function..."
echo "--------------------------"
for i in IO/Inputs/buy/*.txt;
	do echo
	let counter++
	echo "Testing test input buy$counter...."
	echo "-----------------------------------------"
	#Resets the daily transaction file
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt

	#Sets the input file to the program itself
	./frontend.o < IO/Inputs/buy/buy"$counter"_input.txt >> IO/Outputs/buy/actual/buy"$counter"_actout.txt
	
	#copies the transaciton file from that test to a separate folder
	cp daily_transaction_file.txt IO/Outputs/buy/actual/buy"$counter"_actfile_output.txt

	#compares the console outputs
	diff -u --ignore-all-space IO/Outputs/buy/buy"$counter"_expout.txt IO/Outputs/buy/actual/buy"$counter"_actout.txt
	
	#compares the daily transaction file outputs
	diff -u --ignore-all-space IO/Outputs/buy/buy"$counter"_expfile_output.txt IO/Outputs/buy/actual/buy"$counter"_actfile_output.txt

	#Compares ATF output files
	cp available_tickets.txt IO/Outputs/files/buy/actual/buy"$counter"_actatf.txt

	diff -u --ignore-all-space IO/Outputs/files/buy/buy"$counter"_expatf.txt IO/Outputs/files/buy/actual/buy"$counter"_actatf.txt

	#Compares UAF Output files

	cp user_accounts.txt IO/Outputs/files/buy/actual/buy"$counter"_actuaf.txt
	
	diff -u --ignore-all-space IO/Outputs/files/buy/buy"$counter"_expuaf.txt IO/Outputs/files/buy/actual/buy"$counter"_actuaf.txt


	
done
