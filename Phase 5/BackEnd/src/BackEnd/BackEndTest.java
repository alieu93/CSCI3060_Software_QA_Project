package BackEnd;

import static org.junit.Assert.*;

import org.junit.Test;

public class BackEndTest {

	@Test
	public void testMain() {
		//Test for Normal input
		String test[] = {""};
		BackEnd.main(test);
		
		
		//Test for a custom input where it takes arguments, only for testing
		String args[] = {"daily_transaction", "user_accounts.txt", "available_tickets.txt"};
		//testInstance = new BackEnd();
		BackEnd.main(args);
		assertTrue("readDTF statement", BackEnd.readDTF("daily_transaction"));
		//assertTrue("readUAF statement", BackEnd.readUAF("user_accounts.txt"));
		//assertTrue("readATF statement", BackEnd.readATF("available_tickets.txt"));
		BackEnd.newFiles();
		

	}
	
	@Test
	public void testMain2(){
		String test[] = {""};
		BackEnd.main(test);
		//Test for a custom input where it takes arguments, only for testing
		String args[] = {"daily_transaction", "user_accounts.txt", "available_tickets.txt"};
		BackEnd.main(args);
		assertTrue("readUAF statement", BackEnd.readUAF("user_accounts.txt"));
		BackEnd.newFiles();

	}
	
	@Test
	public void testMain3(){
		//Test for Normal input
		String test[] = {""};
		BackEnd.main(test);
		//Test for a custom input where it takes arguments, only for testing
		String args[] = {"daily_transaction", "user_accounts.txt", "available_tickets.txt"};
		//testInstance = new BackEnd();
		BackEnd.main(args);
		assertTrue("readATF statement", BackEnd.readATF("available_tickets.txt"));
		BackEnd.newFiles();
	}
	


	@Test
	public void testReadDTF() {
		//Test for failure to find DTFs
		String nonsenseDTF[] = {"dadwfewfe", "user_accounts.txt", "available_tickets.txt"};
		//BackEnd testInstance = new BackEnd();
		BackEnd.main(nonsenseDTF);
		assertFalse("readDTF statement", BackEnd.readDTF(nonsenseDTF[0]));
	}

	@Test
	public void testReadUAF() {
		//Test for failure to find UAFs
		String nonsenseUAF[] = {"daily_transaction", "wfewfewfewgw", "available_tickets.txt"};
		//BackEnd testInstance = new BackEnd();
		BackEnd.main(nonsenseUAF);
		assertFalse("readDTF statement", BackEnd.readUAF(nonsenseUAF[1]));
	}

	@Test
	public void testReadATF() {
		//Test for failure to find ATFs
		String nonsenseATF[] = {"daily_transaction", "user_accounts.txt", "aaaaaaaaaa"};
		//BackEnd testInstance = new BackEnd();
		BackEnd.main(nonsenseATF);
		assertFalse("readDTF statement", BackEnd.readATF(nonsenseATF[2]));
	}

}
