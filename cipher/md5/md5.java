package MD5;

import java.io.UnsupportedEncodingException;  
import java.security.MessageDigest;  
import java.security.NoSuchAlgorithmException;  

import sun.misc.BASE64Encoder;
 
public class MakeMD5 {  
  
    public String EncoderByMd5(String str) throws NoSuchAlgorithmException,  
            UnsupportedEncodingException {  
        // ȷ�����㷽��  
        MessageDigest md5 = MessageDigest.getInstance("MD5");  
        BASE64Encoder base64en = new BASE64Encoder();  
        // ���ܺ���ַ���  
        String newstr = base64en.encode(md5.digest(str.getBytes("UTF-8")));  
        return newstr;  
    }  
     
    public boolean checkpassword(String newpasswd, String oldpasswd)  
            throws NoSuchAlgorithmException, UnsupportedEncodingException {  
        if (EncoderByMd5(newpasswd).equals(oldpasswd))  
            return true;  
        else  
            return false;  
    }  
  
    public static void main(String[] args) throws Exception {  
        MakeMD5 make = new MakeMD5();  
        System.out.println(make.EncoderByMd5("000000"));  
    }  
  
}  
