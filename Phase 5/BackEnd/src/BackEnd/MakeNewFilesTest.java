package BackEnd;

import static org.junit.Assert.*;

import org.junit.Test;

public class MakeNewFilesTest {
	/*String[] ATF = {"testevent___________admin___________100_000100",
			"testsellevent_______sellstduser_____080_000050",
			"testnoticksev_______sellstduser_____000_000050"};
	String[] UAF = {"admin___________AA_000010000", 
			"fullstduser_____FS_000099999",
			"buystduser______BS_000999900",
			"sellstduser_____SS_001000000",
			"user001_________FS_000000000",
			"user002_________FS_001000050"};*/
	String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC"};
	MakeNewFiles applyTest = null;

	@Test
	public void testApplyTransactions1() {
		String[] ATF = {"testevent___________admin___________100_000100",
						"testsellevent_______sellstduser_____080_000050",
						"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
						"fullstduser_____FS_000099999",
						"buystduser______BS_000999900",
						"sellstduser_____SS_001000000",
						"user001_________FS_000000000",
						"user002_________FS_001000050"};
		String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC"};
		MakeNewFiles applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		//applyTest.applyTransactions();
		assertTrue(applyTest.applyTransactions());

	}
	@Test
	public void testApplyTransactions2(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for create
		finalDTF[0] = "01_admin___________AA_000010000";
		applyTest = new MakeNewFiles(finalDTF,UAF,ATF);
		assertFalse(applyTest.applyTransactions());
	}
		
	@Test
	public void testApplyTransactions3(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Delete
		finalDTF[0] = "02_admin___________AA_000010000";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertTrue(applyTest.applyTransactions());
		
	}
	
	@Test
	public void testApplyTransactions4(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for delete
		finalDTF[0] = "02_admin123________AA_000010000";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
		
	}
	@Test
	public void testApplyTransactions5(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Sell
		finalDTF[0] = "03_test________________sellstduser_____100_000010";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertTrue(applyTest.applyTransactions());
	}
	@Test
	public void testApplyTransactions6(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for sell
		finalDTF[0] = "03_testevent___________admin___________100_000100";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
	
	@Test
	public void testApplyTransactions7(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Buy
		finalDTF[0] = "04_testsellevent_______sellstduser_____078_000050";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertTrue(applyTest.applyTransactions());
	}
	
	@Test
	public void testApplyTransactions8(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for buy (Event not existing)
		finalDTF[0] = "04_whatever____________sellstduser_____000_000000";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
	
	@Test
	public void testApplyTransactions9(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for buy (Not enough tickets)
		finalDTF[0] = "04_testnoticksev_______sellstduser_____003_000050";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
		
	@Test
	public void testApplyTransactions10(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Refund
		finalDTF[0] = "05_buystduser______sellstduser_____000000050";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertTrue(applyTest.applyTransactions());
	}
	
	@Test
	public void testApplyTransactions11(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for refund (Not enough credits)
		finalDTF[0] = "05_buystduser______sellstduser_____010000050";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
		
	@Test
	public void testApplyTransactions12(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//AddCredit
		finalDTF[0] = "06_user002_________FS_001000050";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertTrue(applyTest.applyTransactions());
	}
	
	@Test
	public void testApplyTransactions13(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for addCredit (User does not exist)
		finalDTF[0] = "06_fake002_________FS_001000050";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
		
	
	@Test
	public void testApplyTransactions14(){
		//Logout
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
						"fullstduser_____FS_000099999",
						"buystduser______BS_000999900",
						"sellstduser_____SS_001000000",
						"user001_________FS_000000000",
						"user002_________FS_001000050"};
		finalDTF[0] = "00_admin___________AA_000010000";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertTrue(applyTest.applyTransactions());
	}
		
	@Test
	public void testApplyTransactions15(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Failure for logout
		finalDTF[0] = "00_fake1___________AA_000010000";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
	
	@Test
	public void testApplyTransactions16(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Error transaction line
		finalDTF[0] = "23r3243232432";
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		assertFalse(applyTest.applyTransactions());
	}
	

	@Test
	public void testWriteToUAF1() {
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC",};
		
		
		//Test for correct UAF output
		MakeNewFiles applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		applyTest.UAFFile = "user_accounts.txt";
		assertTrue(applyTest.writeToUAF("user_accounts.txt"));
	}
	@Test
	public void testWriteToUAF2(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Test for incorrect UAF output (invalid filename)
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		applyTest.UAFFile = "";
		assertFalse(applyTest.applyTransactions());
	}

	@Test
	public void testWriteToATF1() {
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC",};
		
		
		//Test for correct UAF output
		MakeNewFiles applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		applyTest.ATFFile = "available_tickets.txt";
		assertTrue(applyTest.writeToUAF("available_tickets.txt"));
		
		
	}
	@Test
	public void testWriteToATF2(){
		String[] ATF = {"testevent___________admin___________100_000100",
				"testsellevent_______sellstduser_____080_000050",
				"testnoticksev_______sellstduser_____000_000050"};
		String[] UAF = {"admin___________AA_000010000", 
				"fullstduser_____FS_000099999",
				"buystduser______BS_000999900",
				"sellstduser_____SS_001000000",
				"user001_________FS_000000000",
				"user002_________FS_001000050"};
		//Test for incorrect UAF output (invalid filename)
		applyTest = new MakeNewFiles(finalDTF, UAF, ATF);
		applyTest.ATFFile = "";
		assertFalse(applyTest.applyTransactions());
	}


}
