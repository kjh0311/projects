package eml_parser;

import java.io.ByteArrayOutputStream;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Base64.Decoder;
import java.util.List;
import java.util.Properties;

import javax.mail.BodyPart;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.Part;
import javax.mail.Session;
import javax.mail.internet.MimeMessage;
//import com.sun.mail.util.BASE64DecoderStream;
import javax.mail.internet.MimeMultipart;


import com.sun.mail.util.BASE64DecoderStream;

public class JavaMailTester {

	public static void main(String args[]) throws Exception{
		display(new File("201701161332475930.eml"));
	}

	public static String decode(String value) throws Exception {
		byte[] decodedValue = Base64.getDecoder().decode(value);  // Basic Base64 decoding
		return new String(decodedValue, StandardCharsets.UTF_8);
	}

	public static void display(File emlFile) throws Exception{
		Properties props = System.getProperties();
		props.put("mail.host", "smtp.dummydomain.com");
		props.put("mail.transport.protocol", "smtp");

		Session mailSession = Session.getDefaultInstance(props, null);
		InputStream source = new FileInputStream(emlFile);
		MimeMessage message = new MimeMessage(mailSession, source);




		System.out.println("Subject : " + message.getSubject());
		System.out.println("From : " + message.getFrom()[0]);
		System.out.println("--------------");
		//System.out.println("Body : " +  ((MimeMultipart)message.getContent()));
		//System.out.println("Body : " +  message.getContent());
		
		
		// 분석해서 출력하도록 만듬
		parseMultipart((MimeMultipart)message.getContent());
		
	}



	//private final StringBuilder text = new StringBuilder();

	private static void parseMultipart(MimeMultipart mimeMultipart) throws MessagingException, IOException
	{
		String text = null, attachments = null;
		//List<String> attachments = new ArrayList<String>(1);
		
		
		for (int i = 0; i < mimeMultipart.getCount(); i++)
		{
			BodyPart part = mimeMultipart.getBodyPart(i);
			if (part.getContent() instanceof MimeMultipart)
			{
				parseMultipart((MimeMultipart) part.getContent());

			}
			if (part.getContentType().contains("text/plain") || part.getContentType().contains("text/html"))
			{
				//text.append(part.getContent());
				text = part.getContent() + "";
			}
			if (part.getHeader("Content-Disposition") != null)
			{
				//attachments.add(part.getHeader("Content-Disposition")[0]);
				//attachments = part.getHeader("Content-Disposition")[0];
				attachments = part.getContent() + "";
			}
			
			
			System.out.println("part#"+i);
			if (text != null) {
				System.out.println("text");
				System.out.println(text);
			} else if (attachments != null) {
				System.out.println("attachments");
				System.out.println(attachments);
			}
			
			text = null;
			attachments = null;			
		}		
	}
}
