

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!




public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }


   public void testManualTest()
   {

      UrlValidator newUrl = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      assertTrue(newUrl.isValid("http://www.google.com"));
//      assertFalse(newUrl.isValid("http://www.google.laj"));
      assertFalse(newUrl.isValid("http//www.google.com"));
//      assertFalse(newUrl.isValid("http:/www.google.com"));
      assertFalse(newUrl.isValid("http:www.google.com"));
      assertFalse(newUrl.isValid("ftp:www.google.com"));

   }


   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing
      UrlValidator newUrl = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

      //test if the query parameter "num" takes a variety of numbers
//      assertFalse(newUrl.isValid("https://www.google.com/search?as_oq=\"cat%20kittens\"&num=0"));
//      assertFalse(newUrl.isValid("https://www.google.com/search?as_oq=\"cat%20kittens\"&num=100"));
//      assertFalse(newUrl.isValid("https://www.google.com/search?as_oq=\"cat%20kittens\"&num=1000"));
//      assertFalse(newUrl.isValid("https://www.google.com/search?as_oq=\"cat%20kittens\"&num=-1"));
      assertFalse(newUrl.isValid("https://www.google.com/search?as_oq=\"cat%20kittens\"&num=.5"));


   }

   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing

   }
   //You need to create more test cases for your Partitions if you need to

   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }



}
