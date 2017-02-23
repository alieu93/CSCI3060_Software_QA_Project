package BackEnd;

/**
 * ErrorLog: A class used to handle errors specified
 * in the project design document for Back End Error Logging>
 * 
 * All errors should be in the form of: ERROR: <msg>
 * 
 * Failed constraint errors: <msg> contains type, description and transaction
 * Constraint errors are only for invalid transactions
 * 
 * Fatal errors: <msg> contains type, description and file
 * Fatal errors are only for errors caused by reading the files
 * 
 * Inputs: Error type, description of error and transaction type depending if fatal or failed constraint
 * Outputs: Error messages printed to terminal depending on error 
 */

public class ErrorLog {
	static String errorType;
	//String errorType;
	static String description;
	//String description;
	static String transactionType;
	//String transactionType;
	//static String fileName;
	
	// For failed constraint errors
	public ErrorLog(String errorType, String description, String transactionType){
		this.errorType = errorType;
		this.description = description;
		this.transactionType = transactionType;
		printError(false);
	}
	
	// For fatal errors
	public ErrorLog(String errorType, String description){
		this.errorType = errorType;
		this.description = description;
		///this.fileName = fileName;
		printError(true);
		
	}
	
	// Prints the error to the terminal depending on the type
	public static void printError(boolean isFatal){
		// Checks if the error is fatal and prints a fatal error message
		if(isFatal){
			System.out.println("ERROR: " + "\n" + 
							   "type: " + errorType + "\n" +
								"description: " + description);
								//"filename: " + fileName);
			
		} else {
			// Prints a failed constraint error message
			System.out.println("ERROR: " + "\n" +
								"type: " + errorType + "\n" +
								"description: " + description + "\n" +
								"transaction: " + transactionType);
		}
	}

	

}
