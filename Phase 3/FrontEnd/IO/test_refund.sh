echo "--------------------------"
echo "Testing refund function..."
echo "--------------------------"
for i in IO/Inputs/refund/*.txt;
	do echo
	let counter++
	echo "Testing test input refund$counter...."
	echo "-----------------------------------------"
	rm daily_transaction_file.txt
	> daily_transaction_file.txt

	rm available_tickets.txt
	rm user_accounts.txt
	cp IO/available_tickets.txt available_tickets.txt
	cp IO/user_accounts.txt user_accounts.txt



	./frontend.o < IO/Inputs/refund/refund"$counter"_input.txt >> IO/Outputs/refund/actual/refund"$counter"_actout.txt

	cp daily_transaction_file.txt IO/Outputs/refund/actual/refund"$counter"_actfile_output.txt

	diff -u --ignore-all-space IO/Outputs/refund/refund"$counter"_expout.txt IO/Outputs/refund/actual/refund"$counter"_actout.txt

	diff -u --ignore-all-space IO/Outputs/refund/refund"$counter"_expfile_output.txt IO/Outputs/refund/actual/refund"$counter"_actfile_output.txt


	#Compares UAF output files
	cp user_accounts.txt IO/Outputs/files/refund/actual/refund"$counter"_actuaf.txt

	diff -u --ignore-all-space IO/Outputs/files/refund/refund"$counter"_expuaf.txt IO/Outputs/files/refund/actual/refund"$counter"_actuaf.txt
	
done
