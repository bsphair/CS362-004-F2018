
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest() {
      // You can use this function to implement your manual testing
      UrlValidator newUrl = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      System.out.println("\n----------------- TESTING VALID URL PROTOCOL ----------------");

      // Valid URL Protocol Test 1
      System.out.println("\nTEST 1: \"http://www.google.com/\"");
      try {
         if (newUrl.isValid("http://www.google.com/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Valid URL Protocol Test 2
      System.out.println("\nTEST 2: \"http://www.google.co.jp/\"");
      try {
         if (newUrl.isValid("http://www.google.co.jp/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Valid URL Protocol Test 3
      System.out.println("\nTEST 3: \"https://www.google.com/\"");
      try {
         if (newUrl.isValid("https://www.google.com/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Valid URL Protocol Test 4
      System.out.println("\nTEST 4: \"www.google.com\"");
      try {
         if (newUrl.isValid("www.google.com") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Valid URL Protocol Test 5
      System.out.println("\nTEST 5: \"ftp://speedtest.tele2.net/\"");
      try {
         if (newUrl.isValid("ftp://speedtest.tele2.net/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      System.out.println("\n\n------------ FINISHED TESTING VALID URL PROTOCOL ------------");

      System.out.println("\n\n---------------- TESTING INVALID URL PROTOCOL ---------------");

      // Invalid URL Protocol Test 1
      System.out.println("\nTEST 1: \"http://www.google.laj/\"");
      try {
         if (newUrl.isValid("http://www.google.laj/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Invalid URL Protocol Test 2
      System.out.println("\nTEST 2: \"http//www.google.com/\"");
      try {
         if (newUrl.isValid("http//www.google.com/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Invalid URL Protocol Test 3
      System.out.println("\nTEST 3: \"http:www.google.com\"");
      try {
         if (newUrl.isValid("http:www.google.com") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Invalid URL Protocol Test 4
      System.out.println("\nTEST 4: \"ftp:www.google.com\"");
      try {
         if (newUrl.isValid("ftp:www.google.com") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      // Invalid URL Protocol Test 5
      System.out.println("\nTEST 5: \"ftp:speedtest.tele2.net/\"");
      try {
         if (newUrl.isValid("ftp:speedtest.tele2.net/") == true) {
            System.out.println("PASSED: VALID URL PROTOCOL");
         } else {
            System.out.println("FAILED: INVALID URL PROTOCOL");
         }
      } catch (Error e) {
         System.out.println("FAILED: BUG FOUND");
      }

      System.out.println("\n\n----------- FINISHED TESTING INVALID URL PROTOCOL -----------");
   }

   public void testYourFirstPartition() {
      // You can use this function to implement your First Partition testing
      // URI = scheme:[//authority]path[?query][#fragment]

      // First Partition Test 1 - Valid Scheme
      System.out.println("\n\n-------------------- TESTING VALID SCHEME -------------------\n");

      String[] testValidScheme = { "http://", "ftp://", "h3t://", "" };
      UrlValidator newValidScheme = new UrlValidator(testValidScheme, 0);
      for (int i = 0; i < testValidScheme.length; i++) {
         String currentScheme = testValidScheme[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentScheme);
         try {
            boolean validScheme = newValidScheme.isValidScheme(currentScheme);

            if (validScheme == true) {
               System.out.println("PASSED: VALID SCHEME\n");
            }

            else {
               System.out.println("FAILED: INVALID SCHEME\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND");
         }

      }

      System.out.println("--------------- FINISHED TESTING VALID SCHEME ---------------");

      // First Partition Test 2 - Invalid Scheme
      System.out.println("\n\n------------------- TESTING INVALID SCHEME ------------------\n");

      String[] testInvalidScheme = { "3ht://", "http:/", "http:", "http/", "://" };
      UrlValidator newInvalidScheme = new UrlValidator(testInvalidScheme, 0);
      for (int i = 0; i < testInvalidScheme.length; i++) {
         String currentScheme = testInvalidScheme[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentScheme);
         try {
            boolean validScheme = newInvalidScheme.isValidScheme(currentScheme);

            if (validScheme == false) {
               System.out.println("PASSED: INVALID SCHEME\n");
            }

            else {
               System.out.println("FAILED: VALID SCHEME\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND");
         }

      }

      System.out.println("-------------- FINISHED TESTING INVALID SCHEME --------------");
   }

   public void testYourSecondPartition() {
      // You can use this function to implement your Second Partition testing
      // URI = scheme:[//authority]path[?query][#fragment]

      // Second Partition Test 1 - Valid Authority
      System.out.println("\n\n------------------ TESTING VALID AUTHORITY ------------------\n");

      String[] testValidAuthority = { "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255", "255.com" };
      UrlValidator newValidAuthority = new UrlValidator(testValidAuthority, 0);
      for (int i = 0; i < testValidAuthority.length; i++) {
         String currentAuthority = testValidAuthority[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentAuthority);
         try {
            boolean validAuthority = newValidAuthority.isValidAuthority(currentAuthority);

            if (validAuthority == true) {
               System.out.println("PASSED: VALID AUTHORITY\n");
            }

            else {
               System.out.println("FAILED: INVALID AUTHORITY\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("------------- FINISHED TESTING VALID AUTHORITY --------------");

      // Second Partition Test 2 - Invalid Authority
      System.out.println("\n\n----------------- TESTING INVALID AUTHORITY -----------------\n");

      String[] testInvalidAuthority = { "1.2.3.4.5", "1.2.3.4.", "1.2.3", ".1.2.3.4", "go.a", "go.a1a", "go.1aa",
              "aaa.", ".aaa", "" };
      UrlValidator newInvalidAuthority = new UrlValidator(testInvalidAuthority, 0);
      for (int i = 0; i < testInvalidAuthority.length; i++) {
         String currentAuthority = testInvalidAuthority[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentAuthority);
         try {
            boolean validAuthority = newInvalidAuthority.isValidAuthority(currentAuthority);

            if (validAuthority == false) {
               System.out.println("PASSED: INVALID AUTHORITY\n");
            }

            else {
               System.out.println("FAILED: VALID AUTHORITY\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("------------ FINISHED TESTING INVALID AUTHORITY -------------");
   }
   // You need to create more test cases for your Partitions if you need to

   public void testYourThirdPartition() {
      // You can use this function to implement your Third Partition testing
      // URI = scheme:[//authority]path[?query][#fragment]

      // Third Partition Test 1 - Valid Path
      System.out.println("\n\n--------------------- TESTING VALID PATH --------------------\n");

      String[] testValidPath = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file" };
      UrlValidator newValidPath = new UrlValidator(testValidPath, 0);
      for (int i = 0; i < testValidPath.length; i++) {
         String currentPath = testValidPath[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentPath);
         try {
            boolean validPath = newValidPath.isValidPath(currentPath);

            if (validPath == true) {
               System.out.println("PASSED: VALID PATH\n");
            }

            else {
               System.out.println("FAILED: INVALID PATH\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("---------------- FINISHED TESTING VALID PATH ----------------");

      // Third Partition Test 2 - Invalid Path
      System.out.println("\n\n-------------------- TESTING INVALID PATH -------------------\n");

      String[] testInvalidPath = { "/..", "/../", "/..//file", "/test1//file" };
      UrlValidator newInvalidPath = new UrlValidator(testInvalidPath, 0);
      for (int i = 0; i < testInvalidPath.length; i++) {
         String currentPath = testInvalidPath[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentPath);
         try {
            boolean validPath = newInvalidPath.isValidPath(currentPath);

            if (validPath == false) {
               System.out.println("PASSED: INVALID PATH\n");
            }

            else {
               System.out.println("FAILED: VALID PATH\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("--------------- FINISHED TESTING INVALID PATH ---------------");
   }

   public void testYourFourthPartition() {
      // You can use this function to implement your Fourth Partition testing
      // URI = scheme:[//authority]path[?query][#fragment]

      // Fourth Partition Test 1 - Valid Path Options
      System.out.println("\n\n----------------- TESTING VALID PATH OPTIONS ----------------\n");

      String[] testValidPath = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file", "/t123/file", "/$23/file",
              "/test1//file" };
      UrlValidator newValidPath = new UrlValidator(testValidPath, 0);
      for (int i = 0; i < testValidPath.length; i++) {
         String currentPath = testValidPath[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentPath);
         try {
            boolean validPath = newValidPath.isValidPath(currentPath);

            if (validPath == true) {
               System.out.println("PASSED: VALID PATH OPTION\n");
            }

            else {
               System.out.println("FAILED: INVALID PATH OPTION\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("------------ FINISHED TESTING VALID PATH OPTIONS ------------");

      // Fourth Partition Test 2 - Invalid Path Options
      System.out.println("\n\n---------------- TESTING INVALID PATH OPTIONS ---------------\n");

      String[] testInvalidPath = { "/..", "/../", "/#", "/../file", "/..//file", "/#/file" };
      UrlValidator newInvalidPath = new UrlValidator(testInvalidPath, 0);
      for (int i = 0; i < testInvalidPath.length; i++) {
         String currentPath = testInvalidPath[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentPath);
         try {
            boolean validPath = newInvalidPath.isValidPath(currentPath);

            if (validPath == false) {
               System.out.println("PASSED: INVALID PATH OPTION\n");
            }

            else {
               System.out.println("FAILED: VALID PATH OPTION\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("----------- FINISHED TESTING INVALID PATH OPTIONS -----------");
   }

   public void testYourFifthPartition() {
      // You can use this function to implement your Fourth Partition testing
      // URI = scheme:[//authority]path[?query][#fragment]

      // Fifth Partition Test 1 - Valid Query
      System.out.println("\n\n-------------------- TESTING VALID QUERY --------------------\n");

      String[] testValidQuery = { "?action=view", "?action=edit&mode=up", "", "search?q=%s", "?hl=en-US" };
      UrlValidator newValidQuery = new UrlValidator(testValidQuery, 0);
      for (int i = 0; i < testValidQuery.length; i++) {
         String currentQuery = testValidQuery[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentQuery);
         try {
            boolean validPath = newValidQuery.isValidQuery(currentQuery);

            if (validPath == true) {
               System.out.println("PASSED: VALID QUERY\n");
            }

            else {
               System.out.println("FAILED: INVALID QUERY\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("--------------- FINISHED TESTING VALID QUERY ----------------");

      // Fifth Partition Test 2 - Invalid Query
      System.out.println("\n\n------------------- TESTING INVALID QUERY -------------------\n");

      String[] testInvalidQuery = { "?action=", "?action=edit&mode=", "search?q=", "?hl=" };
      UrlValidator newInvalidQuery = new UrlValidator(testInvalidQuery, 0);
      for (int i = 0; i < testInvalidQuery.length; i++) {
         String currentQuery = testInvalidQuery[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentQuery);
         try {
            boolean validPath = newInvalidQuery.isValidQuery(currentQuery);

            if (validPath == false) {
               System.out.println("PASSED: INVALID QUERY\n");
            }

            else {
               System.out.println("FAILED: VALID QUERY\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("-------------- FINISHED TESTING INVALID QUERY ---------------");
   }

   public void testYourSixthPartition() {
      // You can use this function to implement your Fifth Partition testing
      // URI = scheme:[//authority]path[?query][#fragment]

      // Sizth Partition Test 1 - Valid Port
      System.out.println("\n\n--------------------- TESTING VALID PORT --------------------\n");

      String[] testValidPort = { ":80", ":65535", ":0", "" };
      UrlValidator newValidPort = new UrlValidator(testValidPort, 0);
      for (int i = 0; i < testValidPort.length; i++) {
         String currentPort = testValidPort[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentPort);
         try {
            boolean validPath = newValidPort.isValidAuthority(currentPort);

            if (validPath == true) {
               System.out.println("PASSED: VALID PORT\n");
            }

            else {
               System.out.println("FAILED: INVALID PORT\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("---------------- FINISHED TESTING VALID PORT ----------------");

      // Sizth Partition Test 2 - Invalid Port
      System.out.println("\n\n-------------------- TESTING INVALID PORT -------------------\n");

      String[] testInvalidPort = { ":-1", ":65636", ":65a" };
      UrlValidator newInvalidPort = new UrlValidator(testInvalidPort, 0);
      for (int i = 0; i < testInvalidPort.length; i++) {
         String currentPort = testInvalidPort[i];
         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentPort);
         try {
            boolean validPath = newInvalidPort.isValidAuthority(currentPort);

            if (validPath == false) {
               System.out.println("PASSED: INVALID PORT\n");
            }

            else {
               System.out.println("FAILED: VALID PORT\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("--------------- FINISHED TESTING INVALID PORT ---------------");

   }

   public void testIsValid() {
      // You can use this function for programming based testing
      System.out.println("\n\n--------------------- TESTING VALID URL ---------------------\n");

      int numTests = 10;

      for (int i = 0; i < numTests; i++) {

         String[] testValidScheme = { "http://", "ftp://", "h3t://", "" };
         int randScheme = (int) (Math.random() * 4);

         String[] testValidAuthority = { "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255",
                 "255.com" };
         int randAuthority = (int) (Math.random() * 6);

         String[] testValidPath = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file" };
         int randPath = (int) (Math.random() * 6);

         String[] testValidQuery = { "?action=view", "?action=edit&mode=up", "", "search?q=%s", "?hl=en-US" };
         int radnQuery = 2; //(int) (Math.random() * 5);

         String[] testValidPort = { ":80", ":65535", ":0", "" };
         int randPort = 3;// (int) (Math.random() * 4);

         String currentUrl = testValidScheme[randScheme] + testValidAuthority[randAuthority] + testValidPort[randPort]
                 + testValidPath[randPath] + testValidQuery[radnQuery];

         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentUrl);

         UrlValidator newValidUrl = new UrlValidator();
         try {
            boolean validUrl = newValidUrl.isValid("http://255.com/t123");

            System.out.println(validUrl);

            if (validUrl == true) {
               System.out.println("PASSED: VALID URL INPUT\n");
            }

            else {
               System.out.println("FAILED: INVALID URL INPUT\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("---------------- FINISHED TESTING VALID URL -----------------");
   }

   // TODO: CHOOSE 2 FROM THE BOTTOM AND IMPLEMENT

   // TODO: Implement Unit Test for Valid Scheme
   public void testIsValidSchemeUnitTest() {
      // Unit test for testing valid Scheme
      // You can use this function for programming based testing
      System.out.println("\n\n-------------- TESTING VALID SCHEME UNIT TEST ---------------\n");

      String[] testValidScheme = { "http://", "ftp://", "h3t://", "" };

      for (int i = 0; i < testValidScheme.length; i++) {

         String[] testValidAuthority = { "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255",
                 "255.com" };
         int randAuthority = (int) (Math.random() * 6);

         String[] testValidPath = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file" };
         int randPath = (int) (Math.random() * 6);

         String[] testValidQuery = { "?action=view", "?action=edit&mode=up", "", "search?q=%s", "?hl=en-US" };
         int radnQuery = 2; //(int) (Math.random() * 5);

         String[] testValidPort = { ":80", ":65535", ":0", "" };
         int randPort = 3;// (int) (Math.random() * 4);

         String currentUrl = testValidScheme[i] + testValidAuthority[randAuthority] + testValidPort[randPort]
                 + testValidPath[randPath] + testValidQuery[radnQuery];

         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentUrl);

         UrlValidator newValidUrl = new UrlValidator();
         try {
            boolean validUrl = newValidUrl.isValid("http://255.com/t123");

            System.out.println(validUrl);

            if (validUrl == true) {
               System.out.println("PASSED: VALID URL INPUT\n");
            }

            else {
               System.out.println("FAILED: INVALID URL INPUT\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("---------- FINISHED TESTING VALID SCHEME UNIT TEST ----------");
   }

   // TODO: Implement Unit Test for Valid Authority
   public void testIsValidAuthorityUnitTest() {
      // Unit test for testing valid Authority
      // You can use this function for programming based testing
      System.out.println("\n\n------------- TESTING VALID AUTHORITY UNIT TEST -------------\n");

      String[] testValidAuthority = { "www.google.com", "go.com", "go.au", "0.0.0.0", "255.255.255.255",
              "255.com" };

      for (int i = 0; i < testValidAuthority.length; i++) {

         String[] testValidScheme = { "http://", "ftp://", "h3t://", "" };
         int randScheme = (int) (Math.random() * 4);

         int randAuthority = (int) (Math.random() * 6);

         String[] testValidPath = { "/test1", "/t123", "/$23", "/test1/", "", "/test1/file" };
         int randPath = (int) (Math.random() * 6);

         String[] testValidQuery = { "?action=view", "?action=edit&mode=up", "", "search?q=%s", "?hl=en-US" };
         int radnQuery = 2; //(int) (Math.random() * 5);

         String[] testValidPort = { ":80", ":65535", ":0", "" };
         int randPort = 3;// (int) (Math.random() * 4);

         String currentUrl = testValidScheme[randScheme] + testValidAuthority[i] + testValidPort[randPort]
                 + testValidPath[randPath] + testValidQuery[radnQuery];

         System.out.format("TEST %d: \"%s\"\n", (i + 1), currentUrl);

         UrlValidator newValidUrl = new UrlValidator();
         try {
            boolean validUrl = newValidUrl.isValid("http://255.com/t123");

            System.out.println(validUrl);

            if (validUrl == true) {
               System.out.println("PASSED: VALID URL INPUT\n");
            }

            else {
               System.out.println("FAILED: INVALID URL INPUT\n");
            }
         } catch (Error e) {
            System.out.println("FAILED: BUG FOUND\n");
         }
      }

      System.out.println("--------- FINISHED TESTING VALID AUTHORITY UNIT TEST --------");
   }
}