import org.junit.Test;

import static org.junit.Assert.*;

public class MakeNewFilesTest {


    @Test
    public void testApplyTransactions() throws Exception {
        System.out.println("test for all ApplyTransaction Condition Statements");
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC"};
        // testing all switch cases
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
        finalDTF[0] = "02_UUUUUUUUUUUUUUU_TT_CCCCCCCCC";
        applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
        finalDTF[0] = "03_UUUUUUUUUUUUUUU_TT_CCCCCCCCC";
        applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
        finalDTF[0] = "04_UUUUUUUUUUUUUUU_TT_CCCCCCCCC";
        applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
        finalDTF[0] = "05_UUUUUUUUUUUUUUU_TT_CCCCCCCCC";
        applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
        finalDTF[0] = "06_UUUUUUUUUUUUUUU_TT_CCCCCCCCC";
        applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
        finalDTF[0] = "00_UUUUUUUUUUUUUUU_TT_CCCCCCCCC";
        applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.applyTransactions() == true);
    }

    @Test
    public void testWriteToUAF() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"01_testUUUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.writeToUAF() == true);





    }

    @Test
    public void testWriteToATF() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.writeToATF() == true);
    }

    @Test
    public void testLogout() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"00_UUUUUUUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.logout("00_testUUUUUUUUUUU_TT_CCCCCCCCC") == true);
    }

    @Test
    public void testCreate() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"01_UUUUUUUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.create("01_newUUUUUUUUUUUU_TT_CCCCCCCCC")==true);
    }

    @Test
    public void testDelete() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"02_deleteUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.delete("02_deleteUUUUUUUUU_TT_CCCCCCCCC")==true);

    }

    @Test
    public void testAddCredit() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"06_deleteUUUUUUUUU_TT_9999CCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.addCredit("06_deleteUUUUUUUUU_TT_CCCCCCCC1")== true);

    }

    @Test
    public void testRefund() throws Exception {
       // XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"05_buyerUUUUUUUUUU_TT_CCCCCCCCC", "05_sellerUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.refund("X5_buyerUUUUUUUUUU_sellerSSSSSSSSS_50CCCCCCC")==true);

        // zero credits test
        assertTrue(applyTest.refund("X5_buyerUUUUUUUUUU_sellerSSSSSSSSS_CCCCCCCCC")==true);
    }

    @Test
    public void testSell() throws Exception {
        String[] ATF = {"EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP"};
        String[] UAF = {"UUUUUUUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {"05_buyerUUUUUUUUUU_TT_CCCCCCCCC"};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        assertTrue(applyTest.sell("XX_eveEEEEEEEEEEEEEEEE_SSSSSSSSSSSSSSS_TTT_PPPPPP")== true);
    }

    @Test
    public void testBuy() throws Exception {
        String[] ATF = {"eveEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_T30_PPPPPP"};
        String[] UAF = {"sellerUUUUUUUUU_TT_CCCCCCCCCC"};
        String[] finalDTF = {""};
        MakeNewFiles applyTest = new MakeNewFiles(finalDTF,ATF,UAF);
        // invalid tickets bought
        assertTrue(applyTest.buy("X4_eveEEEEEEEEEEEEEEEE_sellerSSSSSSSSS_TT0_PPPPPP")==true);
        // valid tickets bought
        assertTrue(applyTest.buy("X4_eveEEEEEEEEEEEEEEEE_sellerSSSSSSSSS_TT5_PPPPPP")==true);




        // EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSSSS_TTT_PPPPPP

    }
}